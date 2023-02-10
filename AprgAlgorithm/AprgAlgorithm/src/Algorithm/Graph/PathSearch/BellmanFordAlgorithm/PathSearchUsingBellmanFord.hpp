#pragma once

#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class PathSearchUsingBellmanFord : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>
{
public:
    using Graph = EdgeWeightedGraph;
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>;
    using DequeOfVertices = typename GraphTypes<Vertex>::DequeOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using VertexToEdgeOrderedByWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeOrderedByWeightMap;

    PathSearchUsingBellmanFord(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
        , b_graph(BaseClass::m_graph)
        , b_startVertex(BaseClass::m_startVertex)
        , b_vertexToEdgeWithBestWeightMap(BaseClass::m_vertexToEdgeWithBestWeightMap)
        , m_hasPositiveOrNegativeCycle(false)
    {
        //searchForPathUsingOriginalBellmanFord(); // this is inefficient because of manual cycle detection
        searchForPathUsingAutomaticCycleDetection();
    }

private:

    void searchForPathUsingAutomaticCycleDetection()
    {
        unsigned int numberOfVertices(b_graph.getNumberOfVertices());
        unsigned int numberOfVerticesProcessed(0U);
        enqueue(b_startVertex);
        while(!m_queueOfVertices.empty() && !m_hasPositiveOrNegativeCycle)
        {
            // Repeat V times: Relax each edge
            bool isNewWeightFound(false);
            Vertex vertexAtQueue(dequeue());
            this->relaxAt(
                        vertexAtQueue,
                        [&](Vertex const&, Vertex const& destinationVertex, Weight const&)
            {
                isNewWeightFound = true;
                if(m_verticesInQueue.isNotFound(destinationVertex))
                {
                    enqueue(destinationVertex);
                }
            },
            [&]()
            {
                // As soon as processed number vertices reached the total number of vertices check for a positive/negative cycle.
                if(numberOfVerticesProcessed++ >= numberOfVertices)
                {
                    // there is a positive or negative cycle if new weight is found when number total number of vertices is reached
                    m_hasPositiveOrNegativeCycle = isNewWeightFound;
                }
            });
        }
    }

    void searchForPathUsingOriginalBellmanFord() // manually positive or negative cycle
    {
        unsigned int numberOfVertices(b_graph.getNumberOfVertices());
        unsigned int numberOfVerticesProcessed(0U);
        enqueue(b_startVertex);
        while(!m_queueOfVertices.empty() && !m_hasPositiveOrNegativeCycle)
        {
            // Repeat V times: Relax each edge
            Vertex vertexAtQueue(dequeue());
            this->relaxAt(vertexAtQueue, [&](Vertex const&, Vertex const& destinationVertex, Weight const&)
            {
                if(m_verticesInQueue.isNotFound(destinationVertex))
                {
                    enqueue(destinationVertex);
                }
            },
            [&]()
            {
                // As soon as processed number vertices reached the total number of vertices check for a postive/negative cycle.
                if(numberOfVerticesProcessed++!=0 && numberOfVerticesProcessed % numberOfVertices == 0)
                {
                    findAPositiveOrNegativeCycle();
                }
            });
        }
    }

    void enqueue(Vertex const& vertex)
    {
        m_queueOfVertices.emplace_back(vertex);
        m_verticesInQueue.putVertex(vertex);
    }

    Vertex dequeue()
    {
        Vertex result{};
        if(!m_queueOfVertices.empty())
        {
            result = m_queueOfVertices.front();
            m_queueOfVertices.pop_front();
            m_verticesInQueue.removeVertex(result);
        }
        return result;
    }

    void findAPositiveOrNegativeCycle()
    {
        // A positive cycle is a directed cycle whose sum of edge weight is positive.
        // A negative cycle is a directed cycle whose sum of edge weight is negative.
        // This is a negative cycle check on shortest path.
        // This is a positive cycle check on longest path.

        EdgeWeightedGraph bestPathTree;
        for(Vertex const& vertex : b_graph.getVertices())
        {
            auto it = b_vertexToEdgeWithBestWeightMap.find(vertex);
            if(it != b_vertexToEdgeWithBestWeightMap.cend())
            {
                bestPathTree.connect(it->second.first, it->second.second, it->second.weight);
            }
        }
        CycleDetectionUsingDfs<Vertex> cycleDetection(bestPathTree);
        m_hasPositiveOrNegativeCycle = !cycleDetection.getOneCycle().empty(); // a cycle in best tree means a positive or negative cycle
    }

    Graph const& b_graph;
    Vertex const& b_startVertex;
    VertexToEdgeOrderedByWeightMap & b_vertexToEdgeWithBestWeightMap;
    bool m_hasPositiveOrNegativeCycle;
    DequeOfVertices m_queueOfVertices; // SPFA improvement
    CheckableVertices<Vertex> m_verticesInQueue;
};

}

}

