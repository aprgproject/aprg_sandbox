#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

namespace algorithm
{

using LaplaceanMatrix = matrix::AlbaMatrix<int>;

template <typename Vertex, unsigned int MAX_VERTEX_VALUE>
LaplaceanMatrix createLaplaceanMatrix(
        BaseGraph<Vertex> const& graph)
{
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;

    std::array<unsigned int, MAX_VERTEX_VALUE> vertexToIndexArray{};
    Vertices const& vertices(graph.getVertices());
    LaplaceanMatrix result(vertices.size(), vertices.size());

    unsigned int i=0;
    for(Vertex const& vertex : vertices)
    {
        result.setEntry(i, i, GraphUtilities::getDegreeAt(graph, vertex));
        vertexToIndexArray[vertex] = i++;
    }

    bool isUndirectedGraph = GraphDirectionType::Undirected == graph.getGraphDirectionType();
    for(Edge const& edge : graph.getEdges())
    {
        unsigned int index1 = vertexToIndexArray.at(edge.first);
        unsigned int index2 = vertexToIndexArray.at(edge.second);
        result.setEntry(index1, index2, -1);
        if(isUndirectedGraph)
        {
            result.setEntry(index2, index1, -1);
        }
    }
    return result;
}

}

}
