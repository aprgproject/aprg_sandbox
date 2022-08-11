#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Common/Math/AlbaMathConstants.hpp>

#include <functional>
#include <deque>
#include <map>

namespace alba
{

namespace algorithm
{

template <typename SinkSourceFlowNetworkType>
class FordFulkersonUsingBfs
{
public:
    using Vertex = typename SinkSourceFlowNetworkType::Vertex;
    using FlowDataType = typename SinkSourceFlowNetworkType::FlowDataType;
    using FlowEdge = typename SinkSourceFlowNetworkType::FlowEdge;
    using Path = typename GraphTypes<Vertex>::Path;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using VertexToFlowEdgeMap = std::map<Vertex, FlowEdge>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using TraverseFunction = std::function<void(Vertex)>;

    FordFulkersonUsingBfs(SinkSourceFlowNetworkType const& flowNetwork)
        : m_flowNetwork(flowNetwork)
        , m_maxFlowValue{}
    {
        initialize();
    }

    FlowDataType getMaxFlowValue() const
    {
        return m_maxFlowValue;
    }

    Paths getAugmentingPaths() const
    {
        return m_augmentingPaths;
    }

    Edges getMinCutEdges() const
    {
        Edges result;
        // Let A be the set of nodes that can be reached from the source using positive-weight edges.
        // The processed vertices have positive-weight edges from source of last iteration.

        // Now the minimum cut consists of the edges of the original graph that start at some node in A, end at some node outside A.
        // So we just need to check for edges that isFound and isNotFound in processed vertices

        for(auto const& flowEdge : m_flowNetwork.getFlowEdges())
        {
            if(m_processedVertices.isFound(flowEdge.source)
                    && m_processedVertices.isNotFound(flowEdge.destination))
            {
                result.emplace_back(flowEdge.source, flowEdge.destination);
            }
        }
        return result;
    }

private:

    void initialize()
    {
        while(findAnAugmentingPathAndReturnIfFound())
        {
            FlowDataType bottleNeckFlow(getBottleNeckFlow());
            Path augmentingPath;

            traverseAugmentingPathInReverse([&](Vertex const& vertex)
            {
                auto flowEdge(m_vertexToAugmentingPathEdgeMap[vertex]);
                flowEdge.addResidualCapacityTo(vertex, bottleNeckFlow); // add the bottleNeckFlow in the augmenting path
                m_flowNetwork.updateEdge(flowEdge);
                augmentingPath.emplace_back(vertex);
            });

            m_maxFlowValue += bottleNeckFlow;

            augmentingPath.emplace_back(m_flowNetwork.getSourceVertex());
            std::reverse(augmentingPath.begin(), augmentingPath.end());
            m_augmentingPaths.emplace_back(augmentingPath);
        }
    }

    bool findAnAugmentingPathAndReturnIfFound()
    {
        m_vertexToAugmentingPathEdgeMap.clear();
        m_processedVertices.clear();
        m_processedVertices.putVertex(m_flowNetwork.getSourceVertex());
        std::deque<Vertex> queueOfVerticesToProcess{m_flowNetwork.getSourceVertex()};

        while(!queueOfVerticesToProcess.empty()) // BFS like traversal
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            for(auto const& flowEdge : m_flowNetwork.getFlowEdgesWithVertex(vertex))
            {
                Vertex otherVertex(flowEdge.getTheOtherVertex(vertex));
                if(m_processedVertices.isNotFound(otherVertex) && flowEdge.getResidualCapacityTo(otherVertex) > 0) // we can still put flow to this other vertex
                {
                    m_processedVertices.putVertex(otherVertex);
                    m_vertexToAugmentingPathEdgeMap[otherVertex] = flowEdge;
                    queueOfVerticesToProcess.emplace_front(otherVertex);
                }
            }
        }
        return m_processedVertices.isFound(m_flowNetwork.getSinkVertex()); // is sink vertex reached
    }

    void traverseAugmentingPathInReverse(TraverseFunction const& function)
    {
        // traverse augmenting path in reverse (does not reach source vertex)
        for(Vertex vertex = m_flowNetwork.getSinkVertex();
            vertex != m_flowNetwork.getSourceVertex();
            vertex = m_vertexToAugmentingPathEdgeMap.at(vertex).getTheOtherVertex(vertex))
        {
            function(vertex);
        }
    }

    FlowDataType getBottleNeckFlow()
    {
        // find minimum residual capacity in augmenting path
        FlowDataType bottleNeckFlow{};
        if(!m_vertexToAugmentingPathEdgeMap.empty())
        {
            Vertex firstVertex(m_vertexToAugmentingPathEdgeMap.cbegin()->first);
            bottleNeckFlow = m_vertexToAugmentingPathEdgeMap.at(firstVertex).getResidualCapacityTo(firstVertex);
            traverseAugmentingPathInReverse([&](Vertex const& vertex)
            {
                bottleNeckFlow = std::min(bottleNeckFlow, m_vertexToAugmentingPathEdgeMap.at(vertex).getResidualCapacityTo(vertex));
            });
        }
        return bottleNeckFlow;
    }

