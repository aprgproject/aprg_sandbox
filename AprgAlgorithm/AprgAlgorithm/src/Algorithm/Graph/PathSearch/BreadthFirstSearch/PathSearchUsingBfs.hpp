#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

#include <deque>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class PathSearchUsingBfs : public BasePathSearch<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearch<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    PathSearchUsingBfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
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
        VertexToBoolMap & isProcessedMap(this->m_isProcessedMap);
        isProcessedMap[startVertex] = true;

        while(!queueOfVerticesToProcess.empty())
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
            {
                if(this->isNotProcessed(adjacentVertex))
                {
                    this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    isProcessedMap[adjacentVertex] = true;
                    queueOfVerticesToProcess.emplace_front(adjacentVertex);
                }
            }

        }
    }
};

}

}
