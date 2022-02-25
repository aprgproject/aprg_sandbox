#pragma once

#include <vector>

namespace alba
{

namespace algorithm
{

using Vertex = unsigned int;
using Vertices = std::vector<Vertex>;
using Path = std::vector<Vertex>;
using Paths = std::vector<Path>;

using Edge = std::pair<Vertex, Vertex>;
using Edges = std::vector<Edge>;
using ListOfEdges = std::vector<Edges>;

}

}
