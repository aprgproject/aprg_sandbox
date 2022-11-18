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
    // Path cover are set of paths that covers nodes.

    // A general path cover is a path cover where a node can belong to more than one path.
    // A minimum general path cover may be smaller than a minimum node-disjoint path cover, because a node can be used multiple times in paths.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using DequeOfVertices = typename GraphTypes<Vertex>::DequeOfVertices;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;
    using DequeOfEdges = typename GraphTypes<Vertex>::DequeOfEdges;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using VectorOfDequeOfVertices = std::vector<DequeOfVertices>;
    using VertexPair = std::pair<Vertex, Vertex>; // same definition with edge but edge is not correct in name
    using VertexPairs = std::vector<VertexPair>;
    using VertexWithLeftRight = VertexWithBool<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<VertexWithLeftRight, int, DirectedGraphWithListOfEdges<VertexWithLeftRight>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;
    using TransitiveClosure = TransitiveClosureWithMap<Vertex>;

    GeneralPathCover(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Paths getGeneralPathCover(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        VertexPairs vertexPairs(getConnectedVerticesOfGeneralPathCover(newSourceVertex, newSinkVertex));
        return getGeneralPathCover(vertexPairs);
    }

    VertexPairs getConnectedVerticesOfGeneralPathCover(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        VertexPairs result;
        if(GraphUtilities::isDirectedAcyclicGraph(m_graph))
        {
            result = getConnectedVerticesOfGeneralPathCoverUsingFordFulkerson(newSourceVertex, newSinkVertex);
        }
        return result;
    }

    unsigned int getSizeOfMaximumAntichain(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        // Using Dilworth's theorem:
        // An antichain is a set of nodes of a graph such that there is no path from any node to another node using the edges of the graph.
        // Dilworth’s theorem states that in a directed acyclic graph, the size of a minimum general path cover equals the size of a maximum antichain.

        return getGeneralPathCover(newSourceVertex, newSinkVertex).size();
    }

private:

    Paths getGeneralPathCover(
            VertexPairs const& vertexPairs) const
    {
        Paths result;
        Edges allEdges(m_graph.getEdges());
        DequeOfEdges detectedEdges;
        SetOfEdges unprocessedEdges(allEdges.cbegin(), allEdges.cend());
        for(VertexPair const& vertexPair : vertexPairs) // get detected edges and unprocessed edges
        {
            if(m_graph.isDirectlyConnected(vertexPair.first, vertexPair.second))
            {
                detectedEdges.emplace_back(vertexPair.first, vertexPair.second);
                unprocessedEdges.erase(Edge(vertexPair.first, vertexPair.second));
            }
        }
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
        for(DequeOfVertices & pathInDeque : paths) // add unprocessed edges to existing paths
        {
            for(auto it=unprocessedEdges.begin(); it!=unprocessedEdges.end();)
            {
                Edge const& unprocessedEdge(*it);
                if(pathInDeque.front() == unprocessedEdge.second)
                {
                    pathInDeque.emplace_front(unprocessedEdge.first);
                    unprocessedEdges.erase(it);
                    it=unprocessedEdges.begin();
                }
                else if(pathInDeque.back() == unprocessedEdge.first)
                {
                    pathInDeque.emplace_back(unprocessedEdge.second);
                    unprocessedEdges.erase(it);
                    it=unprocessedEdges.begin();
                }
                else
                {
                    it++;
                }
            }
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

    VertexPairs getConnectedVerticesOfGeneralPathCoverUsingFordFulkerson(
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
        // A minimum general path cover can be found almost like a minimum node-disjoint path cover.
        // It suffices to add some new edges to the matching graph so that there is an edge a->b always
        // when there is a path from a to b in the original graph (possibly through several edges).

        VertexWithLeftRight sourceVertexWithLeft{newSourceVertex, false};
        VertexWithLeftRight sinkVertexWithRight{newSinkVertex, true};
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
