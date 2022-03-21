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
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

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
        VertexToBoolMap & isProcessedMap(this->m_isProcessedMap);
        isProcessedMap[vertex] = true;
        for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
        {
            if(this->isNotProcessed(adjacentVertex))
            {
                this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                continueTraversal(adjacentVertex);
            }
        }
    }
};

}

}
