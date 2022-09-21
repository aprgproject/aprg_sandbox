#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/Common/Utilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <string>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseEulerPathSearchForUndirectedGraph
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BaseEulerPathSearchForUndirectedGraph(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    virtual ~BaseEulerPathSearchForUndirectedGraph()
    {}

    bool hasEulerCycle() const
    {
        return hasEulerCycleForUndirectedGraph(m_graph);
    }

    bool hasEulerPath() const
    {
        return hasEulerPathForUndirectedGraph(m_graph);
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

    BaseUndirectedGraphWithVertex const& m_graph;
};

}

}
