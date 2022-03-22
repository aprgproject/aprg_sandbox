#pragma once

#include <map>
#include <set>
#include <vector>

namespace alba
{

namespace algorithm
{

enum class GraphDirectionType
{
    Undirected,
    Directed
};

template<typename Vertex>
struct GraphTypes
{
    // Vertex
    using Vertices = std::vector<Vertex>;
    using SetOfVertices = std::set<Vertex>;

    //Edge
    using Edge = std::pair<Vertex, Vertex>;
    using Edges = std::vector<Edge>;
    using ListOfEdges = std::vector<Edges>;
    struct EdgeInSet : public Edge
    {
        EdgeInSet(Vertex const& vertex1, Vertex const& vertex2)
            : Edge{vertex1, vertex2}
        {}

        bool operator<(EdgeInSet const& otherEdge) const        {
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

    //Path
    using Path = std::vector<Vertex>;
    using Paths = std::vector<Path>;

    //Complicated types
    using VertexToUnsignedIntMap = std::map<Vertex, unsigned int>;
    using VertexToVertexMap = std::map<Vertex, Vertex>;

};

}

}