#include "ChessPeek.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/User/DisplayTable.hpp>

#include <algorithm>
#include <iostream>

#define CHESS_ENGINE_PATH APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)"
//#define CHESS_ENGINE_PATH APRG_DIR R"(\Chess\ChessPeek\Files\zappa.exe)"
#define SCREEN_SHOT_PATH APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShot.bmp)"

// Chess.com - user vs user
#define CHESS_BOARD_TOP_LEFT_CORNER 2200, 151
#define CHESS_BOARD_BOTTOM_RIGHT_CORNER 3023, 974
#define TOP_BOTTOM_INDENTION 0.05
#define LEFT_RIGHT_INDENTION 0.03
#define WHITE_COLOR_LIMIT 0.91
#define BLACK_COLOR_LIMIT 0.40

// Chess.com - user vs computer
//#define CHESS_BOARD_TOP_LEFT_CORNER 2207, 151
//#define CHESS_BOARD_BOTTOM_RIGHT_CORNER 3014, 958
//#define TOP_BOTTOM_INDENTION 0.05
//#define LEFT_RIGHT_INDENTION 0.03
//#define WHITE_COLOR_LIMIT 0.91
//#define BLACK_COLOR_LIMIT 0.40


using namespace alba::AprgBitmap;
using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

ChessPeek::ChessPeek()
    : m_chessEngineHandler(CHESS_ENGINE_PATH)
    , m_chessEngineController(m_chessEngineHandler)
    , m_chessPieceConverter()
    , m_userAutomation()
    , m_chessBoard(Board::Orientation::BlackUpWhiteDown)
    , m_playerColor(PieceColor::White)
    , m_isEngineNewlyReseted(true)
{
    initialize();
}

void ChessPeek::runForever()
{
    while(true)
    {
        runOneIteration();
        //Sleep(1);
        //break; //
    }
}

void ChessPeek::runOneIteration()
{
    Board::PieceMatrix previousPieceMatrix(m_chessBoard.getPieceMatrix());
    checkScreenAndSaveDetails();
    if(m_isEngineNewlyReseted || previousPieceMatrix != m_chessBoard.getPieceMatrix())
    {
        startAnalysisUsingEngine();
    }
}

void ChessPeek::checkScreenAndSaveDetails()
{
    m_userAutomation.saveBitmapOnScreen(SCREEN_SHOT_PATH);
    Bitmap bitmap(SCREEN_SHOT_PATH);
    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(CHESS_BOARD_TOP_LEFT_CORNER), BitmapXY(CHESS_BOARD_BOTTOM_RIGHT_CORNER)));
    checkSnippetAndSaveDetails(snippet);
    //bitmap.setSnippetWriteToFile(snippet);//
}

void ChessPeek::startAnalysisUsingEngine()
{
    string fenString(constructFenString(m_chessBoard, m_playerColor, m_chessBoard.getCastlingFenString(), "-", 0, 1));
    m_chessEngineController.stop();
    m_chessEngineController.setupFenString(fenString);
    if(!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed()) // reset was not performed
    {
        m_chessEngineController.goWithPonder();
        m_isEngineNewlyReseted=false;
    }
    else
    {
        m_isEngineNewlyReseted=true;
    }
}

void ChessPeek::calculationMonitoringCallBack(EngineCalculationDetails const& calculationDetails)
{
    saveCalculationDetails(calculationDetails);
    checkCalculationDetails();
}

void ChessPeek::saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails)
{
    if(!engineCalculationDetails.bestMove.empty())
    {
        m_savedCalculationDetails.bestMove = engineCalculationDetails.bestMove;
    }
    m_savedCalculationDetails.scoreInCentipawns = engineCalculationDetails.scoreInCentipawns;
    m_savedCalculationDetails.mateInNumberOfMoves = engineCalculationDetails.mateInNumberOfMoves;
    if(!engineCalculationDetails.currentlySearchingMoves.empty())
    {
        m_savedCalculationDetails.currentlySearchingMoves = engineCalculationDetails.currentlySearchingMoves;
    }
    if(!engineCalculationDetails.pvMovesInBestLine.empty())
    {
        m_savedCalculationDetails.pvMovesInBestLine = engineCalculationDetails.pvMovesInBestLine;
    }
}

