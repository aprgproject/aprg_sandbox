#pragma once

#include <Common/Print/AlbaPrintFunctions.hpp>

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
    struct EdgeWithVertexComparison : public Edge
    {
        EdgeWithVertexComparison(Vertex const& vertex1, Vertex const& vertex2)
            : Edge{vertex1, vertex2}
        {}

        bool operator<(EdgeWithVertexComparison const& otherEdge) const
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
    using SetOfEdges = std::set<EdgeWithVertexComparison>;

    //Path
    using Path = std::vector<Vertex>;
    using Paths = std::vector<Path>;

    //Complicated types
    using VertexToUnsignedIntMap = std::map<Vertex, unsigned int>;
    using VertexToVertexMap = std::map<Vertex, Vertex>;
};

template<typename Vertex, typename Weight>
struct GraphTypesWithWeights
{
    struct VertexWithWeight
    {
        VertexWithWeight(Vertex const& vertexParameter, Weight const& weightParameter)
            : vertex(vertexParameter)
            , weight(weightParameter)
        {}

        bool operator<(VertexWithWeight const& otherVertex) const
        {
            return weight < otherVertex.weight;
        }

        bool operator>(VertexWithWeight const& otherVertex) const
        {
            return weight > otherVertex.weight;
        }

        bool operator==(VertexWithWeight const& otherVertex) const
        {
            return weight == otherVertex.weight;
        }
        Vertex vertex;
        Weight weight;
    };
    using SetOfVerticesWithWeight = std::set<VertexWithWeight>;


    struct EdgeWithWeight : public GraphTypes<Vertex>::Edge
    {
        using Edge = typename GraphTypes<Vertex>::Edge;

        EdgeWithWeight()
            : Edge{}
            , weight{}
        {}

        EdgeWithWeight(Vertex const& vertex1, Vertex const& vertex2, Weight const& weightParameter)
            : Edge{vertex1, vertex2}
            , weight(weightParameter)
        {}

        bool operator<(EdgeWithWeight const& otherEdge) const
        {
            return weight < otherEdge.weight;
        }

        bool operator>(EdgeWithWeight const& otherEdge) const
        {
            return weight > otherEdge.weight;
        }

        bool operator==(EdgeWithWeight const& otherEdge) const
        {
            return weight == otherEdge.weight;
        }

        Weight weight;
    };
    using EdgesWithWeight = std::vector<EdgeWithWeight>;
    using SetOfEdgesWithWeight = std::set<EdgeWithWeight>;
};

}

}
