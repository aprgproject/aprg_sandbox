#include "ChessPeek.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>

#include <algorithm>



#include <Common/Debug/AlbaDebug.hpp>

#define SCREEN_SHOT_PATH APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShotBasis.bmp)"
#define CHESS_BOARD_TOP_LEFT_CORNER 272, 140
#define CHESS_BOARD_BOTTOM_RIGHT_CORNER 1103, 971
#define WHITE_COLOR_LIMIT 0.91
#define BLACK_COLOR_LIMIT 0.40

using namespace alba::AprgBitmap;
using namespace std;

namespace alba
{

namespace chess
{

ChessPeek::ChessPeek()
    : m_chessEngineHandler(APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)")
    , m_chessEngineController(m_chessEngineHandler)
    , m_chessPieceConverter()
    , m_userAutomation()
    , m_chessCellBitValueMatrix(8U, 8U)
    , m_chessBoard(Board::Orientation::BlackUpWhiteDown)
    , m_playerSideColor(PieceColor::White)
{
    initialize();
}

ChessPeek::ChessCellBitValueMatrix const& ChessPeek::getChessCellBitValueMatrix() const
{
    return m_chessCellBitValueMatrix;
}

void ChessPeek::checkScreenAndSaveDetails()
{
    //m_userAutomation.saveBitmapOnScreen(SCREEN_SHOT_PATH);
    Bitmap bitmap(SCREEN_SHOT_PATH);
    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(CHESS_BOARD_TOP_LEFT_CORNER), BitmapXY(CHESS_BOARD_BOTTOM_RIGHT_CORNER)));
    checkSnippetAndSaveDetails(snippet);
    ALBA_PRINT1(m_chessBoard.getPieceMatrix().getString());
}

void ChessPeek::analyzeBoardUsingEngine()
{
    string fenString(constructFenString(m_chessBoard, m_playerSideColor, "-", "-", 0, 1));
    ALBA_PRINT1(fenString);
    m_chessEngineController.setupFenString(fenString);
    m_chessEngineController.goWithPonder();
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet const& snippet)
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
            square.left = round(startX + deltaX*i);
            square.right = round(startX + deltaX*(i+1));
            square.top = round(startY + deltaY*j);
            square.bottom = round(startY + deltaY*(j+1));

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
    Piece pieceAtKingPosition(m_chessBoard.getPieceAt(Coordinate(4, 7)));
    if(32U == pieceCount && PieceType::King == pieceAtKingPosition.getType())
    {
        PieceColor newColor(pieceAtKingPosition.getColor());
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
        }
    }
}

void ChessPeek::retrieveChessCellBitValueAt(
        BitSet64 & whiteValue,
        BitSet64 & blackValue,
        BitmapSnippet const& snippet,
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
    m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\Engine.log)");
}

}

}
