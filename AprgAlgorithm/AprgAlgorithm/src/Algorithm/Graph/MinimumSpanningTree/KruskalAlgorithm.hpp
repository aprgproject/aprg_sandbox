#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class KruskalAlgorithm
{
public:
    using Graph = EdgeWeightedGraph;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using EdgesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgesWithWeight;
    using EdgeWithWeightsPriorityQueue = std::priority_queue<EdgeWithWeight, EdgesWithWeight, std::greater<EdgeWithWeight>>;

    KruskalAlgorithm(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
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
        putAllEdgesToPriorityQueue();
        unsigned int maxNumberOfEdgesInSpanningTree(m_graph.getNumberOfVertices()-1);
        UnionFindUsingMap<Vertex> unionFind;
        while(!m_edgesInOrder.empty() && m_minimumSpanningTreeEdges.size() < maxNumberOfEdgesInSpanningTree)
        {
            // traverse all edges (shortest edges first) and add it to MST if vertices are not already connected in the MST (does not produce a cycle)
            EdgeWithWeight shortestEdge(m_edgesInOrder.top());
            m_edgesInOrder.pop();
            addEdgeToMstIfVerticesAreNotConnected(unionFind, shortestEdge);
        }
    }

    void putAllEdgesToPriorityQueue()
    {
        for(Edge const& edge : m_graph.getEdges())
        {
            m_edgesInOrder.emplace(edge.first, edge.second, m_graph.getWeight(edge.first, edge.second));
        }
    }

    void addEdgeToMstIfVerticesAreNotConnected(UnionFindUsingMap<Vertex> & unionFind, EdgeWithWeight const& edge)
    {
        Vertex const& vertex1(edge.first);
        Vertex const& vertex2(edge.second);
        if(!unionFind.isConnected(vertex1, vertex2))
        {
            unionFind.connect(vertex1, vertex2);
            m_minimumSpanningTreeEdges.emplace_back(createSortedEdge<Vertex, Edge>(vertex1, vertex2));
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    Edges m_minimumSpanningTreeEdges;
    EdgeWithWeightsPriorityQueue m_edgesInOrder;
};

// Proposition: Kruskal's algorithm computes MST.
// Proof:
// -> Kruskal algorithm is a special case of the greedy MST algorithm.
// -> Suppose Kruskal algorithm colors the edge e = v-w black.
// -> Cut = set of vertices connected to v in tree T
// -> No crossing edge is black
// -> No crossing edge has lower weight.

// Proposition: Kruskal's algorithm computes MST in time proportional to E log E (in the worst case).
// Proof:
// -> Time for each part:
// ---> Building the priority queue = 1(frequency) * E(time per operation)
// ---> Deleting the minimum in PQ = E(frequency) * log E(time per operation) -> main part of the running time
// ---> UnionFind connect = V(frequency) * log* V(time per operation)
// ---> UnionFind isConnected = E(frequency) * log* V(time per operation)

}

}
