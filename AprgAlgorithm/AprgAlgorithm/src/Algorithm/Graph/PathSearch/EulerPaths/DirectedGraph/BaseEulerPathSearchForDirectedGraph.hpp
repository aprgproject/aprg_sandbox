#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/Common/Utilities.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

#include <string>
namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseEulerPathSearchForDirectedGraph
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BaseEulerPathSearchForDirectedGraph(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    virtual ~BaseEulerPathSearchForDirectedGraph()
    {}

    bool hasEulerCycle() const
    {
        return hasEulerCycleForDirectedGraph(m_graph);
    }

    bool hasEulerPath() const
    {
        return hasEulerPathForDirectedGraph(m_graph);
    }

    // An Euler circuit is a circuit that uses every edge in a graph with no repeats. Being a circuit, it must start and end at the same vertex.
    virtual Path getEulerCycle() const = 0;

    // An Euler path is a path that uses every edge in a graph with no repeats. Being a path, it does not have to return to the starting vertex.
    virtual Path getEulerPath() const = 0;

protected:

    Vertex getStartingVertexForEulerCycle() const
    {
        Vertex result{};
        Vertices vertices(m_graph.getVertices());
        if(!vertices.empty())
        {
            result = vertices.front();
        }
        return result;
    }

    Vertex getStartingVertexForEulerPath() const
    {
        Vertex result{};
        Vertices vertices(m_graph.getVertices());
        if(!vertices.empty())
        {
            result = vertices.front();
            for(Vertex const& vertex : vertices)
            {
                if((GraphUtilities::getDegreeAt(m_graph, vertex) % 2) == 1)
                {
                    result = vertex;
                    break;
                }
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
};

}

}
