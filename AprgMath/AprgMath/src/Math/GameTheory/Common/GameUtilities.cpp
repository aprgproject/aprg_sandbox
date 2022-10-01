#include "GameUtilities.hpp"

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

}

}
