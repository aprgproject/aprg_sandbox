#include <Algorithm/Graph/PathSearch/HamiltonianPaths/HamiltonianPathSearchWithDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HamiltonianPathSearchWithDfs<VertexForTest>;
using PathForTest = PathSearchForTest::Path;
using PathsForTest = PathSearchForTest::Paths;
}  // namespace

TEST(HamiltonianPathSearchWithDfsTest_ForUndirectedGraph, GetAllHamiltonianPathsWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianPaths());

    PathsForTest pathsToExpect{{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {1, 0, 2, 3}, {1, 3, 2, 0},
                               {2, 0, 1, 3}, {2, 3, 1, 0}, {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForUndirectedGraph, GetOneHamiltonianPathWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianPath());

    PathForTest pathsToExpect{0, 1, 2, 3};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForUndirectedGraph, GetAllHamiltonianCyclesWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianCycles());

    PathsForTest pathsToExpect{{0, 1, 3, 2, 0}, {0, 2, 3, 1, 0}, {1, 0, 2, 3, 1}, {1, 3, 2, 0, 1},
                               {2, 0, 1, 3, 2}, {2, 3, 1, 0, 2}, {3, 1, 0, 2, 3}, {3, 2, 0, 1, 3}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForUndirectedGraph, GetOneHamiltonianCycleWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianCycle());

    PathForTest pathsToExpect{0, 1, 3, 2, 0};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}  // namespace algorithm

}  // namespace alba
