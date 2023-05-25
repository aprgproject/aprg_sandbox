#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/FloydWarshallAlgorithm/PathSearchUsingFloydWarshall.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
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
    graph.connect(0, 1, 0.26);
    graph.connect(1, 2, 0.38);
    graph.connect(2, 3, 0.29);
    graph.connect(3, 0, 0.34);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 4));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 1, 2, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 4));
}

TEST(PathSearchUsingFloydWarshallTest, ShortestPathSearchEndsWhenThereAreNegativeCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 1, -0.26);
    graph.connect(1, 2, -0.38);
    graph.connect(2, 3, -0.29);
    graph.connect(3, 0, -0.34);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 4));
    EXPECT_EQ(PathForTest({}), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 3, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 3, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 2, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 4));
}

TEST(PathSearchUsingFloydWarshallTest, LongestPathSearchEndsWhenThereArePositiveCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 1, 0.26);
    graph.connect(1, 2, 0.38);
    graph.connect(2, 3, 0.29);
    graph.connect(3, 0, 0.34);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 4));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 2, 3, 0, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 2, 3, 1, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 2, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 4));
}

TEST(PathSearchUsingFloydWarshallTest, LongestPathSearchEndsWhenThereAreNegativeCyclesButDoesNotWork) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 1, -0.26);
    graph.connect(1, 2, -0.38);
    graph.connect(2, 3, -0.29);
    graph.connect(3, 0, -0.34);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 4));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 2, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 4));
}

TEST(PathSearchUsingFloydWarshallTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(1, 3, 0.29);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 1, 0.32);
    graph.connect(5, 7, 0.28);
    graph.connect(7, 3, 0.39);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 4));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 5));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 6));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 7));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 8));
}

TEST(PathSearchUsingFloydWarshallTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(1, 3, 0.29);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 1, 0.32);
    graph.connect(5, 7, 0.28);
    graph.connect(7, 3, 0.39);
    ShortestPathSearchForTest pathSearch(graph);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 4, 5, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 2, 7, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest({0, 4}), pathSearch.getPathTo(0, 4));
    EXPECT_EQ(PathForTest({0, 4, 5}), pathSearch.getPathTo(0, 5));
    EXPECT_EQ(PathForTest({0, 2, 7, 3, 6}), pathSearch.getPathTo(0, 6));
    EXPECT_EQ(PathForTest({0, 2, 7}), pathSearch.getPathTo(0, 7));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 8));
}

TEST(PathSearchUsingFloydWarshallTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(1, 3, 0.29);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 1, 0.32);
    graph.connect(5, 7, 0.28);
    graph.connect(7, 3, 0.39);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasPathTo(0, 0));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 1));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 2));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 3));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 4));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 5));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 6));
    EXPECT_TRUE(pathSearch.hasPathTo(0, 7));
    EXPECT_FALSE(pathSearch.hasPathTo(0, 8));
}

TEST(PathSearchUsingFloydWarshallTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(1, 3, 0.29);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 1, 0.32);
    graph.connect(5, 7, 0.28);
    graph.connect(7, 3, 0.39);
    LongestPathSearchForTest pathSearch(graph);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 0));
    EXPECT_EQ(PathForTest({0, 4, 5, 1}), pathSearch.getPathTo(0, 1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getPathTo(0, 2));
    EXPECT_EQ(PathForTest({0, 4, 5, 7, 3}), pathSearch.getPathTo(0, 3));
    EXPECT_EQ(PathForTest({0, 4}), pathSearch.getPathTo(0, 4));
    EXPECT_EQ(PathForTest({0, 4, 5}), pathSearch.getPathTo(0, 5));
    EXPECT_EQ(PathForTest({0, 4, 5, 7, 3, 6}), pathSearch.getPathTo(0, 6));
    EXPECT_EQ(PathForTest({0, 4, 5, 7}), pathSearch.getPathTo(0, 7));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0, 8));
}

}  // namespace algorithm

}  // namespace alba
