#include <ChessUtilities/Board/Piece.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace chess
{

TEST(PieceTest, ExtractColorWorks)
{
    EXPECT_EQ(PieceColor::White, Piece::extractColor(0U));
    EXPECT_EQ(PieceColor::White, Piece::extractColor(1U));
    EXPECT_EQ(PieceColor::Black, Piece::extractColor(8U));
    EXPECT_EQ(PieceColor::Black, Piece::extractColor(9U));
}

TEST(PieceTest, ExtractTypeWorks)
{
    EXPECT_EQ(PieceType::Empty, Piece::extractType(0U));
    EXPECT_EQ(PieceType::Pawn, Piece::extractType(1U));
    EXPECT_EQ(PieceType::Knight, Piece::extractType(2U));
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

TEST(PieceTest, GetColorWorks)
{
    Piece piece1(0U);
    Piece piece2(13U);

    EXPECT_EQ(PieceColor::White, piece1.getColor());
    EXPECT_EQ(PieceColor::Black, piece2.getColor());
}

TEST(PieceTest, GetTypeWorks)
{
    Piece piece1(0U);
    Piece piece2(13U);

    EXPECT_EQ(PieceType::Empty, piece1.getType());
    EXPECT_EQ(PieceType::Queen, piece2.getType());
}

}

}
