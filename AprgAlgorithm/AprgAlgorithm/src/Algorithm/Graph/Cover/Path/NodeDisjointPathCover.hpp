#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Graph/Utilities/VertexWithBool.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class NodeDisjointPathCover
{
public:
    // In a node-disjoint path cover, each node belongs to exactly one path.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using VertexWithEndpoint = VertexWithBool<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<VertexWithEndpoint, int, DirectedGraphWithListOfEdges<VertexWithEndpoint>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;

    NodeDisjointPathCover(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Edges getEdgesOfNodeDisjointPathCover(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        // A path cover is a set of paths in a graph such that each node of the graph belongs to at least one path.
        // It turns out that in directed, acyclic graphs,
        // we can reduce the problem of finding a minimum path cover to the problem of finding a maximum flow in another graph.
        Edges result;
        if(GraphUtilities::isDirectedAcyclicGraph(m_graph))
        {
            FordFulkerson fordFulkerson(getFlowNetwork(m_graph, newSourceVertex, newSinkVertex));
            result = getEdgesOfNodeDisjointPathCover(fordFulkerson);
        }
        return result;
    }

private:

    Edges getEdgesOfNodeDisjointPathCover(
            FordFulkerson const& fordFulkerson) const
    {
        Edges result;
        for(auto const& path : fordFulkerson.getAugmentingPaths())
        {
            if(path.size()>=2)
            {
                for(unsigned int i=1; i<=path.size()-2; i+=2)
                {
                    result.emplace_back(path.at(i).first, path.at(i+1).first);
                }
            }
        }
        return result;
    }

    FlowNetwork getFlowNetwork(
            BaseDirectedGraphWithVertex const& graph,
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        // We can find a minimum node-disjoint path cover by constructing a matching graph
        // where each node of the original graph is represented by two nodes: a left node and a right node.
        // There is an edge from a left node to a right node if there is such an edge in the original graph.
        // In addition, the matching graph contains a source and a sink, and there are edges from the source to all left nodes and from all right nodes to the sink.

        VertexWithEndpoint sourceVertexWithLeft{newSourceVertex, false};
        VertexWithEndpoint sinkVertexWithRight{newSinkVertex, true};
        FlowNetwork flowNetwork(sourceVertexWithLeft, sinkVertexWithRight);
        for(Vertex const& vertex : graph.getVertices())
        {
            flowNetwork.connect(sourceVertexWithLeft, {vertex, false}, 1, 0);
            flowNetwork.connect({vertex, true}, sinkVertexWithRight, 1, 0);
        }
        for(Edge const& edge : graph.getEdges())
        {
            flowNetwork.connect({edge.first, false}, {edge.second, true}, 1, 0);
        }
        return flowNetwork;
    }

    BaseDirectedGraphWithVertex const& m_graph;
};

}

}
