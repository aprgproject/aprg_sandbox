#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Math/GameTheory/GameWithGraph.hpp>

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

    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameState(1U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameState(2U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameState(3U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameState(4U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameState(5U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameState(6U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameState(7U));
    EXPECT_EQ(GameState::Winning, gameWithGraph.getGameState(8U));
    EXPECT_EQ(GameState::Losing, gameWithGraph.getGameState(9U));
    EXPECT_EQ(1U, gameWithGraph.getOptimalNextState(1U));
    EXPECT_EQ(1U, gameWithGraph.getOptimalNextState(2U));
    EXPECT_EQ(2U, gameWithGraph.getOptimalNextState(3U));
    EXPECT_EQ(3U, gameWithGraph.getOptimalNextState(4U));
    EXPECT_EQ(4U, gameWithGraph.getOptimalNextState(5U));
    EXPECT_EQ(5U, gameWithGraph.getOptimalNextState(6U));
    EXPECT_EQ(6U, gameWithGraph.getOptimalNextState(7U));
    EXPECT_EQ(7U, gameWithGraph.getOptimalNextState(8U));
    EXPECT_EQ(8U, gameWithGraph.getOptimalNextState(9U));
}

}

}