void ChessPeek::checkCalculationDetails()
{
    string bestMoveToDisplayString(getBestMoveToDisplayString());
    strings currentMoves(getCurrentMoves(bestMoveToDisplayString));
    strings futureMoves(getFutureMoves());

    printCalculationDetails();
    printCurrentMovesIfNeeded(currentMoves);
    printFutureMovesIfNeeded(futureMoves);
    cout<<endl;
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet & snippet)
{
    double startX = snippet.getTopLeftCorner().getX();
    double startY = snippet.getTopLeftCorner().getY();
    double endX = snippet.getBottomRightCorner().getX();
    double endY = snippet.getBottomRightCorner().getY();
    double deltaX = (endX-startX)/8;
    double deltaY = (endY-startY)/8;
    //snippet.setPixelAt(snippet.getTopLeftCorner(), 0xA1BA00);//
    //snippet.setPixelAt(snippet.getBottomRightCorner(), 0xA1BA00);//

    DataForYellow dataForYellow{};
    unsigned int pieceCount = 0U;
    for(unsigned int j=0; j<8; j++)
    {
        for(unsigned int i=0; i<8; i++)
        {
            ChessCellCoordinates chessCellCoordinates(getChessCellCoordinates(i, j, startX, startY, deltaX, deltaY));
            BitSet64 whiteValue, blackValue;
            double averageYellowValue;
            retrieveChessCellDataBasedFromPixels(whiteValue, blackValue, averageYellowValue, snippet, chessCellCoordinates);

            Coordinate chessCoordinate(i, j);
            Piece chessPiece(getChessPieceIfPossible(blackValue, whiteValue));
            if(!chessPiece.isEmpty())
            {
                m_chessBoard.setPieceAt(chessCoordinate, chessPiece);
                pieceCount++;
            }
            updateDataForYellow(dataForYellow, averageYellowValue, chessCoordinate);
        }
    }
    updatePlayerSideAndOrientation(pieceCount);
    updateLastMoveColor(dataForYellow);
}

ChessPeek::ChessCellCoordinates ChessPeek::getChessCellCoordinates(
        unsigned int const i,
        unsigned int const j,
        double const startX,
        double const startY,
        double const deltaX,
        double const deltaY)
{
    return ChessCellCoordinates {static_cast<unsigned int>(round(startX + deltaX*i + deltaX*LEFT_RIGHT_INDENTION)),
                static_cast<unsigned int>(round(startX + deltaX*(i+1) - deltaX*LEFT_RIGHT_INDENTION)),
                static_cast<unsigned int>(round(startY + deltaY*j + deltaX*TOP_BOTTOM_INDENTION)),
                static_cast<unsigned int>(round(startY + deltaY*(j+1) - deltaX*TOP_BOTTOM_INDENTION)),
    };
}

void ChessPeek::updateDataForYellow(
        DataForYellow & dataForYellow,
        double const averageYellowValue,
        Coordinate const& chessCoordinate)
{
    if(dataForYellow.secondHighestYellow < averageYellowValue)
    {
        dataForYellow.secondHighestYellow = averageYellowValue;
        dataForYellow.coordinateSecond = chessCoordinate;
        if(dataForYellow.highestYellow < dataForYellow.secondHighestYellow)
        {
            std::swap(dataForYellow.highestYellow, dataForYellow.secondHighestYellow);
            std::swap(dataForYellow.coordinateFirst, dataForYellow.coordinateSecond);
        }
    }
}

Piece ChessPeek::getChessPieceIfPossible(BitSet64 const& blackValue, BitSet64 const& whiteValue)
{
    Piece chessPiece;
    uint64_t chessCellBitValue;
    PieceColor pieceColor = (whiteValue.count() >= blackValue.count()) ? PieceColor::White : PieceColor::Black;
    chessCellBitValue = whiteValue.to_ullong() | blackValue.to_ullong();
    if(chessCellBitValue != 0U)
    {
        chessPiece = m_chessPieceConverter.convertBitValueToPiece(pieceColor, chessCellBitValue);
    }
    return chessPiece;
}

