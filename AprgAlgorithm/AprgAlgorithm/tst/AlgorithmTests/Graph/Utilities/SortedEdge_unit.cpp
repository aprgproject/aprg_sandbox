#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using WeightForTest = double;
}  // namespace

TEST(SortedEdgeTest, CreateSortedEdgeWorks) {
    using EdgeForTest = GraphTypes<VertexForTest>::Edge;

    EdgeForTest sortedEdge1ToVerify(createSortedEdge<VertexForTest, EdgeForTest>(4, 5));
    EdgeForTest sortedEdge2ToVerify(createSortedEdge<VertexForTest, EdgeForTest>(5, 4));

    EdgeForTest expectedSortedEdge(4, 5);
    EXPECT_EQ(expectedSortedEdge, sortedEdge1ToVerify);
    EXPECT_EQ(expectedSortedEdge, sortedEdge2ToVerify);
}

TEST(SortedEdgeTest, CreateSortedEdgeOrderedByWeightWorks) {
    using EdgeForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::EdgeOrderedByWeight;

    EdgeForTest sortedEdge1ToVerify(
        createSortedEdgeOrderedByWeight<VertexForTest, WeightForTest, EdgeForTest>(4, 5, 9.9));
    EdgeForTest sortedEdge2ToVerify(
        createSortedEdgeOrderedByWeight<VertexForTest, WeightForTest, EdgeForTest>(5, 4, 9.9));

    EdgeForTest expectedSortedEdge(4, 5, 9.9);
    EXPECT_EQ(expectedSortedEdge, sortedEdge1ToVerify);
    EXPECT_EQ(expectedSortedEdge, sortedEdge2ToVerify);
}

}  // namespace algorithm

}  // namespace alba