    SinkSourceFlowNetworkType m_flowNetwork;
    FlowDataType m_maxFlowValue;
    Paths m_augmentingPaths;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToFlowEdgeMap m_vertexToAugmentingPathEdgeMap;
};

// Ford fulkerson algorithm
// -> Initialization: start with 0 flow
// -> Find an undirected path from s to t such that (this is called the augmenting path):
// ---> Can increase flow on forward edges (not full)
// ---> Can decrease flow on backward edge (not empty)
// -> Termination All paths s to t are blocked by either a:
// ---> full forward edge
// ---> empty backward edge

// Process:
// -> Start with 0 flow
// -> While there exists an augmenting path:
// ---> Find an augmenting path
// ---> Compute bottleneck capacity
// ---> Increase flow on that path by bottleneck capacity.

// How to find an augmenting path? Any graph search will work but BFS works well.
// If FF terminates, does it always compute a maxflow?
// Does FF always terminate? If so after how many augmentations?
// -> yes, provided edge capacities are integers or augmenting paths are chosen carefully

// Ford-Fulkerson algorithm with integer capacities.
// -> Important special case. Edge capacities are integer between 1 and U.
// -> Invariant. The flow is integer- valued through Ford-Fulkerson
// ---> Proof (by induction):
// -----> BottleNeck capacity is an integer
// -----> Flow on an edge increases/decreases by bottleneck capacity.
// -> Proposition. Number of augmentations <= the value of the max flow.
// ---> Proof: Each augmentation increases the value by at least 1.
// -> Integrality theorem: There exists an integer value max flow. (and Ford Fulkerson finds it)
// ---> Proof: Ford-Fulkerson terminates and maxflow that it finds is integer-valued.

// Bad news: Even when edge capacities are integers, number of augmenting paths could be equal to the value of the maxflow.
// Good news: This case is easily avoided (use shortest/fattest path)

// FF performance depends on choice of augmenting paths.
// U is value of capacity
// augmenting path | number of paths | implementation
// shortest path   | <= (1/2)*E*V    | queue(BFS)
// fattest path    | <= E ln(E*U)    | priority queue
// random path     | <= E*U          | randomized queue
// DFS path        | <= E*U          | stack (DFS)
// Shortest path/BFS is implemented above.




// Other discussion:

// The Ford–Fulkerson algorithm finds the maximum flow in a graph.
// The algorithm begins with an empty flow, and at each step finds a path from the source to the sink that generates more flow.
// Finally, when the algorithm cannot increase the flow anymore, the maximum flow has been found.

// Note: This is a different representation compared to implementation above.
// The algorithm uses a special representation of the graph where each original edge has a reverse edge in another direction.
// The weight of each edge indicates how much more flow we could route through it.
// At the beginning of the algorithm, the weight of each original edge equals the capacity of the edge and the weight of each reverse edge is zero.

// Algorithm description
// Note: This is a different implementation compared to the implementation above.
// The Ford–Fulkerson algorithm consists of several rounds.
// On each round, the algorithm finds a path from the source to the sink such that each edge on the path has a positive weight.
// If there is more than one possible path available, we can choose ANY of them.
// The idea is that increasing the flow decreases the amount of flow that can go through the edges in the future.
// On the other hand, it is possible to cancel flow later using the reverse edges of the graph if it turns out that
// it would be beneficial to route the flow in another way.
// The algorithm increases the flow as long as there is a path from the source to the sink through positive-weight edges.

// Finding paths
// The Ford–Fulkerson algorithm does not specify how we should choose the paths that increase the flow.
// In any case, the algorithm will terminate sooner or later and correctly find the maximum flow.
// However, the efficiency of the algorithm depends on the way the paths are chosen.
// A simple way to find paths is to use depth-first search (BFS IS IMPLEMENTED ABOVE).
// Usually, this works well, but in the worst case, each path only increases the flow by 1 and the algorithm is slow.
// Fortunately, we can avoid this situation by using one of the following techniques:
// 1) Edmonds–Karp algorithm
// -> The Edmonds–Karp algorithm chooses each path so that the number of edges on the path is as small as possible.
// -> This can be done by using breadthfirst search instead of depth-first search for finding paths. THIS IS IMPLELENTED ABOVE.
// -> It can be proven that this guarantees that the flow increases quickly, and the time complexity of the algorithm is O(m2n).
// 2) Scaling algorithm
// -> The scaling algorithm uses depth-first search to find paths where each edge weight is at least a threshold value.
// -> Initially, the threshold value is some large number, for example the sum of all edge weights of the graph.
// -> Always when a path cannot be found, the threshold value is divided by 2.
// -> The time complexity of the algorithm is O(m^2 * logc), where c is the initial threshold value.

// Minimum cuts
// It turns out that once the Ford–Fulkerson algorithm has found a maximum flow, it has also determined a minimum cut.
// Let A be the set of nodes that can be reached from the source using positive-weight edges.
// Now the minimum cut consists of the edges of the original graph that start at some node in A,
// end at some node outside A, and whose capacity is fully used in the maximum flow.
// Why is the flow produced by the algorithm maximum and why is the cut minimum?
// The reason is that a graph cannot contain a flow whose size is larger than the weight of any cut of the graph.
// Hence, always when a flow and a cut are equally large, they are a maximum flow and a minimum cut.

}

}
