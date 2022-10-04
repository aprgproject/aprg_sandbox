#include <Math/GameTheory/SpecificGames/GameWithMaze.hpp>

#include <gtest/gtest.h>



#include <Common/Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace math
{

TEST(GameWithMazeTest, Example1Works)
{
    GameWithMaze::BooleanMatrix isBlockedMatrix(5U, 5U,
    {false, false, true, false, false,
     true, false, false, false, true,
     false, false, true, false, false,
     true, false, false, false, false,
     false, false, false, false, false});
    GameWithMaze gameWithMaze(isBlockedMatrix);

    EXPECT_EQ(3U, gameWithMaze.getGrundyNumberAt({4U, 4U}));
    ALBA_PRINT1(gameWithMaze.getString());
}

}

}
