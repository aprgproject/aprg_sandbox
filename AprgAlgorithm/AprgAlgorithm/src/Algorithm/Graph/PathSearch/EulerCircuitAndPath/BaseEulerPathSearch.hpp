#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseEulerPathSearch
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BaseEulerPathSearch(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    bool hasEulerCircuit() const
    {
        // Euler path is possible iff graph is connected and all vertices have even degree
        // A graph will contain an Euler path if it contains at most two vertices of odd degree.
        return GraphUtilities::isGraphConnected(m_graph) && areAllDegreesEven();
    }

    bool hasEulerPath() const
    {
        // A graph will contain an Euler path if it contains at most two vertices of odd degree.
        return GraphUtilities::isGraphConnected(m_graph) && isAtMostTwoVerticesHaveOddDegrees();
    }

    // An Euler circuit is a circuit that uses every edge in a graph with no repeats. Being a circuit, it must start and end at the same vertex.
    virtual Path getEulerCircuit() const = 0;

    // An Euler path is a path that uses every edge in a graph with no repeats. Being a path, it does not have to return to the starting vertex.
    virtual Path getEulerPath() const = 0;

protected:

    Vertex getStartingVertexForEulerCircuit() const
    {
        return m_graph.getVertices().front();
    }

    Vertex getStartingVertexForEulerPath() const
    {
        Vertices vertices(m_graph.getVertices());
        Vertex result(vertices.front());
        for(Vertex const& vertex : vertices)
        {
            if((GraphUtilities::getDegreeAt(m_graph, vertex) % 2) == 1)
            {
                result = vertex;
                break;
            }
        }
        return result;
    }

    bool areAllDegreesEven() const
    {
        bool result(true);
        for(Vertex const& vertex : m_graph.getVertices())
        {
            result = (GraphUtilities::getDegreeAt(m_graph, vertex) % 2) == 0;
            if(!result)
            {
                break;
            }
        }
        return result;
    }

    bool isAtMostTwoVerticesHaveOddDegrees() const
    {
        unsigned int countOfOdd(0U);
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if((GraphUtilities::getDegreeAt(m_graph, vertex) % 2) == 1)
            {
                countOfOdd++;
            }
            if(countOfOdd > 2)
            {
                break;
            }
        }
        return countOfOdd <= 2;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
};

}

}
