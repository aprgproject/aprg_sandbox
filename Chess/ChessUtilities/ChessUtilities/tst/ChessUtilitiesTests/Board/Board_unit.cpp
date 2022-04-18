#include <ChessUtilities/Board/Board.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace chess
{

TEST(BoardTest, ConstructionWorks)
{
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Board::PieceValueMatrix expectedMatrix1(8U, 8U,
    {12,10,11,14,13,11,10,12,
     9,9,9,9,9,9,9,9,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     1,1,1,1,1,1,1,1,
     4,2,3,6,5,3,2,4});
    Board::PieceValueMatrix expectedMatrix2(8U, 8U,
    {4,2,3,6,5,3,2,4,
     1,1,1,1,1,1,1,1,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     9,9,9,9,9,9,9,9,
     12,10,11,14,13,11,10,12});
    EXPECT_EQ(expectedMatrix1, board1.getPieceValueMatrix());
    EXPECT_EQ(expectedMatrix2, board2.getPieceValueMatrix());
}

TEST(BoardTest, IsCoordinateOnBoardWorks)
{
    Board board(Board::Orientation::BlackUpWhiteDown);
    Coordinate inBoardCoordinate{4, 4};
    Coordinate outBoardCoordinate{-1, 8};

    EXPECT_TRUE(board.isCoordinateOnBoard(inBoardCoordinate));
    EXPECT_FALSE(board.isCoordinateOnBoard(outBoardCoordinate));
}

TEST(BoardTest, IsEmptyWorks)
{
    Board board(Board::Orientation::BlackUpWhiteDown);
    Coordinate emptyCoordinate{4, 4};
    Coordinate nonEmptyCoordinate{3, 6};

    EXPECT_TRUE(board.isEmpty(emptyCoordinate));
    EXPECT_FALSE(board.isEmpty(nonEmptyCoordinate));
}

TEST(BoardTest, IsMovePossibleWorks)
{
    Board board(Board::Orientation::BlackUpWhiteDown);
    Move possibleMove1{{3, 6}, {3, 5}};
    Move possibleMove2{{3, 6}, {3, 4}};
    Move notPossibleMove1{{3, 6}, {3, 3}};
    Move notPossibleMove2{{3, 6}, {3, 2}};

    EXPECT_TRUE(board.isMovePossible(possibleMove1));
    EXPECT_TRUE(board.isMovePossible(possibleMove2));
    EXPECT_FALSE(board.isMovePossible(notPossibleMove1));
    EXPECT_FALSE(board.isMovePossible(notPossibleMove2));
}

TEST(BoardTest, IsPromotionMoveWorks)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     0,1,0,0,0,0,0,0,
     0,0,1,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0});

    Move promotionMove{{1, 1}, {1, 0}};
    Move nonPromotionMove{{2, 2}, {2, 1}};

    EXPECT_TRUE(board.isPromotionMove(promotionMove));
    EXPECT_FALSE(board.isPromotionMove(nonPromotionMove));
}

TEST(BoardTest, GetPossibleMovesWorksWithPawn)
{
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Moves moves1(board1.getPossibleMoves(Coordinate(3, 6)));
    Moves moves2(board2.getPossibleMoves(Coordinate(5, 1)));

    Moves expectedMoves1{{{3, 6}, {3, 5}}, {{3, 6}, {3, 4}}};
    Moves expectedMoves2{{{5, 1}, {5, 2}}, {{5, 1}, {5, 3}}};
    EXPECT_EQ(expectedMoves1, moves1);
    EXPECT_EQ(expectedMoves2, moves2);
}

TEST(BoardTest, GetPossibleMovesWorksWithKnight)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     12,10,11,14,13,11,10,12,
     9,9,9,9,9,9,9,9,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     1,1,1,1,1,1,1,1,
     4,2,3,6,5,3,2,4,
     0,0,0,0,0,0,0,0});

    Moves moves(board.getPossibleMoves(Coordinate(1, 1)));

    Moves expectedMoves{{{1, 1}, {0, 3}}, {{1, 1}, {2, 3}}, {{1, 1}, {3, 0}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithBishop)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     12,10,11,14,13,11,10,12,
     1,1,1,1,1,1,1,1,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     9,9,9,9,9,9,9,9,
     4,2,3,6,5,3,2,4,
     0,0,0,0,0,0,0,0});

    Moves moves(board.getPossibleMoves(Coordinate(2, 1)));

    Moves expectedMoves{{{2, 1}, {1, 0}}, {{2, 1}, {1, 2}}, {{2, 1}, {3, 0}}, {{2, 1}, {3, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithRook)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     12,10,11,14,13,11,10,12,
     1,1,1,1,1,1,1,1,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     9,9,9,9,9,9,9,9,
     4,2,3,6,5,3,2,4,
     0,0,0,0,0,0,0,0});

    Moves moves(board.getPossibleMoves(Coordinate(0, 1)));

    Moves expectedMoves{{{0, 1}, {0, 0}}, {{0, 1}, {0, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithQueen)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     12,10,11,14,13,11,10,12,
     1,1,1,1,1,1,1,1,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     9,9,9,9,9,9,9,9,
     4,2,3,6,5,3,2,4,
     0,0,0,0,0,0,0,0});

    Moves moves(board.getPossibleMoves(Coordinate(4, 1)));

    Moves expectedMoves{{{4, 1}, {3, 0}}, {{4, 1}, {3, 2}}, {{4, 1}, {5, 0}}, {{4, 1}, {5, 2}}, {{4, 1}, {4, 0}}, {{4, 1}, {4, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithKing)
{
    Board board(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,0,0,0,0,0,
     12,10,11,14,13,11,10,12,
     1,1,1,1,1,1,1,1,
     0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,
     9,9,9,9,9,9,9,9,
     4,2,3,6,5,3,2,4,
     0,0,0,0,0,0,0,0});

    Moves moves(board.getPossibleMoves(Coordinate(3, 1)));

    Moves expectedMoves{{{3, 1}, {2, 0}}, {{3, 1}, {2, 2}}, {{3, 1}, {3, 0}}, {{3, 1}, {3, 2}}, {{3, 1}, {4, 0}}, {{3, 1}, {4, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetFenStringWorks)
{
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);
    Board board3(Board::Orientation::BlackUpWhiteDown,
    {0,0,0,14,13,0,0,0,
     12,10,11,0,0,11,10,12,
     1,0,1,0,1,0,1,0,
     0,1,0,1,0,1,0,1,
     9,9,0,0,9,9,0,0,
     0,0,9,9,0,0,9,9,
     4,2,3,0 ,0,3,2,4,
     0,0,0,6,5,0,0,0});


    string actualFenString1(board1.getFenString());
    string actualFenString2(board2.getFenString());
    string actualFenString3(board3.getFenString());

    string expectedFenString1("rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR");
    string expectedFenString2("RNBKQBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbkqbnr");
    string expectedFenString3("3kq3/rnb2bnr/P1P1P1P1/1P1P1P1P/pp2pp2/2pp2pp/RNB2BNR/3KQ3");
    EXPECT_EQ(expectedFenString1, actualFenString1);
    EXPECT_EQ(expectedFenString2, actualFenString2);
    EXPECT_EQ(expectedFenString3, actualFenString3);
}

}

}