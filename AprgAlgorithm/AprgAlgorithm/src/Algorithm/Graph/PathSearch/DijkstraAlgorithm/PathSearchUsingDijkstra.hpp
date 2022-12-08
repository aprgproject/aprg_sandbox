#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class PathSearchUsingDijkstra : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>
{
public:
    using Graph = EdgeWeightedGraph;
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, Graph, ComparatorTemplateType>;
    using VertexOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::VertexOrderedByWeight;
    template<typename ValueType>
    struct ReverseComparator
    {
        bool operator()(ValueType const& first, ValueType const& second) const
        {
            return ComparatorTemplateType<ValueType>()(second, first);
        }
    };
    using VertexOrderedByWeightPriorityQueue = std::priority_queue<VertexOrderedByWeight, std::deque<VertexOrderedByWeight>, ReverseComparator<VertexOrderedByWeight>>;

    PathSearchUsingDijkstra(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
        , b_graph(BaseClass::m_graph)
        , b_startVertex(BaseClass::m_startVertex)
    {
        searchForPathIfPossible();
    }

private:

    bool isComparisonLessThan() const
    {
        ComparatorTemplateType<unsigned int> comparisonInUnsignedInt;
        return (comparisonInUnsignedInt(1U, 2U) && !comparisonInUnsignedInt(1U, 1U));
    }

    void searchForPathIfPossible()
    {
        if(isComparisonLessThan()
                || GraphUtilities::isDirectedAcyclicGraph(b_graph))
        {
            searchForPath();
        }
    }

    void searchForPath()
    {
        VertexOrderedByWeightPriorityQueue foundVerticesOrderedByWeight;
        foundVerticesOrderedByWeight.emplace(b_startVertex, Weight{}); // start vertex with weight zero for start
        while(!foundVerticesOrderedByWeight.empty())
        {
            // loops all current best weight vertices and only updates if the weight is better
            // this essentially prims algorithm but here weight is accumulated from the start vertex (Prim just take the closest)

            VertexOrderedByWeight vertexWithBestWeight(foundVerticesOrderedByWeight.top());
            foundVerticesOrderedByWeight.pop();
            this->relaxAt(vertexWithBestWeight.vertex, [&](Vertex const&, Vertex const& destinationVertex, Weight const& newWeight)
            {
                // this step is after relaxation on every adjacent vertex
                // this always add new entry if weight is changed -> this is important for longest path
                foundVerticesOrderedByWeight.emplace(destinationVertex, newWeight);
            });
        }
    }

    Graph const& b_graph;
    Vertex const& b_startVertex;
};

// Algorithm in short terms: Relax the current shortest/longest node.


// Dijkstra algorithm computes a shortest path tree in any edge-weighted digraph with non negative weights,
// Proof:
// -> Each edge e=v->w is relaxed exactly once (when v is relaxed), leaving distTo[w] <= distTo[v] + e.weight()
// -> Inequality holds until algorithm terminates because:
// ---> distTo[w] cannot decrease (relax prevents this)
// ---> distTo[v] will not change at all
// ---> Thus, upon termination shortest path optimality conditions hold.

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

// Negative weights:
// Dijsktra algorithm: Does not work on negative weights
// The efficiency of Dijkstra’s algorithm is based on the fact that the graph does not contain negative edges.
// If there is an edge with negative weights, the algorithm may give incorrect results.


// Other discussion:
// Dijkstra’s algorithm finds shortest paths from the starting node to all nodes of the graph, like the Bellman–Ford algorithm.
// The benefit of Dijsktra’s algorithm is that it is more efficient and can be used for processing large graphs.// However, the algorithm requires that there are no negative weight edges in the graph.

// Like in the Bellman–Ford algorithm, initially the distance to the starting node is 0 and the distance to all other nodes is infinite.
// At each step, Dijkstra’s algorithm selects a node that has not been processed yet and whose distance is as small as possible.
// The first such node is node 1 with distance 0.
// A remarkable property in Dijkstra’s algorithm is that whenever a node is selected (selected in the PQ), its distance is final
// (because there are no negative weights).


// Dijkstra’s algorithm is very similar to Prim’s algorithm for minimum spanning tree.
// Like Prim’s MST, we generate a SPT (shortest path tree) with a given source as a root.
// We maintain two sets, one set contains vertices included in the shortest-path tree,
// other set includes vertices not yet included in the shortest-path tree.
// At every step of the algorithm, we find a vertex that is in the other set (set of not yet included) and has a minimum distance from the source.
// Below are the detailed steps used in Dijkstra’s algorithm to find the shortest path from a single source vertex to all other vertices in the given graph.

// Algorithm
// -> 1) Create a set sptSet (shortest path tree set) that keeps track of vertices included in the shortest-path tree, i.e., whose minimum distance from the source is calculated and finalized. Initially, this set is empty.
// -> 2) Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign distance value as 0 for the source vertex so that it is picked first.
// -> 3) While sptSet doesn’t include all vertices
// ---> 3.a) Pick a vertex u which is not there in sptSet and has a minimum distance value.
// ---> 3.b) Include u to sptSet.
// ---> 3.c) Update distance value of all adjacent vertices of u.
// -----> To update the distance values, iterate through all adjacent vertices.
// -----> For every adjacent vertex v, if the sum of distance value of u (from source)
// -----> and weight of edge u-v, is less than the distance value of v, then update the distance value of v.

// Notes:
// -> 1) The code calculates the shortest distance but doesn’t calculate the path information.
// ---> We can create a parent array, update the parent array when distance is updated (like prim’s implementation)
// ---> and use it to show the shortest path from source to different vertices.
// -> 2) The code is for undirected graphs, the same Dijkstra function can be used for directed graphs also.
// -> 3) The code finds the shortest distances from the source to all vertices.
// ---> If we are interested only in the shortest distance from the source to a single target,
// ---> we can break the for loop when the picked minimum distance vertex is equal to the target (Step 3.a of the algorithm).
// -> 4) Time Complexity of the implementation is O(V^2).
// ---> If the input graph is represented using adjacency list, it can be reduced to O(E log V) with the help of a binary heap.
// -> 5) Dijkstra’s algorithm doesn’t work for graphs with negative weight cycles.
// ---> It may give correct results for a graph with negative edges but you must allow a vertex can be visited multiple times
// ---> and that version will lose its fast time complexity.
// ---> For graphs with negative weight edges and cycles, Bellman–Ford algorithm can be used, we will soon be discussing it as a separate post.


// Other analysis:
// The time complexity of the above implementation is O(n + mlogm). Note: 'n' is nodes and 'm' is edges.
// This because the algorithm goes through all nodes of the graph and adds for each edge at most one distance to the priority queue.// Note: In the implementation above, relax function uses a map to store weights which will result to have a different running time instead.

}
}
