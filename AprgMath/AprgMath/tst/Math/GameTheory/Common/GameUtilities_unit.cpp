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

TEST(GameUtilitiesTest, GetGameStateFromGrundyNumberWorks)
{
    EXPECT_EQ(GameState::Losing, getGameStateFromGrundyNumber(0U));
    EXPECT_EQ(GameState::Winning, getGameStateFromGrundyNumber(1U));
    EXPECT_EQ(GameState::Winning, getGameStateFromGrundyNumber(2U));
    EXPECT_EQ(GameState::Winning, getGameStateFromGrundyNumber(3U));
}

TEST(GameUtilitiesTest, GetGrundyNumberWorks)
{
    EXPECT_EQ(0U, getGrundyNumber({}));
    EXPECT_EQ(1U, getGrundyNumber({0U}));
    EXPECT_EQ(2U, getGrundyNumber({0U, 1U}));
    EXPECT_EQ(0U, getGrundyNumber({1U, 2U}));
    EXPECT_EQ(1U, getGrundyNumber({0U, 2U}));
}

TEST(GameUtilitiesTest, GetCombinedGrundyNumberWorks)
{
    EXPECT_EQ(0U, getCombinedGrundyNumber(0U, 0U));
    EXPECT_EQ(1U, getCombinedGrundyNumber(0U, 1U));
    EXPECT_EQ(2U, getCombinedGrundyNumber(0U, 2U));
    EXPECT_EQ(1U, getCombinedGrundyNumber(2U, 3U));
    EXPECT_EQ(133U, getCombinedGrundyNumber(404U, 273U));
}

TEST(GameUtilitiesTest, GetOverallGrundyNumberWorks)
{
    EXPECT_EQ(0U, getOverallGrundyNumber({0U, 0U, 0U, 0U}));
    EXPECT_EQ(4U, getOverallGrundyNumber({0U, 1U, 2U, 3U, 4U}));
    EXPECT_EQ(419U, getOverallGrundyNumber({124U, 196U, 687U, 948U}));
}

}

}
