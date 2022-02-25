#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/BaseUnionFind.hpp>
namespace alba
{
namespace algorithm{

bool isASimplePath(Path const& path);
bool isACycle(Path const& path);
bool isASimpleCycle(Path const& path);
bool isATree(BaseUndirectedGraph const& graph);
bool hasAnyCyclesOnGraph(BaseUndirectedGraph const& graph);
bool isGraphConnected(BaseUndirectedGraph const& graph);
unsigned int getDegreeAt(BaseUndirectedGraph const& graph, Vertex const vertex);
unsigned int getMaxDegree(BaseUndirectedGraph const& graph);
double getAverageDegree(BaseUndirectedGraph const& graph);unsigned int getNumberOfSelfLoops(BaseUndirectedGraph const& graph);

ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseUndirectedGraph const& graph);

}

}