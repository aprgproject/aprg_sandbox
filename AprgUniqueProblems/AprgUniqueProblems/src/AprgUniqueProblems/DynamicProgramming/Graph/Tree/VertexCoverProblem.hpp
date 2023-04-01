#pragma once

#include <Algorithm/Graph/Tree/ChildrenInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

namespace alba
{

class VertexCoverProblem
{
public:

    using Count = unsigned int;
    using Index = unsigned int;
    using Vertex = unsigned int;
    using SetOfVertices = algorithm::GraphTypes<Vertex>::SetOfVertices;
    using Graph = algorithm::UndirectedGraphWithListOfEdges<Vertex>;
    using ChildrenInTree = algorithm::ChildrenInTree<Vertex>;
    using VertexToCountMap = std::map<Vertex, Count>;
    using VertexToSetOfVerticesMap = std::map<Vertex, SetOfVertices>;
    static constexpr unsigned int UNUSED_COUNT=std::numeric_limits<unsigned int>::max();

    VertexCoverProblem(Graph const& nAryTreeGraph, Vertex const rootOfTree);

    Count getMinimumCountUsingNaiveRecursion() const;
    Count getMinimumCountUsingMemoizationDP() const;    SetOfVertices getMinimumSetUsingMemoizationDP() const;

private:
    Count getMinimumCountUsingNaiveRecursion(Vertex const vertex) const;    Count getMinimumCountUsingMemoizationDP(VertexToCountMap & vertexToCountMap, Vertex const vertex) const;
    SetOfVertices getMinimumSetUsingMemoizationDP(VertexToSetOfVerticesMap & vertexToMinimumSetMap, Vertex const vertex) const;

    Graph m_nAryTreeGraph;
    Vertex m_rootOfTree;
    ChildrenInTree m_childrenInTree;
};

}


// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "node/vertex" has a "minimum count" and this can be computed by:
// ---> Get count when vertex is included (recursively call the count of children and add 1 for this vertex)
// ---> Get count when vertex is not included (recursively call the count of grandChildren and add 1 for this each children)
// ---> Return the minimum of the two counts



// Vertex Cover Problem

// A vertex cover of an undirected graph is a subset of its vertices such that
// for every edge (u, v) of the graph, either ‘u’ or ‘v’ is in vertex cover.
// Although the name is Vertex Cover, the set covers all edges of the given graph.
// The problem to find minimum size vertex cover of a graph is NP complete.
// But it can be solved in polynomial time for trees.
// In this post a solution for Binary Tree is discussed.
// The same solution can be extended for n-ary trees.

// For example, consider the following binary tree. The smallest vertex cover is {20, 50, 30} and size of the vertex cover is 3.

// The idea is to consider following two possibilities for root and recursively for all nodes down the root.
// 1) Root is part of vertex cover:
// -> In this case root covers all children edges.
// -> We recursively calculate size of vertex covers for left and right subtrees and add 1 to the result (for root).
// 2) Root is not part of vertex cover:
// -> In this case, both children of root must be included in vertex cover to cover all root to children edges.
// -> We recursively calculate size of vertex covers of all grandchildren
// -> and number of children to the result (for two children of root).