void ChessPeek::updateLastMoveColor(DataForYellow const& dataForYellow)
{
    Piece piece1(m_chessBoard.getPieceAt(dataForYellow.coordinateFirst));
    if(!piece1.isEmpty())
    {
        m_lastMoveColor = piece1.getColor();
    }
    else
    {
        Piece piece2(m_chessBoard.getPieceAt(dataForYellow.coordinateSecond));
        if(!piece2.isEmpty())
        {
            m_lastMoveColor = piece2.getColor();
        }
    }
}

void ChessPeek::updatePlayerSideAndOrientation(unsigned int const pieceCount)
{
    Piece pieceAtKingWhitePosition(m_chessBoard.getPieceAt(Coordinate(4, 7)));
    Piece pieceAtKingBlackPosition(m_chessBoard.getPieceAt(Coordinate(3, 7)));
    if(pieceCount >= 24U)
    {
        PieceColor newPlayerColor(m_playerColor);
        if(PieceType::King == pieceAtKingWhitePosition.getType() && PieceColor::White == pieceAtKingWhitePosition.getColor())
        {
            newPlayerColor = PieceColor::White;
        }
        else if(PieceType::King == pieceAtKingBlackPosition.getType() && PieceColor::Black == pieceAtKingBlackPosition.getColor())
        {
            newPlayerColor = PieceColor::Black;
        }
        if(m_playerColor != newPlayerColor)
        {
            m_playerColor = newPlayerColor;
            setOrientationDependingOnPlayerColor(newPlayerColor);
            m_chessEngineController.resetToNewGame();
            m_isEngineNewlyReseted=true;
        }
    }
}

void ChessPeek::setOrientationDependingOnPlayerColor(PieceColor const newColor)
{
    if(PieceColor::White == newColor)
    {
        m_chessBoard.setOrientation(Board::Orientation::BlackUpWhiteDown);
    }
    else if(PieceColor::Black == newColor)
    {
        m_chessBoard.setOrientation(Board::Orientation::WhiteUpBlackDown);
    }
}

void ChessPeek::printCalculationDetails() const
{
    cout << "Last move color: " << m_lastMoveColor << endl;
    cout << "Score: " << static_cast<double>(m_savedCalculationDetails.scoreInCentipawns) / 100
         << " Mate: " << m_savedCalculationDetails.mateInNumberOfMoves << endl;
    cout << "Best move: [" << m_savedCalculationDetails.bestMove << "]" << endl;
    cout << "Searching moves: ";
    for(string const& searchingMoves : m_savedCalculationDetails.currentlySearchingMoves)
    {
        cout << searchingMoves << " ";
    }
    cout << "PV: ";
    for(string const& moveInPv : m_savedCalculationDetails.pvMovesInBestLine)
    {
        cout << moveInPv << " ";
    }
    cout << endl;
}

void ChessPeek::printCurrentMovesIfNeeded(strings const& currentMoves) const
{
    if(!currentMoves.empty())
    {
        DisplayTable displayTable(getDisplayTableForCurrentMoves(currentMoves));
        cout << displayTable.drawOutput();
    }
}

void ChessPeek::printFutureMovesIfNeeded(strings const& futureMoves) const
{
    if(!futureMoves.empty())
    {
        DisplayTable displayTable(getDisplayTableForFutureMoves(futureMoves));
        cout << displayTable.drawOutput();
    }
}

string ChessPeek::getBestMoveToDisplayString() const
{
    if(!m_savedCalculationDetails.bestMove.empty())
    {
        return m_savedCalculationDetails.bestMove;
    }
    if(!m_savedCalculationDetails.currentlySearchingMoves.empty())
    {
        string firstMove(m_savedCalculationDetails.currentlySearchingMoves.front());
        if(!firstMove.empty())
        {
            return firstMove;
        }
    }
    if(!m_savedCalculationDetails.pvMovesInBestLine.empty())
    {
        string firstMove(m_savedCalculationDetails.pvMovesInBestLine.front());
        if(!firstMove.empty())
        {
            return firstMove;
        }
    }
    return string();
}

