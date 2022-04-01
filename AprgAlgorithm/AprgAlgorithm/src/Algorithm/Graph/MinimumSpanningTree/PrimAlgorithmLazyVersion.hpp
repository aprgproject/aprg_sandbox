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
    using EdgesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgesWithWeight;
    using EdgeWithWeightsPriorityQueue = std::priority_queue<EdgeWithWeight, EdgesWithWeight, std::greater<EdgeWithWeight>>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

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

    void searchForMinimumSpanningTree()
    {
        checkAdjacentEdgesOfVertex(m_startVertex);
        while(!m_adjacentEdgesInOrder.empty())
        {
            EdgeWithWeight adjacentEdgeWithLowestWeight(m_adjacentEdgesInOrder.top());
            m_adjacentEdgesInOrder.pop();
            checkAdjacentEdgesOfEdgeAndAddToMstIfNeeded(adjacentEdgeWithLowestWeight);
        }
    }

    void checkAdjacentEdgesOfEdgeAndAddToMstIfNeeded(EdgeWithWeight const& edgeWithWeight)
    {
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
    EdgeWithWeightsPriorityQueue m_adjacentEdgesInOrder;

};

}

}
