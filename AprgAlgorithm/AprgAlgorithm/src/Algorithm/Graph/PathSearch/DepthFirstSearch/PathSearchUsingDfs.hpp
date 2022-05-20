#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithBfsAndDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class PathSearchUsingDfs : public BasePathSearchWithBfsAndDfs<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph)
    {
        reinitializeStartingFrom({startVertex});
    }

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseClass(graph)
    {
        reinitializeStartingFrom(startVertices);
    }

    Path getOrderedPathTo(Vertex const& endVertex) const    {
        return this->getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertices const& startVertices) override
    {
        this->clear();
        this->addStartVertices(startVertices);
        for(Vertex const& startVertex : this->m_startVertices.getVertices())  // to maintain order, get the vertices in start vertices
        {
            traverseUsingDfs(startVertex);
        }
    }

private:    void traverseUsingDfs(Vertex const& vertex)
    {
        CheckableVerticesWithVertex & processedVertices(this->m_processedVertices);
        processedVertices.putVertex(vertex);        for(Vertex const& adjacentVertex : this->m_graph.getAdjacentVerticesAt(vertex))
        {
            if(processedVertices.isNotFound(adjacentVertex))
            {
                this->m_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                traverseUsingDfs(adjacentVertex);
            }
        }
    }
};

// Proposition: DFS marks all vertices connected to s in time proportional to the sum of their degrees
// Proof:
// -> If w is marked, then w is connected to s
// -> If w is connected to s, then w is marked.
// --> If w is unmarked, then consider last edge on a path from s to w that goes from a marked vertex to an unmarked one.
// Proof (running time):
// -> Each vertex connected to s is visited once

}

}
