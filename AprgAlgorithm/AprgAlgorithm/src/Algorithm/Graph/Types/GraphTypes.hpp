#pragma once

#include <deque>
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

template <typename Vertex>
struct GraphTypes
{
    // Vertex
    using Vertices = std::vector<Vertex>;
    using DequeOfVertices = std::deque<Vertex>;
    using SetOfVertices = std::set<Vertex>;

    //Edge
    using Edge = std::pair<Vertex, Vertex>;
    using Edges = std::vector<Edge>;
    using DequeOfEdges = std::deque<Edge>;
    using SetOfEdges = std::set<Edge>;
    using ListOfEdges = std::vector<Edges>;

    //Path
    using Path = std::vector<Vertex>;
    using Paths = std::vector<Path>;

    //Complicated types
    using VertexToUnsignedIntMap = std::map<Vertex, unsigned int>;
    using VertexToVertexMap = std::map<Vertex, Vertex>;
};

template <typename Vertex, typename Weight>
struct GraphTypesWithWeights
{
    struct VertexOrderedByWeight
    {
        VertexOrderedByWeight(Vertex const& vertexParameter, Weight const& weightParameter)
            : vertex(vertexParameter)
            , weight(weightParameter)
        {}

        bool operator<(VertexOrderedByWeight const& otherVertex) const
        {
            return weight < otherVertex.weight;
        }

        bool operator>(VertexOrderedByWeight const& otherVertex) const
        {
            return weight > otherVertex.weight;
        }

        bool operator==(VertexOrderedByWeight const& otherVertex) const
        {
            return weight == otherVertex.weight;
        }        Vertex vertex;
        Weight weight;
    };
    using VerticesWithWeight = std::vector<VertexOrderedByWeight>;
    using SetOfVerticesWithWeight = std::set<VertexOrderedByWeight>;


    struct EdgeOrderedByWeight : public GraphTypes<Vertex>::Edge
    {
        using Edge = typename GraphTypes<Vertex>::Edge;

        EdgeOrderedByWeight()
            : Edge{}
            , weight{}
        {}

        EdgeOrderedByWeight(Vertex const& vertex1, Vertex const& vertex2, Weight const& weightParameter)
            : Edge{vertex1, vertex2}
            , weight(weightParameter)
        {}

        bool operator<(EdgeOrderedByWeight const& otherEdge) const
        {
            return weight < otherEdge.weight;
        }

        bool operator>(EdgeOrderedByWeight const& otherEdge) const
        {
            return weight > otherEdge.weight;
        }

        bool operator==(EdgeOrderedByWeight const& otherEdge) const
        {
            return weight == otherEdge.weight;
        }
        Weight weight;
    };
    using EdgesWithWeight = std::vector<EdgeOrderedByWeight>;
    using SetOfEdgesWithWeight = std::set<EdgeOrderedByWeight>;

    //Complicated Types
    using VertexToEdgeOrderedByWeightMap = std::map<Vertex, EdgeOrderedByWeight>;
};

}
}