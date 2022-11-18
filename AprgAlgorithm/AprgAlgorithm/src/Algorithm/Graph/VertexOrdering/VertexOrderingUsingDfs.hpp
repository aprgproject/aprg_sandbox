#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

enum class VertexTraversalOrder
{
    PreOrder, // order: DFS traversal order (not really useful)
    PostOrder, // order: dependent vertices are first in the list (edge might not exist -> not useful)
    ReversePostOrder, // order: dependent vertices are last in the list (topological sort)
};

template <typename Vertex>
class VertexOrderingUsingDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    VertexOrderingUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    Vertices getVerticesInThisOrder(Vertex const& startVertex, VertexTraversalOrder const traversalOrder)
    {
        Vertices traversedVertices;
        traverseStartingFromAVertex(traversedVertices, startVertex, traversalOrder);
        reverseVerticesIfNeeded(traversedVertices, traversalOrder);
        return traversedVertices;
    }

    Vertices getVerticesInThisOrder(VertexTraversalOrder const traversalOrder)
    {
        Vertices traversedVertices;
        traverseStartingFromAllVertices(traversedVertices, traversalOrder);
        reverseVerticesIfNeeded(traversedVertices, traversalOrder);
        return traversedVertices;
    }

    Vertices getVerticesInTopologicalOrder()
    {
        //Useful on determining path that checks prerequisites and precedence scheduling
        return getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder);
    }

    Vertices getVerticesInTopologicalOrder(Vertex const& startVertex)
    {
        // Algorithm in short terms: Traverse DFS post order("add vertex after DFS is done for the vertex"), then reverse the order

        return getVerticesInThisOrder(startVertex, VertexTraversalOrder::ReversePostOrder);
    }

private:

    void reverseVerticesIfNeeded(Vertices & traversedVertices, VertexTraversalOrder const traversalOrder) const
    {
        if(VertexTraversalOrder::ReversePostOrder == traversalOrder)
        {
            std::reverse(traversedVertices.begin(), traversedVertices.end());
        }
    }

    void clear()
    {
        m_processedVertices.clear();
    }

    void traverseStartingFromAVertex(Vertices & traversedVertices, Vertex const& startVertex, VertexTraversalOrder const traversalOrder)
    {
        clear();
        if(m_processedVertices.isNotFound(startVertex) && !m_graph.getAdjacentVerticesAt(startVertex).empty()) // dont include invalid vertex
        {
            traverseAt(traversedVertices, traversalOrder, startVertex);
        }
    }

    void traverseStartingFromAllVertices(Vertices & traversedVertices, VertexTraversalOrder const traversalOrder)
    {
        clear();
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                traverseAt(traversedVertices, traversalOrder, vertex);
            }
        }
    }

    void traverseAt(Vertices & traversedVertices, VertexTraversalOrder const traversalOrder, Vertex const& startVertex)
    {
        switch(traversalOrder)
        {
        case VertexTraversalOrder::PreOrder:
        {
            traversePreOrderAt(traversedVertices, startVertex);
            break;
        }
        case VertexTraversalOrder::PostOrder:
        {
            traversePostOrderAt(traversedVertices, startVertex);
            break;
        }
        case VertexTraversalOrder::ReversePostOrder:
        {
            traversePostOrderAt(traversedVertices, startVertex);
            break;
        }
        }
    }

    void traversePreOrderAt(Vertices & traversedVertices, Vertex const& vertex)
    {
        traversedVertices.emplace_back(vertex); // add vertex before DFS

        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traversePreOrderAt(traversedVertices, adjacentVertex);
            }
        }
    }

    void traversePostOrderAt(Vertices & traversedVertices, Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traversePostOrderAt(traversedVertices, adjacentVertex);
            }
        }
        traversedVertices.emplace_back(vertex); // add vertex after DFS is done for the vertex
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
