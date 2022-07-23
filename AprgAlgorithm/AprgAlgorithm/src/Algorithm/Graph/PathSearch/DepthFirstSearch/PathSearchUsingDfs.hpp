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
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
        , b_startVertices(BaseClass::m_startVertices)
        , b_processedVertices(BaseClass::m_processedVertices)
        , b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap)
        , b_vertexToDistanceToStartMap(BaseClass::m_vertexToDistanceToStartMap)
    {
        reinitializeStartingFrom({startVertex});
    }

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
        , b_startVertices(BaseClass::m_startVertices)
        , b_processedVertices(BaseClass::m_processedVertices)
        , b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap)
        , b_vertexToDistanceToStartMap(BaseClass::m_vertexToDistanceToStartMap)
    {
        reinitializeStartingFrom(startVertices);
    }

    Path getOrderedPathTo(Vertex const& endVertex) const
    {
        return this->getPathTo(endVertex);
    }

    void reinitializeStartingFrom(Vertices const& startVertices) override
    {
        this->clear();
        this->initializeWithStartVertices(startVertices);
        for(Vertex const& startVertex : b_startVertices.getVertices())  // to maintain order, get the vertices in start vertices (because its sorted)
        {
            traverseUsingDfs(startVertex);
        }
    }

private:
    void traverseUsingDfs(Vertex const& vertex)
    {
        b_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : b_graph.getAdjacentVerticesAt(vertex))
        {
            if(b_processedVertices.isNotFound(adjacentVertex))
            {
                b_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                b_vertexToDistanceToStartMap[adjacentVertex] = b_vertexToDistanceToStartMap.at(vertex)+1;
                traverseUsingDfs(adjacentVertex);
            }
        }
    }
    BaseGraphWithVertex const& b_graph;
    CheckableVerticesWithVertex & b_startVertices;
    CheckableVerticesWithVertex & b_processedVertices;
    VertexToVertexMap & b_vertexToPreviousVertexMap;
    VertexToUnsignedIntMap & b_vertexToDistanceToStartMap;
};

// Proposition: DFS marks all vertices connected to s in time proportional to the sum of their degrees
// Proof:
// -> If w is marked, then w is connected to s
// -> If w is connected to s, then w is marked.
// --> If w is unmarked, then consider last edge on a path from s to w that goes from a marked vertex to an unmarked one.
// Proof (running time):
// -> Each vertex connected to s is visited once

// Other analysis:
// The time complexity of depth-first search is O(n+m) where n is the number of nodes and m is the number of edges,
// because the algorithm processes each node and edge once.

}

}
