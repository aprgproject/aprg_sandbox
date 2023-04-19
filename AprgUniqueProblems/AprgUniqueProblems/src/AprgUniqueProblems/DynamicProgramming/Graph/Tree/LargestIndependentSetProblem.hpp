#pragma once

#include <Algorithm/Graph/Tree/ChildrenInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

namespace alba
{

class LargestIndependentSetProblem
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

    LargestIndependentSetProblem(Graph const& nAryTreeGraph, Vertex const rootOfTree);

    Count getMaximumCountUsingNaiveRecursion() const;
    Count getMaximumCountUsingMemoizationDP() const;    SetOfVertices getMaximumSetUsingMemoizationDP() const;

private:
    Count getMaximumCountUsingNaiveRecursion(Vertex const vertex) const;
    Count getMaximumCountUsingMemoizationDP(VertexToCountMap & vertexToCountMap, Vertex const vertex) const;
    SetOfVertices getMaximumSetUsingMemoizationDP(VertexToSetOfVerticesMap & vertexToMaximumSetMap, Vertex const vertex) const;

    Graph m_nAryTreeGraph;
    Vertex m_rootOfTree;
    ChildrenInTree m_childrenInTree;
};
}


// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "node/vertex" has a "maximum count" and this can be computed by:
// ---> Get count when vertex is included (recursively call the count of grandchildren and add 1 for this vertex)
// ---> Get count when vertex is not included (recursively call the count of children)
// ---> Return the maximum of the two counts



// Largest Independent Set Problem

// Given a Binary Tree, find size of the Largest Independent Set(LIS) in it.
// A subset of all tree nodes is an independent set if there is no edge between any two nodes of the subset.
// For example, consider the following binary tree. The largest independent set(LIS) is {10, 40, 60, 70, 80} and size of the LIS is 5.
//       10
//      |  |
//    20   30
//   |  |   |
//  40  50   60
//     |  |
//    70  80

// A Dynamic Programming solution solves a given problem using solutions of subproblems in bottom up manner.
// Can the given problem be solved using solutions to subproblems?
// If yes, then what are the subproblems?
// Can we find largest independent set size (LISS) for a node X f we know LISS for all descendants of X?
// If a node is considered as part of LIS, then its children cannot be part of LIS, but its grandchildren can be.
// Following is optimal substructure property.

// 1) Optimal Substructure:
// Let LISS(X) indicates size of largest independent set of a tree with root X.
//      LISS(X) = MAX { (1 + sum of LISS for all grandchildren of X),
//                      (sum of LISS for all children of X) }
// The idea is simple, there are two possibilities for every node X, either X is a member of the set or not a member.
// If X is a member, then the value of LISS(X) is 1 plus LISS of all grandchildren.
// If X is not a member, then the value is sum of LISS of all children.

// Time complexity of the above naive recursive approach is exponential.
// It should be noted that the above function computes the same subproblems again and again.
// For example, LISS of node with value 50 is evaluated for node with values 10 and 20 as 50 is grandchild of 10 and child of 20.

// Since same subproblems are called again, this problem has Overlapping Subproblems property.
// So LISS problem has both properties (see this and this) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of same subproblems can be avoided by storing the solutions to subproblems and solving problems in bottom up manner.

// Following are implementation of Dynamic Programming based solution.
// In the following solution, an additional field ‘liss’ is added to tree nodes.
// The initial value of ‘liss’ is set as 0 for all nodes.
// The recursive function LISS() calculates ‘liss’ for a node only if it is not already set.

// Following extensions to above solution can be tried as an exercise:
// 1) Extend the above solution for n-ary tree. (DONE!)
// 2) The above solution modifies the given tree structure by adding an additional field ‘liss’ to tree nodes.
// -> Extend the solution so that it doesn’t modify the tree structure.
// 3) The above solution only returns size of LIS, it doesn’t print elements of LIS.// -> Extend the solution to print all nodes that are part of LIS.



