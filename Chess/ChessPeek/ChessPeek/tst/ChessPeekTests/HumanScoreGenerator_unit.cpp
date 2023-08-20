#include <ChessPeek/HumanScoreGenerator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(HumanScoreGeneratorTest, GetHumanScoreWorks) {
    Board board(BoardOrientation::BlackUpWhiteDown);
    BoardWithContext boardWithContext(PieceColor::White, board);
    HumanScoreGenerator humanScoreGenerator(boardWithContext, -127, 52);

    EXPECT_EQ(0x08FF348FFFU, humanScoreGenerator.getHumanScore({{{6, 7}, {5, 5}}, 0, 52}));
    EXPECT_EQ(0x08FF151FFFU, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 4}}, 0, 52}));
    EXPECT_EQ(0x08FF152FFFU, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 4}}, 0, 49}));
    EXPECT_EQ(0x08FF14EFFFU, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 4}}, 0, 39}));
    EXPECT_EQ(0x08FF145FFFU, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 5}}, 0, 31}));
    EXPECT_EQ(0x08FF149FFFU, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 5}}, 0, 25}));
    EXPECT_EQ(0x08FF145FFFU, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 5}}, 0, 21}));
    EXPECT_EQ(0x08FF140FFFU, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 5}}, 0, 10}));
    EXPECT_EQ(0x08FF140FFFU, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 5}}, 0, 3}));
    EXPECT_EQ(0x08FF139FFFU, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 5}}, 0, -1}));
    EXPECT_EQ(0x08FF148FFFU, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 5}}, 0, -2}));
    EXPECT_EQ(0x08FF345FFFU, humanScoreGenerator.getHumanScore({{{1, 7}, {2, 5}}, 0, -6}));
    EXPECT_EQ(0x08FF142FFFU, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 4}}, 0, -6}));
    EXPECT_EQ(0x08FF149FFFU, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 4}}, 0, -22}));
    EXPECT_EQ(0x08FF151FFFU, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 4}}, 0, -25}));
    EXPECT_EQ(0x08FF149FFFU, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 4}}, 0, -52}));
    EXPECT_EQ(0x08FF339FFFU, humanScoreGenerator.getHumanScore({{{1, 7}, {0, 5}}, 0, -52}));
    EXPECT_EQ(0x08FF148FFFU, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 5}}, 0, -57}));
    EXPECT_EQ(0x08FF340FFFU, humanScoreGenerator.getHumanScore({{{6, 7}, {7, 5}}, 0, -61}));
    EXPECT_EQ(0x08FF14EFFFU, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 4}}, 0, -127}));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
