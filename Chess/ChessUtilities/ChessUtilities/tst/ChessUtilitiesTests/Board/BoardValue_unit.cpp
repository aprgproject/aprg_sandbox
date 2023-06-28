#include <ChessUtilities/Board/BoardValue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

TEST(BoardValueTest, ConstructionWorks) {
    Board board(BoardOrientation::BlackUpWhiteDown);
    BoardValue boardValue(board);

    auto data(boardValue.getData());

    EXPECT_EQ(0x0000000000000000U, data[0]);
    EXPECT_EQ(0x9999111100000000U, data[1]);
    EXPECT_EQ(0xBDEB3563A9A91212U, data[2]);
    EXPECT_EQ(0xC9C9141400000000U, data[3]);
}

TEST(BoardValueTest, DifferentOrientationsHasSameValueWorks) {
    Board board1(BoardOrientation::BlackUpWhiteDown);
    Board board2(BoardOrientation::WhiteUpBlackDown);
    BoardValue boardValue1(board1);
    BoardValue boardValue2(board2);

    EXPECT_EQ(boardValue1, boardValue2);
}

TEST(BoardValueTest, DifferentOrientationsHasSameValueWorksEvenAfterMove) {
    Board board1(BoardOrientation::BlackUpWhiteDown);
    Board board2(BoardOrientation::WhiteUpBlackDown);
    BoardValue boardValue1(board1);
    BoardValue boardValue2(board2);

    board1.move(board1.getMoveUsingAlgebraicNotation("d4", PieceColor::White));
    board2.move(board2.getMoveUsingAlgebraicNotation("d4", PieceColor::White));

    EXPECT_EQ(boardValue1, boardValue2);
}

}  // namespace chess

}  // namespace alba
