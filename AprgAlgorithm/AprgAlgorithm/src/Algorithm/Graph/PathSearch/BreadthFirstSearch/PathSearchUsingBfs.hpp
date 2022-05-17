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
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

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

// Proposition: BFS computes shortest paths (fewest number of edges) from s to all other vertices ina graph in time proportional to E+V
// Proof(correctness): Queue always consists of zero or more vertices of distance k from s, followed by zero or more vertices of distance k+1.
// In short, vertices with distance 1 are first, and then vertices with distance 2 and then vertices with distance and so on.
// Proof(running time): Each vertex connected to s is visited once.

}

}