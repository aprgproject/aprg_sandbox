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
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PathSearchUsingBfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph)
    {
        reinitializeStartingFrom({startVertex});
    }

    PathSearchUsingBfs(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseClass(graph)
    {
        reinitializeStartingFrom(startVertices);
    }

    Path getShortestPathTo(Vertex const& endVertex) const
    {
        return this->getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertices const& startVertices) override
    {
        this->clear();
        this->addStartVertices(startVertices);
        traverseUsingBfs(startVertices);
    }

private:
    void traverseUsingBfs(Vertices const& startVertices)
    {
        CheckableVerticesWithVertex & processedVertices(this->m_processedVertices);
        processedVertices.putVertices(startVertices);

        std::deque<Vertex> nearestVertices;
        std::copy(startVertices.cbegin(), startVertices.cend(), std::back_inserter(nearestVertices)); // for multiple-source shortest path so multiple vertices here
        while(!nearestVertices.empty())
        {
            Vertex vertex(nearestVertices.back());
            nearestVertices.pop_back();
            for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
            {
                if(processedVertices.isNotFound(adjacentVertex))
                {
                    processedVertices.putVertex(adjacentVertex);
                    this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    nearestVertices.emplace_front(adjacentVertex);
                }
            }
        }
    }
};

// Proposition: BFS computes shortest paths (fewest number of edges) from s to all other vertices in a graph in time proportional to E+V
// Proof(correctness): Queue always consists of zero or more vertices of distance k from s, followed by zero or more vertices of distance k+1.
// In short, vertices with distance 1 are first, and then vertices with distance 2 and then vertices with distance 3 and so on.
// Proof(running time): Each vertex connected to s is visited once.

// Other analysis:
// Like in depth-first search, the time complexity of breadth-first search is O(n+m),
// where n is the number of nodes and m is the number of edges.
// The algorithm processes each node and edge once.

}

}