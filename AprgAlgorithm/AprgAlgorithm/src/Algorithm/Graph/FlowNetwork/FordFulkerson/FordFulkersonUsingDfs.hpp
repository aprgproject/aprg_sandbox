#pragma once

#include <Algorithm/Graph/FlowNetwork/FordFulkerson/BaseFordFulkerson.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <deque>
#include <map>

namespace alba {

namespace algorithm {

template <typename SinkSourceFlowNetworkType>
class FordFulkersonUsingDfs : public BaseFordFulkerson<SinkSourceFlowNetworkType> {
public:
    using BaseClass = BaseFordFulkerson<SinkSourceFlowNetworkType>;
    using Vertex = typename SinkSourceFlowNetworkType::Vertex;
    using FlowEdge = typename SinkSourceFlowNetworkType::FlowEdge;
    using VertexToFlowEdgeMap = std::map<Vertex, FlowEdge>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    FordFulkersonUsingDfs(SinkSourceFlowNetworkType const& flowNetwork)
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
        traverseUsingDfs(b_flowNetwork.getSourceVertex());
        return b_processedVertices.isFound(b_flowNetwork.getSinkVertex());  // is sink vertex reached
    }

    void traverseUsingDfs(Vertex const& vertex) {
        b_processedVertices.putVertex(vertex);
        for (FlowEdge const& flowEdge : b_flowNetwork.getFlowEdgesWithVertex(vertex)) {
            Vertex otherVertex(flowEdge.getTheOtherVertex(vertex));
            if (b_processedVertices.isNotFound(otherVertex) && flowEdge.getResidualCapacityTo(otherVertex) > 0) {
                b_vertexToAugmentingPathEdgeMap[otherVertex] = flowEdge;
                traverseUsingDfs(otherVertex);
            }
        }
    }

    SinkSourceFlowNetworkType const& b_flowNetwork;
    CheckableVerticesWithVertex& b_processedVertices;
    VertexToFlowEdgeMap& b_vertexToAugmentingPathEdgeMap;
};

}  // namespace algorithm

}  // namespace alba
