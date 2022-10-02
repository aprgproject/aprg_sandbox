#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

class GrundyNumberOfGraph
{
public:
    // We will focus on two-player games that do not contain random elements.
    // Our goal is to find a strategy that we can follow to win the game no matter what the opponent does, if such a strategy exists.

    using Vertex = UnsignedInteger;
    using Vertices = std::vector<UnsignedInteger>;
    using Graph = algorithm::BaseDirectedGraph<Vertex>;
    using VertexToGrundyNumberMap = std::map<Vertex, Vertex>;

    GrundyNumberOfGraph(Graph const& graph);

    UnsignedInteger getGrundyNumberAt(Vertex const vertex);
    GameState getGameStateAt(Vertex const vertex);
    Vertex getOptimalNextVertexAt(Vertex const vertex);

private:
    Graph const& m_graph;
    VertexToGrundyNumberMap m_vertexToGrundyNumberMap; // dynamic programming
};

}

}
