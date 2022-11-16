#pragma once

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename EdgeType>
EdgeType createSortedEdge(Vertex const& vertex1, Vertex const& vertex2)
{
    if(vertex1 <= vertex2)
    {
        return EdgeType(vertex1, vertex2);
    }
    else
    {
        return EdgeType(vertex2, vertex1);
    }
}

template <typename Vertex, typename Weight, typename EdgeType>
EdgeType createSortedEdgeOrderedByWeight(Vertex const& vertex1, Vertex const& vertex2, Weight const& weight)
{
    if(vertex1 <= vertex2)
    {
        return EdgeType(vertex1, vertex2, weight);
    }
    else
    {
        return EdgeType(vertex2, vertex1, weight);
    }
}

}

}
