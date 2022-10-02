#include <Math/GameTheory/Common/GameUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(GameUtilitiesTest, ReverseGameStateWorks)
{
    EXPECT_EQ(GameState::Winning, reverseGameState(GameState::Losing));
    EXPECT_EQ(GameState::Losing, reverseGameState(GameState::Winning));
}

TEST(GameUtilitiesTest, GetGrundyNumberWorks)
{
    EXPECT_EQ(0U, getGrundyNumber({}));
    EXPECT_EQ(1U, getGrundyNumber({0U}));
    EXPECT_EQ(2U, getGrundyNumber({0U, 1U}));
    EXPECT_EQ(0U, getGrundyNumber({1U, 2U}));
    EXPECT_EQ(1U, getGrundyNumber({0U, 2U}));
}

}

}