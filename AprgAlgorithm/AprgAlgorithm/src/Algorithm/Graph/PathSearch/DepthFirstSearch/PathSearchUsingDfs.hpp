#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithBfsAndDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class PathSearchUsingDfs : public BasePathSearchWithBfsAndDfs<Vertex>
{
public:    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

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
        traverseUsingDfs(startVertex);
    }

private:
    void traverseUsingDfs(Vertex const& vertex)
    {
        CheckableVerticesWithVertex & processedVertices(this->m_processedVertices);
        processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
        {
            if(processedVertices.isNotFound(adjacentVertex))
            {
                this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                traverseUsingDfs(adjacentVertex);
            }
        }
    }
};

}

}
