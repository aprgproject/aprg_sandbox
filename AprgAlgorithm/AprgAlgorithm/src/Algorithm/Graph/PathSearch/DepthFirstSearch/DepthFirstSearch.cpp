#include "DepthFirstSearch.hpp"

using namespace std;

namespace alba
{

namespace algorithm
{

DepthFirstSearch::DepthFirstSearch(
        BaseUndirectedGraph const& graph,
        Vertex const startVertex)
    : BasePathSearch(graph, startVertex)
{
    reinitializeStartingFrom(startVertex);
}

Path DepthFirstSearch::getOrderedPathTo(Vertex const endVertex)
{
    return getPathTo(endVertex);
}

void DepthFirstSearch::reinitializeStartingFrom(Vertex const startVertex){
    clear();
    m_startVertex = startVertex;
    continueTraversal(startVertex);
}

void DepthFirstSearch::continueTraversal(Vertex const vertex)
{
    m_isProcessed[vertex] = true;
    Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(vertex));
    for(Vertex const adjacentVertex : adjacentVertices)
    {
        if(!m_isProcessed.at(adjacentVertex))
        {
            m_vertexToNextVertexMap[adjacentVertex] = vertex;
            continueTraversal(adjacentVertex);
        }
    }
}

}

}