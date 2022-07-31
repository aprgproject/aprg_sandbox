#include <AprgUniqueProblems/KnightsTour/KnightsTour.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn3By3)
{
    KnightsTour knightsTour(3U, 3U);

    KnightsTour::ChessBoardIndexes expectedKnightsTour{0U, 5U, 6U, 1U, 8U, 3U, 2U, 7U};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn3By3)
{
    KnightsTour knightsTour(3U, 3U);

    KnightsTour::ChessBoardIndexes expectedKnightsTour{0U, 5U, 6U, 1U, 8U, 3U, 2U, 7U, 0U};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAClosedKnightsTour());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn4By4)
{
    KnightsTour knightsTour(4U, 4U);

    EXPECT_TRUE(knightsTour.getAnOpenKnightsTour().empty());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn4By4)
{
    KnightsTour knightsTour(4U, 4U);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn5By5)
{
    KnightsTour knightsTour(5U, 5U);

    KnightsTour::ChessBoardIndexes expectedKnightsTour{0U, 7U, 4U, 13U, 24U, 17U, 20U, 11U, 2U, 5U, 16U, 23U, 14U, 3U, 6U, 15U, 22U, 19U, 8U, 1U, 10U, 21U, 18U, 9U, 12U};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}

TEST(KnightsTourTest, DISABLED_GetAClosedKnightsTourWorksOn5By5)
{
    KnightsTour knightsTour(5U, 5U);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn2By4)
{
    KnightsTour knightsTour(2U, 4U);

    EXPECT_TRUE(knightsTour.getAnOpenKnightsTour().empty());
}

TEST(KnightsTourTest, GetAClosedKnightsTourWorksOn2By4)
{
    KnightsTour knightsTour(2U, 4U);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

TEST(KnightsTourTest, GetAnOpenKnightsTourWorksOn4By5)
{
    KnightsTour knightsTour(4U, 5U);

    KnightsTour::ChessBoardIndexes expectedKnightsTour{0U, 6U, 15U, 17U, 8U, 1U, 7U, 14U, 16U, 9U, 2U, 4U, 13U, 19U, 10U, 3U, 5U, 12U, 18U, 11U};
    EXPECT_EQ(expectedKnightsTour, knightsTour.getAnOpenKnightsTour());
}

TEST(KnightsTourTest, DISABLED_GetAClosedKnightsTourWorksOn4By5)
{
    KnightsTour knightsTour(4U, 5U);

    EXPECT_TRUE(knightsTour.getAClosedKnightsTour().empty());
}

}
