#pragma once

#include <Algorithm/Graph/GraphTypes.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/BaseUnionFind.hpp>

namespace alba
{
namespace algorithm
{

bool isSimplePath(Path const& path);
bool isCycle(Path const& path, BaseUndirectedGraph const& graph);
bool isSimpleCycle(Path const& path, BaseUndirectedGraph const& graph);
bool isATree(BaseUndirectedGraph const& graph);
bool hasAnyCyclesOnGraph(BaseUndirectedGraph const& graph);
bool isGraphConnected(BaseUndirectedGraph const& graph);

unsigned int getDegreeAt(BaseUndirectedGraph const& graph, Vertex const vertex);
unsigned int getMaxDegree(BaseUndirectedGraph const& graph);
double getAverageDegree(BaseUndirectedGraph const& graph);
unsigned int getNumberOfSelfLoops(BaseUndirectedGraph const& graph);

ListOfEdges getEdgesOfMaximalConnectedSubgraphs(BaseUndirectedGraph const& graph);

}

}