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

}

}
