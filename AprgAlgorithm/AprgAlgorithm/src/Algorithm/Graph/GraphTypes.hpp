#pragma once

#include <map>
#include <vector>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
struct GraphTypes
{
    using Vertices = std::vector<Vertex>;
    using Path = std::vector<Vertex>;
    using Paths = std::vector<Path>;

    using Edge = std::pair<Vertex, Vertex>;
    using Edges = std::vector<Edge>;
    using ListOfEdges = std::vector<Edges>;

    using VertexToUnsignedIntMap = std::map<Vertex, unsigned int>;
    using VertexToBoolMap = std::map<Vertex, bool>;
    using VertexToVertexMap = std::map<Vertex, Vertex>;
};

}
}