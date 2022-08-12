#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/TransitiveClosureWithMap.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Graph/Utilities/VertexWithBool.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class GeneralPathCover
{
public:
    // A general path cover is a path cover where a node can belong to more than one path.
    // A minimum general path cover may be smaller than a minimum node-disjoint path cover, because a node can be used multiple times in paths.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using VertexWithEndpoint = VertexWithBool<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<VertexWithEndpoint, int, DirectedGraphWithListOfEdges<VertexWithEndpoint>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;
    using TransitiveClosure = TransitiveClosureWithMap<Vertex>;

    GeneralPathCover(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Edges getEdgesOfGeneralPathCover(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges result;
        if(GraphUtilities::isDirectedAcyclicGraph(m_graph))
        {
            FordFulkerson fordFulkerson(getFlowNetwork(m_graph, newSourceVertex, newSinkVertex));
            result = getEdgesOfGeneralPathCover(fordFulkerson);
        }
        return result;
    }

private:

    Edges getEdgesOfGeneralPathCover(
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
        // A minimum general path cover can be found almost like a minimum node-disjoint path cover.
        // It suffices to add some new edges to the matching graph so that there is an edge a->b always
        // when there is a path from a to b in the original graph (possibly through several edges).

        VertexWithEndpoint sourceVertexWithLeft{newSourceVertex, false};
        VertexWithEndpoint sinkVertexWithRight{newSinkVertex, true};
        FlowNetwork flowNetwork(sourceVertexWithLeft, sinkVertexWithRight);
        Vertices vertices(graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            flowNetwork.connect(sourceVertexWithLeft, {vertex, false}, 1, 0);
            flowNetwork.connect({vertex, true}, sinkVertexWithRight, 1, 0);
        }
        TransitiveClosure transitiveClosure(m_graph);
        for(Vertex const& vertex1 : vertices)
        {
            for(Vertex const& vertex2 : vertices)
            {
                if(transitiveClosure.isReachable(vertex1, vertex2) && vertex1 != vertex2)
                {
                    flowNetwork.connect({vertex1, false}, {vertex2, true}, 1, 0);
                }
            }
        }
        return flowNetwork;
    }

    BaseDirectedGraphWithVertex const& m_graph;
};

}

}
