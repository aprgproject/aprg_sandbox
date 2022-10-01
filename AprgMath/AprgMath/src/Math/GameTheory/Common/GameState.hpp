#pragma once

namespace alba
{

namespace math
{

// A losing state is a state where the player will lose the game if the opponent plays optimally.
// A winning state is a state where the player will win the game if they play optimally.

enum class GameState
{
    Losing,
    Winning
};

}

}
