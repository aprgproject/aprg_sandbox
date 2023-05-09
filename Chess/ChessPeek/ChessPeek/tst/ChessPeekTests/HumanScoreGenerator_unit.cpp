#include <ChessPeek/HumanScoreGenerator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(HumanScoreGeneratorTest, GetHumanScoreWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    BoardWithContext boardWithContext(PieceColor::White, board);
    HumanScoreGenerator humanScoreGenerator(boardWithContext, 52, -127);

    EXPECT_EQ(0x08054893, humanScoreGenerator.getHumanScore({{{6, 7}, {5, 5}}, 52, 0}));
    EXPECT_EQ(0x08055192, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 4}}, 52, 0}));
    EXPECT_EQ(0x08055292, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 4}}, 49, 0}));
    EXPECT_EQ(0x08054E92, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 4}}, 39, 0}));
    EXPECT_EQ(0x08054582, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 5}}, 31, 0}));
    EXPECT_EQ(0x08054982, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 5}}, 25, 0}));
    EXPECT_EQ(0x08054582, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 5}}, 21, 0}));
    EXPECT_EQ(0x08054082, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 5}}, 10, 0}));
    EXPECT_EQ(0x08054082, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 5}}, 3, 0}));
    EXPECT_EQ(0x08053982, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 5}}, -1, 0}));
    EXPECT_EQ(0x08054882, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 5}}, -2, 0}));
    EXPECT_EQ(0x08054593, humanScoreGenerator.getHumanScore({{{1, 7}, {2, 5}}, -6, 0}));
    EXPECT_EQ(0x08054292, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 4}}, -6, 0}));
    EXPECT_EQ(0x08054992, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 4}}, -22, 0}));
    EXPECT_EQ(0x08055192, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 4}}, -25, 0}));
    EXPECT_EQ(0x08014992, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 4}}, -52, 0}));
    EXPECT_EQ(0x08013993, humanScoreGenerator.getHumanScore({{{1, 7}, {0, 5}}, -52, 0}));
    EXPECT_EQ(0x08014882, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 5}}, -57, 0}));
    EXPECT_EQ(0x08014093, humanScoreGenerator.getHumanScore({{{6, 7}, {7, 5}}, -61, 0}));
    EXPECT_EQ(0x08014E92, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 4}}, -127, 0}));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
