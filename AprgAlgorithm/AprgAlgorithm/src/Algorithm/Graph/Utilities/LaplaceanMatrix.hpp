#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <array>

namespace alba {

namespace algorithm {
using LaplaceanMatrix = matrix::AlbaMatrix<int>;

template <typename Vertex, int MAX_VERTEX_VALUE>LaplaceanMatrix createLaplaceanMatrix(BaseGraph<Vertex> const& graph) {
    // Laplacean matrix L is where L[i,i] is the degree of node i
    // and L[i,j] = -1 if there is an edge between nodes i and j, and otherwise L[i, j] = 0.

    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;

    std::array<int, MAX_VERTEX_VALUE> vertexToIndexArray{};
    Vertices const& vertices(graph.getVertices());
    LaplaceanMatrix result(vertices.size(), vertices.size());

    int i = 0;
    for (Vertex const& vertex : vertices) {
        result.setEntry(i, i, GraphUtilities::getDegreeAt(graph, vertex));
        vertexToIndexArray[vertex] = i++;
    }

    bool isUndirectedGraph = GraphDirectionType::Undirected == graph.getGraphDirectionType();
    for (Edge const& edge : graph.getEdges()) {
        int index1 = vertexToIndexArray[edge.first];
        int index2 = vertexToIndexArray[edge.second];
        result.setEntry(index1, index2, -1);
        if (isUndirectedGraph) {
            result.setEntry(index2, index1, -1);
        }
    }
    return result;
}

}  // namespace algorithm

}  // namespace alba
