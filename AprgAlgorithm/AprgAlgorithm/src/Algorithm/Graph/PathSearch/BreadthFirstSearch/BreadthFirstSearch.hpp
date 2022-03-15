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
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseClass = BasePathSearch<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BreadthFirstSearch(BaseUndirectedGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        reinitializeStartingFrom(startVertex);
    }

    Path getShortestPathTo(Vertex const& endVertex) const
    {
        return BaseClass::getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertex const& startVertex) override
    {
        BaseClass::clear();
        BaseClass::m_startVertex = startVertex;
        std::deque<Vertex> queueOfVerticesToProcess{startVertex};
        BaseClass::m_isProcessed[startVertex] = true;

        while(!queueOfVerticesToProcess.empty())
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            Vertices adjacentVertices(BaseClass::m_graph.getAdjacentVerticesAt(vertex));
            for(Vertex const& adjacentVertex : adjacentVertices)
            {
                if(!BaseClass::m_isProcessed.at(adjacentVertex))
                {
                    BaseClass::m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    BaseClass::m_isProcessed[adjacentVertex] = true;
                    queueOfVerticesToProcess.emplace_front(adjacentVertex);
                }
            }

        }
    }
};

}

}