// Algorithm in short terms: Relax all nodes.


// Negative weights failed attempts:
// -> Dijkstra does not work on negative edge weights
// -> Reweighting (adding a constant to make all weights positive) does not work either.

// Proposition: A SPT (shortest path tree) exists iff no negative cycles.
// Proposition: A LPT (longest path tree) exists iff no positive cycles.

// Bellman Ford algorithm: Works on negative weights
// Process:
// "s" is the starting vertex
// 1) Initialize distTo[s]=0 and distTo[v]=infinity for all other vertices
// 2) Repeat V times: Relax each edge.

// Proposition: Dynamic programming algorithm computes SPT in any edge weight digraph with no negative cycles in time proportional to E*V
// Proof idea: After pass i, it found the shortest path containing at most i edges.

// Observation: If distTo[v] does not change during pass i, no need to relax any edge pointing from v in pass i+1
// -> Use a queue! Maintain a queue of vertices whose distTo are changed.

// Overall effect:
// -> running time is still proportional to E*V in worst case.
// -> But much faster than that in practice.

// Observation: If there is a negative cycle, Bellman-Ford gets stuck in a loop, updating distTo and edgeTo entries in the cycle.
// Proposition: If any vertex V is updated in phase V there exists a negative cycle (and can be traced back edgeTo[v] entries to find it)
// We can just check if there are any cycles when relax happened V times. This is implemented above.


// Other discusssions:

// Bellman–Ford Algorithm
// Given a graph and a source vertex src in graph, find shortest paths from src to all vertices in the given graph.
// The graph may contain negative weight edges.
// We have discussed Dijkstra’s algorithm for this problem.
// Dijkstra’s algorithm is a Greedy algorithm and time complexity is O(V+E LogV) (with the use of Fibonacci heap).
// Dijkstra doesn’t work for Graphs with negative weight edges, Bellman-Ford works for such graphs.
// Bellman-Ford is also simpler than Dijkstra and suites well for distributed systems.
// But time complexity of Bellman-Ford is O(VE), which is more than Dijkstra.

// Algorithm
// Following are the detailed steps.
// Input: Graph and a source vertex src
// Output: Shortest distance to all vertices from src.
// If there is a negative weight cycle, then shortest distances are not calculated, negative weight cycle is reported.
// -> 1) This step initializes distances from the source to all vertices as infinite and distance to the source itself as 0.
// ---> Create an array dist[] of size |V| with all values as infinite except dist[src] where src is source vertex.
// -> 2) This step calculates shortest distances. Do following |V|-1 times where |V| is the number of vertices in given graph.
// ---> a) Do following for each edge u-v
// -----> If dist[v] > dist[u] + weight of edge uv, then update dist[v]
// -------> dist[v] = dist[u] + weight of edge uv
// -> 3) This step reports if there is a negative weight cycle in graph. Do following for each edge u-v
// ---> If dist[v] > dist[u] + weight of edge uv, then “Graph contains negative weight cycle”

// The idea of step 3 is, step 2 guarantees the shortest distances if the graph doesn’t contain a negative weight cycle.
// If we iterate through all edges one more time and get a shorter path for any vertex, then there is a negative weight cycle. (AUTOMATIC CYCLE DETECTION)

