#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

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
    using EdgesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgesWithWeight;
    using EdgeWithWeightsPriorityQueue = std::priority_queue<EdgeWithWeight, EdgesWithWeight, std::greater<EdgeWithWeight>>;

    PrimAlgorithmLazyVersion(EdgeWeightedGraph const& graph, Vertex const& startVertex)
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

    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_processedVertices.find(vertex) == m_processedVertices.cend();
    }

    Edge createSortedEdge(Vertex const& vertex1, Vertex const& vertex2) const
    {
        if(vertex1 <= vertex2)
        {
            return Edge(vertex1, vertex2);
        }
        else
        {
            return Edge(vertex2, vertex1);
        }
    }

    void searchForMinimumSpanningTree()
    {
        searchTheAdjacentVertices(m_startVertex);
        while(!m_edgeWithWeightsPriorityQueue.empty())
        {
            EdgeWithWeight edgeWithWeight(m_edgeWithWeightsPriorityQueue.top());
            m_edgeWithWeightsPriorityQueue.pop();
            Vertex const& vertex1(edgeWithWeight.first);
            Vertex const& vertex2(edgeWithWeight.second);
            bool isVertex1NotProcessed(isNotProcessed(vertex1));
            bool isVertex2NotProcessed(isNotProcessed(vertex2));
            if(isVertex1NotProcessed || isVertex2NotProcessed)
            {
                m_minimumSpanningTreeEdges.emplace_back(createSortedEdge(vertex1, vertex2));
                if(isVertex1NotProcessed)
                {
                    searchTheAdjacentVertices(vertex1);
                }
                if(isVertex2NotProcessed)
                {
                    searchTheAdjacentVertices(vertex2);
                }
            }
        }
    }

    void searchTheAdjacentVertices(Vertex const& vertex)
    {
        m_processedVertices.emplace(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                m_edgeWithWeightsPriorityQueue.emplace(vertex, adjacentVertex, m_graph.getWeight(vertex, adjacentVertex));
            }
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    SetOfVertices m_processedVertices;
    Edges m_minimumSpanningTreeEdges;
    EdgeWithWeightsPriorityQueue m_edgeWithWeightsPriorityQueue;

};

}

}
