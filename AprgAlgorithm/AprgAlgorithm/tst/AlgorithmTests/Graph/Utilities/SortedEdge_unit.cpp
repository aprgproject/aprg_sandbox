#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
}

TEST(SortedEdgeTest, CreateSortedEdgeWorks)
{
    using EdgeForTest = GraphTypes<VertexForTest>::Edge;

    EdgeForTest sortedEdge1ToVerify(createSortedEdge<VertexForTest, EdgeForTest>(4U, 5U));
    EdgeForTest sortedEdge2ToVerify(createSortedEdge<VertexForTest, EdgeForTest>(5U, 4U));

    EdgeForTest expectedSortedEdge(4U, 5U);
    EXPECT_EQ(expectedSortedEdge, sortedEdge1ToVerify);
    EXPECT_EQ(expectedSortedEdge, sortedEdge2ToVerify);
}

TEST(SortedEdgeTest, CreateSortedEdgeWithWeightWorks)
{
    using EdgeForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::EdgeWithWeight;

    EdgeForTest sortedEdge1ToVerify(createSortedEdgeWithWeight<VertexForTest, WeightForTest, EdgeForTest>(4U, 5U, 9.9));
    EdgeForTest sortedEdge2ToVerify(createSortedEdgeWithWeight<VertexForTest, WeightForTest, EdgeForTest>(5U, 4U, 9.9));

    EdgeForTest expectedSortedEdge(4U, 5U, 9.9);
    EXPECT_EQ(expectedSortedEdge, sortedEdge1ToVerify);
    EXPECT_EQ(expectedSortedEdge, sortedEdge2ToVerify);
}

}

}
