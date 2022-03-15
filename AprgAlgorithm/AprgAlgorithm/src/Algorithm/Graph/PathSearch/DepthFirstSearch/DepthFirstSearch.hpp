#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class DepthFirstSearch : public BasePathSearch<Vertex>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseClass = BasePathSearch<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    DepthFirstSearch(BaseUndirectedGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        reinitializeStartingFrom(startVertex);
    }

    Path getOrderedPathTo(Vertex const& endVertex) const
    {
        return BaseClass::getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertex const& startVertex) override
    {
        BaseClass::clear();
        BaseClass::m_startVertex = startVertex;
        continueTraversal(startVertex);
    }

private:
    void continueTraversal(Vertex const& vertex)
    {
        BaseClass::m_isProcessed[vertex] = true;
        Vertices adjacentVertices(BaseClass::m_graph.getAdjacentVerticesAt(vertex));
        for(Vertex const& adjacentVertex : adjacentVertices)
        {
            if(!BaseClass::m_isProcessed.at(adjacentVertex))
            {
                BaseClass::m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                continueTraversal(adjacentVertex);
            }
        }
    }
};

}
}