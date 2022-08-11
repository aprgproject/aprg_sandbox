#pragma once

#include <ostream>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Vertex> using VertexWithBool = std::pair<Vertex, bool>;

template <typename Vertex>
std::ostream & operator<<(std::ostream & out, VertexWithBool<Vertex> const& vertexWithDuplicate)
{
    out << "(" << vertexWithDuplicate.first << ", " << vertexWithDuplicate.second << ")";
    return out;
}

}

}
