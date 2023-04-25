#pragma once

#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/GameTheory/Common/NimTypes.hpp>

namespace alba {

namespace math {

class MisereGame {
public:
    // In a misère game, the goal of the game is opposite, so the player who removes the last stick loses the game.
    // It turns out that the misère nim game can be optimally played almost like the standard nim game.

    // The idea is to first play the misère game like the standard nim game, but change the strategy at the end of the
    // game. The new strategy will be introduced in a situation where each heap would contain AT MOST one stick after
    // the next move.

    // In the standard nim game, we should choose a move after which there is an even number of heaps with one stick.
    // However, in the misère game, we choose a move so that there is an odd number of heaps with one stick.

    // This strategy works because a state where the strategy changes always appears in the game, and this state is a
    // winning state, because it contains exactly one heap that has more than one stick so the nim sum is not 0.

    static GameState getGameState(NimState const& nimState);
    static NimState getOptimalNextState(NimState const& nimState);

private:
    static UnsignedInteger countNonEmptyHeaps(NimState const& nimState);
    static NimHeapSize getMaxHeapSize(NimState const& nimState);
};

}  // namespace math

}  // namespace alba
