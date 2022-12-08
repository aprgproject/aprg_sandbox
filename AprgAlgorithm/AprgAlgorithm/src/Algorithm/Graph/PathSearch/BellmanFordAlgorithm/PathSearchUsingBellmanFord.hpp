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
                if(numberOfVerticesProcessed++!=0 && numberOfVerticesProcessed >= numberOfVertices)
                {
                    // there is a positive or negative cycle if new weight is found when number total number of vertices is reached                    m_hasPositiveOrNegativeCycle = isNewWeightFound;
                }
            });
        }    }

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
        Vertex result;
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



// Other discussion:
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


}

}
