#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class VertexOrderingUsingDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    enum class TraverseOrder
    {
        PreOrder,
        PostOrder,
        ReversePostOrder,
    };

    VertexOrderingUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_isProcessedMap()
    {}

    Path traverseAndGetPath(TraverseOrder const traverseOrder)
    {
        Path traversedPath;
        traverseStartingFromAllVertices(traversedPath, traverseOrder);
        reversePathIfNeeded(traversedPath, traverseOrder);
        return traversedPath;
    }

    Path getPathInTopologicalOrder()
    {
        //Useful on determining path that checks prerequisites
        return traverseAndGetPath(TraverseOrder::ReversePostOrder);
    }

private:

    bool isNotProcessed(Vertex const& vertex) const
    {
        auto it = m_isProcessedMap.find(vertex);
        return it == m_isProcessedMap.cend() || !it->second;
    }

    void clear()
    {
        m_isProcessedMap.clear();
    }

    void reversePathIfNeeded(Path & traversedPath, TraverseOrder const traverseOrder) const
    {
        if(TraverseOrder::ReversePostOrder == traverseOrder)
        {
            Path reversedPath(traversedPath.crbegin(), traversedPath.crend());
            traversedPath = reversedPath;
        }
    }

    void traverseStartingFromAllVertices(Path & traversedPath, TraverseOrder const traverseOrder)
    {
        clear();
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(isNotProcessed(vertex) && !m_graph.getAdjacentVerticesAt(vertex).empty())
            {
                traverseAt(traversedPath, traverseOrder, vertex);
            }
        }
    }

    void traverseAt(Path & traversedPath, TraverseOrder const traverseOrder, Vertex const& startVertex)
    {
        switch(traverseOrder)
        {
        case TraverseOrder::PreOrder:
        {
            traversePreOrderAt(traversedPath, startVertex);
            break;
        }
        case TraverseOrder::PostOrder:
        {
            traversePostOrderAt(traversedPath, startVertex);
            break;
        }
        case TraverseOrder::ReversePostOrder:
        {
            traverseReversePostOrderAt(traversedPath, startVertex);
            break;
        }
        }
    }

    void traversePreOrderAt(Path & traversedPath, Vertex const& startVertex)
    {
        traversedPath.emplace_back(startVertex);

        m_isProcessedMap[startVertex] = true;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                traversePreOrderAt(traversedPath, adjacentVertex);
            }
        }
    }

    void traversePostOrderAt(Path & traversedPath, Vertex const& startVertex)
    {
        m_isProcessedMap[startVertex] = true;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                traversePostOrderAt(traversedPath, adjacentVertex);
            }
        }

        traversedPath.emplace_back(startVertex);
    }

    void traverseReversePostOrderAt(Path & traversedPath, Vertex const& startVertex)
    {
        m_isProcessedMap[startVertex] = true;

        // Traversing adjacents in order results in higher vertices to be first in the list after reversal
        // Reverse the traversal of adjacents is not fine either
        // Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(startVertex));
        // std::for_each(adjacentVertices.crbegin(), adjacentVertices.crend(), [&](Vertex const& adjacentVertex)

        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                traverseReversePostOrderAt(traversedPath, adjacentVertex);
            }
        }

        traversedPath.emplace_back(startVertex);
    }

    BaseGraphWithVertex const& m_graph;
    VertexToBoolMap m_isProcessedMap;
};

}

}
