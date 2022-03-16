#pragma once

#include <map>
#include <set>
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

    using SetOfVertices = std::set<Vertex>;
    struct EdgeInSet : public Edge
    {
        EdgeInSet(Vertex const& vertex1, Vertex const& vertex2)
            : Edge{vertex1, vertex2}
        {}

        bool operator<(EdgeInSet const& otherEdge) const
        {
            bool result(false);
            if(Edge::first != otherEdge.first)
            {
                result = Edge::first < otherEdge.first;
            }
            else
            {
                result = Edge::second < otherEdge.second;
            }
            return result;
        }
    };
    using SetOfEdges = std::set<EdgeInSet>;
};

}

}
