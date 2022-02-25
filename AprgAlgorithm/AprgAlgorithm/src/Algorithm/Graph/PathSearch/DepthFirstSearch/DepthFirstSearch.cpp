#include "DepthFirstSearch.hpp"

using namespace std;

namespace alba
{

namespace algorithm
{

DepthFirstSearch::DepthFirstSearch(
        BaseUndirectedGraph const& graph,
        Vertex const startVertex)
    : m_graph(graph)
    , m_startVertex(startVertex)
    , m_vertexToNextVertex()
    , m_isProcessed()
{
    reinitializeStartingFrom(startVertex);
}

bool DepthFirstSearch::hasPathTo(Vertex const endVertex)
{
    bool result(false);
    auto it = m_isProcessed.find(endVertex);
    if(it != m_isProcessed.cend())
    {
        result = it->second;
    }
    return result;
}

Path DepthFirstSearch::getOrderedPathTo(Vertex const endVertex)
{
    bool isSuccessful(true);
    Vertex currentVertex = endVertex;
    Path reversedPath;
    while(currentVertex != m_startVertex)
    {
        reversedPath.emplace_back(currentVertex);
        auto it = m_vertexToNextVertex.find(currentVertex);
        if(it != m_vertexToNextVertex.cend())
        {
            currentVertex = it->second;
        }
        else
        {
            isSuccessful = false;
            break;
        }
    }
    Path result;
    if(isSuccessful)
    {
        reversedPath.emplace_back(m_startVertex);
        copy(reversedPath.crbegin(), reversedPath.crend(), back_inserter(result));
    }
    return result;
}

void DepthFirstSearch::reinitializeStartingFrom(Vertex const startVertex)
{
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
            m_vertexToNextVertex[adjacentVertex] = vertex;
            continueTraversal(adjacentVertex);
        }
    }
}


void DepthFirstSearch::clear()
{
    m_vertexToNextVertex.clear();
    Vertices vertices(m_graph.getVertices());
    for(Vertex const vertex : vertices)
    {
        m_isProcessed[vertex] = false;
    }
}

}

}
