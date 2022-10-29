#include "ChessPeek.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/User/DisplayTable.hpp>
#include <algorithm>
#include <iostream>

#define CHESS_ENGINE_PATH APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)"
//#define CHESS_ENGINE_PATH APRG_DIR R"(\Chess\ChessPeek\Files\zappa.exe)"
#define SCREEN_SHOT_PATH APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShot.bmp)"



#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

ChessPeek::ChessPeek()
    : m_configuration(ChessPeekConfigurationType::ChessDotComUserVsUser)
    , m_chessPieceConverter(m_configuration.getType())
    , m_chessEngineHandler(CHESS_ENGINE_PATH)
    , m_chessEngineController(m_chessEngineHandler)
    , m_userAutomation()
    , m_chessBoard(Board::Orientation::BlackUpWhiteDown, {})
    , m_playerColor(PieceColor::White)
    , m_playerKingCoordinate{}
    , m_opponentKingCoordinate{}
    , m_isEngineNewlyReseted(true){
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
    if(canAnalyzeBoard() && (m_isEngineNewlyReseted || didBoardChange(previousPieceMatrix)))
    {
        startEngineAnalysisOfNewPosition();
    }
}
void ChessPeek::checkScreenAndSaveDetails()
{
    m_userAutomation.saveBitmapOnScreen(SCREEN_SHOT_PATH);
    Bitmap bitmap(SCREEN_SHOT_PATH);
    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(m_configuration.getTopLeftCorner(), m_configuration.getBottomRightCorner()));
    checkSnippetAndSaveDetails(snippet);
    //bitmap.setSnippetWriteToFile(snippet);//
}

