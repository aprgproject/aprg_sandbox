#pragma once

#include <Algorithm/Graph/Bipartite/BipartiteCheckerUsingDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba
{

namespace algorithm
{


template <typename Vertex>
class MaximumMatchings
{
public:

    // The maximum matching problem asks to find a maximum-size set of node pairs
    // in an undirected graph such that each pair is connected with an edge and each node belongs to at most one pair.
    // The nodes of a bipartite graph can be always divided into two groups such that all edges of the graph go from the left group to the right group.

    // We can reduce the bipartite maximum matching problem to the maximum flow problem by adding two new nodes to the graph: a source and a sink.
    // We also add edges from the source to each left node and from each right node to the sink.
    // After this, the size of a maximum flow in the graph equals the size of a maximum matching in the original graph.

    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using BipartiteChecker = BipartiteCheckerUsingDfs<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<Vertex, int, DirectedGraphWithListOfEdges<Vertex>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;

    Edges getMaximumMatchings(
            BaseUndirectedGraphWithVertex const& graph,
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges result;
        BipartiteChecker bipartiteChecker(graph);
        if(bipartiteChecker.isBipartite())
        {
            FordFulkerson fordFulkerson(getFlowNetwork(graph, newSourceVertex, newSinkVertex, bipartiteChecker));
            result = getMaximumMatchings(fordFulkerson, newSourceVertex, newSinkVertex);
        }
        return result;
    }

private:

    Edges getMaximumMatchings(
            FordFulkerson const& fordFulkerson,
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges result;
        for(auto const& path : fordFulkerson.getAugmentingPaths())
        {
            Vertex previousVertex(path.front());
            for(unsigned int i=1; i<path.size(); i++)
            {
                Vertex const& vertex(path.at(i));
                if(previousVertex != newSourceVertex && vertex != newSinkVertex)
                {
                    result.emplace_back(previousVertex, vertex);
                }
                previousVertex = vertex;
            }
        }
        return result;
    }

    FlowNetwork getFlowNetwork(
            BaseUndirectedGraphWithVertex const& graph,
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex,
            BipartiteChecker const& bipartiteChecker) const
    {
        FlowNetwork flowNetwork(newSourceVertex, newSinkVertex);
        for(Vertex const& vertex : graph.getVertices())
        {
            if(!bipartiteChecker.getColor(vertex)) // "false" of first color
            {
                flowNetwork.connect(newSourceVertex, vertex, 1, 0);
            }
            else
            {
                flowNetwork.connect(vertex, newSinkVertex, 1, 0);
            }
        }
        for(Edge const& edge : graph.getEdges())
        {
            bool firstColor = bipartiteChecker.getColor(edge.first);
            bool secondColor = bipartiteChecker.getColor(edge.second);
            if(!firstColor && secondColor) // "false" of first color
            {
                flowNetwork.connect(edge.first, edge.second, 1, 0);
            }
            else if(firstColor && !secondColor)
            {
                flowNetwork.connect(edge.second, edge.first, 1, 0);
            }
        }
        return flowNetwork;
    }
};

// There are polynomial algorithms for finding maximum matchings in general graphs, but such algorithms are complex and rarely seen in programming contests.
// However, in bipartite graphs, the maximum matching problem is much easier to solve, because we can reduce it to the maximum flow problem.

}

}
