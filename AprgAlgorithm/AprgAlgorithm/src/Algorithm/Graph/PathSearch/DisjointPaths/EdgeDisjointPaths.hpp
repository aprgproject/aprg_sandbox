#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class EdgeDisjointPaths
{
public:

    // We will first focus on the problem of finding the maximum number of edge-disjoint paths from the source to the sink.
    // This means that we should construct a set of paths such that "each edge appears in at most one path".

    // It turns out that the maximum number of edge-disjoint paths equals the maximum flow of the graph, assuming that the capacity of each edge is one.
    // After the maximum flow has been constructed, the edge-disjoint paths can be found greedily by following paths from the source to the sink.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<Vertex, int, DirectedGraphWithListOfEdges<Vertex>>;
    using Edge = typename GraphTypes<Vertex>::Edge;

    unsigned int getNumberOfEdgeDisjointPaths(
            BaseDirectedGraphWithVertex const& graph,
            Vertex const& startVertex,
            Vertex const& endVertex) const
    {
        FlowNetwork flowNetwork(startVertex, endVertex);
        for(Edge const& edge : graph.getEdges())
        {
            flowNetwork.connect(edge.first, edge.second, 1, 0);
        }
        FordFulkersonUsingBfs<FlowNetwork> fordFulkerson(flowNetwork);
        return static_cast<unsigned int>(fordFulkerson.getMaxFlowValue());
    }

};

}

}
