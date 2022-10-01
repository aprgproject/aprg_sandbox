#include "NimGame.hpp"

using namespace std;

namespace alba
{

namespace math
{

GameState NimGame::getGameState(NimState const& nimState) const
{
    return getGameState(getNimSum(nimState));
}

GameState NimGame::getGameState(NimHeap const nimSum) const
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

NimGame::NimState NimGame::getOptimalNextState(NimState const& nimState) const
{
    NimState result(nimState);
    NimHeap nimSum(getNimSum(nimState));
    GameState gameState(getGameState(nimSum));
    if(GameState::Losing == gameState)
    {
        // Losing states: The final state [0,0,...,0] is a losing state, and its nim sum is 0, as expected.
        // In other losing states, any move leads to a winning state, because when a single value xk changes,
        // the nim sum also changes, so the nim sum is different from 0 after the move.

        for(NimHeap & nimHeap : result)
        {
            if(nimHeap > 0) // just take one to prolong the game
            {
                nimHeap--;
                break;
            }
        }
    }
    else if(GameState::Winning == gameState)
    {
        // Winning states: We can move to a losing state if there is any heap k for which xk^s < xk.
        // In this case, we can remove sticks from heap k so that IT WILL CONTAIN xk^s sticks, which will lead to a losing state.
        // There is always such a heap, where xk has a one bit at the position of the leftmost one bit of s.

        for(NimHeap & nimHeap : result)
        {
            NimHeap hammingDistanceFromNimSum = nimHeap ^ nimSum;
            if(hammingDistanceFromNimSum < nimHeap)
            {
                nimHeap=hammingDistanceFromNimSum;
                break;
            }
        }
    }
    return result;
}

NimGame::NimHeap NimGame::getNimSum(NimState const& nimState) const
{
    // It turns out that we can easily classify any nim state by calculating the nim sum s Æ x1 ^ x2 ^ ... ^ xn, where ^ is the xor operation.

    return accumulate(
                nimState.cbegin(), nimState.cend(), 0U,
                [](NimHeap const nimHeap1, NimHeap const nimHeap2)
    {
        return nimHeap1 ^ nimHeap2;
    });
}

}

}
