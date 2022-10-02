#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Math/GameTheory/SpecificGames/GameWithGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

namespace math
{

TEST(GameWithGraphTest, Example1Works)
{
    DirectedGraphWithAdjacencyMatrix<GameWithGraph::State, 10U> graph;
    graph.connect(2U, 1U);
    graph.connect(3U, 2U);
    graph.connect(4U, 2U);
    graph.connect(4U, 3U);
    graph.connect(5U, 4U);
    graph.connect(6U, 3U);
    graph.connect(6U, 4U);
    graph.connect(6U, 5U);
    graph.connect(7U, 6U);
    graph.connect(8U, 4U);
    graph.connect(8U, 6U);
    graph.connect(8U, 7U);
    graph.connect(9U, 6U);
    graph.connect(9U, 8U);
    GameWithGraph gameWithGraph(graph);

    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameStateAt(1U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameStateAt(2U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameStateAt(3U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameStateAt(4U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameStateAt(5U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameStateAt(6U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameStateAt(7U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameStateAt(8U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameStateAt(9U));
    EXPECT_EQ(1U, gameWithGraph.getOptimalNextStateAt(1U));
    EXPECT_EQ(1U, gameWithGraph.getOptimalNextStateAt(2U));
    EXPECT_EQ(2U, gameWithGraph.getOptimalNextStateAt(3U));
    EXPECT_EQ(3U, gameWithGraph.getOptimalNextStateAt(4U));
    EXPECT_EQ(4U, gameWithGraph.getOptimalNextStateAt(5U));
    EXPECT_EQ(5U, gameWithGraph.getOptimalNextStateAt(6U));
    EXPECT_EQ(6U, gameWithGraph.getOptimalNextStateAt(7U));
    EXPECT_EQ(7U, gameWithGraph.getOptimalNextStateAt(8U));
    EXPECT_EQ(8U, gameWithGraph.getOptimalNextStateAt(9U));
}

}
}