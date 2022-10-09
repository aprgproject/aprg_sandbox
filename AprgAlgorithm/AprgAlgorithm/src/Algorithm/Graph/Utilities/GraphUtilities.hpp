#pragma once

#include "GraphUtilitiesHeaders.hpp" // needs to be first

#include <Algorithm/Graph/Bipartite/BipartiteCheckerUsingDfs.hpp>
#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/PathSearch/DirectedAcyclicGraph/PathSearchForDirectedAcyclicGraph.hpp>
#include <Algorithm/Graph/Tree/LongestPathsInTree.hpp>
#include <Algorithm/UnionFind/BaseUnionFind.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

#include <algorithm>
#include <set>

namespace alba
{

namespace algorithm
{

namespace GraphUtilities
{

namespace
{
// utilities in utilities
template <typename Vertex>
void putEdgesToUnionFind(BaseUnionFind<Vertex> & unionFind, typename GraphTypes<Vertex>::Edges const& edges)
{
    using Edge = typename GraphTypes<Vertex>::Edge;
    for(Edge const& edge : edges)
    {
        unionFind.connect(edge.first, edge.second);
    }
}

template <typename Vertex>
void putGraphToUnionFind(BaseUnionFind<Vertex> & unionFind, BaseGraph<Vertex> const& graph)
{
    putEdgesToUnionFind(unionFind, graph.getEdges());
}
}



template <typename Vertex>
bool isASimplePath(typename GraphTypes<Vertex>::Path const& path)
{
    // A simple path is one with no repeated vertices
    // Other definition: A path is simple if each node appears at most once in the path.

    std::set<Vertex> uniqueVertices;
    copy(path.cbegin(), path.cend(), inserter(uniqueVertices, uniqueVertices.cbegin()));
    return uniqueVertices.size() == path.size();
}

template <typename Vertex>
bool isACycle(typename GraphTypes<Vertex>::Path const& path)
{
    // A cycle is a path with at least one edge whose first and last vertices are the same.

    bool result(false);
    if(!path.empty())
    {
        Vertex const& first(path.front());
        Vertex const& last(path.back());
        result = first == last;
    }
    return result;
}

template <typename Vertex>
bool isASimpleCycle(typename GraphTypes<Vertex>::Path const& path)
{
    // A simple cycle is a cycle with no repeated edges or vertices (except the requisite repetition of the first and last vertices).

    using Path = typename GraphTypes<Vertex>::Path;

    bool result(false);
    if(!path.empty() && isACycle<Vertex>(path))
    {
        Path pathWithOutEnd(path.cbegin(), path.cbegin()+path.size()-1);
        result = isASimplePath<Vertex>(pathWithOutEnd);
    }
    return result;
}

template <typename Vertex>
bool isDirectedAcyclicGraph(BaseGraph<Vertex> const& graph)
{
    // A directed acyclic graph (DAG) is a digraph with no directed cycles

    return GraphDirectionType::Directed == graph.getGraphDirectionType()
            && !hasAnyCyclesOnGraph(graph);
}

template <typename Vertex>
bool isDirectedSuccessorGraph(BaseGraph<Vertex> const& graph)
{
    // The outdegree of each node is 1, so each node has a unique successor.

    return GraphDirectionType::Directed == graph.getGraphDirectionType()
            && getMaxDegree(graph) == 1U;
}

template <typename Vertex>
bool hasAnyCyclesOnGraph(BaseGraph<Vertex> const& graph)
{
    CycleDetectionUsingDfs<Vertex> cycleDetection(graph);
    return !cycleDetection.getOneCycle().empty();
}

template <typename Vertex>
bool isARegularGraph(BaseGraph<Vertex> const& graph)
{
    // A graph is regular if the degree of every node is the same (a constant).

    bool result(true);
    auto vertices(graph.getVertices());
    if(!vertices.empty())
    {
        unsigned int degreeThatShouldMatch = getDegreeAt(graph, vertices.front());
        for(auto it=vertices.cbegin()+1; it!=vertices.cend(); it++)
        {
            if(degreeThatShouldMatch != getDegreeAt(graph, *it))
            {
                result=false;
                break;            }
        }
    }
    return result;}

template <typename Vertex>
bool isACompleteGraph(BaseGraph<Vertex> const& graph)
{
    // A graph is complete if the degree of every node is n-1, i.e., the graph contains all possible edges between the nodes.

    return areAllDegrees(graph, graph.getNumberOfVertices()-1);
}

template <typename Vertex>
bool isASimpleGraph(BaseGraph<Vertex> const& graph)
{
    // A graph is simple if no edge starts and ends at the same node, and there are no multiple edges between two nodes.
    // Often we assume that graphs are simple.

    return getNumberOfSelfLoops(graph) == 0; // "no edge starts and ends at the same node"
    // How to check "multiple edges between two nodes"?
}

template <typename Vertex>
bool isATree(BaseUndirectedGraph<Vertex> const& graph)
{
    // A tree is an acyclic connected graph.
    // Other definition: A tree is a connected, acyclic graph that consists of n nodes and n-1 edges.
    // Basically it needs to be: "Undirected", "Acyclic", and "Connected"

    return !hasAnyCyclesOnGraph(graph) && isGraphConnected(graph);
}

template <typename Vertex>
bool isAForest(BaseUndirectedGraph<Vertex> const& graph)
{
    // A disjoint set of trees is called a forest

    return !hasAnyCyclesOnGraph(graph) && !isGraphConnected(graph);
}

template <typename Vertex>
bool areAllDegrees(BaseGraph<Vertex> const& graph, unsigned int const degreeThatShouldMatch)
{
    auto const& vertices(graph.getVertices());
    return std::all_of(vertices.cbegin(), vertices.cend(), [&](Vertex const& vertex)
    {
        return degreeThatShouldMatch == getDegreeAt(graph, vertex);
    });
}

template <typename Vertex>
bool isASpanningTree(
        BaseUndirectedGraph<Vertex> const& mainGraph,
        BaseUndirectedGraph<Vertex> const& subGraphToCheck)
{
    // A spanning tree of a connected graph is a subgraph that contains all fo the graphs' vertices and is a single tree
    // Note: It should be a subgraph.

    return isATree(subGraphToCheck)
            && mainGraph.getVertices() == subGraphToCheck.getVertices();
}

template <typename Vertex>
bool isASpanningForest(
        BaseUndirectedGraph<Vertex> const& mainGraph,
        BaseUndirectedGraph<Vertex> const& subGraphToCheck)
{
    // A spanning forest of graph is the union of spanning trees of its connected components
    // Note: It should be a subgraph.

    return isAForest(subGraphToCheck)
            && mainGraph.getVertices() == subGraphToCheck.getVertices();
}

template <typename Vertex>
bool isGraphConnected(BaseUndirectedGraph<Vertex> const& graph)
{
    // A graph is connected if there is a path from every vertex to every other vertex in the graph.
    // This is used for undirected graphs.

    ConnectedComponentsUsingDfs<Vertex> connectedComponents(graph);
    return 1U == connectedComponents.getNumberOfComponentIds();
}

template <typename Vertex>
bool isGraphConnected(BaseDirectedGraph<Vertex> const& graph)
{
    // A graph is connected if there is a path from every vertex to every other vertex in the graph.
    // This is used for directed graphs.
    // Other definition: A graph is connected if there is a path between any two nodes.

    return isGraphStronglyConnected(graph);
}

template <typename Vertex>
bool isGraphStronglyConnected(BaseDirectedGraph<Vertex> const& graph)
{
    // Two vertices v and w are strongly connected if they are mutually reachable (so there is a edge from v to w and from w to v)
    // A directed graph is strongly connected if all its vertices are strongly connected to one another

    StronglyConnectedComponentsUsingKosarajuSharir<Vertex> connectedComponents(graph);
    return 1U == connectedComponents.getNumberOfComponentIds();
}

template <typename Vertex>
bool isBipartite(BaseUndirectedGraph<Vertex> const& graph)
{
    // A bipartite is a graph whose vertices we can divide into two sets
    // such that all edges connect a vertex in one set with a vertex in the other set.
    // In short, you can split the vertices in two groups and all edges should bridge the two groups

    // Other definition:
    // In a coloring of a graph, each node is assigned a color so that no adjacent nodes have the same color.
    // A graph is bipartite if it is possible to color it using two colors.
    // It turns out that a graph is bipartite exactly when it does not contain a cycle with an odd number of edges.

    return BipartiteCheckerUsingDfs<Vertex>(graph).isBipartite();
}

template <typename EdgeWeightedGraphType>
bool isFlowNetwork(EdgeWeightedGraphType const& graph)
{
    // A flow network is an edge-weighted digraph with positive edge weights (which we refer to as capacities).

    bool result(false);
    if(GraphDirectionType::Directed == graph.getGraphDirectionType())
    {
        auto weights(graph.getSortedWeights());
        result = std::all_of(weights.cbegin(), weights.cend(), [](auto const& weight)
        {
            return weight > 0;
        });
    }
    return result;
}

template <typename SinkSourceFlowNetworkType>
bool isSinkSourceFlowNetworkFeasible(SinkSourceFlowNetworkType const& flowNetwork)
{
    bool result(true);
    for(auto const& vertex: flowNetwork.getVertices())
    {
        for(auto const& adjacentVertex: flowNetwork.getAdjacentVerticesAt(vertex))
        {
            auto edgeDetails(flowNetwork.getFlowEdgeDetails(vertex, adjacentVertex));
            if(edgeDetails.flow < 0 || edgeDetails.flow > edgeDetails.capacity) // out of range
            {
                result = false;
                break;
            }
        }
    }
    if(result)
    {
        for(auto const& vertex: flowNetwork.getVertices())
        {
            if(flowNetwork.getSourceVertex() != vertex
                    && flowNetwork.getSinkVertex() != vertex
                    && !flowNetwork.hasLocalEquilibrium(vertex)) // should have local equilibrium at non source and sink vertices
            {
                result = false;
                break;
            }
        }
    }
    return result;
}

template <typename Vertex>
unsigned int getLengthOfPath(typename GraphTypes<Vertex>::Path const& path)
{
    // The length of a path is the number of edges in it.

    unsigned int result(0);
    if(!path.empty())
    {
        result = path.size() - 1;
    }
    return result;
}

template <typename Vertex>
unsigned int getDegreeAt(BaseGraph<Vertex> const& graph, Vertex const& vertex)
{
    // Other definition: The degree of a node is the number of its neighbors.

    return graph.getAdjacentVerticesAt(vertex).size();
}

template <typename Vertex>
unsigned int getMaxDegree(BaseGraph<Vertex> const& graph)
{
    unsigned int result(0);
    for(Vertex const& vertex : graph.getVertices())
    {
        result = std::max(result, getDegreeAt(graph, vertex));
    }
    return result;
}

template <typename Vertex>
unsigned int getMinDegree(BaseGraph<Vertex> const& graph)
{
    unsigned int result(0);
    auto vertices(graph.getVertices());
    if(!vertices.empty())
    {
        result = getDegreeAt(graph, vertices.front());
        for(auto it=vertices.cbegin()+1; it!=vertices.cend(); it++)
        {
            result = std::min(result, getDegreeAt(graph, *it));
        }
    }
    return result;}

template <typename Vertex>
unsigned int getSumOfDegrees(BaseGraph<Vertex> const& graph){
    // Other definition:
    // The sum of degrees in a graph is always 2m, where m is the number of edges, because each edge increases the degree of exactly two nodes by one.
    // For this reason, the sum of degrees is always even.
    // -> Is this only for undirected graphs?

    return graph.getNumberOfEdges()*2;
}

template <typename Vertex>
double getAverageDegree(BaseGraph<Vertex> const& graph)
{
    // Times two because edges are only counted once and degree is per vertex
    return static_cast<double>(graph.getNumberOfEdges()) / graph.getNumberOfVertices() * 2;
}

template <typename Vertex>
unsigned int getNumberOfSelfLoops(BaseGraph<Vertex> const& graph)
{
    using Edge = typename GraphTypes<Vertex>::Edge;
    unsigned int count(0);
    for(Edge const& edge : graph.getEdges())
    {
        if(edge.first == edge.second)
        {
            count++;
        }
    }
    return count;
}

template <typename Vertex>
unsigned int getDiameterOfATree(BaseUndirectedGraph<Vertex> const& graph)
{
    // The diameter of a tree is the maximum length of a path between two nodes.

    LongestPathsInTree<Vertex> longestPathsInTree(graph);
    longestPathsInTree.searchForAtLeastOneEndPointPair();
    return longestPathsInTree.getLongestDistance();
}

template <typename Vertex>
std::pair<unsigned int, unsigned int> getInDegreeAndOutDegreeAt(BaseDirectedGraph<Vertex> const& graph, Vertex const& vertex)
{
    // In a directed graph, the indegree of a node is the number of edges that end at the node,
    // and the outdegree of a node is the number of edges that start at the node.

    using Edge = typename GraphTypes<Vertex>::Edge;

    std::pair<unsigned int, unsigned int> result{};
    for(Edge const& edge : graph.getEdges())
    {
        if(edge.first == vertex)
        {
            result.first++;
        }
        if(edge.second == vertex)
        {
            result.second++;
        }
    }
    return result;
}

template <typename Vertex>
std::map<Vertex, std::pair<unsigned int, unsigned int>> getAllInDegreesAndOutDegrees(BaseDirectedGraph<Vertex> const& graph)
{
    // In a directed graph, the indegree of a node is the number of edges that end at the node,
    // and the outdegree of a node is the number of edges that start at the node.

    using Edge = typename GraphTypes<Vertex>::Edge;

    std::map<Vertex, std::pair<unsigned int, unsigned int>> result;
    for(Edge const& edge : graph.getEdges())
    {
        result[edge.first].first++;
        result[edge.second].second++;
    }
    return result;
}

template <typename Vertex, typename Weight, typename EdgeWeightedGraphType>
typename GraphTypes<Vertex>::Path getCriticalPath(
        EdgeWeightedGraphType const& graph,
        Vertex const& sourceVertex,
        Vertex const& destinationVertex)
{
    using Path = typename GraphTypes<Vertex>::Path;

    Path result;
    // Needs to be a directed acyclic path because if not the maximum path will be forever loop around the cycle
    if(isDirectedAcyclicGraph(graph))
    {
        // Use greater comparison for longest path
        PathSearchForDirectedAcyclicGraph<Vertex, Weight, EdgeWeightedGraphType, std::greater> pathSearch(graph, sourceVertex);
        result = pathSearch.getPathTo(destinationVertex);
    }
    return result;
}

template <typename Vertex>
typename GraphTypes<Vertex>::ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseUndirectedGraph<Vertex> const& graph)
{
    // A graph that is not connected (see isGraphConnected) consists of a set of connected components which are maximal connected subgraphs.

    using Edges = typename GraphTypes<Vertex>::Edges;
    using ListOfEdges = typename GraphTypes<Vertex>::ListOfEdges;

    UnionFindUsingMap<Vertex> unionFind;
    putGraphToUnionFind(unionFind, graph);
    std::map<Vertex, Edges> rootToEdgeMap;
    for(Vertex const& vertex : graph.getVertices())
    {
        Vertex root(unionFind.getRoot(vertex));
        for(Vertex const& adjacentVertex : graph.getAdjacentVerticesAt(vertex))
        {
            if(vertex <= adjacentVertex)
            {
                rootToEdgeMap[root].emplace_back(vertex, adjacentVertex);
            }
        }
    }
    ListOfEdges result;
    for(auto const& rootAndEdgesPair : rootToEdgeMap)
    {
        result.emplace_back(rootAndEdgesPair.second);
    }
    return result;
}

}

}

}
