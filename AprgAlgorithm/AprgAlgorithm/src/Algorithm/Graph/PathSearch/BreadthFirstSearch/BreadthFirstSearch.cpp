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
    : BasePathSearch(graph, startVertex)
{
    reinitializeStartingFrom(startVertex);
}

Path BreadthFirstSearch::getShortestPathTo(Vertex const endVertex) const
{
    return getPathTo(endVertex);
}

void BreadthFirstSearch::reinitializeStartingFrom(Vertex const startVertex){
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
                m_vertexToNextVertexMap[adjacentVertex] = vertex;
                m_isProcessed[adjacentVertex] = true;
                queueOfVerticesToProcess.emplace_front(adjacentVertex);
            }        }

    }
}

}

}