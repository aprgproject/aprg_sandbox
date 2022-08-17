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
    // Path cover are set of paths that covers nodes.

    // In a node-disjoint path cover, each node belongs to exactly one path.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using DequeOfVertices = typename GraphTypes<Vertex>::DequeOfVertices;
    using DequeOfEdges = typename GraphTypes<Vertex>::DequeOfEdges;
    using VectorOfDequeOfVertices = std::vector<DequeOfVertices>;
    using VertexWithLeftRight = VertexWithBool<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<VertexWithLeftRight, int, DirectedGraphWithListOfEdges<VertexWithLeftRight>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;

    NodeDisjointPathCover(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Paths getNodeDisjointPathCover(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges edges(getEdgesOfNodeDisjointPathCover(newSourceVertex, newSinkVertex));
        return getNodeDisjointPathCover(edges);
    }

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
            result = getEdgesOfNodeDisjointPathCoverUsingFordFulkerson(newSourceVertex, newSinkVertex);
        }
        return result;
    }

private:

    Paths getNodeDisjointPathCover(
            Edges const& edges) const
    {
        Paths result;
        DequeOfEdges detectedEdges(edges.cbegin(), edges.cend());
        VectorOfDequeOfVertices paths;
        while(!detectedEdges.empty()) // construct paths from detected edges
        {
            Edge firstEdge(detectedEdges.front());
            detectedEdges.pop_front();
            DequeOfVertices pathInDeque{firstEdge.first, firstEdge.second};
            for(unsigned int i=0; i<detectedEdges.size();)
            {
                Edge const& edge(detectedEdges.at(i));
                if(pathInDeque.front() == edge.second)
                {
                    pathInDeque.emplace_front(edge.first);
                    detectedEdges.erase(detectedEdges.begin()+i);
                    i=0;
                }
                else if(pathInDeque.back() == edge.first)
                {
                    pathInDeque.emplace_back(edge.second);
                    detectedEdges.erase(detectedEdges.begin()+i);
                    i=0;
                }
                else
                {
                    i++;
                }
            }
            paths.emplace_back(pathInDeque);
        }
        Vertices allVertices(m_graph.getVertices());
        SetOfVertices unprocessedVertices(allVertices.cbegin(), allVertices.cend());
        for(DequeOfVertices const& pathInDeque : paths) // remove vertices from path to get unprocessed vertices
        {
            for(Vertex const& vertex : pathInDeque)
            {
                unprocessedVertices.erase(vertex);
            }
        }
        for(Vertex const& unprocessedVertex : unprocessedVertices) // add each of the unprocessed vertices as its own path
        {
            paths.emplace_back(DequeOfVertices{unprocessedVertex});
        }
        for(DequeOfVertices const& pathInDeque : paths) // convert pathsInDeque to paths
        {
            result.emplace_back(pathInDeque.begin(), pathInDeque.cend());
        }
        return result;
    }

    Edges getEdgesOfNodeDisjointPathCoverUsingFordFulkerson(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges result;
        FordFulkerson fordFulkerson(getFlowNetwork(m_graph, newSourceVertex, newSinkVertex));
        auto const& flowNetwork(fordFulkerson.getFlowNetwork());
        VertexWithLeftRight source(flowNetwork.getSourceVertex());
        VertexWithLeftRight sink(flowNetwork.getSinkVertex());
        for(auto const& flowEdge : flowNetwork.getFlowEdges())
        {
            if(1==flowEdge.flow && source != flowEdge.source && sink != flowEdge.destination)
            {
                result.emplace_back(flowEdge.source.first, flowEdge.destination.first);
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

        VertexWithLeftRight sourceVertexWithLeft{newSourceVertex, false};
        VertexWithLeftRight sinkVertexWithRight{newSinkVertex, true};
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
