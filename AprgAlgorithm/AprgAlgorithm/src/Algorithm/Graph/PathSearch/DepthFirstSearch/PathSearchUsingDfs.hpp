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
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)    {
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
        traverseUsingDfs(startVertex);
    }

private:
    void traverseUsingDfs(Vertex const& vertex)
    {
        SetOfVertices & processedVertices(this->m_processedVertices);
        processedVertices.emplace(vertex);
        for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
        {
            if(this->isNotProcessed(adjacentVertex))
            {
                this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                traverseUsingDfs(adjacentVertex);
            }
        }
    }};

}

}
