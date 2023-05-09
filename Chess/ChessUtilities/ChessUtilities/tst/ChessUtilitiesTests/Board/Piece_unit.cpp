#include <ChessUtilities/Board/Piece.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

TEST(PieceTest, ExtractColorWorks) {
    EXPECT_EQ(PieceColor::Unknown, Piece::extractColor(0U));
    EXPECT_EQ(PieceColor::White, Piece::extractColor(1U));
    EXPECT_EQ(PieceColor::Unknown, Piece::extractColor(8U));
    EXPECT_EQ(PieceColor::Black, Piece::extractColor(9U));
}
TEST(PieceTest, ExtractTypeWorks) {
    EXPECT_EQ(PieceType::Empty, Piece::extractType(0U));
    EXPECT_EQ(PieceType::Pawn, Piece::extractType(1U));    EXPECT_EQ(PieceType::Knight, Piece::extractType(2U));
    EXPECT_EQ(PieceType::Bishop, Piece::extractType(3U));
    EXPECT_EQ(PieceType::Rook, Piece::extractType(4U));
    EXPECT_EQ(PieceType::Queen, Piece::extractType(5U));
    EXPECT_EQ(PieceType::King, Piece::extractType(6U));
    EXPECT_EQ(PieceType::Empty, Piece::extractType(8U));
    EXPECT_EQ(PieceType::Pawn, Piece::extractType(9U));
    EXPECT_EQ(PieceType::Knight, Piece::extractType(10U));
    EXPECT_EQ(PieceType::Bishop, Piece::extractType(11U));
    EXPECT_EQ(PieceType::Rook, Piece::extractType(12U));
    EXPECT_EQ(PieceType::Queen, Piece::extractType(13U));
    EXPECT_EQ(PieceType::King, Piece::extractType(14U));
}

TEST(PieceTest, ExtractColorAndTypeWorks) {
    EXPECT_EQ(PieceColorAndType::Empty, Piece::extractColorAndType(0U));
    EXPECT_EQ(PieceColorAndType::WhitePawn, Piece::extractColorAndType(1U));
    EXPECT_EQ(PieceColorAndType::WhiteKnight, Piece::extractColorAndType(2U));
    EXPECT_EQ(PieceColorAndType::WhiteBishop, Piece::extractColorAndType(3U));
    EXPECT_EQ(PieceColorAndType::WhiteRook, Piece::extractColorAndType(4U));
    EXPECT_EQ(PieceColorAndType::WhiteQueen, Piece::extractColorAndType(5U));
    EXPECT_EQ(PieceColorAndType::WhiteKing, Piece::extractColorAndType(6U));
    EXPECT_EQ(PieceColorAndType::BlackPawn, Piece::extractColorAndType(9U));
    EXPECT_EQ(PieceColorAndType::BlackKnight, Piece::extractColorAndType(10U));
    EXPECT_EQ(PieceColorAndType::BlackBishop, Piece::extractColorAndType(11U));
    EXPECT_EQ(PieceColorAndType::BlackRook, Piece::extractColorAndType(12U));
    EXPECT_EQ(PieceColorAndType::BlackQueen, Piece::extractColorAndType(13U));
    EXPECT_EQ(PieceColorAndType::BlackKing, Piece::extractColorAndType(14U));
}

TEST(PieceTest, GetColorWorks) {
    Piece piece1(0U);
    Piece piece2(5U);
    Piece piece3(13U);

    EXPECT_EQ(PieceColor::Unknown, piece1.getColor());
    EXPECT_EQ(PieceColor::White, piece2.getColor());
    EXPECT_EQ(PieceColor::Black, piece3.getColor());
}

TEST(PieceTest, GetTypeWorks) {    Piece piece1(0U);
    Piece piece2(13U);

    EXPECT_EQ(PieceType::Empty, piece1.getType());    EXPECT_EQ(PieceType::Queen, piece2.getType());
}

TEST(PieceTest, GetColorAndTypeWorks) {
    Piece piece1(0U);
    Piece piece2(13U);

    EXPECT_EQ(PieceColorAndType::Empty, piece1.getColorAndType());
    EXPECT_EQ(PieceColorAndType::BlackQueen, piece2.getColorAndType());
}

}  // namespace chess

}  // namespace alba
