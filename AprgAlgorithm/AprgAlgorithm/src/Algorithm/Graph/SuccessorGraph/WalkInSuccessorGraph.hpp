#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class WalkInSuccessorGraph
{
public:

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexAndCountPair = std::pair<Vertex, unsigned int>;
    using VertexAndCountPairToVertexMap = std::map<VertexAndCountPair, Vertex>;

    WalkInSuccessorGraph(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    bool isAtTheEnd(Vertex const& vertex) const
    {
        return m_graph.getAdjacentVerticesAt(vertex).empty();
    }

    Vertex walk(Vertex const& start, unsigned int const walkCount)
    {
        return walkInternal(start, walkCount);
    }

private:

    Vertex walkInternal(Vertex const& vertex, unsigned int const walkCount)
    {
        Vertex result(vertex);
        if(walkCount != 0)
        {
            auto it = m_walkToDestinationMap.find({vertex, walkCount});
            if(it != m_walkToDestinationMap.cend())
            {
                result = it->second;
            }
            else
            {
                if(walkCount > 1)
                {
                    unsigned int halfWalk = walkCount/2;
                    result = walkInternal(walkInternal(vertex, walkCount-halfWalk), halfWalk);
                }
                else if(walkCount == 1)
                {
                    Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(vertex)); // should be one because its a successor graph
                    if(!adjacentVertices.empty())
                    {
                        result = adjacentVertices.front();
                    }
                }
                if(walkCount%2 == 0 || walkCount == 1)
                {
                    m_walkToDestinationMap.emplace(VertexAndCountPair{vertex, walkCount}, result);
                }
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
    VertexAndCountPairToVertexMap m_walkToDestinationMap; // dynamic programming
};

}

}
