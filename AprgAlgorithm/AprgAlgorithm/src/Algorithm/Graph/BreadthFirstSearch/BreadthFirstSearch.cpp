#include "BreadthFirstSearch.hpp"

#include <deque>

using namespace std;

namespace alba
{

namespace algorithm
{

BreadthFirstSearch::BreadthFirstSearch(
        BaseUndirectedGraph const& graph,
        Vertex const startVertex)
    : m_graph(graph)
    , m_startVertex(startVertex)
    , m_vertexToNextVertex()
    , m_isProcessed()
{
    reinitializeStartingFrom(startVertex);
}

bool BreadthFirstSearch::hasPathTo(Vertex const endVertex) const
{
    bool result(false);
    auto it = m_isProcessed.find(endVertex);
    if(it != m_isProcessed.cend())
    {
        result = it->second;
    }
    return result;
}

Path BreadthFirstSearch::getShortestPathTo(Vertex const endVertex) const
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

void BreadthFirstSearch::reinitializeStartingFrom(Vertex const startVertex)
{
    clear();
    m_startVertex = startVertex;
    deque<Vertex> queueOfVerticesToProcess{startVertex};
    m_isProcessed[startVertex] = true;

    while(!queueOfVerticesToProcess.empty())
    {
        Vertex vertex(queueOfVerticesToProcess.back());
        queueOfVerticesToProcess.pop_back();
        Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(vertex));
        for(Vertex const adjacentVertex : adjacentVertices)
        {
            if(!m_isProcessed.at(adjacentVertex))
            {
                m_vertexToNextVertex[adjacentVertex] = vertex;
                m_isProcessed[adjacentVertex] = true;
                queueOfVerticesToProcess.emplace_front(adjacentVertex);
            }
        }

    }
}


void BreadthFirstSearch::clear()
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
