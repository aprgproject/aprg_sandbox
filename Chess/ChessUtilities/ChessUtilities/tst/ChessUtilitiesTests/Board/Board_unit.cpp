#include <ChessUtilities/Board/Board.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

TEST(BoardTest, ConstructionWorks) {
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Board::PieceMatrix expectedMatrix1(
        8U, 8U,
        {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4});
    Board::PieceMatrix expectedMatrix2(8U, 8U, {4, 2, 3, 6, 5, 3, 2, 4, 1, 1, 1, 1, 1,  1,  1,  1,  0,  0,  0,  0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0,
                                                0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 10, 11, 14, 13, 11, 10, 12});
    EXPECT_EQ(expectedMatrix1, board1.getPieceMatrix());
    EXPECT_EQ(expectedMatrix2, board2.getPieceMatrix());
}

TEST(BoardTest, IsEmptyWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    Coordinate emptyCoordinate{4, 4};
    Coordinate nonEmptyCoordinate{3, 6};

    EXPECT_TRUE(board.isEmptyAt(emptyCoordinate));
    EXPECT_FALSE(board.isEmptyAt(nonEmptyCoordinate));
}

TEST(BoardTest, CanBeCapturedWorksOnExample1) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0,
         0,  0,  0,  0,  1,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4});

    EXPECT_TRUE(board.canBeCaptured(Coordinate{3, 3}));
    EXPECT_FALSE(board.canBeCaptured(Coordinate{3, 4}));
    EXPECT_FALSE(board.canBeCaptured(Coordinate{4, 3}));
    EXPECT_TRUE(board.canBeCaptured(Coordinate{4, 4}));
}

TEST(BoardTest, CanBeCapturedWorksOnExample2) {
    Board board(
        Board::Orientation::WhiteUpBlackDown,
        {6, 0, 4, 0, 4, 0, 0, 0, 11, 1, 1, 0,  0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  13, 0, 0, 0,
         0, 9, 0, 0, 0, 0, 0, 0, 0,  0, 0, 11, 0, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 12, 0, 0, 14, 13, 0, 0, 12});

    EXPECT_FALSE(board.canBeCaptured(Coordinate{0, 0}));
}

TEST(BoardTest, IsAPossibleMoveWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    Move possibleMove1{{3, 6}, {3, 5}};
    Move possibleMove2{{3, 6}, {3, 4}};
    Move notPossibleMove1{{3, 6}, {3, 3}};
    Move notPossibleMove2{{3, 6}, {3, 2}};

    EXPECT_TRUE(board.isAPossibleMove(possibleMove1));
    EXPECT_TRUE(board.isAPossibleMove(possibleMove2));
    EXPECT_FALSE(board.isAPossibleMove(notPossibleMove1));
    EXPECT_FALSE(board.isAPossibleMove(notPossibleMove2));
}

TEST(BoardTest, IsAPromotionMoveWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    Move promotionMove{{1, 1}, {1, 0}};
    Move nonPromotionMove{{2, 2}, {2, 1}};

    EXPECT_TRUE(board.isAPromotionMove(promotionMove));
    EXPECT_FALSE(board.isAPromotionMove(nonPromotionMove));
}

TEST(BoardTest, GetPossibleMovesWorksWithPawn) {    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Moves moves1(board1.getPossibleMoves(Coordinate(3, 6)));    Moves moves2(board2.getPossibleMoves(Coordinate(5, 1)));

    Moves expectedMoves1{{{3, 6}, {3, 5}}, {{3, 6}, {3, 4}}};
    Moves expectedMoves2{{{5, 1}, {5, 2}}, {{5, 1}, {5, 3}}};
    EXPECT_EQ(expectedMoves1, moves1);
    EXPECT_EQ(expectedMoves2, moves2);
}