void ChessPeek::startEngineAnalysisOfNewPosition()
{
    string fenString(constructFenString(m_chessBoard, m_playerColor, m_chessBoard.getCastlingFenString(), "-", 0, 1));
    m_chessEngineController.stop();    m_chessEngineController.setupFenString(fenString);
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

void ChessPeek::calculationMonitoringCallBackForEngine(EngineCalculationDetails const& calculationDetails)
{
    saveCalculationDetails(calculationDetails);
    checkCalculationDetailsFromEngine();
}

bool ChessPeek::didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const
{
    return previousPieceMatrix != m_chessBoard.getPieceMatrix();
}

bool ChessPeek::canAnalyzeBoard() const{
    return doCorrectKingsExist() && !isOpponentKingOnCheck();
}

bool ChessPeek::doCorrectKingsExist() const
{
    return m_numberOfDetectedKings==2 && isPlayerKingAndOpponentKingValid();
}

bool ChessPeek::isPlayerKingAndOpponentKingValid() const
{
    Piece pieceAtPlayerKing(m_chessBoard.getPieceAt(m_playerKingCoordinate));
    Piece pieceAtOpponentKing(m_chessBoard.getPieceAt(m_opponentKingCoordinate));
    return PieceType::King == pieceAtPlayerKing.getType() && m_playerColor == pieceAtPlayerKing.getColor()
            && PieceType::King == pieceAtOpponentKing.getType() && getOppositeColor(m_playerColor) == pieceAtOpponentKing.getColor();
}

bool ChessPeek::isOpponentKingOnCheck() const{
    return m_chessBoard.canBeCaptured(m_opponentKingCoordinate);
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet & snippet)
{
    double startX = snippet.getTopLeftCorner().getX();    double startY = snippet.getTopLeftCorner().getY();
    double endX = snippet.getBottomRightCorner().getX();
    double endY = snippet.getBottomRightCorner().getY();
    double deltaX = (endX-startX)/8;
    double deltaY = (endY-startY)/8;
    //snippet.setPixelAt(snippet.getTopLeftCorner(), 0xA1BA00);//
    //snippet.setPixelAt(snippet.getBottomRightCorner(), 0xA1BA00);//

    m_numberOfDetectedKings = 0U;
    unsigned int pieceCount = 0U;
    for(unsigned int j=0; j<8; j++)
    {
        for(unsigned int i=0; i<8; i++)
        {
            ChessCellCoordinates chessCellCoordinates(getChessCellCoordinates(i, j, startX, startY, deltaX, deltaY));
            BitSet64 whiteValue, blackValue;
            retrieveChessCellDataBasedFromPixels(whiteValue, blackValue, snippet, chessCellCoordinates);

            Coordinate chessCoordinate(i, j);
            Piece chessPiece(getChessPieceIfPossible(blackValue, whiteValue));
            m_chessBoard.setPieceAt(chessCoordinate, chessPiece);
            if(!chessPiece.isEmpty())
            {
                setKingDetailsIfPossible(chessCoordinate, chessPiece);
                pieceCount++;
            }
        }
    }
    updatePlayerSideAndOrientation(pieceCount);
}

ChessPeek::ChessCellCoordinates ChessPeek::getChessCellCoordinates(
        unsigned int const i,
        unsigned int const j,
        double const startX,
        double const startY,
        double const deltaX,
        double const deltaY)
{
    return ChessCellCoordinates {static_cast<unsigned int>(round(startX + deltaX*i + deltaX*m_configuration.getXIndentionMultiplier())),
                static_cast<unsigned int>(round(startX + deltaX*(i+1) - deltaX*m_configuration.getXIndentionMultiplier())),
                static_cast<unsigned int>(round(startY + deltaY*j + deltaX*m_configuration.getYIndentionMultiplier())),
                static_cast<unsigned int>(round(startY + deltaY*(j+1) - deltaX*m_configuration.getYIndentionMultiplier())),
    };
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

void ChessPeek::setKingDetailsIfPossible(
        Coordinate const& chessCoordinate,
        Piece const& chessPiece)
{
    if(PieceType::King == chessPiece.getType())
    {
        m_numberOfDetectedKings++;
        if(m_playerColor == chessPiece.getColor())
        {
            m_playerKingCoordinate = chessCoordinate;
        }
        else
        {
            m_opponentKingCoordinate = chessCoordinate;
        }
    }
}

void ChessPeek::saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails)
{
    constexpr unsigned int minimumNumberOfPvMovesForUpdate = 3U;
    m_savedCalculationDetails.depth = engineCalculationDetails.depth;
    m_savedCalculationDetails.scoreInCentipawns = engineCalculationDetails.scoreInCentipawns;
    m_savedCalculationDetails.mateInNumberOfMoves = engineCalculationDetails.mateInNumberOfMoves;
    if(!engineCalculationDetails.bestMove.empty())
    {
        m_savedCalculationDetails.bestMove = engineCalculationDetails.bestMove;
    }
    if(!engineCalculationDetails.currentlySearchingMoves.empty())
    {
        m_savedCalculationDetails.currentlySearchingMoves = engineCalculationDetails.currentlySearchingMoves;
    }
    if(m_savedCalculationDetails.mateInNumberOfMoves > 0
            || engineCalculationDetails.pvMovesInBestLine.size() >= minimumNumberOfPvMovesForUpdate)
    {
        m_savedCalculationDetails.pvMovesInBestLine = engineCalculationDetails.pvMovesInBestLine;
    }
}

void ChessPeek::checkCalculationDetailsFromEngine()
{
    string bestMoveToDisplayString(getBestMoveToDisplayString());
    Moves currentMoves(getCurrentMoves(bestMoveToDisplayString));
    Moves futureMoves(getFutureMoves());

    printCalculationDetails();
    printMoveTables(currentMoves, futureMoves);
    cout<<endl;
}

Moves ChessPeek::getCurrentMoves(
        string const& bestMoveToDisplay) const
{
    constexpr unsigned int maxNumberOfCurrentMoves = 5U;
    Moves result;
    result.reserve(maxNumberOfCurrentMoves);

    strings const& searchingMovesStrings(m_savedCalculationDetails.currentlySearchingMoves);
    for(string const& searchingMoveString : searchingMovesStrings)
    {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(searchingMoveString));
        if(isValidMove(move))
        {
            result.emplace_back(move);
            if(result.size() >= maxNumberOfCurrentMoves)
            {
                break;
            }
        }
    }

    Move bestMove(m_chessBoard.getMoveFromTwoLetterNumberNotation(bestMoveToDisplay));
    if(isValidMove(bestMove) && result.empty())
    {
        result.emplace_back(bestMove);
    }

    return result;
}

