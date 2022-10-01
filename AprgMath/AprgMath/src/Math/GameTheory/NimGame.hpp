#pragma once

#include <Math/GameTheory/GameState.hpp>
#include <Math/Types.hpp>

namespace alba
{

namespace math
{

class NimGame
{
public:
    // The nim game is a simple game that has an important role in game theory, because many other games can be played using the same strategy.
    // First, we focus on nim, and then we generalize the strategy to other games.
    // There are n heaps in nim, and each heap contains some number of sticks.
    // The players move alternately, and on each turn, the player chooses a heap that still contains sticks and removes ANY NUMBER of sticks from it.
    // The winner is the player who removes the last stick.

    using NimHeap = UnsignedInteger;
    using NimState = UnsignedIntegers;
    // The states in nim are of the form [x1, x2,..., xn], where xk denotes the number of sticks in heap k.
    // For example, [10,12,5] is a game where there are three heaps with 10, 12 and 5 sticks.
    // The state [0,0,...,0] is a losing state, because it is not possible to remove any sticks, and this is always the final state.

    GameState getGameState(NimState const& nimState) const;
    GameState getGameState(NimHeap const nimSum) const;
    NimState getOptimalNextState(NimState const& nimState) const;
private:
    NimHeap getNimSum(NimState const& nimState) const;
};

}

}
