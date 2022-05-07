#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba
{

namespace algorithm
{

namespace GraphUtilities
{

template <typename Vertex> bool isASimplePath(typename GraphTypes<Vertex>::Path const& path);
template <typename Vertex> bool isACycle(typename GraphTypes<Vertex>::Path const& path);
template <typename Vertex> bool isASimpleCycle(typename GraphTypes<Vertex>::Path const& path);
template <typename Vertex> bool isDirectedAcyclicGraph(BaseGraph<Vertex> const& graph);
template <typename Vertex> bool hasAnyCyclesOnGraph(BaseGraph<Vertex> const& graph);
template <typename Vertex> bool isATree(BaseUndirectedGraph<Vertex> const& graph);
template <typename Vertex> bool isAForest(BaseUndirectedGraph<Vertex> const& graph);
template <typename Vertex> bool isASpanningTree(
        BaseUndirectedGraph<Vertex> const& mainGraph,
        BaseUndirectedGraph<Vertex> const& subGraphToCheck);
template <typename Vertex> bool isASpanningForest(
        BaseUndirectedGraph<Vertex> const& mainGraph,
        BaseUndirectedGraph<Vertex> const& subGraphToCheck);
template <typename Vertex> bool isGraphConnected(BaseUndirectedGraph<Vertex> const& graph);
template <typename Vertex> bool isGraphStronglyConnected(BaseDirectedGraph<Vertex> const& graph);
template <typename Vertex> bool isBipartite(BaseUndirectedGraph<Vertex> const& graph);
template <typename EdgeWeightedGraphType> bool isFlowNetwork(EdgeWeightedGraphType const& graph);
template <typename Vertex> unsigned int getDegreeAt(BaseGraph<Vertex> const& graph, Vertex const& vertex);
template <typename Vertex> unsigned int getMaxDegree(BaseGraph<Vertex> const& graph);
template <typename Vertex> double getAverageDegree(BaseGraph<Vertex> const& graph);template <typename Vertex> unsigned int getNumberOfSelfLoops(BaseGraph<Vertex> const& graph);

template <typename Vertex, typename Weight, typename EdgeWeightedGraphType>
typename GraphTypes<Vertex>::Path getCriticalPath(        EdgeWeightedGraphType const& graph,
        Vertex const& sourceVertex,
        Vertex const& destinationVertex);

template <typename Vertex> typename GraphTypes<Vertex>::ListOfEdges getEdgesOfMaximalConnectedSubgraphs(
        BaseUndirectedGraph<Vertex> const& graph);

}

}

}
