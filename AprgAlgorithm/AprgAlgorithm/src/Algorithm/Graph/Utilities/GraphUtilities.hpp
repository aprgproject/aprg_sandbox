#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/BaseUnionFind.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

#include <algorithm>
#include <set>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
struct GraphUtilities
{
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseUnionFindWithVertex = BaseUnionFind<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using ListOfEdges = typename GraphTypes<Vertex>::ListOfEdges;
    using Path = typename GraphTypes<Vertex>::Path;

    static bool isASimplePath(Path const& path)
    {        // A simple path is one with no repeated vertices;

        std::set<Vertex> uniqueVertices;
        copy(path.cbegin(), path.cend(), inserter(uniqueVertices, uniqueVertices.cbegin()));
        return uniqueVertices.size() == path.size();
    }

    static bool isACycle(Path const& path)
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

    static bool isASimpleCycle(Path const& path)
    {
        // A simple cycle is a cycle with no repeated edges or vertices (except the requisite repetition of the first and last vertices).

        bool result(false);
        if(!path.empty() && isACycle(path))
        {
            Path pathWithOutEnd(path.cbegin(), path.cbegin()+path.size()-1);
            result = isASimplePath(pathWithOutEnd);
        }
        return result;
    }

    static bool isDirectedAcyclicGraph(BaseGraphWithVertex const& graph)
    {
        // A directed acyclic graph (DAG) is a digraph with no directed cycles

        return GraphDirectionType::Directed == graph.getGraphDirectionType()
                 && hasAnyCyclesOnGraph(graph);
    }

    static bool hasAnyCyclesOnGraph(BaseGraphWithVertex const& graph)
    {
        CycleDetectionUsingDfs<Vertex> cycleDetection(graph);
        cycleDetection.checkForCycles();
        return cycleDetection.hasCycle();
    }

    static bool isATree(BaseUndirectedGraphWithVertex const& graph)
    {
        // A tree is an acyclic connected graph.

        return !hasAnyCyclesOnGraph(graph) && isGraphConnected(graph);
    }

    static bool isGraphConnected(BaseUndirectedGraphWithVertex const& graph)
    {
        // A graph is connected if there is a path from every vertex to every other vertex in the graph.
        // This is used for undirected graphs.

        ConnectedComponentsUsingDfs<Vertex> connectedComponents(graph);
        return 1U == connectedComponents.getNumberOfComponentIds();
    }

    static bool isGraphStronglyConnected(BaseDirectedGraphWithVertex const& graph)
    {
        // Two vertices v and w are strongly connected if they are mutually reachable (so there is a v to w and w to v)
        // A directed graph is strongly connected if all its vertices are strongly connected to one another

        StronglyConnectedComponentsUsingKosarajuSharir<Vertex> connectedComponents(graph);
        return 1U == connectedComponents.getNumberOfComponentIds();
    }

    static bool isBipartite(BaseUndirectedGraphWithVertex const& graph)
    {
        // A bipartite is a graph whose vertices we can divide into two sets
        // such that all edges connect a vertex in one set with a vertex in the other set.
        // So there is only one edge connecting both sets, and if that edge is removed the graph is no longer connected

        /*SetOfVertices processedVertices;
        Vertices vertices(graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            colorMap[vertex] = false;
        }
        bool isTwoColorable(true);        for(Vertex const& vertex : vertices)
        {
            if(!isProcessedMap.at(vertex))
            {
                checkIsBipartiteUsingDfs(graph, vertex, isProcessedMap, colorMap, isTwoColorable);
            }
            if(!isTwoColorable)
            {
                break;
            }
        }*/
        return false;
    }

    static unsigned int getDegreeAt(BaseGraphWithVertex const& graph, Vertex const& vertex)    {
        return graph.getAdjacentVerticesAt(vertex).size();
    }

    static unsigned int getMaxDegree(BaseGraphWithVertex const& graph)
    {
        unsigned int result(0);
        for(Vertex const& vertex : graph.getVertices())
        {
            result = std::max(result, getDegreeAt(graph, vertex));
        }
        return result;
    }

    static double getAverageDegree(BaseGraphWithVertex const& graph)
    {
        return static_cast<double>(graph.getNumberOfEdges()) / graph.getNumberOfVertices() * 2;
    }

    static unsigned int getNumberOfSelfLoops(BaseGraphWithVertex const& graph)
    {
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

    static ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseUndirectedGraphWithVertex const& graph)
    {
        // A graph that is not connected (see isGraphConnected) consists of a set of connected components which are maximal connected subgraphs.

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

private:
    static void putEdgesToUnionFind(BaseUnionFindWithVertex & unionFind, Edges const& edges)
    {
        for(Edge const& edge : edges)
        {
            unionFind.connect(edge.first, edge.second);
        }
    }

    static void putGraphToUnionFind(BaseUnionFindWithVertex & unionFind, BaseGraphWithVertex const& graph)
    {
        putEdgesToUnionFind(unionFind, graph.getEdges());
    }
};

}
}
