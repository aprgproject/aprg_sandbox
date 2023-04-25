#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/FloydWarshallAlgorithm/PathSearchUsingFloydWarshall.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using WeightForTest = double;
using PathForTest = GraphTypes<VertexForTest>::Path;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using ShortestPathSearchForTest =
    PathSearchUsingFloydWarshall<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, less>;
using LongestPathSearchForTest =
    PathSearchUsingFloydWarshall<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, greater>;
}  // namespace

TEST(PathSearchUsingFloydWarshallTest, ShortestPathSearchEndsWhenThereArePositiveCycles) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 1U, 0.26);
    graph.connect(1U, 2U, 0.38);
    graph.connect(2U, 3U, 0.29);
    graph.connect(3U, 0U, 0.34);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 4U));
}

TEST(PathSearchUsingFloydWarshallTest, ShortestPathSearchEndsWhenThereAreNegativeCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 1U, -0.26);
    graph.connect(1U, 2U, -0.38);
    graph.connect(2U, 3U, -0.29);
    graph.connect(3U, 0U, -0.34);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_EQ(PathForTest({}), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 3U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 3U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 4U));
}

TEST(PathSearchUsingFloydWarshallTest, LongestPathSearchEndsWhenThereArePositiveCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 1U, 0.26);
    graph.connect(1U, 2U, 0.38);
    graph.connect(2U, 3U, 0.29);
    graph.connect(3U, 0U, 0.34);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U, 0U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U, 1U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 4U));
}

TEST(PathSearchUsingFloydWarshallTest, LongestPathSearchEndsWhenThereAreNegativeCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 1U, -0.26);
    graph.connect(1U, 2U, -0.38);
    graph.connect(2U, 3U, -0.29);
    graph.connect(3U, 0U, -0.34);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 4U));
}

TEST(PathSearchUsingFloydWarshallTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(1U, 3U, 0.29);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 1U, 0.32);
    graph.connect(5U, 7U, 0.28);
    graph.connect(7U, 3U, 0.39);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 5U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 6U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 7U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 8U));
}

TEST(PathSearchUsingFloydWarshallTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(1U, 3U, 0.29);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 1U, 0.32);
    graph.connect(5U, 7U, 0.28);
    graph.connect(7U, 3U, 0.39);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 2U, 7U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest({0U, 4U}), pathSearch.getPathTo(0U, 4U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U}), pathSearch.getPathTo(0U, 5U));
    EXPECT_EQ(PathForTest({0U, 2U, 7U, 3U, 6U}), pathSearch.getPathTo(0U, 6U));
    EXPECT_EQ(PathForTest({0U, 2U, 7U}), pathSearch.getPathTo(0U, 7U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 8U));
}

TEST(PathSearchUsingFloydWarshallTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(1U, 3U, 0.29);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 1U, 0.32);
    graph.connect(5U, 7U, 0.28);
    graph.connect(7U, 3U, 0.39);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0U, 0U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 1U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 2U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 3U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 4U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 5U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 6U));
    EXPECT_TRUE(pathSearch.hasPathTo(0U, 7U));
    EXPECT_FALSE(pathSearch.hasPathTo(0U, 8U));
}

TEST(PathSearchUsingFloydWarshallTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(1U, 3U, 0.29);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 1U, 0.32);
    graph.connect(5U, 7U, 0.28);
    graph.connect(7U, 3U, 0.39);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 0U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U, 1U}), pathSearch.getPathTo(0U, 1U));
    EXPECT_EQ(PathForTest({0U, 2U}), pathSearch.getPathTo(0U, 2U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U, 7U, 3U}), pathSearch.getPathTo(0U, 3U));
    EXPECT_EQ(PathForTest({0U, 4U}), pathSearch.getPathTo(0U, 4U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U}), pathSearch.getPathTo(0U, 5U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U, 7U, 3U, 6U}), pathSearch.getPathTo(0U, 6U));
    EXPECT_EQ(PathForTest({0U, 4U, 5U, 7U}), pathSearch.getPathTo(0U, 7U));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0U, 8U));
}

}  // namespace algorithm

}  // namespace alba
