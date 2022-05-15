#include "ChessPeek.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/User/DisplayTable.hpp>

#include <algorithm>
#include <iostream>

#define CHESS_ENGINE_PATH APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)"
#define SCREEN_SHOT_PATH APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShot.bmp)"
#define CHESS_BOARD_TOP_LEFT_CORNER 2195, 140
#define CHESS_BOARD_BOTTOM_RIGHT_CORNER 3026, 971
#define TOP_BOTTOM_INDENTION 0.05
#define LEFT_RIGHT_INDENTION 0.03
#define WHITE_COLOR_LIMIT 0.91
#define BLACK_COLOR_LIMIT 0.40

using namespace alba::AprgBitmap;
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
    , m_chessCellBitValueMatrix(8U, 8U)
    , m_chessBoard(Board::Orientation::BlackUpWhiteDown)
    , m_playerSideColor(PieceColor::White)
    , m_currentMoveOnDisplay()
    , m_isPreviousAnalysisNotSuccessful(false)
{
    initialize();
}

ChessPeek::ChessCellBitValueMatrix const& ChessPeek::getChessCellBitValueMatrix() const
{
    return m_chessCellBitValueMatrix;
}

void ChessPeek::runForever()
{
    while(true)
    {
        runOneIteration();
        Sleep(1);
    }
}

void ChessPeek::runOneIteration()
{
    Board::PieceMatrix previousPieceMatrix(m_chessBoard.getPieceMatrix());
    checkScreenAndSaveDetails();
    if(m_isPreviousAnalysisNotSuccessful || previousPieceMatrix != m_chessBoard.getPieceMatrix())
    {
        startNewAnalysisUsingEngine();
    }
}

void ChessPeek::checkScreenAndSaveDetails()
{
    m_userAutomation.saveBitmapOnScreen(SCREEN_SHOT_PATH);//
    Bitmap bitmap(SCREEN_SHOT_PATH);
    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(CHESS_BOARD_TOP_LEFT_CORNER), BitmapXY(CHESS_BOARD_BOTTOM_RIGHT_CORNER)));
    checkSnippetAndSaveDetails(snippet);
    //bitmap.setSnippetWriteToFile(snippet);//
}

void ChessPeek::startNewAnalysisUsingEngine()
{
    m_isPreviousAnalysisNotSuccessful = true;
    if(!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed())
    {
        m_chessEngineController.stop();
        if(!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed())
        {
            string fenString(constructFenString(m_chessBoard, m_playerSideColor, "KQkq", "-", 0, 1));
            m_chessEngineController.setupFenString(fenString);
            if(!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed())
            {
                m_isPreviousAnalysisNotSuccessful=false;
                m_chessEngineController.goWithPonder();
            }
        }
    }
}

void ChessPeek::checkCalculationDetails(ChessEngineControllerWithUci::CalculationDetails const& calculationDetails)
{
    string moveToDisplay(getMoveToDisplay(calculationDetails));

    printCalculationDetails(calculationDetails, moveToDisplay);
    if(moveToDisplay != m_currentMoveOnDisplay)
    {
        m_currentMoveOnDisplay = moveToDisplay;
    }
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet & snippet)
{
    double startX = snippet.getTopLeftCorner().getX();
    double startY = snippet.getTopLeftCorner().getY();
    double endX = snippet.getBottomRightCorner().getX();
    double endY = snippet.getBottomRightCorner().getY();
    double deltaX = (endX-startX)/8;
    double deltaY = (endY-startY)/8;
    unsigned int pieceCount = 0U;
    for(unsigned int j=0; j<8; j++)
    {
        for(unsigned int i=0; i<8; i++)
        {
            CoordinateSquare square{};
            square.left = round(startX + deltaX*i + deltaX*LEFT_RIGHT_INDENTION);
            square.right = round(startX + deltaX*(i+1) - deltaX*LEFT_RIGHT_INDENTION);
            square.top = round(startY + deltaY*j + deltaX*TOP_BOTTOM_INDENTION);
            square.bottom = round(startY + deltaY*(j+1) - deltaX*TOP_BOTTOM_INDENTION);

            BitSet64 whiteValue;
            BitSet64 blackValue;
            retrieveChessCellBitValueAt(whiteValue, blackValue, snippet, square);
            uint64_t chessCellBitValue;
            PieceColor pieceColor = (whiteValue.count() >= blackValue.count()) ? PieceColor::White : PieceColor::Black;
            chessCellBitValue = whiteValue.to_ullong() | blackValue.to_ullong();
            m_chessCellBitValueMatrix.setEntry(i, j, chessCellBitValue);
            Piece chessPiece;
            if(chessCellBitValue != 0U)
            {
                chessPiece = m_chessPieceConverter.convertBitValueToPiece(pieceColor, chessCellBitValue);
                pieceCount++;
            }
            m_chessBoard.setPieceAt(Coordinate(i, j), chessPiece);
        }
    }
    updatePlayerSideAndOrientation(pieceCount);
}

void ChessPeek::updatePlayerSideAndOrientation(unsigned int const pieceCount)
{
    Piece pieceAtKingWhitePosition(m_chessBoard.getPieceAt(Coordinate(4, 7)));
    Piece pieceAtKingBlackPosition(m_chessBoard.getPieceAt(Coordinate(3, 7)));
    if(pieceCount >= 24U)
    {
        PieceColor newColor(m_playerSideColor);
        if(PieceType::King == pieceAtKingWhitePosition.getType() && PieceColor::White == pieceAtKingWhitePosition.getColor())
        {
            newColor = PieceColor::White;
        }
        else if(PieceType::King == pieceAtKingBlackPosition.getType() && PieceColor::Black == pieceAtKingBlackPosition.getColor())
        {
            newColor = PieceColor::Black;
        }
        if(m_playerSideColor != newColor)
        {
            m_playerSideColor = newColor;
            if(PieceColor::White == newColor)
            {
                m_chessBoard.setOrientation(Board::Orientation::BlackUpWhiteDown);
            }
            else if(PieceColor::Black == newColor)
            {
                m_chessBoard.setOrientation(Board::Orientation::WhiteUpBlackDown);
            }
            m_chessEngineController.resetToNewGame();
        }
    }
}