// How does this work?
// -> Like other Dynamic Programming Problems, the algorithm calculates shortest paths in a bottom-up manner.
// -> It first calculates the shortest distances which have at-most one edge in the path.
// -> Then, it calculates the shortest paths with at-most 2 edges, and so on.
// -> After the i-th iteration of the outer loop, the shortest paths with at most i edges are calculated.
// -> There can be maximum |V|–1 edges in any simple path, that is why the outer loop runs |v|–1 times.
// -> The idea is, assuming that there is no negative weight cycle,
// -> if we have calculated shortest paths with at most i edges,
// -> then an iteration over all edges guarantees to give shortest path with at-most (i+1) edges.
// Proof:
// -> Correctness if G(V, E) has no negative weight cycles, then Bellman-Ford terminate with d[v] = S(s,v) for all v is an element of V.
// -> Proof approach: Consider any v in V, by monotonicity and correctness (d[v]>=S(s,v)) only need to show that d[v]=S(s,v) at the same time.
// -> Let: Path p = v0->v1->v2-> ... ->vk, be a shortest path from s to v with the minimum number edges.
// ---> So p is a simple path (no repeating vertices)
// ---> S(s, vi) = S(s, vi-1) + w(vi-1, vi) (by optimal substructure)
// ---> d[V0] = 0 = S(s, v0)
// -> Assume by induction that d[vj] = S(s, vj) after j rounds for j<i.
// -> Before last round: After i-1 rounds d[vi-1] = S(s, vi-1)
// -> During round i: relax (vi-1, vi) ->  so d[vi] = S(s, vi) (by correctness lemma)
// -> After k rounds, we have the correct answer for vk. k<=|V|-1 because p is simple.
// Corollary (contrapositive): If the Bellman Ford for fails to converge after |V|-1 round, then there must be a negative weight cycle.

// Notes:
// -> 1) Negative weights are found in various applications of graphs.
// For example, instead of paying cost for a path, we may get some advantage if we follow the path.
// -> 2) Bellman-Ford works better (better than Dijkstra’s) for distributed systems (for example in a network).
// Unlike Dijkstra’s where we need to find the minimum value of all vertices, in Bellman-Ford, edges are considered one by one.
// -> 3) Bellman-Ford does not work with undirected graph with negative edges as it will declared as negative cycle.

// Exercise:
// -> 1) The standard Bellman-Ford algorithm reports the shortest path only if there are no negative weight cycles.
// Modify it so that it reports minimum distances even if there is a negative weight cycle.
// -> 2) Can we use Dijkstra’s algorithm for shortest paths
// for graphs with negative weights – one idea can be, calculate the minimum weight value,
// add a positive value (equal to absolute value of minimum weight value)
// to all weights and run the Dijkstra’s algorithm for the modified graph. Will this algorithm work?


// Other discussions:
// The Bellman–Ford algorithm finds shortest paths from a starting node to all nodes of the graph.
// The algorithm can process all kinds of graphs, provided that the graph does not contain a cycle with negative length.
// If the graph contains a negative cycle, the algorithm can detect this.

// The algorithm keeps track of distances from the starting node to all nodes of the graph.
// Initially, the distance to the starting node is 0 and the distance to all other nodes in infinite.
// The algorithm reduces the distances by finding edges that shorten the paths until it is not possible to reduce any distance.

// Other analysis:
// The time complexity of the algorithm is O(nm), because the algorithm consists of n-1 rounds and iterates through all m edges during a round.
// If there are no negative cycles in the graph, all distances are final after n=1 rounds, because each shortest path can contain at most n-1 edges.
// In practice, the final distances can usually be found faster than in n-1 rounds.
// Thus, a possible way to make the algorithm more efficient is to stop the algorithm if no distance can be reduced during a round.
// Note: In the implementation above, relax function uses a map to store weights which will result to have a logarithmic term in the running time instead.

// Other improvements:
// The SPFA algorithm ("Shortest Path Faster Algorithm") is a variant of the Bellman–Ford algorithm,
// that is often more efficient than the original algorithm.
// -> The algorithm maintains a queue of nodes that might be used for reducing the distances.
// -> First, the algorithm adds the starting node x to the queue.
// -> Then, the algorithm always processes the first node in the queue, and when an edge a->b reduces a distance, node b is added to the queue.
// Note: This is implemented above.