TEST(BoardTest, GetPossibleMovesWorksWithKnight) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 1,  1,  1,  1,  1,  1,  1,  1,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Moves moves(board.getPossibleMoves(Coordinate(1, 1)));

    Moves expectedMoves{{{1, 1}, {0, 3}}, {{1, 1}, {2, 3}}, {{1, 1}, {3, 0}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithBishop) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Moves moves(board.getPossibleMoves(Coordinate(2, 1)));

    Moves expectedMoves{{{2, 1}, {1, 0}}, {{2, 1}, {1, 2}}, {{2, 1}, {3, 0}}, {{2, 1}, {3, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithRook) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Moves moves(board.getPossibleMoves(Coordinate(0, 1)));

    Moves expectedMoves{{{0, 1}, {0, 0}}, {{0, 1}, {0, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithQueen) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Moves moves(board.getPossibleMoves(Coordinate(4, 1)));

    Moves expectedMoves{{{4, 1}, {3, 0}}, {{4, 1}, {3, 2}}, {{4, 1}, {5, 0}},
                        {{4, 1}, {5, 2}}, {{4, 1}, {4, 0}}, {{4, 1}, {4, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetPossibleMovesWorksWithKing) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Moves moves(board.getPossibleMoves(Coordinate(3, 1)));

    Moves expectedMoves{{{3, 1}, {2, 0}}, {{3, 1}, {2, 2}}, {{3, 1}, {3, 0}},
                        {{3, 1}, {3, 2}}, {{3, 1}, {4, 0}}, {{3, 1}, {4, 2}}};
    EXPECT_EQ(expectedMoves, moves);
}

TEST(BoardTest, GetMoveFromTwoLetterNumberNotationWorks) {
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Move move1(board1.getMoveFromTwoLetterNumberNotation("c2c4"));
    Move move2(board2.getMoveFromTwoLetterNumberNotation("c2c4"));

    EXPECT_EQ(Move({2, 6}, {2, 4}), move1);
    EXPECT_EQ(Move({5, 1}, {5, 3}), move2);
}

TEST(BoardTest, GetCoordinateFromLetterNumberNotationWorks) {
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    Coordinate coordinate1(board1.getCoordinateFromLetterNumberNotation("c2"));
    Coordinate coordinate2(board2.getCoordinateFromLetterNumberNotation("c2"));

    EXPECT_EQ((Coordinate{2, 6}), coordinate1);
    EXPECT_EQ((Coordinate{5, 1}), coordinate2);
}

TEST(BoardTest, GetLetterNumberNotationStringFromCoordinateWorks) {
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);

    string letterNumber1(board1.getLetterNumberNotationStringFromCoordinate({4, 4}));
    string letterNumber2(board2.getLetterNumberNotationStringFromCoordinate({4, 4}));

    EXPECT_EQ("e4", letterNumber1);
    EXPECT_EQ("d5", letterNumber2);
}

TEST(BoardTest, GetReadableStringForMoveWorks) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 10, 11, 14, 13, 11, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  4, 2, 3, 6, 5, 3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0});

    Move move{{3, 1}, {2, 0}};
    string readableMoveString(board.getReadableStringForMove(move));

    EXPECT_EQ("King d7->c8", readableMoveString);
}

TEST(BoardTest, GetFenStringWorks) {
    Board board1(Board::Orientation::BlackUpWhiteDown);
    Board board2(Board::Orientation::WhiteUpBlackDown);
    Board board3(
        Board::Orientation::BlackUpWhiteDown,
        {0, 0, 0, 14, 13, 0, 0, 0, 12, 10, 11, 0, 0, 11, 10, 12, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1,
         9, 9, 0, 0,  9,  9, 0, 0, 0,  0,  9,  9, 0, 0,  9,  9,  4, 2, 3, 0, 0, 3, 2, 4, 0, 0, 0, 6, 5, 0, 0, 0});
    Board board4(
        Board::Orientation::WhiteUpBlackDown,
        {4, 0, 3, 6,  5, 3, 0, 4, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 2, 0, 0, 2, 0, 0, 0,  0,  0,  1,  0,  0,  0, 0,
         0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 12, 10, 11, 14, 13, 11, 0, 12});

    string actualFenString1(board1.getFenString());
    string actualFenString2(board2.getFenString());
    string actualFenString3(board3.getFenString());
    string actualFenString4(board4.getFenString());

    string expectedFenString1("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    string expectedFenString2("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    string expectedFenString3("3kq3/rnb2bnr/P1P1P1P1/1P1P1P1P/pp2pp2/2pp2pp/RNB2BNR/3KQ3");
    string expectedFenString4("r1bqkbnr/ppp1pppp/3p4/4n3/4P3/2N2N2/PPPP1PPP/R1BQKB1R");
    EXPECT_EQ(expectedFenString1, actualFenString1);
    EXPECT_EQ(expectedFenString2, actualFenString2);
    EXPECT_EQ(expectedFenString3, actualFenString3);
    EXPECT_EQ(expectedFenString4, actualFenString4);
}

TEST(BoardTest, MoveWorksForWhitePawnMovingTwoSpaces) {
    Board board(Board::Orientation::BlackUpWhiteDown);

    board.move(Move{{2, 6}, {2, 4}});

    Board::PieceMatrix expectedMatrix(8U, 8U, {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  1,  1,  0,  1,  1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4});
    EXPECT_EQ(expectedMatrix, board.getPieceMatrix());
}

TEST(BoardTest, MoveWorksForWhiteRookCapturingABlackPawn) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {12, 10, 0, 0, 0, 0, 0, 0, 9, 11, 0, 0,  0, 9, 9, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 3, 0, 0, 0,
         0,  0,  1, 0, 0, 0, 0, 0, 0, 0,  1, 12, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 4, 0, 0, 0, 0, 4, 6, 0});

    board.move(Move{{5, 7}, {5, 1}});

    Board::PieceMatrix expectedMatrix(
        8U, 8U, {12, 10, 0, 0, 0, 0, 0, 0, 9, 11, 0, 0,  0, 4, 9, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 3, 0, 0, 0,
                 0,  0,  1, 0, 0, 0, 0, 0, 0, 0,  1, 12, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 4, 0, 0, 0, 0, 0, 6, 0});
    EXPECT_EQ(expectedMatrix, board.getPieceMatrix());
}

TEST(BoardTest, MoveWorksForWhitePawnCapturingABlackBishop) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {12, 0, 0,  0, 0, 0, 14, 0, 9, 9, 0, 11, 0,  9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 1, 0, 0, 0, 5,
         0,  0, 13, 0, 0, 0, 0,  0, 0, 0, 1, 0,  11, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 4, 0, 0, 0, 2, 0, 6, 0});

    board.move(Move{{5, 6}, {4, 5}});

    Board::PieceMatrix expectedMatrix(
        8U, 8U, {12, 0, 0,  0, 0, 0, 14, 0, 9, 9, 0, 11, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 1, 0, 0, 0, 5,
                 0,  0, 13, 0, 0, 0, 0,  0, 0, 0, 1, 0,  1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 2, 0, 6, 0});
    EXPECT_EQ(expectedMatrix, board.getPieceMatrix());
}

TEST(BoardTest, MoveWorksWithCastling) {
    Board board(
        Board::Orientation::BlackUpWhiteDown,
        {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 6, 3, 2, 4});

    board.move(Move{{4, 7}, {2, 7}});

    Board::PieceMatrix expectedMatrix(8U, 8U, {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  1,  1,  1,  1,  1, 1, 1, 1, 0, 0, 6, 4, 0, 3, 2, 4});
    EXPECT_EQ(expectedMatrix, board.getPieceMatrix());
}

}  // namespace chess

}  // namespace alba
