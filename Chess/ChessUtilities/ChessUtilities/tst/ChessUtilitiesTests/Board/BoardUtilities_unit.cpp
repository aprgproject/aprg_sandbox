#include <ChessUtilities/Board/BoardUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace chess
{

TEST(BoardUtilitiesTest, IsCoordinateOnBoardWorks)
{
    Coordinate inBoardCoordinate{4, 4};
    Coordinate outBoardCoordinate{-1, 8};

    EXPECT_TRUE(isCoordinateOnBoard(inBoardCoordinate));
    EXPECT_FALSE(isCoordinateOnBoard(outBoardCoordinate));
}

TEST(BoardUtilitiesTest, ConstructFenStringWorks)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,14,13,0,0,0,
     12,10,11,0,0,11,10,12,
     1,0,1,0,1,0,1,0,
     0,1,0,1,0,1,0,1,
     9,9,0,0,9,9,0,0,
     0,0,9,9,0,0,9,9,
     4,2,3,0 ,0,3,2,4,
     0,0,0,6,5,0,0,0});

    string actualFenString(constructFenString(board, PieceColor::White, "KQkq", "e3", 0, 1));

    string expectedFenString("3kq3/rnb2bnr/P1P1P1P1/1P1P1P1P/pp2pp2/2pp2pp/RNB2BNR/3KQ3 w KQkq e3 0 1");
    EXPECT_EQ(expectedFenString, actualFenString);
}

}

}
