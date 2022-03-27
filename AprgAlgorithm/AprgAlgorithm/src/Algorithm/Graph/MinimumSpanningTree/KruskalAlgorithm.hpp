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
        putAllEdgesToPriorityQueue();        unsigned int maxNumberOfEdgesInSpanningTree(m_graph.getNumberOfVertices()-1);
        UnionFindUsingMap<Vertex> unionFind;
        while(!m_edgesInOrder.empty() && m_minimumSpanningTreeEdges.size() < maxNumberOfEdgesInSpanningTree)
        {            EdgeWithWeight edgeWithWeight(m_edgesInOrder.top());
            m_edgesInOrder.pop();
            Vertex const& vertex1(edgeWithWeight.first);
            Vertex const& vertex2(edgeWithWeight.second);
            if(!unionFind.isConnected(vertex1, vertex2))
            {
                unionFind.connect(vertex1, vertex2);
                m_minimumSpanningTreeEdges.emplace_back(createSortedEdge<Vertex, Edge>(vertex1, vertex2));
            }
        }
    }
    void putAllEdgesToPriorityQueue()
    {
        for(Edge const& edge : m_graph.getEdges())        {
            m_edgesInOrder.emplace(edge.first, edge.second, m_graph.getWeight(edge.first, edge.second));
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    Edges m_minimumSpanningTreeEdges;
    EdgeWithWeightsPriorityQueue m_edgesInOrder;

};

}

}
