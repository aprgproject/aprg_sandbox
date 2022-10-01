#pragma once

#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

namespace alba
{

namespace math
{

class StickGame
{
public:
    // We will focus on two-player games that do not contain random elements.
    // Our goal is to find a strategy that we can follow to win the game no matter what the opponent does, if such a strategy exists.

    // Let us consider a game where there is initially a heap of n sticks.
    // Players A and B move alternately, and player A begins.
    // On each move, the player has to remove 1, 2 or 3 sticks from the heap,
    // and the player who removes the last stick wins the game.

    // It turns out that we can classify all states of a game so that each state is either a winning state or a losing state.
    // In the above game, state 0 is clearly a losing state, because the player cannot  make any moves.
    // States 1, 2 and 3 are winning states, because we can remove 1, or 3 sticks and win the game.
    // State 4, in turn, is a losing state, because any move leads to a state that is a winning state for the opponent.

    // More generally, if there is a move that leads from the current state to a losing state,
    // the current state is a winning state, and otherwise the current state is a losing state.
    // Using this observation, we can classify all states of a game starting with losing states where there are no possible moves.
    // The states 0...15 of the above game can be classified as follows (W denotes a winning state and L denotes a losing state):
    // 0:L, 1:W, 2:W, 3:W, 4:L, 5:W, 6:W, 7:W, 8:L, 9:W, 10:W, 11:W, 12:L, 13:W, 14:W, 15:W, 16:L

    // It is easy to analyze this game: a state k is a losing state if k is divisible by 4, and otherwise it is a winning state.
    // An optimal way to play the game is to always choose a move after which the number of sticks in the heap is divisible by 4.
    // Finally, there are no sticks left and the opponent has lost.
    // Of course, this strategy requires that the number of sticks is not divisible by 4 when it is our move.
    // If it is, there is nothing we can do, and the opponent will win the game if they play optimally.

    StickGame(UnsignedInteger const maxSticksToTake);

    GameState getGameState(UnsignedInteger const remainingSticks) const;
    UnsignedInteger getOptimalNumberOfSticksToTake(UnsignedInteger const remainingSticks) const;
private:
    UnsignedInteger const m_maxSticksToTake;
};

}

}
