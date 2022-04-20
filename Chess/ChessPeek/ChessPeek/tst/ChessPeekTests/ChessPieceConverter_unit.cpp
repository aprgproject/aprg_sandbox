#include <ChessPeek/ChessPieceConverter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace chess
{

TEST(ChessPieceConverterTest, ConvertBitValueToPieceWorks)
{
    ChessPieceConverter chessPeek;

    Piece actualPiece1(chessPeek.convertBitValueToPiece(PieceColor::Black, 0B0000000000000000000110000001100000011000000110000011110000111100));
    Piece actualPiece2(chessPeek.convertBitValueToPiece(PieceColor::Black, 0B0000000000010000000110000001100000111000000110000011110001111100));
    Piece actualPiece3(chessPeek.convertBitValueToPiece(PieceColor::White, 0B0000000000000000000110000001000000111000000100000011110001111100));
    Piece actualPiece4(chessPeek.convertBitValueToPiece(PieceColor::White, 0B0000000000111100001111000011010000111000001110000011111001111110));

    Piece expectedPiece1(PieceColor::Black, PieceType::Pawn);
    Piece expectedPiece2(PieceColor::Black, PieceType::Pawn);
    Piece expectedPiece3(PieceColor::White, PieceType::Pawn);
    Piece expectedPiece4(PieceColor::White, PieceType::Rook);
    EXPECT_EQ(expectedPiece1, actualPiece1);
    EXPECT_EQ(expectedPiece2, actualPiece2);
    EXPECT_EQ(expectedPiece3, actualPiece3);
    EXPECT_EQ(expectedPiece4, actualPiece4);
}
}

}