void ChessPeek::printCalculationDetails(
        ChessEngineControllerWithUci::CalculationDetails const& calculationDetails,
        string const& moveToDisplay) const
{
    string firstCurrentlySearchingMove;
    if(!calculationDetails.currentlySearchingMoves.empty())
    {
        firstCurrentlySearchingMove = calculationDetails.currentlySearchingMoves.front();
    }
    cout << "Player side color: " << m_playerSideColor << endl;
    cout << "CP score: " << calculationDetails.scoreInCentipawns << " Mate: " << calculationDetails.mateInNumberOfMoves << endl;
    cout << "Best move: [" << calculationDetails.bestMove << "]" << endl;
    cout << "Currently searching move: [" << firstCurrentlySearchingMove << "]" << endl;
    cout << "PV: ";
    for(string const& moveInPv : calculationDetails.pvMovesInBestLine)
    {
        cout << moveInPv << " ";
    }
    cout << endl;
    cout << "Move to display: [" << moveToDisplay << "]" << endl;
    Move actualMove(m_chessBoard.getMoveFromTwoLetterNumberNotation(moveToDisplay));
    DisplayTable displayTable(getDisplayTable(actualMove));
    cout << "Board:" << endl;
    cout << displayTable.drawOutput();
    cout << endl;
}

string ChessPeek::getMoveToDisplay(
        ChessEngineControllerWithUci::CalculationDetails const& calculationDetails) const
{
    string moveToDisplay(m_currentMoveOnDisplay);
    if(!calculationDetails.pvMovesInBestLine.empty())
    {
        string firstMove(calculationDetails.pvMovesInBestLine.front());
        if(!firstMove.empty())
        {
            moveToDisplay = firstMove;
        }
    }
    if(!calculationDetails.currentlySearchingMoves.empty())
    {
        string firstMove(calculationDetails.currentlySearchingMoves.front());
        if(!firstMove.empty())
        {
            moveToDisplay = firstMove;
        }
    }
    if(!calculationDetails.bestMove.empty())
    {
        moveToDisplay = calculationDetails.bestMove;
    }
    return moveToDisplay;
}

DisplayTable ChessPeek::getDisplayTable(Move const& actualMove) const
{
    DisplayTable displayTable;
    for(CoordinateDataType j=0; j<8; j++)
    {
        displayTable.addRow();
        for(CoordinateDataType i=0; i<8; i++)
        {
            Coordinate coordinate(i, j);
            string cell(" ");
            cell += m_chessBoard.getPieceAt(coordinate).getCharacter();
            cell += " ";
            displayTable.getLastRow().addCell(cell);
        }
        displayTable.getLastRow().addCell("      ");
        for(CoordinateDataType i=0; i<8; i++)
        {
            Coordinate coordinate(i, j);
            string cell;
            if(actualMove.first == coordinate)
            {
                cell += "1";
                cell += m_chessBoard.getPieceAt(actualMove.first).getCharacter();
                cell += "1";
            }
            else if(actualMove.second == coordinate)
            {
                cell += "2";
                cell += m_chessBoard.getPieceAt(actualMove.first).getCharacter();
                cell += "2";
            }
            else
            {
                cell += " ";
                cell += m_chessBoard.getPieceAt(coordinate).getCharacter();
                cell += " ";
            }
            displayTable.getLastRow().addCell(cell);
        }
    }
    displayTable.setBorders("-", "|");
    return displayTable;
}

void ChessPeek::retrieveChessCellBitValueAt(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        BitmapSnippet & snippet,
        CoordinateSquare const& square) const
{
    double deltaX = static_cast<double>(square.right-square.left)/9;
    double deltaY = static_cast<double>(square.bottom-square.top)/9;
    unsigned int count(0U);
    for(unsigned int j=1; j<=8; j++)
    {
        for(unsigned int i=1; i<=8; i++)
        {
            BitmapXY bitmapCoordinate(round(square.left + deltaX*i), round(square.top + deltaY*(j)));
            setBitsBasedFromColor(whiteValue, blackValue, 63-count, snippet, bitmapCoordinate);
            //snippet.setPixelAt(bitmapCoordinate, 0xBB0000 | count << 8);//
            count++;
        }
    }
}

void ChessPeek::setBitsBasedFromColor(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        unsigned int const index,
        BitmapSnippet const& snippet,
        BitmapXY const& bitmapCoordinate) const
{
    static BitmapXYs xys
    {BitmapXY(0, -1), BitmapXY(0, 1), BitmapXY(-1, 0), BitmapXY(1, 0)};
    double currentIntensity(calculateColorIntensityDecimal(snippet.getColorAt(bitmapCoordinate)));
    double minimum(currentIntensity);
    double maximum(currentIntensity);
    for(BitmapXY const& xy : xys)
    {
        currentIntensity = calculateColorIntensityDecimal(snippet.getColorAt(bitmapCoordinate + xy));
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
    m_chessEngineController.setAdditionalStepsInCalculationMonitoring([&](ChessEngineControllerWithUci::CalculationDetails const& calculationDetails)
    {
        checkCalculationDetails(calculationDetails);
    });
}

}

}
