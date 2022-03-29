#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>

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
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using ProcessedVerticesWithVertex = ProcessedVertices<Vertex>;

    enum class TraverseOrder
    {
        PreOrder,
        PostOrder,
        ReversePostOrder,
    };

    VertexOrderingUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Vertices traverseAndGetVertices(TraverseOrder const traverseOrder)
    {
        Vertices traversedVertices;
        traverseStartingFromAllVertices(traversedVertices, traverseOrder);
        reverseVerticesIfNeeded(traversedVertices, traverseOrder);
        return traversedVertices;
    }

    Vertices getVerticesInTopologicalOrder()
    {
        //Useful on determining path that checks prerequisites
        return traverseAndGetVertices(TraverseOrder::ReversePostOrder);
    }

private:

    void clear()
    {
        m_processedVertices.clear();
    }

    void reverseVerticesIfNeeded(Vertices & traversedVertices, TraverseOrder const traverseOrder) const
    {
        if(TraverseOrder::ReversePostOrder == traverseOrder)
        {
            Vertices reversedVertices(traversedVertices.crbegin(), traversedVertices.crend());
            traversedVertices = reversedVertices;
        }
    }

    void traverseStartingFromAllVertices(Vertices & traversedVertices, TraverseOrder const traverseOrder)
    {
        clear();
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotProcessed(vertex) && !m_graph.getAdjacentVerticesAt(vertex).empty())
            {
                traverseAt(traversedVertices, traverseOrder, vertex);
            }
        }
    }

    void traverseAt(Vertices & traversedVertices, TraverseOrder const traverseOrder, Vertex const& startVertex)
    {
        switch(traverseOrder)
        {
        case TraverseOrder::PreOrder:
        {
            traversePreOrderAt(traversedVertices, startVertex);
            break;
        }
        case TraverseOrder::PostOrder:
        {
            traversePostOrderAt(traversedVertices, startVertex);
            break;
        }
        case TraverseOrder::ReversePostOrder:
        {
            traverseReversePostOrderAt(traversedVertices, startVertex);
            break;
        }
        }
    }

    void traversePreOrderAt(Vertices & traversedVertices, Vertex const& startVertex)
    {
        traversedVertices.emplace_back(startVertex);

        m_processedVertices.putVertexAsProcessed(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traversePreOrderAt(traversedVertices, adjacentVertex);
            }
        }
    }

    void traversePostOrderAt(Vertices & traversedVertices, Vertex const& startVertex)
    {
        m_processedVertices.putVertexAsProcessed(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traversePostOrderAt(traversedVertices, adjacentVertex);
            }
        }

        traversedVertices.emplace_back(startVertex);
    }

    void traverseReversePostOrderAt(Vertices & traversedVertices, Vertex const& startVertex)
    {
        m_processedVertices.putVertexAsProcessed(startVertex);

        // Traversing adjacents in order results in higher vertices to be first in the list after reversal
        // Reverse the traversal of adjacents is not fine either
        // Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(startVertex));
        // std::for_each(adjacentVertices.crbegin(), adjacentVertices.crend(), [&](Vertex const& adjacentVertex)

        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traverseReversePostOrderAt(traversedVertices, adjacentVertex);
            }
        }

        traversedVertices.emplace_back(startVertex);
    }

    BaseGraphWithVertex const& m_graph;
    ProcessedVerticesWithVertex m_processedVertices;
};

}

}
