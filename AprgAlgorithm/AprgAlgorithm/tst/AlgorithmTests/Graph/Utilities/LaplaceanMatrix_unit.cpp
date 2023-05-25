#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/LaplaceanMatrix.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
}  // namespace

TEST(LaplaceanMatrixTest, CreateLaplaceanMatrixWorksWithUndirectedGraph) {
    UndirectedGraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(3, 4);

    LaplaceanMatrix matrixToVerify(createLaplaceanMatrix<VertexForTest, 5>(graph));

    LaplaceanMatrix expectedMatrix(4, 4, {3, -1, -1, -1, -1, 1, 0, 0, -1, 0, 2, -1, -1, 0, -1, 2});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(LaplaceanMatrixTest, CreateLaplaceanMatrixWorksWithDirectedGraph) {
    DirectedGraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(3, 4);

    LaplaceanMatrix matrixToVerify(createLaplaceanMatrix<VertexForTest, 5>(graph));

    LaplaceanMatrix expectedMatrix(4, 4, {3, 0, 0, 0, -1, 0, 0, 0, -1, 0, 1, 0, -1, 0, -1, 0});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

}  // namespace algorithm

}  // namespace alba
