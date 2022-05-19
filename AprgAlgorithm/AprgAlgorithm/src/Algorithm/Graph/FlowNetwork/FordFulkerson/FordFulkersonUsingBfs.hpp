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
    using VertexToFlowEdgeMap = std::map<Vertex, FlowEdge>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using TraverseFunction = std::function<void(Vertex)>;

    FordFulkersonUsingBfs(SinkSourceFlowNetworkType const& flowNetwork)
        : m_flowNetwork(flowNetwork)        , m_maxFlowValue{}
    {
        reinitialize();
    }

    bool isInMaxFlowMinCut(Vertex const& vertex) const
    {
        return m_processedVertices.isFound(vertex);
    }

    FlowDataType getMaxFlowValue() const
    {
        return m_maxFlowValue;
    }

    void reinitialize()
    {
        while(findAnAugmentingPathAndReturnIfFound())
        {
            FlowDataType bottleNeckFlow(getBottleNeckFlow());
            traverseAugmentingPathInReverse([&](Vertex const& vertex)
            {
                auto flowEdge(m_vertexToAugmentingPathEdgeMap[vertex]);
                flowEdge.addResidualCapacityTo(vertex, bottleNeckFlow); // add the bottleNeckFlow in the augmenting path
                m_flowNetwork.updateEdge(flowEdge);
            });
            m_maxFlowValue += bottleNeckFlow;
        }
    }

private:

    bool findAnAugmentingPathAndReturnIfFound()
    {
        m_vertexToAugmentingPathEdgeMap.clear();
        m_processedVertices.clear();
        m_processedVertices.putVertex(m_flowNetwork.getSourceVertex());
        std::deque<Vertex> queueOfVerticesToProcess{m_flowNetwork.getSourceVertex()};

        while(!queueOfVerticesToProcess.empty()) // BFS like traversal
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();            for(auto const& flowEdge : m_flowNetwork.getFlowEdgesWithVertex(vertex))
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
        return m_processedVertices.isFound(m_flowNetwork.getSinkVertex()); // if it reached sink vertex
    }

    void traverseAugmentingPathInReverse(TraverseFunction const& function)
    {
        // traverse augmenting path in reverse (does not reach source vertex)
        for(Vertex vertex = m_flowNetwork.getSinkVertex(); vertex != m_flowNetwork.getSourceVertex(); vertex = m_vertexToAugmentingPathEdgeMap.at(vertex).getTheOtherVertex(vertex))
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

}

}