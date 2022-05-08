#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Common/Math/AlbaMathConstants.hpp>

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

    FordFulkersonUsingBfs(SinkSourceFlowNetworkType const& flowNetwork)
        : m_flowNetwork(flowNetwork)
        , m_maxFlowValue{}
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
        while(clearAndCheckIfItHasAugmentingPath())
        {
            FlowDataType bottleneck(POSITIVE_INFINITY_DOUBLE_VALUE);
            for(Vertex vertex = m_flowNetwork.getSinkVertex(); vertex != m_flowNetwork.getSourceVertex(); vertex = m_vertexToFlowEdgeMap.at(vertex).getTheOtherVertex(vertex))
            {
                bottleneck = std::min(bottleneck, m_vertexToFlowEdgeMap.at(vertex).getResidualCapacityTo(vertex));
            }
            for(Vertex vertex = m_flowNetwork.getSinkVertex(); vertex != m_flowNetwork.getSourceVertex(); vertex = m_vertexToFlowEdgeMap.at(vertex).getTheOtherVertex(vertex))
            {
                auto flowEdge(m_vertexToFlowEdgeMap[vertex]);
                flowEdge.addResidualCapacityTo(vertex, bottleneck);
                m_flowNetwork.updateEdge(flowEdge);
            }
            m_maxFlowValue += bottleneck;
        }
    }

private:

    bool clearAndCheckIfItHasAugmentingPath()
    {
        m_vertexToFlowEdgeMap.clear();
        m_processedVertices.clear();
        m_processedVertices.putVertex(m_flowNetwork.getSourceVertex());
        std::deque<Vertex> queueOfVerticesToProcess{m_flowNetwork.getSourceVertex()};

        while(!queueOfVerticesToProcess.empty())
        {
            Vertex vertex(queueOfVerticesToProcess.back());
            queueOfVerticesToProcess.pop_back();
            for(auto const& flowEdge : m_flowNetwork.getFlowEdgesWithVertex(vertex))
            {
                Vertex otherVertex(flowEdge.getTheOtherVertex(vertex));
                if(m_processedVertices.isNotFound(otherVertex) && flowEdge.getResidualCapacityTo(otherVertex) > 0)
                {
                    m_processedVertices.putVertex(otherVertex);
                    m_vertexToFlowEdgeMap[otherVertex] = flowEdge;
                    queueOfVerticesToProcess.emplace_front(otherVertex);
                }
            }
        }
        return m_processedVertices.isFound(m_flowNetwork.getSinkVertex());
    }

    SinkSourceFlowNetworkType m_flowNetwork;
    FlowDataType m_maxFlowValue;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToFlowEdgeMap m_vertexToFlowEdgeMap;
};

}

}
