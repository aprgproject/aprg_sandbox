#include <Algorithm/Graph/Cover/Path/GeneralPathCover.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using Paths = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using GeneralPathCoverForTest = GeneralPathCover<VertexForTest>;
using VertexPairs = typename GeneralPathCoverForTest::VertexPairs;

VertexForTest newSourceVertex = numeric_limits<int>::max();
VertexForTest newSinkVertex = numeric_limits<int>::max() - 1;
}  // namespace

TEST(GeneralPathCoverTest, GetGeneralPathCoverWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(3, 4);
    graph.connect(5, 6);
    graph.connect(6, 3);
    graph.connect(6, 7);
    GeneralPathCoverForTest generalPathCover(graph);

    Paths expectedPaths{{1, 5, 6, 7}, {2, 6, 3, 4}};
    VertexPairs expectedVertexPairs{{1, 5}, {2, 3}, {3, 4}, {5, 6}, {6, 7}};
    EXPECT_EQ(
        expectedVertexPairs, generalPathCover.getConnectedVerticesOfGeneralPathCover(newSourceVertex, newSinkVertex));
    EXPECT_EQ(expectedPaths, generalPathCover.getGeneralPathCover(newSourceVertex, newSinkVertex));
}

TEST(GeneralPathCoverTest, GetSizeOfMaximumAntichainOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(3, 4);
    graph.connect(5, 6);
    graph.connect(6, 3);
    graph.connect(6, 7);
    GeneralPathCoverForTest generalPathCover(graph);

    EXPECT_EQ(2, generalPathCover.getSizeOfMaximumAntichain(newSourceVertex, newSinkVertex));
}

}  // namespace algorithm

}  // namespace alba
