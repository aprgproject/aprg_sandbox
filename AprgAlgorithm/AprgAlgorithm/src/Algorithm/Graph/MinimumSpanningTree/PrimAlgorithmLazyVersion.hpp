#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PrimAlgorithmLazyVersion
{
public:
    using Graph = EdgeWeightedGraph;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using EdgeWithWeightsPriorityQueue = std::priority_queue<EdgeWithWeight, std::deque<EdgeWithWeight>, std::greater<EdgeWithWeight>>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PrimAlgorithmLazyVersion(EdgeWeightedGraph const& graph, Vertex const& startVertex)        : m_graph(graph)
        , m_startVertex(startVertex)
    {
        searchForMinimumSpanningTree();
    }

    Edges const& getMinimumSpanningTreeEdges() const
    {
        return m_minimumSpanningTreeEdges;
    }

private:

    void searchForMinimumSpanningTree()
    {
        checkAdjacentEdgesOfVertex(m_startVertex);
        while(!m_adjacentEdgesInOrder.empty())
        {
            // continue to grow the MST by processing the current nearest edge and only adding only edges with minimum weight
            EdgeWithWeight adjacentEdgeWithLowestWeight(m_adjacentEdgesInOrder.top());
            m_adjacentEdgesInOrder.pop();
            checkAdjacentEdgesOfEdgeAndAddToMstIfNeeded(adjacentEdgeWithLowestWeight);
        }
    }

    void checkAdjacentEdgesOfEdgeAndAddToMstIfNeeded(EdgeWithWeight const& edgeWithWeight)
    {
        // Since this is lazy algorithm (nearest vertices are not kept), we need to find which vertex/s is not included in the tree
        Vertex const& vertex1(edgeWithWeight.first);
        Vertex const& vertex2(edgeWithWeight.second);
        bool isVertex1NotProcessed(m_processedVertices.isNotFound(vertex1));
        bool isVertex2NotProcessed(m_processedVertices.isNotFound(vertex2));
        if(isVertex1NotProcessed || isVertex2NotProcessed)
        {
            m_minimumSpanningTreeEdges.emplace_back(createSortedEdge<Vertex, Edge>(vertex1, vertex2));
            if(isVertex1NotProcessed)
            {
                checkAdjacentEdgesOfVertex(vertex1);
            }
            if(isVertex2NotProcessed)
            {
                checkAdjacentEdgesOfVertex(vertex2);
            }
        }
    }

    void checkAdjacentEdgesOfVertex(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_adjacentEdgesInOrder.emplace(vertex, adjacentVertex, m_graph.getWeight(vertex, adjacentVertex));
            }
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    CheckableVerticesWithVertex m_processedVertices;
    Edges m_minimumSpanningTreeEdges;
    EdgeWithWeightsPriorityQueue m_adjacentEdgesInOrder; // makes this lazy algorithm (only find the nearest edge when needed)
};

// Prim's algorithm: proof of correctness
// Proposition: Prim's algorithm computes the MST.(Jarnik 1930, Dijkstra 1957, Prim 1959)
// Proof: Prims algorithm is a special case of the greedy MST algorithm
// -> Suppose edge e = minimum weight edge connecting a vertex on the tree to a vertex not on the tree.
// -> Cut = set of vertices connected on tree
// -> No crossing edge is black
// -> No crossing edge has lower weight

// Running time:
// Proposition: Lazy Prim's algorithm computes the MST in time proportional to E log E and extra space proportional to E(worst)
// Proof:
// -> Time for each part:
// ---> Deleting the minimum in PQ = E(frequency) * log E(time per operation)
// ---> Inserting in PQ = E(frequency) * log E(time per operation)


}

}
