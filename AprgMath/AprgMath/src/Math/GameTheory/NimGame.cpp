#include "NimGame.hpp"

#include <numeric>

using namespace std;

namespace alba
{

namespace math
{

GameState NimGame::getGameState(NimState const& nimState)
{
    return getGameState(getNimSum(nimState));
}

GameState NimGame::getGameState(NimHeapSize const nimSum)
{
    // The states whose nim sum is 0 are losing states, and all other states are winning states.
    // For example, the nim sum of [10,12,5] is 10^12^5 = 3, so the state is a winning state.

    if(nimSum > 0)
    {
        return GameState::Winning;
    }
    else
    {
        return GameState::Losing;
    }
}

NimState NimGame::getOptimalNextState(NimState const& nimState)
{
    NimState result(nimState);
    NimHeapSize nimSum(getNimSum(nimState));
    GameState gameState(getGameState(nimSum));
    if(GameState::Losing == gameState)
    {
        // Losing states: The final state [0,0,...,0] is a losing state, and its nim sum is 0, as expected.
        // In other losing states, any move leads to a winning state, because when a single value xk changes,
        // the nim sum also changes, so the nim sum is different from 0 after the move.

        for(NimHeapSize & nimHeapSize : result)
        {
            if(nimHeapSize > 0) // just take one to prolong the game
            {
                nimHeapSize--;
                break;
            }
        }
    }
    else if(GameState::Winning == gameState)
    {
        // Winning states: We can move to a losing state if there is any heap k for which xk^s < xk.
        // In this case, we can remove sticks from heap k so that IT WILL CONTAIN xk^s sticks, which will lead to a losing state.
        // There is always such a heap, where xk has a one bit at the position of the leftmost one bit of s.

        for(NimHeapSize & nimHeapSize : result)
        {
            NimHeapSize hammingDistanceFromNimSum = nimHeapSize ^ nimSum;
            if(hammingDistanceFromNimSum < nimHeapSize)
            {
                nimHeapSize=hammingDistanceFromNimSum;
                break;
            }
        }
    }
    return result;
}

NimHeapSize NimGame::getNimSum(NimState const& nimState)
{
    // It turns out that we can easily classify any nim state by calculating the nim sum s = x1 ^ x2 ^ ... ^ xn, where ^ is the xor operation.

    return accumulate(
                nimState.cbegin(), nimState.cend(), 0U,
                [](NimHeapSize const nimHeapSize1, NimHeapSize const nimHeapSize2)
    {
        return nimHeapSize1 ^ nimHeapSize2;
    });
}

}

}
