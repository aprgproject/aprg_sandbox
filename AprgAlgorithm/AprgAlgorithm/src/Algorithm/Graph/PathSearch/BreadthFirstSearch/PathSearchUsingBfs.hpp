#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithBfsAndDfs.hpp>

#include <deque>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class PathSearchUsingBfs : public BasePathSearchWithBfsAndDfs<Vertex>
{
public:    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

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
        CheckableVerticesWithVertex & processedVertices(this->m_processedVertices);
        processedVertices.putVertex(startVertex);

        std::deque<Vertex> queueOfVerticesToProcess{startVertex};
        while(!queueOfVerticesToProcess.empty())
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
            {
                if(processedVertices.isNotFound(adjacentVertex))
                {
                    processedVertices.putVertex(adjacentVertex);
                    this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    queueOfVerticesToProcess.emplace_front(adjacentVertex);
                }
            }
        }
    }
};

}

}
