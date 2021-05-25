#include <Cube36.hpp>
#include <gtest/gtest.h>

#include <PathHandlers/AlbaWindowsPathHandler.hpp>

#include <iostream>
#include <string>

using namespace alba;
using namespace std;

TEST(BoardTest, GetHeightAtIndex)
{
    Board board(6,6);
    EXPECT_EQ(5, board.getHeightAt(5,5));
    EXPECT_EQ(5, board.getHeightAt(0,1));
    EXPECT_EQ(2, board.getHeightAt(1,0));
}

TEST(AvailablePiecesTest, GetNextColorWithHeightWithAllPiecesAvailable)
{
    Pieces pieces(6,6);
    EXPECT_EQ(1, pieces.getNextColorWithHeight(1,1));
    EXPECT_EQ(2, pieces.getNextColorWithHeight(2,2));
    EXPECT_EQ(3, pieces.getNextColorWithHeight(3,3));
    EXPECT_EQ(4, pieces.getNextColorWithHeight(4,4));
    EXPECT_EQ(5, pieces.getNextColorWithHeight(5,5));
    EXPECT_EQ(6, pieces.getNextColorWithHeight(6,6));
}

TEST(AvailablePiecesTest, GetNextColorWithHeightWithSomePiecesAlreadyUsed)
{
    Pieces pieces(6,6);
    pieces.setPieceAsUnavailable(1,1);
    pieces.setPieceAsUnavailable(1,2);
    pieces.setPieceAsUnavailable(1,3);
    pieces.setPieceAsUnavailable(1,4);
    pieces.setPieceAsUnavailable(1,5);
    pieces.setPieceAsUnavailable(1,6);
    pieces.setPieceAsUnavailable(2,1);
    pieces.setPieceAsUnavailable(2,2);
    pieces.setPieceAsUnavailable(2,3);
    pieces.setPieceAsUnavailable(2,4);
    pieces.setPieceAsUnavailable(2,5);
    pieces.setPieceAsUnavailable(3,1);
    pieces.setPieceAsUnavailable(3,2);
    pieces.setPieceAsUnavailable(3,3);
    pieces.setPieceAsUnavailable(3,4);
    pieces.setPieceAsUnavailable(4,1);
    pieces.setPieceAsUnavailable(4,2);
    pieces.setPieceAsUnavailable(4,3);
    pieces.setPieceAsUnavailable(5,1);
    pieces.setPieceAsUnavailable(5,2);
    pieces.setPieceAsUnavailable(6,1);
    EXPECT_EQ(0, pieces.getNextColorWithHeight(1,1));
    EXPECT_EQ(6, pieces.getNextColorWithHeight(2,1));
    EXPECT_EQ(5, pieces.getNextColorWithHeight(3,1));
    EXPECT_EQ(4, pieces.getNextColorWithHeight(4,1));
    EXPECT_EQ(5, pieces.getNextColorWithHeight(5,5));
    EXPECT_EQ(6, pieces.getNextColorWithHeight(6,6));
}

TEST(BoardTest, IsColorUniqueAtRow)
{
    Board board(6,6);
    board.setColorAt(1, 0, 0);
    board.setColorAt(2, 0, 1);
    board.setColorAt(3, 0, 2);
    board.setColorAt(4, 0, 3);
    board.setColorAt(5, 0, 4);
    board.setColorAt(6, 0, 5);
    board.setColorAt(1, 1, 0);
    board.setColorAt(2, 1, 1);
    board.setColorAt(3, 1, 2);
    board.setColorAt(3, 1, 3);
    board.setColorAt(3, 1, 4);
    board.setColorAt(3, 1, 5);
    EXPECT_TRUE(board.isColorUniqueAtRow(0));
    EXPECT_FALSE(board.isColorUniqueAtRow(1));
}

TEST(BoardTest, IsColorUniqueAtColumn)
{
    Board board(6,6);
    board.setColorAt(1, 0, 0);
    board.setColorAt(2, 1, 0);
    board.setColorAt(3, 2, 0);
    board.setColorAt(4, 3, 0);
    board.setColorAt(5, 4, 0);
    board.setColorAt(6, 5, 0);
    board.setColorAt(1, 0, 1);
    board.setColorAt(2, 1, 1);
    board.setColorAt(3, 2, 1);
    board.setColorAt(4, 3, 1);
    board.setColorAt(4, 4, 1);
    board.setColorAt(4, 5, 1);
    EXPECT_TRUE(board.isColorUniqueAtColumn(0));
    EXPECT_FALSE(board.isColorUniqueAtColumn(1));
}

TEST(BoardTest, Solve)
{
    Board board(6,6);
    board.solve(0,0);
}