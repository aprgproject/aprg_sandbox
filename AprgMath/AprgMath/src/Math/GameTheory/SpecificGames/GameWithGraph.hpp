#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

class GameWithGraph
{
public:

    using Vertex = UnsignedInteger;
    using Vertices = std::vector<UnsignedInteger>;
    using Graph = algorithm::BaseDirectedGraph<Vertex>;
    using VertexToGrundyNumberMap = std::map<Vertex, Vertex>;

    GameWithGraph(Graph const& graph);

    UnsignedInteger getGrundyNumberAt(Vertex const vertex);
    GameState getGameStateAt(Vertex const vertex);
    Vertex getOptimalNextVertexAt(Vertex const vertex);

private:
    Graph const& m_graph;
    VertexToGrundyNumberMap m_vertexToGrundyNumberMap; // dynamic programming
};

}

}
