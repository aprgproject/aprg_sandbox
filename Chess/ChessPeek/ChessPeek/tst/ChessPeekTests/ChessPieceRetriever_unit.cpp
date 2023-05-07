#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPieceRetriever.hpp>
#include <ChessPeek/Utilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::chess;
using namespace std;

namespace alba {

namespace chess {

namespace {
void verifyGetChessCellPieceForBlackUpWhiteDown(ChessPieceRetriever const& retriever) {
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(0U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(1U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(2U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(3U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(4U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(5U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(6U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(7U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getChessCellPiece(0U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getChessCellPiece(7U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getChessCellPiece(1U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getChessCellPiece(6U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getChessCellPiece(2U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getChessCellPiece(5U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteQueen), retriever.getChessCellPiece(3U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKing), retriever.getChessCellPiece(4U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(0U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(1U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(2U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(3U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(4U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(5U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(6U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(7U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getChessCellPiece(0U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getChessCellPiece(7U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getChessCellPiece(1U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getChessCellPiece(6U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getChessCellPiece(2U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getChessCellPiece(5U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackQueen), retriever.getChessCellPiece(3U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKing), retriever.getChessCellPiece(4U, 0U));
}
}  // namespace

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForChessDotComVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForChessDotComPuzzle) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComPuzzle);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForLichessVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForLichessStream) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessStream);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

}  // namespace chess

}  // namespace alba
