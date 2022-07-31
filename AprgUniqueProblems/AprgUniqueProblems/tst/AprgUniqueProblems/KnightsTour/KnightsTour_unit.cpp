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

}
