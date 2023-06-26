#include "MisereGame.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Math/GameTheory/NimGame.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace math {

GameState MisereGame::getGameState(NimState const& nimState) {
    GameState result(GameState::Losing);
    if (getMaxHeapSize(nimState) == 1) {
        if (isEven(countNonEmptyHeaps(nimState))) {
            result = GameState::Winning;
        }
    } else {
        NimHeapSize nimSum(NimGame::getNimSum(nimState));
        if (nimSum > 0) {
            result = GameState::Winning;
        }
    }
    return result;
}

NimState MisereGame::getOptimalNextState(NimState const& inputNimState) {
    NimState result(inputNimState);
    GameState gameState(getGameState(inputNimState));
    if (GameState::Losing == gameState) {
        for (NimHeapSize& nimHeapSize : result) {
            if (nimHeapSize > 0)  // just take one to prolong the game
            {
                nimHeapSize--;
                break;
            }
        }
    } else if (GameState::Winning == gameState)  // state is only winning when size is odd (checked on getGameState)
    {
        NimHeapSize nimSum(NimGame::getNimSum(inputNimState));
        UnsignedInteger i = 0;
        for (; i < result.size(); i++) {
            NimHeapSize hammingDistanceFromNimSum = result[i] ^ nimSum;
            if (hammingDistanceFromNimSum < result[i]) {
                result[i] = hammingDistanceFromNimSum;
                break;
            }        }
        // When it result to maxHeapSize is 1 and its non empty heaps is even, try to make it odd.
        UnsignedInteger nonEmptyHeapsInResult = countNonEmptyHeaps(result);
        UnsignedInteger nonEmptyHeapsInInput = countNonEmptyHeaps(inputNimState);        if (getMaxHeapSize(result) == 1 && isEven(nonEmptyHeapsInResult) &&
            nonEmptyHeapsInResult == nonEmptyHeapsInInput) {
            result[i] = 0;
        }
    }
    return result;
}

UnsignedInteger MisereGame::countNonEmptyHeaps(NimState const& nimState) {
    return count_if(nimState.cbegin(), nimState.cend(), [](NimHeapSize const nimHeapSize) { return nimHeapSize > 0; });
}

NimHeapSize MisereGame::getMaxHeapSize(NimState const& nimState) {
    auto it = minmax_element(nimState.cbegin(), nimState.cend());
    return *(it.second);
}

}  // namespace math

}  // namespace alba
