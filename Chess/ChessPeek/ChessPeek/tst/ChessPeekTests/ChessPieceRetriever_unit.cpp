/*#include <ChessPeek/ChessPieceRetriever.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>
using namespace alba::AprgBitmap;
using namespace std;
namespace alba {

namespace chess {

namespace {
void verifyGetChessCellPieceForBlackUpWhiteDown(
    ChessPieceRetriever const& retriever, BitmapSnippet const& inputSnippet) {
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 0U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 1U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 2U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 3U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 4U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 5U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 6U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getChessCellPiece(inputSnippet, 7U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getChessCellPiece(inputSnippet, 0U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getChessCellPiece(inputSnippet, 7U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getChessCellPiece(inputSnippet, 1U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getChessCellPiece(inputSnippet, 6U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getChessCellPiece(inputSnippet, 2U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getChessCellPiece(inputSnippet, 5U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteQueen), retriever.getChessCellPiece(inputSnippet, 3U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKing), retriever.getChessCellPiece(inputSnippet, 4U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 0U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 1U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 2U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 3U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 4U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 5U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 6U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getChessCellPiece(inputSnippet, 7U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getChessCellPiece(inputSnippet, 0U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getChessCellPiece(inputSnippet, 7U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getChessCellPiece(inputSnippet, 1U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getChessCellPiece(inputSnippet, 6U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getChessCellPiece(inputSnippet, 2U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getChessCellPiece(inputSnippet, 5U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackQueen), retriever.getChessCellPiece(inputSnippet, 3U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKing), retriever.getChessCellPiece(inputSnippet, 4U, 0U));
}
}  // namespace

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForChessDotComUserVsUser) {
    AlbaLocalPathHandler inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsUser\ChessDotComUserVsUser.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsUser);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(
        inputBitmap.getSnippetReadFromFile(configuration.getBoardTopLeft(), configuration.getBoardBottomRight()));
    ChessPieceRetriever retriever(configuration);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever, inputSnippet);}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForChessDotComUserVsComputer) {
    AlbaLocalPathHandler inputFile(        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsComputer\ChessDotComUserVsComputer.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsComputer);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(
        inputBitmap.getSnippetReadFromFile(configuration.getBoardTopLeft(), configuration.getBoardBottomRight()));
    ChessPieceRetriever retriever(configuration);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever, inputSnippet);}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForLichessVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");
    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(
        inputBitmap.getSnippetReadFromFile(configuration.getBoardTopLeft(), configuration.getBoardBottomRight()));
    ChessPieceRetriever retriever(configuration);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever, inputSnippet);}

TEST(ChessPieceRetrieverTest, GetChessCellPieceWorksForLichessVersus_CircleChoicesAreNotPawns) {
    AlbaLocalPathHandler inputFile(        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\ChoiceCirclesAreNotPawns.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(
        inputBitmap.getSnippetReadFromFile(configuration.getBoardTopLeft(), configuration.getBoardBottomRight()));
    ChessPieceRetriever retriever(configuration);

    EXPECT_EQ(Piece(PieceColorAndType::Empty), retriever.getChessCellPiece(inputSnippet, 0U, 1U));}

}  // namespace chess

}  // namespace alba
*/