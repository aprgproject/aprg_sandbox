#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class VertexOrderingUsingDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    enum class TraverseOrder
    {
        PreOrder, // order: DFS traversal order (not really useful)
        PostOrder, // order: dependent vertices are first in the list (edge might not exist -> not useful)
        ReversePostOrder, // order: dependent vertices are last in the list (topological sort)
    };

    VertexOrderingUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Vertices getVerticesInThisOrder(TraverseOrder const traverseOrder)
    {
        Vertices traversedVertices;
        traverseStartingFromAllVertices(traversedVertices, traverseOrder);
        reverseVerticesIfNeeded(traversedVertices, traverseOrder);
        return traversedVertices;
    }

    Vertices getVerticesInTopologicalOrder()
    {
        //Useful on determining path that checks prerequisites and precedence scheduling
        return getVerticesInThisOrder(TraverseOrder::ReversePostOrder);
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
            std::reverse(traversedVertices.begin(), traversedVertices.end());
        }
    }

    void traverseStartingFromAllVertices(Vertices & traversedVertices, TraverseOrder const traverseOrder)
    {
        clear();
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotFound(vertex) && !m_graph.getAdjacentVerticesAt(vertex).empty())
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
            traversePostOrderAt(traversedVertices, startVertex);
            break;
        }
        }
    }

    void traversePreOrderAt(Vertices & traversedVertices, Vertex const& startVertex)
    {
        traversedVertices.emplace_back(startVertex); // add vertex before DFS

        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traversePreOrderAt(traversedVertices, adjacentVertex);
            }
        }
    }

    void traversePostOrderAt(Vertices & traversedVertices, Vertex const& startVertex)
    {
        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traversePostOrderAt(traversedVertices, adjacentVertex);
            }
        }
        traversedVertices.emplace_back(startVertex); // add vertex after DFS is done for the vertex
    }

    BaseGraphWithVertex const& m_graph;
    CheckableVerticesWithVertex m_processedVertices;
};

// Proposition: Reverse DFS postorder of a DAG is a topological order.
// Consider any edge v->w. When dfs(v) is called:
// -> Case 1: dfs(w) has already been called and returned
// ---> Thus w was done before v.
// -> Case 2: dfs(w) has not yet been called. dfs(w) will get called directly or indirectly by dfs(v) and will finish before dfs(v)
// ---> Thus w was done before v.
// -> Case 3: dfs(w) has already been called but has not yet returned.
// ---> Cant happen in a DAG: the function call stack contains path from w to v, so v->w would complete a cycle

// Proposition: A digraph has a topological order iff no directed cycle.
// Proof:
// -> If directed cycle, topological order is impossible.
// -> If no directed cycle, DFS-based algorithm finds a topological order

// Note: In the algorithm above, its possible to have a cycle and vertex ordering will ignore it and will return current ordering.
// -> So if there are cycles, vertex ordering will depend which vertex was used to start DFS.

// Other discussion:
// An acyclic graph always has a topological sort.
// However, if the graph contains a cycle, it is not possible to form a topological sort,
// because no node of the cycle can appear before the other nodes of the cycle in the ordering.

}

}
