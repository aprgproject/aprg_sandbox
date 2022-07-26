#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
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
        // -> Euler path is possible in directed graph iff in each node, the indegree equals the outdegree.
        // -> or in one node, the indegree is one larger than the outdegree, in another node,
        // the outdegree is one larger than the indegree, and in all other nodes, the
        // indegree equals the outdegree
        return  areAllInDegreesEqualsOutDegrees();
    }

    bool hasEulerPath() const
    {
        // -> Euler path is possible in directed graph iff in each node, the indegree equals the outdegree.
        return hasAtLeastOneLesserAndGreaterInAndOutDegrees();
    }

    // An Euler circuit is a circuit that uses every edge in a graph with no repeats. Being a circuit, it must start and end at the same vertex.
    virtual Path getEulerCycle() const = 0;

    // An Euler path is a path that uses every edge in a graph with no repeats. Being a path, it does not have to return to the starting vertex.
    virtual Path getEulerPath() const = 0;

protected:

    Vertex getStartingVertexForEulerCycle() const
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

    bool areAllInDegreesEqualsOutDegrees() const
    {
        auto vertexToDegreesPairMap(GraphUtilities::getAllInDegreesAndOutDegrees<Vertex>(m_graph));
        bool result(true);
        for(auto const& vertexAndDegreesPair : vertexToDegreesPairMap)
        {
            unsigned int inDegree = vertexAndDegreesPair.second.first;
            unsigned int outDegree = vertexAndDegreesPair.second.second;
            result = inDegree == outDegree;
            if(!result)
            {
                break;
            }
        }
        return result;
    }

    bool hasAtLeastOneLesserAndGreaterInAndOutDegrees() const
    {
        auto vertexToDegreesPairMap(GraphUtilities::getAllInDegreesAndOutDegrees<Vertex>(m_graph));
        unsigned int numberOfLesser(0U);
        unsigned int numberOfGreater(0U);
        bool result(true);
        for(auto const& vertexAndDegreesPair : vertexToDegreesPairMap)
        {
            unsigned int inDegree = vertexAndDegreesPair.second.first;
            unsigned int outDegree = vertexAndDegreesPair.second.second;
            bool lesserByOne = inDegree+1 == outDegree;
            bool greaterByOne = inDegree == outDegree+1;
            numberOfLesser += lesserByOne ? 1 : 0;
            numberOfGreater += greaterByOne ? 1 : 0;
            result = inDegree == outDegree || (lesserByOne && numberOfLesser<=1) || (greaterByOne && numberOfGreater<=1);
            if(!result)
            {
                break;
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
};

}

}
