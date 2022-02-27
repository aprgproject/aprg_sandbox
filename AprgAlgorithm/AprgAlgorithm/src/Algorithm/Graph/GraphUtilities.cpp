#include "GraphUtilities.hpp"

#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

#include <algorithm>
#include <set>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace // utilities
{

void putEdgesToUnionFind(BaseUnionFind<Vertex> & unionFind, Edges const& edges)
{
    for(Edge const& edge : edges)
    {
        unionFind.connect(edge.first, edge.second);
    }
}

void putGraphToUnionFind(BaseUnionFind<Vertex> & unionFind, BaseUndirectedGraph const& graph)
{
    putEdgesToUnionFind(unionFind, graph.getEdges());
}

void checkIsBipartiteUsingDfs(
        BaseUndirectedGraph const& graph,
        Vertex const vertex,
        VertexToBoolMap & isProcessedMap,
        VertexToBoolMap & colorMap,
        bool & isTwoColorable)
{
    isProcessedMap[vertex] = true;
    Vertices adjacentVertices(graph.getAdjacentVerticesAt(vertex));
    for(Vertex const adjacentVertex : adjacentVertices)
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

}


bool isASimplePath(Path const& path)
{
    // A simple path is one with no repeated vertices;
    set<Vertex> uniqueVertices;
    copy(path.cbegin(), path.cend(), inserter(uniqueVertices, uniqueVertices.cbegin()));
    return uniqueVertices.size() == path.size();
}

bool isACycle(Path const& path)
{
    // A cycle is a path with at least one edge whose first and last vertices are the same.
    bool result(false);
    if(!path.empty())
    {
        Vertex first(path.front());
        Vertex last(path.back());
        result = first == last;
    }
    return result;
}

bool isASimpleCycle(Path const& path)
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

bool isATree(BaseUndirectedGraph const& graph)
{
    // A tree is an acyclic connected graph.
    return !hasAnyCyclesOnGraph(graph) && isGraphConnected(graph);
}

bool hasAnyCyclesOnGraph(BaseUndirectedGraph const& graph)
{
    bool result(false);
    Edges edges(graph.getEdges());
    for(unsigned int i=0; i<edges.size(); i++)
    {
        Edge removedEdge(edges.at(i));
        Edges edgesWithoutOneEdge(edges);
        edgesWithoutOneEdge.erase(edgesWithoutOneEdge.cbegin()+i);
        UnionFindUsingMap<Vertex> unionFind;
        putEdgesToUnionFind(unionFind, edgesWithoutOneEdge);
        if(unionFind.isConnected(removedEdge.first, removedEdge.second))
        {
            result = true;
            break;
        }
    }
    return result;
}

bool isGraphConnected(BaseUndirectedGraph const& graph)
{
    // A graph is connected if there is a path from every vertex to every other vertex in the graph.

    bool result(true);
    UnionFindUsingMap<Vertex> unionFind;
    putGraphToUnionFind(unionFind, graph);
    bool isFirst(true);
    Vertex commonRoot;
    for(Vertex const vertex : graph.getVertices())
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

bool isBipartite(BaseUndirectedGraph const& graph)
{
    // A bipartite is a graph whose vertices we can divide into two sets
    // such that all edges connect a vertex in one set with a vertex in the other set.
    // So there is only one edge connecting both sets, and if that edge is removed the graph is no longer connected

    VertexToBoolMap isProcessedMap;
    VertexToBoolMap colorMap;
    Vertices vertices(graph.getVertices());
    for(Vertex const vertex : vertices)
    {
        isProcessedMap[vertex] = false;
        colorMap[vertex] = false;
    }
    bool isTwoColorable(true);
    for(Vertex const vertex : vertices)
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

unsigned int getDegreeAt(
        BaseUndirectedGraph const& graph,
        Vertex const vertex)
{
    return graph.getAdjacentVerticesAt(vertex).size();
}

unsigned int getMaxDegree(
        BaseUndirectedGraph const& graph)
{
    unsigned int result(0);
    for(Vertex const vertex : graph.getVertices())
    {
        result = std::max(result, getDegreeAt(graph, vertex));
    }
    return result;
}

double getAverageDegree(
        BaseUndirectedGraph const& graph)
{
    return static_cast<double>(graph.getNumberOfEdges()) / graph.getNumberOfVertices() * 2;
}

unsigned int getNumberOfSelfLoops(
        BaseUndirectedGraph const& graph)
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

ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseUndirectedGraph const& graph)
{
    // A graph that is not connected (see isGraphConnected) consists of a set of connected components which are maximal connected subgraphs.

    UnionFindUsingMap<Vertex> unionFind;
    putGraphToUnionFind(unionFind, graph);
    map<Vertex, Edges> rootToEdgeMap;
    for(Vertex const vertex : graph.getVertices())
    {
        Vertex root(unionFind.getRoot(vertex));
        Vertices adjacentVertices(graph.getAdjacentVerticesAt(vertex));
        for(Vertex const adjacentVertex : adjacentVertices)
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
