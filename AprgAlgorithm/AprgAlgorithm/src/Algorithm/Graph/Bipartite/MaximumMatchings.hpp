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
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using BipartiteChecker = BipartiteCheckerUsingDfs<Vertex>;
    using FlowNetwork = SinkSourceFlowNetwork<Vertex, int, DirectedGraphWithListOfEdges<Vertex>>;
    using FordFulkerson = FordFulkersonUsingBfs<FlowNetwork>;

    MaximumMatchings(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_bipartiteChecker(m_graph)
    {}

    Edges getMaximumMatchings(
            Vertex const& newSourceVertex,
            Vertex const& newSinkVertex) const
    {
        Edges result;
        if(m_bipartiteChecker.isBipartite())
        {
            FordFulkerson fordFulkerson(getFlowNetwork(m_graph, newSourceVertex, newSinkVertex));
            result = getMaximumMatchings(fordFulkerson, newSourceVertex, newSinkVertex);
        }
        return result;
    }

    bool doesHavePerfectMatchingByCheckingASubset(
            Vertices const& subsetWithFirstColor) const
    {
        // Using Hall's theorem
        // Hall’s theorem can be used to find out whether a bipartite graph has a matching that contains all left or right nodes.
        // If the number of left and right nodes is the same,
        // Hall’s theorem tells us if it is possible to construct a perfect matching that contains all nodes of the graph.

        // Assume that we want to find a matching that contains all left nodes.
        // Let X be ANY SET of left nodes and let f(X) be the set of their neighbors.
        // According to Hall’s theorem, a matching that contains all left nodes exists exactly when for each X, the condition |X| <= |f(X)| holds.

        bool result(false);
        if(m_bipartiteChecker.isBipartite())
        {
            bool doAllVerticesInTheSubsetHaveFirstColor(true);
            SetOfVertices neighborVertices;
            for(Vertex const& vertexInSubset : subsetWithFirstColor)
            {
                if(m_bipartiteChecker.hasFirstColor(vertexInSubset))
                {
                    Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(vertexInSubset));
                    std::copy(adjacentVertices.cbegin(), adjacentVertices.cend(), std::inserter(neighborVertices, neighborVertices.cbegin()));
                }
                else
                {
                    doAllVerticesInTheSubsetHaveFirstColor = false;
                    break;
                }
            }
            if(doAllVerticesInTheSubsetHaveFirstColor)
            {
                result = subsetWithFirstColor.size() <= neighborVertices.size();
            }
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
            Vertex const& newSinkVertex) const
    {
        FlowNetwork flowNetwork(newSourceVertex, newSinkVertex);
        for(Vertex const& vertex : graph.getVertices())
        {
            if(m_bipartiteChecker.hasFirstColor(vertex))
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
            bool firstVertexColor = m_bipartiteChecker.hasFirstColor(edge.first);
            bool secondVertexColor = m_bipartiteChecker.hasFirstColor(edge.second);
            if(firstVertexColor && !secondVertexColor)
            {
                flowNetwork.connect(edge.first, edge.second, 1, 0);
            }
            else if(!firstVertexColor && secondVertexColor)
            {
                flowNetwork.connect(edge.second, edge.first, 1, 0);
            }
        }
        return flowNetwork;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    BipartiteChecker m_bipartiteChecker;
};

// There are polynomial algorithms for finding maximum matchings in general graphs, but such algorithms are complex and rarely seen in programming contests.
// However, in bipartite graphs, the maximum matching problem is much easier to solve, because we can reduce it to the maximum flow problem.

}

}
