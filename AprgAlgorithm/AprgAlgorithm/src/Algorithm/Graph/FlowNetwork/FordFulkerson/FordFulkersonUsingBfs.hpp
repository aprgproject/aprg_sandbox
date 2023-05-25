#pragma once

#include <Algorithm/Graph/FlowNetwork/FordFulkerson/BaseFordFulkerson.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <deque>
#include <map>

namespace alba {

namespace algorithm {

template <typename SinkSourceFlowNetworkType>
class FordFulkersonUsingBfs : public BaseFordFulkerson<SinkSourceFlowNetworkType> {
public:
    using BaseClass = BaseFordFulkerson<SinkSourceFlowNetworkType>;
    using Vertex = typename SinkSourceFlowNetworkType::Vertex;
    using FlowEdge = typename SinkSourceFlowNetworkType::FlowEdge;
    using VertexToFlowEdgeMap = std::map<Vertex, FlowEdge>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    // Since this is using BFS this is actually the Edmonds–Karp algorithm.
    FordFulkersonUsingBfs(SinkSourceFlowNetworkType const& flowNetwork)
        : BaseClass(flowNetwork),
          b_flowNetwork(BaseClass::m_flowNetwork),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToAugmentingPathEdgeMap(BaseClass::m_vertexToAugmentingPathEdgeMap) {
        this->initialize();
    }

protected:
    bool findAnAugmentingPathAndReturnIfFound() override {
        b_vertexToAugmentingPathEdgeMap.clear();
        b_processedVertices.clear();
        b_processedVertices.putVertex(b_flowNetwork.getSourceVertex());
        std::deque<Vertex> queueOfVerticesToProcess{b_flowNetwork.getSourceVertex()};

        while (!queueOfVerticesToProcess.empty())  // BFS like traversal
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            for (FlowEdge const& flowEdge : b_flowNetwork.getFlowEdgesWithVertex(vertex)) {
                Vertex otherVertex(flowEdge.getTheOtherVertex(vertex));
                if (b_processedVertices.isNotFound(otherVertex) &&
                    flowEdge.getResidualCapacityTo(otherVertex) > 0)  // we can still put flow to this other vertex
                {
                    b_processedVertices.putVertex(otherVertex);
                    b_vertexToAugmentingPathEdgeMap[otherVertex] = flowEdge;
                    queueOfVerticesToProcess.emplace_front(otherVertex);
                }
            }
        }
        return b_processedVertices.isFound(b_flowNetwork.getSinkVertex());  // is sink vertex reached
    }

    SinkSourceFlowNetworkType const& b_flowNetwork;
    CheckableVerticesWithVertex& b_processedVertices;
    VertexToFlowEdgeMap& b_vertexToAugmentingPathEdgeMap;
};

}  // namespace algorithm

}  // namespace alba
