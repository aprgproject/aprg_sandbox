#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>
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
    using FlowDataTypes = std::vector<FlowDataType>;

    struct FlowEdgeDetails
    {
        FlowDataType capacity;
        FlowDataType flow;
        bool operator==(FlowEdgeDetails const& second) const
        {
            return mathHelper::isAlmostEqual(capacity, second.capacity)
                    && mathHelper::isAlmostEqual(flow, second.flow);
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
            return source == second.source
                    && destination == second.destination
                    && mathHelper::isAlmostEqual(capacity, second.capacity)
                    && mathHelper::isAlmostEqual(flow, second.flow);
        }

        Vertex getTheOtherVertex(Vertex const& mainVertex) const
        {
           return source == mainVertex ? destination : source;
        }

        FlowDataType getResidualCapacityTo(Vertex const& vertex) const
        {
            FlowDataType result{};
            if(source == vertex)
            {
                result = flow;
            }
            else if(destination == vertex)
            {
                result = capacity - flow;
            }
            return result;
        }

        void addResidualCapacityTo(Vertex const& vertex, FlowDataType const delta)
        {
            if(source == vertex)
            {
                flow -= delta;
            }
            else if(destination == vertex)
            {
                flow += delta;
            }
        }
    };
    using FlowEdges = std::vector<FlowEdge>;
    using EdgeToFlowEdgeDetailsMap = std::map<Edge, FlowEdgeDetails>;

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
        auto it = m_edgeToFlowEdgeDetailsMap.find({vertex1, vertex2});
        if(it != m_edgeToFlowEdgeDetailsMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    FlowEdge getFlowEdge(Vertex const& vertex1, Vertex const& vertex2) const
    {
        FlowEdgeDetails flowEdgeDetails(getFlowEdgeDetails(vertex1, vertex2));
        return FlowEdge{vertex1, vertex2, flowEdgeDetails.capacity, flowEdgeDetails.flow};
    }

    FlowDataType getDeltaFlowAt(Vertex const& vertex) const
    {
        // this is linear (not optimized)
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
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
        std::transform(m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
                       [](auto const& edgeAndDetailsPair)
        {
            return FlowEdge{edgeAndDetailsPair.first.first, edgeAndDetailsPair.first.second, edgeAndDetailsPair.second.capacity, edgeAndDetailsPair.second.flow};
        });
        return result;
    }

    FlowEdges getFlowEdgesWithVertex(Vertex const& vertex) const
    {
        // this is linear (not optimized)
        FlowEdges result;
        for(auto const& edgeAndDetailsPair : m_edgeToFlowEdgeDetailsMap)
        {
            if(edgeAndDetailsPair.first.first == vertex || edgeAndDetailsPair.first.second == vertex)
            {
                result.emplace_back(FlowEdge{edgeAndDetailsPair.first.first, edgeAndDetailsPair.first.second, edgeAndDetailsPair.second.capacity, edgeAndDetailsPair.second.flow});
            }
        }
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::string firstPart(BaseClass::getDisplayableString());
        std::stringstream ss;
        ss << "Flow edges: {";
        for(auto const& edgeAndDetailsPair : m_edgeToFlowEdgeDetailsMap)
        {
            ss << edgeAndDetailsPair.first.first << "->"
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
        m_edgeToFlowEdgeDetailsMap[Edge{vertex1, vertex2}] = {capacity, flow};
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        BaseClass::disconnect(vertex1, vertex2);
        m_edgeToFlowEdgeDetailsMap.erase({vertex1, vertex2});
    }

    void updateEdge(FlowEdge const& flowEdge)
    {
        FlowEdgeDetails & detailsToUpdate(m_edgeToFlowEdgeDetailsMap[Edge{flowEdge.source, flowEdge.destination}]);
        detailsToUpdate.capacity = flowEdge.capacity;
        detailsToUpdate.flow = flowEdge.flow;
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
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
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
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
        std::transform(m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
                       [&](auto const& edgeAndDetailsPair)
        {
            return edgeAndDetailsPair.second.flow;
        });
        return result;
    }

    EdgeToFlowEdgeDetailsMap m_edgeToFlowEdgeDetailsMap;
};

}

}
