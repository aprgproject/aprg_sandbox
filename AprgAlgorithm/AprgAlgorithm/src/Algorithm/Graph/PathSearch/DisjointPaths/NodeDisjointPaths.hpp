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
class NodeDisjointPaths
{
public:

    // Let us now consider another problem: finding the maximum number of node-disjoint paths from the source to the sink.
    // In this problem, "every node, except for the source and sink, may appear in at most one path".
    // The number of node-disjoint paths may be smaller than the number of edge-disjoint paths.

    // We can reduce also this problem to the maximum flow problem.
    // Since each node can appear in at most one path, we have to limit the flow that goes through the nodes.
    // A standard method for this is to divide each node into two nodes such that the first node has the incoming edges of the original node,
    // the second node has the outgoing edges of the original node, and there is a new edge from the first node to the second node.

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Path = typename GraphTypes<Vertex>::Path;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using VertexWithDuplicate = std::pair<Vertex, bool>;
    using FlowNetwork = SinkSourceFlowNetwork<VertexWithDuplicate, int, DirectedGraphWithListOfEdges<VertexWithDuplicate>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;

    NodeDisjointPaths(
            BaseDirectedGraphWithVertex const& graph,
            Vertex const& startVertex,
            Vertex const& endVertex)
        : m_fordFulkerson(getFlowNetwork(graph, startVertex, endVertex))
    {}

    unsigned int getNumberOfNodeDisjointPaths() const
    {
        return static_cast<unsigned int>(m_fordFulkerson.getMaxFlowValue());
    }

    Paths getNodeDisjointPaths() const
    {
        Paths result;
        for(auto const& pathWithDuplicate : m_fordFulkerson.getAugmentingPaths())
        {
            if(!pathWithDuplicate.empty())
            {
                Vertex previousVertex(pathWithDuplicate.front().first);
                Path path{previousVertex};
                path.reserve(pathWithDuplicate.size()); // reserve this much even though duplicates exists
                for(unsigned int i=1; i<pathWithDuplicate.size(); i++)
                {
                    Vertex const& vertex(pathWithDuplicate.at(i).first);
                    if(previousVertex != vertex)
                    {
                        path.emplace_back(vertex);
                        previousVertex = vertex;
                    }
                }
                result.emplace_back(path);
            }
        }
        return result;
    }

private:

    FlowNetwork getFlowNetwork(
            BaseDirectedGraphWithVertex const& graph,
            Vertex const& startVertex,
            Vertex const& endVertex) const
    {
        // For description above:
        // A standard method for this is to divide each node into two nodes such that the first node has the incoming edges of the original node,
        // the second node has the outgoing edges of the original node, and there is a new edge from the first node to the second node.

        FlowNetwork flowNetwork({startVertex, false}, {endVertex, false});
        for(Edge const& edge : graph.getEdges())
        {
            if(edge.first == startVertex)
            {
                flowNetwork.connect({edge.first, false}, {edge.second, false}, 1, 0);
            }
            else
            {
                flowNetwork.connect({edge.first, false}, {edge.first, true}, 1, 0);
                flowNetwork.connect({edge.first, true}, {edge.second, false}, 1, 0);
            }
        }
        return flowNetwork;
    }

    FordFulkerson m_fordFulkerson;
};

template <typename Vertex>
std::ostream & operator<<(std::ostream & out, std::pair<Vertex, bool> const& vertexWithDuplicate)
{
    out << "(" << vertexWithDuplicate.first << ", " << vertexWithDuplicate.second << ")";
    return out;
}

}

}
