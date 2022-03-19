#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

#include <deque>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BreadthFirstSearch : public BasePathSearch<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearch<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BreadthFirstSearch(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        reinitializeStartingFrom(startVertex);
    }

    Path getShortestPathTo(Vertex const& endVertex) const
    {
        return this->getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertex const& startVertex) override
    {
        this->clear();
        this->m_startVertex = startVertex;
        std::deque<Vertex> queueOfVerticesToProcess{startVertex};
        this->m_isProcessed[startVertex] = true;

        while(!queueOfVerticesToProcess.empty())
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            Vertices adjacentVertices(this->m_graph.getAdjacentVerticesAt(vertex));
            for(Vertex const& adjacentVertex : adjacentVertices)
            {
                if(!this->m_isProcessed.at(adjacentVertex))
                {
                    this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    this->m_isProcessed[adjacentVertex] = true;
                    queueOfVerticesToProcess.emplace_front(adjacentVertex);
                }
            }
        }
    }
};
}

}
