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
        UnsignedInteger const& nextGrundyNumber)
{
    // The Grundy number of a losing state is 0, and the Grundy number of a winning state is a positive number.
    if(nextGrundyNumber > 0)
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
    // The Grundy number of a game state is mex({g1, g2,..., gn}),
    // where g1, g2,..., gn are the Grundy numbers of the states to which we can move,
    // and the mex function gives the smallest nonnegative number that is NOT in the set.

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