strings ChessPeek::getCurrentMoves(
        string const& bestMoveToDisplay) const
{
    constexpr unsigned int numberOfOtherMoves = 4U;
    strings result;
    result.reserve(numberOfOtherMoves+1U);
    result.emplace_back(bestMoveToDisplay);
    strings const& searchingMoves(m_savedCalculationDetails.currentlySearchingMoves);
    for(unsigned int i=1; i<=numberOfOtherMoves && i<searchingMoves.size(); i++)
    {
        result.emplace_back(searchingMoves.at(i));
    }
    result.erase(std::remove_if(result.begin(), result.end(), [](string const& move) // remove empty moves
    {return move.empty(); }), result.end());
    return result;
}

strings ChessPeek::getFutureMoves() const
{
    constexpr unsigned int numberOfFutureMoves = 4U;
    strings result;
    result.reserve(numberOfFutureMoves);
    strings const& pvMoves(m_savedCalculationDetails.pvMovesInBestLine);
    for(unsigned int i=0; result.size()<=numberOfFutureMoves && i<pvMoves.size(); i+=2)
    {
        // plus two because only players moves are displayed (dont care about opponent move)
        result.emplace_back(pvMoves.at(i));
    }
    result.erase(std::remove_if(result.begin(), result.end(), [](string const& move) // remove empty moves
    {return move.empty();}), result.end());
    return result;
}

DisplayTable ChessPeek::getDisplayTableForCurrentMoves(strings const& currentMoves) const
{
    DisplayTable displayTable;
    Moves moves;
    for(string const& distinctMove : currentMoves)
    {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(distinctMove));
        moves.emplace_back(move);
    }
    for(CoordinateDataType j=0; j<8; j++)
    {
        displayTable.addRow();
        bool isFirst(true);
        for(Move const& move : moves)
        {
            addCellForSpaceIfNotFirst(isFirst, displayTable);
            for(CoordinateDataType i=0; i<8; i++)
            {
                displayTable.getLastRow().addCell(
                            getCellInDisplayTable(m_chessBoard, Coordinate(i, j), move, 1U));
            }
        }
    }
    displayTable.setBorders("-", "|");
    return displayTable;
}

DisplayTable ChessPeek::getDisplayTableForFutureMoves(strings const& futureMoves) const
{
    DisplayTable displayTable;
    std::vector<std::pair<Board, Move>> boardAndMovePairs;
    Board currentBoard(m_chessBoard);
    for(string const& continuousMove : futureMoves)
    {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(continuousMove));
        boardAndMovePairs.emplace_back(currentBoard, move);
        currentBoard.move(move);
    }
    for(CoordinateDataType j=0; j<8; j++)
    {
        displayTable.addRow();
        bool isFirst(true);
        unsigned int moveNumberStart=1U;
        for(auto const& boardAndMovePair : boardAndMovePairs)
        {
            addCellForSpaceIfNotFirst(isFirst, displayTable);
            for(CoordinateDataType i=0; i<8; i++)
            {
                displayTable.getLastRow().addCell(
                            getCellInDisplayTable(boardAndMovePair.first, Coordinate(i, j), boardAndMovePair.second, moveNumberStart));
            }
            moveNumberStart+=2; // only players moves are displayed (dont care about opponent move)
        }
    }
    displayTable.setBorders("-", "|");
    return displayTable;
}

void ChessPeek::addCellForSpaceIfNotFirst(bool & isFirst, DisplayTable & displayTable) const
{
    if(isFirst)
    {
        isFirst=false;
    }
    else
    {
        displayTable.getLastRow().addCell("     ");
    }
}

