#include <AprgUniqueProblems/SpecialProblems/KnightsTour/KnightsTour.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using ChessBoardIndexes = KnightsTour::ChessBoardIndexes;
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn3By3) {
    KnightsTour knightsTour(3, 3);

    ChessBoardIndexes expectedKnightsTour{0, 5, 6, 1, 8, 3, 2, 7};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn3By3) {
    KnightsTour knightsTour(3, 3);

    ChessBoardIndexes expectedKnightsTour{0, 5, 6, 1, 8, 3, 2, 7, 0};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAClosedKnightsTour());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn4By4) {
    KnightsTour knightsTour(4, 4);

    EXPECT_TRUE(knightsTour.getAnOpenKnightsTour().empty());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn4By4) {
    KnightsTour knightsTour(4, 4);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn5By5) {
    KnightsTour knightsTour(5, 5);

    ChessBoardIndexes expectedKnightsTour{0, 7, 4,  13, 24, 17, 20, 11, 2,  5,  16, 23, 14,
                                          3, 6, 15, 22, 19, 8,  1,  10, 21, 18, 9,  12};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}

TEST(KnightsTourTest, DISABLED_GetAClosedKnightsTourWorksOn5By5) {
    KnightsTour knightsTour(5, 5);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn2By4) {
    KnightsTour knightsTour(2, 4);

    EXPECT_TRUE(knightsTour.getAnOpenKnightsTour().empty());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn2By4) {
    KnightsTour knightsTour(2, 4);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn4By5) {
    KnightsTour knightsTour(4, 5);

    ChessBoardIndexes expectedKnightsTour{0, 6, 15, 17, 8, 1, 7, 14, 16, 9, 2, 4, 13, 19, 10, 3, 5, 12, 18, 11};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}
TEST(KnightsTourTest, DISABLED_GetAClosedKnightsTourWorksOn4By5) {
    KnightsTour knightsTour(4, 5);
    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

}  // namespace alba
