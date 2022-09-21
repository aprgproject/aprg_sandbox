#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <algorithm>
#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PrimAlgorithmEagerVersion
{
public:
    using Graph = EdgeWeightedGraph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using VertexWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::VertexWithWeight;
    using VertexWithWeightMinimumPriorityQueue = std::priority_queue<VertexWithWeight, std::deque<VertexWithWeight>, std::greater<VertexWithWeight>>;
    using VertexToEdgeWithWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeWithWeightMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PrimAlgorithmEagerVersion(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {
        searchForMinimumSpanningTree();
    }

    Edges getMinimumSpanningTreeEdges() const
    {
        Edges result;
        result.reserve(m_vertexToEdgeWithMinimumWeightMap.size());
        std::transform(m_vertexToEdgeWithMinimumWeightMap.cbegin(), m_vertexToEdgeWithMinimumWeightMap.cend(), std::back_inserter(result),
                       [](auto const& vertexToEdgeWithWeightPair)
        {
            return static_cast<Edge>(vertexToEdgeWithWeightPair.second);
        });
        return result;
    }

private:

    bool hasNoWeightSaved(Vertex const& vertex) const
    {
        return m_vertexToEdgeWithMinimumWeightMap.find(vertex) == m_vertexToEdgeWithMinimumWeightMap.cend();
    }

    void searchForMinimumSpanningTree()
    {
        m_nearestVerticesToTree.emplace(m_startVertex, Weight{}); // start vertex with weight zero for start
        while(!m_nearestVerticesToTree.empty())
        {
            // continue to grow the MST by processing the current nearest edge and only adding only edges with minimum weight
            // Since this is eager algorithm (nearest vertices are kept),
            // -> we know the vertex to check if not yet included in tree (since its an adjacent vertex previously)
            VertexWithWeight nearestVertex(m_nearestVerticesToTree.top());
            m_nearestVerticesToTree.pop();
            checkAdjacentVerticesWithLowestWeightOfVertex(nearestVertex.vertex);
        }
    }

    void checkAdjacentVerticesWithLowestWeightOfVertex(
            Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex)) // only add vertices and edges from vertices not yet processed
            {
                Weight weightForAdjacentVertex(m_graph.getWeight(vertex, adjacentVertex));
                // check for vertex is not yet included or edge weight is smaller
                if(hasNoWeightSaved(adjacentVertex)
                        || weightForAdjacentVertex < m_vertexToEdgeWithMinimumWeightMap.at(adjacentVertex).weight)
                {
                    saveVertexAndEdgeOfLowestWeight(vertex, adjacentVertex, weightForAdjacentVertex);
                }
            }
        }
    }

    void saveVertexAndEdgeOfLowestWeight(
            Vertex const& vertex,
            Vertex const& adjacentVertex,
            Weight const& lowestWeight)
    {
        m_vertexToEdgeWithMinimumWeightMap[adjacentVertex]
                = createSortedEdgeWithWeight<Vertex, Weight, EdgeWithWeight>(vertex, adjacentVertex, lowestWeight);
        m_nearestVerticesToTree.emplace(adjacentVertex, lowestWeight);
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToEdgeWithWeightMap m_vertexToEdgeWithMinimumWeightMap;
    VertexWithWeightMinimumPriorityQueue m_nearestVerticesToTree; // makes this eager algorithm (nearest vertices is kept to find nearest edges easier)

};

// Running time:
// depends on Indexed-PQ implementation: Total = V inserts + V deletemins + E decrease-keys
// array: insert(1), delete-min(V), decrease-key(1) -> total = V^2
// binary heap: insert(log V), delete-min(log V), decrease-key(log V) -> total = E log V
// d-way heap: insert(d logd V)), delete-min(d logd V), decrease-key(d logd V) -> total = E log(E/V) V
// Fibonacci heap: insert(1*), delete-min(log V*), decrease-key(1*) -> total = E + V log V
// * means amortized
// Bottom line:
// -> Array implementation optimal for dense graphs
// -> Binary heap is faster for sparse graphs
// -> 4 way heap is worth the trouble in performance-critical situations
// -> Fibonacci heap is best in theory, but too complicated to implement (not worth it in practice)


// Other discussion:
// Difference between eager and lazy?
// -> Eager only adds (vertex) to search when it has better weight

// The time complexity of Prim’s algorithm is O(n + mlogm) that equals the time complexity of Dijkstra’s algorithm. Note: 'n' is nodes and 'm' is edges.
// In practice, Prim’s and Kruskal’s algorithms are both efficient, and the choice of the algorithm is a matter of taste.
// Still, most competitive programmers use Kruskal’s algorithm.


}

}
