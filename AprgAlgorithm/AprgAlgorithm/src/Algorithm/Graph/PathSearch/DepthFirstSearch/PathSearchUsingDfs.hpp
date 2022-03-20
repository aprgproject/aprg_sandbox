#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class PathSearchUsingDfs : public BasePathSearch<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearch<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        reinitializeStartingFrom(startVertex);
    }

    Path getOrderedPathTo(Vertex const& endVertex) const
    {
        return this->getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertex const& startVertex) override
    {
        this->clear();
        this->m_startVertex = startVertex;
        continueTraversal(startVertex);
    }

private:
    void continueTraversal(Vertex const& vertex)
    {
        this->m_isProcessed[vertex] = true;
        Vertices adjacentVertices(this->m_graph.getAdjacentVerticesAt(vertex));
        for(Vertex const& adjacentVertex : adjacentVertices)
        {
            if(!this->m_isProcessed.at(adjacentVertex))
            {
                this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                continueTraversal(adjacentVertex);
            }
        }
    }
};

}

}