string ChessPeek::getCellInDisplayTable(
        Board const& chessBoard,
        Coordinate const& coordinate,
        Move const& moveToDisplay,
        unsigned int const moveNumberStart) const
{
    string result(3, ' ');
    if(moveToDisplay.first == coordinate)
    {
        char moveNumber = '0'+ static_cast<char>(moveNumberStart);
        result[0]=moveNumber;
        result[1]=chessBoard.getPieceAt(moveToDisplay.first).getCharacter();
        result[2]=moveNumber;
    }
    else if(moveToDisplay.second == coordinate)
    {
        char moveNumber = '0'+ static_cast<char>(moveNumberStart) + 1;
        result[0]=moveNumber;
        result[1]=chessBoard.getPieceAt(moveToDisplay.first).getCharacter();
        result[2]=moveNumber;
    }
    else
    {
        result[1]=chessBoard.getPieceAt(coordinate).getCharacter();
    }
    return string(result);
}

void ChessPeek::retrieveChessCellDataBasedFromPixels(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        double & averageYellowValue,
        BitmapSnippet & snippet,
        ChessCellCoordinates const& square) const
{
    double deltaX = static_cast<double>(square.right-square.left)/9;
    double deltaY = static_cast<double>(square.bottom-square.top)/9;
    averageYellowValue = 0;
    unsigned int count(0U);
    for(unsigned int j=1; j<=8; j++)
    {
        for(unsigned int i=1; i<=8; i++)
        {
            BitmapXY bitmapCoordinate(round(square.left + deltaX*i), round(square.top + deltaY*(j)));
            retrieveDataBasedFromPixel(whiteValue, blackValue, averageYellowValue, 63-count, snippet, bitmapCoordinate);
            //snippet.setPixelAt(bitmapCoordinate, 0xBB0000);//
            count++;
        }
    }
    averageYellowValue /= 64;
}

void ChessPeek::retrieveDataBasedFromPixel(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        double & yellowValue,
        unsigned int const index,
        BitmapSnippet const& snippet,
        BitmapXY const& bitmapCoordinate) const
{
    static const BitmapXYs aroundOffsets{BitmapXY(0, -1), BitmapXY(0, 1), BitmapXY(-1, 0), BitmapXY(1, 0)};
    uint32_t colorAtCoordinate(snippet.getColorAt(bitmapCoordinate));
    yellowValue += getYellowValue(colorAtCoordinate);
    double currentIntensity(calculateColorIntensityDecimal(colorAtCoordinate));
    double minimum(currentIntensity);
    double maximum(currentIntensity);
    for(BitmapXY const& aroundOffset : aroundOffsets)
    {
        currentIntensity = calculateColorIntensityDecimal(snippet.getColorAt(bitmapCoordinate + aroundOffset));
        if(minimum > currentIntensity)
        {
            minimum = currentIntensity;
        }
        if(maximum < currentIntensity)
        {
            maximum = currentIntensity;
        }
    }
    whiteValue[index] = (maximum > WHITE_COLOR_LIMIT) ? 1 : 0;
    blackValue[index] = (minimum < BLACK_COLOR_LIMIT) ? 1 : 0;
}

double ChessPeek::calculateColorIntensityDecimal(uint32_t const color) const
{
    return (((double)extractRed(color)+extractGreen(color)+extractBlue(color))/0xFF)/3;
}

double ChessPeek::getYellowValue(uint32_t const color) const
{
    uint32_t redAndGreen = min(extractRed(color), extractGreen(color));
    uint32_t blue = extractBlue(color);
    return redAndGreen>blue ? redAndGreen-blue : 0U;
}

uint8_t ChessPeek::extractRed(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color));
}

uint8_t ChessPeek::extractGreen(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color));
}

uint8_t ChessPeek::extractBlue(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color));
}

void ChessPeek::initialize()
{
    m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");
    m_chessEngineController.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineController.log)");
    m_chessEngineController.setAdditionalStepsInCalculationMonitoring([&](EngineCalculationDetails const& engineCalculationDetails)
    {
        calculationMonitoringCallBack(engineCalculationDetails);
    });
}

}

}
