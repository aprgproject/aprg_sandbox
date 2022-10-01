#include "StickGame.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

StickGame::StickGame(
        UnsignedInteger const maxSticksToTake)
    : m_maxSticksToTake(maxSticksToTake)
{}

GameState StickGame::getGameState(
        UnsignedInteger const remainingSticks) const
{
    GameState result(GameState::Winning);
    if(isDivisible(remainingSticks, m_maxSticksToTake+1))
    {
        result = GameState::Losing;
    }
    return result;
}

UnsignedInteger StickGame::getOptimalNumberOfSticksToTake(
        UnsignedInteger const remainingSticks) const
{
    UnsignedInteger result(0);
    if(remainingSticks > 0)
    {
        UnsignedInteger remainder = remainingSticks % (m_maxSticksToTake+1);
        if(remainder == 0)
        {
            result = 1U; // Just take one to prolong the game
        }
        else
        {
            result = remainder; // force the opponent in losing state
        }
    }
    return result;
}

}

}
