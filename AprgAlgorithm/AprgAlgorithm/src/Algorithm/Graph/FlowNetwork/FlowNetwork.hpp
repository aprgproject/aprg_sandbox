#pragma once

#include <Common/Math/AlbaMathHelper.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <algorithm>
#include <sstream>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename FlowDataType, typename DirectedGraph>
class FlowNetwork : public DirectedGraph
{
public:
    using BaseClass = DirectedGraph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using EdgeWithVertexComparison = typename GraphTypes<Vertex>::EdgeWithVertexComparison;
    using FlowDataTypes = std::vector<FlowDataType>;

    struct FlowEdgeDetails
    {
        FlowDataType capacity;
        FlowDataType flow;
        bool operator==(FlowEdgeDetails const& second) const
        {
            return capacity == second.capacity && flow == second.flow;
        }
    };
    struct FlowEdge
    {
        Vertex source;
        Vertex destination;
        FlowDataType capacity;
        FlowDataType flow;
        bool operator==(FlowEdge const& second) const
        {
            return source == second.source && destination == second.destination && capacity == second.capacity && flow == second.flow;
        }
    };
    using FlowEdges = std::vector<FlowEdge>;
    using EdgeToFlowEdgeDetailsMap = std::map<EdgeWithVertexComparison, FlowEdgeDetails>;

    FlowNetwork()
        : BaseClass()
    {
        static_assert(
                    GraphDirectionType::Directed == DirectedGraph::DIRECTION_TYPE,
                    "Flow network's underlying graph should be a directed graph");
    }

    bool hasAUniqueMinimumSpanningTree() const
    {
        return hasNoDuplicateValues(getSortedWeights());
    }

    bool hasLocalEquilibrium(Vertex const& vertex) const
    {
        return mathHelper::isAlmostEqual(getDeltaFlowAt(vertex), static_cast<FlowDataType>(0));
    }

    FlowEdgeDetails getFlowEdgeDetails(Vertex const& vertex1, Vertex const& vertex2) const
    {
        FlowEdgeDetails result{};
        auto it = m_edgeToFlowEdgeDetailsMap.find(createEdgeInMap(vertex1, vertex2));
        if(it != m_edgeToFlowEdgeDetailsMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    FlowDataType getDeltaFlowAt(Vertex const& vertex) const
    {
        FlowDataType result{};
        for(auto const& edgeAndDetailsPair : m_edgeToFlowEdgeDetailsMap)
        {
            if(edgeAndDetailsPair.first.first == vertex)
            {
                result -= edgeAndDetailsPair.second.flow;
            }
            if(edgeAndDetailsPair.first.second == vertex)
            {
                result += edgeAndDetailsPair.second.flow;
            }
        }
        return result;
    }

    FlowDataTypes getSortedCapacities() const
    {
        FlowDataTypes capacities(getAllCapacities());
        std::sort(capacities.begin(), capacities.end());
        return capacities;
    }

    FlowDataTypes getSortedFlows() const
    {
        FlowDataTypes flows(getAllFlows());
        std::sort(flows.begin(), flows.end());
        return flows;
    }

    FlowDataTypes getSortedWeights() const
    {
        return getSortedCapacities();
    }

    EdgeToFlowEdgeDetailsMap const& getEdgeToFlowEdgeDetailsMap() const
    {
        return m_edgeToFlowEdgeDetailsMap;
    }

    FlowEdges getFlowEdges() const
    {
        FlowEdges result;
        std::transform(m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
                       [](auto const& edgeAndDetailsPair)
        {
            return FlowEdge{edgeAndDetailsPair.first.first, edgeAndDetailsPair.first.second, edgeAndDetailsPair.second.capacity, edgeAndDetailsPair.second.flow};
        });
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::string firstPart(BaseClass::getDisplayableString());
        std::stringstream ss;
        ss << "Flow edges: {";
        for(auto const& edgeAndDetailsPair : m_edgeToFlowEdgeDetailsMap)
        {
            ss << edgeAndDetailsPair.first.first << "<->"
               << edgeAndDetailsPair.first.second
               << "(capacity: " << edgeAndDetailsPair.second.capacity
               << " flow: "<< edgeAndDetailsPair.second.flow << "), ";
        }
        ss << "}";
        return firstPart + ss.str();
    }

    void connect(Vertex const& vertex1, Vertex const& vertex2, FlowDataType const& capacity, FlowDataType const& flow)
    {
        connect(vertex1, vertex2);
        m_edgeToFlowEdgeDetailsMap[createEdgeInMap(vertex1, vertex2)] = {capacity, flow};
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        BaseClass::disconnect(vertex1, vertex2);
        m_edgeToFlowEdgeDetailsMap.erase(createEdgeInMap(vertex1, vertex2));
    }

private:

    void connect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        BaseClass::connect(vertex1, vertex2);
    }

    bool hasNoDuplicateValues(FlowDataTypes const& flowDataTypes) const
    {
        return std::adjacent_find(flowDataTypes.cbegin(), flowDataTypes.cend()) == flowDataTypes.cend();
    }

    FlowDataTypes getAllCapacities() const
    {
        FlowDataTypes result;
        std::transform(m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
                       [&](auto const& edgeAndDetailsPair)
        {
            return edgeAndDetailsPair.second.capacity;
        });
        return result;
    }

    FlowDataTypes getAllFlows() const
    {
        FlowDataTypes result;
        std::transform(m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
                       [&](auto const& edgeAndDetailsPair)
        {
            return edgeAndDetailsPair.second.flow;
        });
        return result;
    }

    EdgeWithVertexComparison createEdgeInMap(Vertex const& vertex1, Vertex const& vertex2) const
    {
        return EdgeWithVertexComparison(vertex1, vertex2);
    }

    EdgeToFlowEdgeDetailsMap m_edgeToFlowEdgeDetailsMap;
};

}

}
