#include <ChessUtilities/Board/BoardValue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

TEST(BoardValueTest, ConstructionWorks) {
    Board board(BoardOrientation::BlackUpWhiteDown);
    BoardValue boardValue(board);

    auto data(boardValue.getData());

    EXPECT_EQ(0x0000000000000000U, data.at(0));
    EXPECT_EQ(0x9999111100000000U, data.at(1));
    EXPECT_EQ(0xBDEB3563A9A91212U, data.at(2));
    EXPECT_EQ(0xC9C9141400000000U, data.at(3));
}

}  // namespace chess

}  // namespace alba
