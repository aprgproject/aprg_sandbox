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
    using EdgeOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeOrderedByWeight;
    using VertexOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::VertexOrderedByWeight;
    using VertexOrderedByWeightMinimumPriorityQueue = std::priority_queue<VertexOrderedByWeight, std::deque<VertexOrderedByWeight>, std::greater<VertexOrderedByWeight>>;
    using VertexToEdgeOrderedByWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeOrderedByWeightMap;
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
                       [](auto const& vertexToEdgeOrderedByWeightPair)
        {
            return static_cast<Edge>(vertexToEdgeOrderedByWeightPair.second);
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
            VertexOrderedByWeight nearestVertex(m_nearestVerticesToTree.top());
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
                = createSortedEdgeOrderedByWeight<Vertex, Weight, EdgeOrderedByWeight>(vertex, adjacentVertex, lowestWeight);
        m_nearestVerticesToTree.emplace(adjacentVertex, lowestWeight);
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToEdgeOrderedByWeightMap m_vertexToEdgeWithMinimumWeightMap;
    VertexOrderedByWeightMinimumPriorityQueue m_nearestVerticesToTree; // makes this eager algorithm (nearest vertices is kept to find nearest edges easier)

};


// Algorithm in short terms: Add nearest vertices in the tree.
// Since its eager, nearest vertices are checked every time a new one is added on the tree.


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
// NOTE: decrease-keys mean these steps:
// -> Get the index of v in heap array
// -> Get the node and update its key value
// -> Travel up while the complete tree is not hepified (swim).
// -> THIS IS NOT IMPLEMENTED ABOVE
// ---> Updates to weight should be only decrease updates and decrease-key operation should be used


// Other discussions:
// Difference between eager and lazy?
// -> Eager only adds (vertex) to search when it has better weight

// The time complexity of Prim’s algorithm is O(n + mlogm) that equals the time complexity of Dijkstra’s algorithm. Note: 'n' is nodes and 'm' is edges.
// In practice, Prim’s and Kruskal’s algorithms are both efficient, and the choice of the algorithm is a matter of taste.
// Still, most competitive programmers use Kruskal’s algorithm.


// We have discussed Kruskal’s algorithm for Minimum Spanning Tree.
// Like Kruskal’s algorithm, Prim’s algorithm is also a Greedy algorithm.
// It starts with an empty spanning tree.
// The idea is to maintain two sets of vertices.
// The first set contains the vertices already included in the MST, the other set contains the vertices not yet included.
// At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges.
// After picking the edge, it moves the other endpoint of the edge to the set containing MST.
// A group of edges that connects two set of vertices in a graph is called cut in graph theory.
// So, at every step of Prim’s algorithm, we find a cut (of two sets, one contains the vertices already included in MST
// and other contains rest of the vertices), pick the minimum weight edge from the cut
// and include this vertex to MST Set (the set that contains already included vertices).

// How does Prim’s Algorithm Work?
// The idea behind Prim’s algorithm is simple, a spanning tree means all vertices must be connected.
// So the two disjoint subsets (discussed above) of vertices must be connected to make a Spanning Tree.
// And they must be connected with the minimum weight edge to make it a Minimum Spanning Tree.

// Algorithm
// -> 1) Create a set mstSet that keeps track of vertices already included in MST.
// -> 2) Assign a key value to all vertices in the input graph.
// ---> Initialize all key values as INFINITE. Assign key value as 0 for the first vertex so that it is picked first.
// -> 3) While mstSet doesn’t include all vertices
// ---> 3.a) Pick a vertex u which is not there in mstSet and has minimum key value.
// ---> 3.b) Include u to mstSet.
// ---> 3.c) Update key value of all adjacent vertices of u.
// -----> To update the key values, iterate through all adjacent vertices.
// -----> For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v
// -> The idea of using key values is to pick the minimum weight edge from cut.
// -> The key values are used only for vertices which are not yet included in MST,
// -> the key value for these vertices indicate the minimum weight edges connecting them to the set of vertices included in MST.

// Time Complexity of the above program is O(V^2).
// If the input graph is represented using adjacency list,
// then the time complexity of Prim’s algorithm can be reduced to O(E log V) with the help of binary heap.


}

}
