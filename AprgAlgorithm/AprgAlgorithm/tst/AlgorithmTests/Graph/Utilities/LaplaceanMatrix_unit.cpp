#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/LaplaceanMatrix.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
}  // namespace

TEST(LaplaceanMatrixTest, CreateLaplaceanMatrixWorksWithUndirectedGraph) {
    UndirectedGraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(3U, 4U);

    LaplaceanMatrix matrixToVerify(createLaplaceanMatrix<VertexForTest, 5U>(graph));

    LaplaceanMatrix expectedMatrix(4U, 4U, {3, -1, -1, -1, -1, 1, 0, 0, -1, 0, 2, -1, -1, 0, -1, 2});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(LaplaceanMatrixTest, CreateLaplaceanMatrixWorksWithDirectedGraph) {
    DirectedGraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(3U, 4U);

    LaplaceanMatrix matrixToVerify(createLaplaceanMatrix<VertexForTest, 5U>(graph));

    LaplaceanMatrix expectedMatrix(4U, 4U, {3, 0, 0, 0, -1, 0, 0, 0, -1, 0, 1, 0, -1, 0, -1, 0});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

}  // namespace algorithm

}  // namespace alba
