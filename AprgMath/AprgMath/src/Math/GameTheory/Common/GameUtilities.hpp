#pragma once

#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

namespace alba {

namespace math {

GameState reverseGameState(GameState const gameState);
GameState getGameStateFromGrundyNumber(UnsignedInteger const grundyNumber);
UnsignedInteger getGrundyNumber(SetOfUnsignedIntegers const& nextGrundyNumbers);
UnsignedInteger getCombinedGrundyNumber(UnsignedInteger const grundyNumber1, UnsignedInteger const grundyNumber2);
UnsignedInteger getOverallGrundyNumber(UnsignedIntegers const& grundyNumbers);

}  // namespace math

}  // namespace alba
