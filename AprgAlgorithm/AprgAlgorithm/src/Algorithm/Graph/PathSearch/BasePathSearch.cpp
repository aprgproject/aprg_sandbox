#include "BasePathSearch.hpp"

#include <deque>

using namespace std;

namespace alba
{

namespace algorithm
{

BasePathSearch::BasePathSearch(
        BaseUndirectedGraph const& graph,
        Vertex const startVertex)
    : m_graph(graph)
    , m_startVertex(startVertex)
    , m_vertexToPreviousVertexMap()
    , m_isProcessed()
{}

bool BasePathSearch::hasPathTo(Vertex const endVertex) const
{
    bool result(false);
    auto it = m_isProcessed.find(endVertex);
    if(it != m_isProcessed.cend())
    {
        result = it->second;
    }
    return result;
}

Path BasePathSearch::getPathTo(Vertex const endVertex) const
{
    bool isSuccessful(true);
    Vertex currentVertex = endVertex;
    Path reversedPath;
    while(currentVertex != m_startVertex)
    {
        reversedPath.emplace_back(currentVertex);
        auto it = m_vertexToPreviousVertexMap.find(currentVertex);
        if(it != m_vertexToPreviousVertexMap.cend())
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
        result.reserve(reversedPath.size());
        copy(reversedPath.crbegin(), reversedPath.crend(), back_inserter(result));
    }
    return result;
}

VertexToBoolMap const& BasePathSearch::getIsProcessedMap()
{
    return m_isProcessed;
}

void BasePathSearch::clear()
{
    m_vertexToPreviousVertexMap.clear();
    Vertices vertices(m_graph.getVertices());
    for(Vertex const vertex : vertices)
    {
        m_isProcessed[vertex] = false;
    }
}

}

}