Moves ChessPeek::getFutureMoves() const
{
    constexpr unsigned int maxNumberOfFuturePlayerMoves = 5U;
    Moves result;
    result.reserve(maxNumberOfFuturePlayerMoves);

    strings const& pvMovesStrings(m_savedCalculationDetails.pvMovesInBestLine);
    unsigned int maxNumberOfFutureMoves = maxNumberOfFuturePlayerMoves<=0 ? 0 : (maxNumberOfFuturePlayerMoves*2U)-1U;
    for(string const& pvMoveString : pvMovesStrings)
    {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(pvMoveString));
        if(isValidMove(move))
        {
            result.emplace_back(move);
            if(result.size() >= maxNumberOfFutureMoves)
            {
                break;
            }
        }
    }
    return result;
}

string ChessPeek::getBestMoveToDisplayString() const{
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

void ChessPeek::printCalculationDetails() const
{
    constexpr unsigned int maxNumberOfMovesToDisplay = 20U;
    cout << "Depth: " << m_savedCalculationDetails.depth
         << " Score: " << static_cast<double>(m_savedCalculationDetails.scoreInCentipawns) / 100
         << " Mate: " << m_savedCalculationDetails.mateInNumberOfMoves << endl;
    cout << "Best move: [" << m_savedCalculationDetails.bestMove << "]" << endl;

    cout << "Searching moves: ";
    ostream_iterator<string> outputIterator(cout, ", ");
    auto itStart = m_savedCalculationDetails.currentlySearchingMoves.cbegin();
    auto itEnd = min(m_savedCalculationDetails.currentlySearchingMoves.cend(), itStart+maxNumberOfMovesToDisplay);
    copy(itStart, itEnd, outputIterator);
    cout << endl;

    cout << "PV: ";
    itStart = m_savedCalculationDetails.pvMovesInBestLine.cbegin();
    itEnd = min(m_savedCalculationDetails.pvMovesInBestLine.cend(), itStart+maxNumberOfMovesToDisplay);
    copy(itStart, itEnd, outputIterator);
    cout << endl;
}

void ChessPeek::printMoveTables(Moves const& currentMoves, Moves const& futureMoves) const
{
    if(!currentMoves.empty())
    {
        putCurrentMovesTable(currentMoves);
        cout << endl;
    }
    if(!futureMoves.empty())
    {
        printFutureMovesTable(futureMoves);
        cout << endl;
    }
}

void ChessPeek::putCurrentMovesTable(
        Moves const& currentMoves) const
{
    constexpr unsigned int offsetToNextTable=9U;
    unsigned int numberOfColumns = getNumberOfColumnsOfDisplayTable(currentMoves.size());
    DisplayTable displayTable(numberOfColumns, 8U);
    displayTable.setBorders("-", "|");

    // put separators
    for(CoordinateDataType j=0; j<8; j++)
    {
        for(unsigned int separatorIndex=8; separatorIndex<numberOfColumns; separatorIndex+=offsetToNextTable)
        {
            displayTable.getCellReferenceAt(separatorIndex, j).setText("     ");
        }
    }

    // put chess board
    for(CoordinateDataType j=0; j<8; j++)
    {
        for(CoordinateDataType i=0; i<8; i++)
        {
            for(unsigned int offset=0; offset<numberOfColumns; offset+=offsetToNextTable)
            {
                Piece piece(m_chessBoard.getPieceAt(Coordinate(i, j)));
                displayTable.getCellReferenceAt(i+offset, j).setText(getChessCellForDisplay(piece, 0U));
            }
        }
    }

    // put moves
    unsigned int offset=0U;
    for(Move const& currentMove : currentMoves)
    {
        Piece piece(m_chessBoard.getPieceAt(currentMove.first));
        displayTable.getCellReferenceAt(currentMove.first.getX()+offset, currentMove.first.getY()).setText(
                    getChessCellForDisplay(piece, 1U));
        displayTable.getCellReferenceAt(currentMove.second.getX()+offset, currentMove.second.getY()).setText(
                    getChessCellForDisplay(piece, 2U));
        offset+=offsetToNextTable;
    }

    cout << displayTable.drawOutput();
}


void ChessPeek::printFutureMovesTable(
        Moves const& futureMoves) const
{
    constexpr unsigned int offsetToNextTable=9U;
    unsigned int numberOfColumns = getNumberOfColumnsOfDisplayTable((futureMoves.size()+1U)/2U);
    DisplayTable displayTable(numberOfColumns, 8U);
    displayTable.setBorders("-", "|");

    // put separators
    for(CoordinateDataType j=0; j<8; j++)
    {
        for(unsigned int separatorIndex=8; separatorIndex<numberOfColumns; separatorIndex+=offsetToNextTable)
        {
            displayTable.getCellReferenceAt(separatorIndex, j).setText("     ");
        }
    }

    // put board and moves
    unsigned int moveNumber=1U;
    unsigned int offset=0U;
    unsigned int futureMoveCount=1U;
    Board temporaryBoard(m_chessBoard);
    for(Move const& futureMove : futureMoves)
    {
        if(isOdd(futureMoveCount))
        {
            // put chess board
            for(CoordinateDataType j=0; j<8; j++)
            {
                for(CoordinateDataType i=0; i<8; i++)
                {
                    Piece piece(temporaryBoard.getPieceAt(Coordinate(i, j)));
                    displayTable.getCellReferenceAt(i+offset, j).setText(getChessCellForDisplay(piece, 0U));
                }
            }

            Piece piece(temporaryBoard.getPieceAt(futureMove.first));
            displayTable.getCellReferenceAt(futureMove.first.getX()+offset, futureMove.first.getY()).setText(
                        getChessCellForDisplay(piece, moveNumber));
            displayTable.getCellReferenceAt(futureMove.second.getX()+offset, futureMove.second.getY()).setText(
                        getChessCellForDisplay(piece, moveNumber+1));

            moveNumber++;
            offset+=offsetToNextTable;
        }
        temporaryBoard.move(futureMove);
        futureMoveCount++;
    }

    cout << displayTable.drawOutput();
}

string ChessPeek::getChessCellForDisplay(
        Piece const& piece,
        unsigned int const moveNumber) const
{
    string result(3, ' ');
    if(moveNumber != 0)
    {
        char moveNumberCharacter = '0'+ static_cast<char>(moveNumber);
        result[0]=moveNumberCharacter;
        result[2]=moveNumberCharacter;
    }
    result[1]=piece.getCharacter();
    return result;
}

unsigned int ChessPeek::getNumberOfColumnsOfDisplayTable(unsigned int const numberOfChessBoards) const
{
    return numberOfChessBoards<=0 ? 0U : numberOfChessBoards*8U + numberOfChessBoards-1;
}

void ChessPeek::retrieveChessCellDataBasedFromPixels(        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        BitmapSnippet & snippet,
        ChessCellCoordinates const& square) const
{
    double deltaX = static_cast<double>(square.right-square.left)/9;
    double deltaY = static_cast<double>(square.bottom-square.top)/9;
    unsigned int count(0U);
    for(unsigned int j=1; j<=8; j++)
    {
        for(unsigned int i=1; i<=8; i++)
        {
            BitmapXY bitmapCoordinate(round(square.left + deltaX*i), round(square.top + deltaY*(j)));
            retrieveDataBasedFromPixel(whiteValue, blackValue, 63-count, snippet, bitmapCoordinate);
            //snippet.setPixelAt(bitmapCoordinate, 0xBB0000);//
            count++;
        }
    }
}

void ChessPeek::retrieveDataBasedFromPixel(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        unsigned int const index,
        BitmapSnippet const& snippet,
        BitmapXY const& bitmapCoordinate) const
{
    static const BitmapXYs aroundOffsets{BitmapXY(0, -1), BitmapXY(0, 1), BitmapXY(-1, 0), BitmapXY(1, 0)};
    uint32_t colorAtCoordinate(snippet.getColorAt(bitmapCoordinate));
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
    whiteValue[index] = (maximum > m_configuration.getWhiteColorLimit()) ? 1 : 0;
    blackValue[index] = (minimum < m_configuration.getBlackColorLimit()) ? 1 : 0;
}

double ChessPeek::calculateColorIntensityDecimal(uint32_t const color) const{
    return (((double)extractRed(color)+extractGreen(color)+extractBlue(color))/0xFF)/3;
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
        calculationMonitoringCallBackForEngine(engineCalculationDetails);
    });
}
}

}
