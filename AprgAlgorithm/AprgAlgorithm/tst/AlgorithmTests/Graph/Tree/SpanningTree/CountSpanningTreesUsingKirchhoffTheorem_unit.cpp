#include <Algorithm/Graph/Tree/SpanningTree/CountSpanningTreesUsingKirchhoffTheorem.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using CountTrees = CountSpanningTreesUsingKirchhoffTheorem<VertexForTest>;
}  // namespace

TEST(CountSpanningTreesUsingKirchhoffTheoremTest, GetCountWorks) {
    UndirectedGraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(3, 4);

    EXPECT_EQ(3, CountTrees::getCount<5>(graph));
}

}  // namespace algorithm

}  // namespace alba
