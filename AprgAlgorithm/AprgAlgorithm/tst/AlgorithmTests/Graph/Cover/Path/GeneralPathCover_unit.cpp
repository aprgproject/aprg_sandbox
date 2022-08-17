#include <Algorithm/Graph/Cover/Path/GeneralPathCover.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using Paths = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using GeneralPathCoverForTest = GeneralPathCover<VertexForTest>;
using VertexPairs = typename GeneralPathCoverForTest::VertexPairs;

VertexForTest newSourceVertex = 0xFFFFFFFEU;
VertexForTest newSinkVertex = 0xFFFFFFFFU;
}

TEST(GeneralPathCoverTest, GetGeneralPathCoverWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(5U, 6U);
    graph.connect(6U, 3U);
    graph.connect(6U, 7U);
    GeneralPathCoverForTest generalPathCover(graph);

    Paths expectedPaths{{1U, 5U, 6U, 7U}, {2U, 6U, 3U, 4U}};
    EXPECT_EQ(expectedPaths, generalPathCover.getGeneralPathCover(newSourceVertex, newSinkVertex));
}

TEST(GeneralPathCoverTest, GetConnectedVerticesOfGeneralPathCoverWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(5U, 6U);
    graph.connect(6U, 3U);
    graph.connect(6U, 7U);
    GeneralPathCoverForTest generalPathCover(graph);

    VertexPairs expectedVertexPairs
    {{1U, 3U}, {2U, 4U}, {5U, 6U}, {6U, 7U}, {3U, 4U}, {2U, 3U}, {1U, 5U}};
    EXPECT_EQ(expectedVertexPairs, generalPathCover.getConnectedVerticesOfGeneralPathCover(newSourceVertex, newSinkVertex));
}

TEST(GeneralPathCoverTest, GetSizeOfMaximumAntichainOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(5U, 6U);
    graph.connect(6U, 3U);
    graph.connect(6U, 7U);
    GeneralPathCoverForTest generalPathCover(graph);

    EXPECT_EQ(2U, generalPathCover.getSizeOfMaximumAntichain(newSourceVertex, newSinkVertex));
}

}

}
