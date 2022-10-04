#include "GameUtilities.hpp"

#include <Common/Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace math
{

GameState reverseGameState(GameState const gameState)
{
    if(GameState::Losing == gameState)
    {
        return GameState::Winning;
    }
    else
    {
        return GameState::Losing;
    }
}

GameState getGameStateFromGrundyNumber(
        UnsignedInteger const& grundyNumber)
{
    // The Grundy number of a losing state is 0, and the Grundy number of a winning state is a positive number.

    if(grundyNumber > 0)
    {
        return GameState::Winning;
    }
    else
    {
        return GameState::Losing;
    }
}

UnsignedInteger getGrundyNumber(
        SetOfUnsignedIntegers const& nextGrundyNumbers)
{
    // Sprague–Grundy theorem
    // The Sprague–Grundy theorem generalizes the strategy used in nim to all games that fulfill the following requirements:
    // -> There are two players who move alternately.
    // -> The game consists of states, and the possible moves in a state do not depend on whose turn it is.
    // -> The game ends when a player cannot make a move.
    // -> The game surely ends sooner or later.
    // -> The players have complete information about the states and allowed moves, and there is no randomness in the game.
    // The idea is to calculate for each game state a Grundy number that corresponds o the number of sticks in a nim heap.
    // When we know the Grundy numbers of all states, we can play the game like the nim game.

    // The Grundy number of a game state is mex({g1, g2,..., gn}),
    // where g1, g2,..., gn are the Grundy numbers of the states to which we can move,
    // and the mex function gives the SMALLEST NONNEGATIVE number that is NOT in the SET.

    // The Grundy number of a state corresponds to the number of sticks in a nim heap.
    // If the Grundy number is 0, we can only move to states whose Grundy numbers are positive,
    // and if the Grundy number is x>0, we can move to states whose Grundy numbers include all numbers 0,1,...,x-1.

    UnsignedInteger result(0);
    if(!nextGrundyNumbers.empty())
    {
        UnsignedInteger possibleGrundyNumber=0;
        for(UnsignedInteger const nextGrundyNumber : nextGrundyNumbers)
        {
            if(possibleGrundyNumber != nextGrundyNumber)
            {
                break;
            }
            possibleGrundyNumber++;
        }
        result = possibleGrundyNumber;
    }
    return result;
}

}

}
