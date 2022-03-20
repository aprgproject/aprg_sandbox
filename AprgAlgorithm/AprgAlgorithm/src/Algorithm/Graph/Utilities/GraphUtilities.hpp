#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
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
    using BaseUnionFindWithVertex = BaseUnionFind<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using ListOfEdges = typename GraphTypes<Vertex>::ListOfEdges;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    static bool isASimplePath(Path const& path)
    {
        // A simple path is one with no repeated vertices;
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

    static bool isATree(BaseGraphWithVertex const& graph)
    {
        // A tree is an acyclic connected graph.
        return !hasAnyCyclesOnGraph(graph) && isGraphConnected(graph);
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

    static bool isGraphConnected(BaseGraphWithVertex const& graph)    {
        // A graph is connected if there is a path from every vertex to every other vertex in the graph.

        bool result(true);        UnionFindUsingMap<Vertex> unionFind;
        putGraphToUnionFind(unionFind, graph);
        bool isFirst(true);
        Vertex commonRoot;
        for(Vertex const& vertex : graph.getVertices())
        {
            if(isFirst)
            {
                commonRoot = unionFind.getRoot(vertex);
                isFirst = false;
            }
            else if(commonRoot != unionFind.getRoot(vertex))
            {
                result = false;
                break;
            }
        }
        return result;
    }

    static bool isBipartite(BaseGraphWithVertex const& graph)
    {
        // A bipartite is a graph whose vertices we can divide into two sets
        // such that all edges connect a vertex in one set with a vertex in the other set.
        // So there is only one edge connecting both sets, and if that edge is removed the graph is no longer connected

        VertexToBoolMap isProcessedMap;
        VertexToBoolMap colorMap;
        Vertices vertices(graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            isProcessedMap[vertex] = false;
            colorMap[vertex] = false;
        }
        bool isTwoColorable(true);
        for(Vertex const& vertex : vertices)
        {
            if(!isProcessedMap.at(vertex))
            {
                checkIsBipartiteUsingDfs(graph, vertex, isProcessedMap, colorMap, isTwoColorable);
            }
            if(!isTwoColorable)
            {
                break;
            }
        }
        return isTwoColorable;
    }

    static unsigned int getDegreeAt(BaseGraphWithVertex const& graph, Vertex const& vertex)
    {
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

    static ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseGraphWithVertex const& graph)
    {
        // A graph that is not connected (see isGraphConnected) consists of a set of connected components which are maximal connected subgraphs.

        UnionFindUsingMap<Vertex> unionFind;
        putGraphToUnionFind(unionFind, graph);
        std::map<Vertex, Edges> rootToEdgeMap;
        for(Vertex const& vertex : graph.getVertices())
        {
            Vertex root(unionFind.getRoot(vertex));
            Vertices adjacentVertices(graph.getAdjacentVerticesAt(vertex));
            for(Vertex const& adjacentVertex : adjacentVertices)
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

    static void checkIsBipartiteUsingDfs(
            BaseGraphWithVertex const& graph,
            Vertex const& vertex,
            VertexToBoolMap & isProcessedMap,
            VertexToBoolMap & colorMap,
            bool & isTwoColorable)
    {
        isProcessedMap[vertex] = true;
        Vertices adjacentVertices(graph.getAdjacentVerticesAt(vertex));
        for(Vertex const& adjacentVertex : adjacentVertices)
        {
            if(!isProcessedMap.at(adjacentVertex))
            {
                colorMap[adjacentVertex] = !colorMap.at(vertex);
                checkIsBipartiteUsingDfs(graph, adjacentVertex, isProcessedMap, colorMap, isTwoColorable);
            }
            else if(colorMap.at(adjacentVertex) == colorMap.at(vertex))
            {
                isTwoColorable = false;
            }
            if(!isTwoColorable)
            {
                break;
            }
        }
    }
};

}

}
