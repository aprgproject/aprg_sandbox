#pragma once

#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

namespace alba
{

namespace math
{

GameState reverseGameState(GameState const gameState);
GameState getGameStateFromGrundyNumber(UnsignedInteger const& grundyNumber);
UnsignedInteger getGrundyNumber(SetOfUnsignedIntegers const& nextGrundyNumbers);
UnsignedInteger getOverallGrundyNumber(UnsignedIntegers const& grundyNumbers);

}
}
