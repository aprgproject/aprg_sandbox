#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class OptimalBinarySearchTree
{
public:

    using Cost = unsigned int;
    using Index = unsigned int;
    using Frequency = unsigned int;
    using Frequencies = std::vector<Frequency>;
    using ValueAndFrequencyPair = std::pair<unsigned int, Frequency>;
    using ValueAndFrequencyPairs = std::vector<ValueAndFrequencyPair>;
    using CostMatrix = matrix::AlbaMatrix<Cost>;
    static constexpr Cost MAX_COUNT=std::numeric_limits<Cost>::max();

    OptimalBinarySearchTree(ValueAndFrequencyPairs const& valueAndFrequencyPairs);

    Cost getMinimumCostUsingNaiveRecursion() const;
    Cost getMinimumCostUsingTabularDP() const;

private:
    Cost getMinimumCostUsingNaiveRecursion(Cost const depth, Index const left, Index const right) const;

    Cost getCost(Cost const depth, Cost const frequency) const;
    void initialize();
    void sortByValue();
    ValueAndFrequencyPairs m_valueAndFrequencyPairs;
};

}

// Given a sorted array key [0.. n-1] of search keys and an array freq[0.. n-1] of frequency counts,
// where freq[i] is the number of searches for keys[i].
// Construct a binary search tree of all keys such that the total cost of all the searches is as small as possible.
// Let us first define the cost of a BST.
// The cost of a BST node is the level of that node multiplied by its frequency.
// The level of the root is 1.

// Examples:
// -> Input:  keys[] = {10, 12}, freq[] = {34, 50}
// ---> There can be following two possible BSTs
// --->         10                       12
// --->           |                     |
// --->            12                 10
// --->           I                     II
// ---> Frequency of searches of 10 and 12 are 34 and 50 respectively.
// ---> The cost of tree I is 34*1 + 50*2 = 134
// ---> The cost of tree II is 50*1 + 34*2 = 118

// -> Input:  keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
// ---> There can be following possible BSTs
// --->     10                12                 20         10              20
// --->       |             |    |              |             |            |
// --->       12          10     20           12               20         10
// --->         |                            |                 |           |
// --->          20                        10                12             12
// --->      I               II             III             IV             V
// ---> Among all possible BSTs, cost of the fifth BST is minimum.
// ---> Cost of the fifth BST is 1*50 + 2*34 + 3*8 = 142

// 1) Optimal Substructure:
// -> The optimal cost for freq[i..j] can be recursively calculated using the following formula.
// -> optcost(i,j) = Summation for k=i to j {freq[k] + minimum of(optcost(i,r-1)+optcost(r+1,j)) from i to j}
// -> We need to calculate optCost(0, n-1) to find the result.
// -> The idea of above formula is simple, we one by one try all nodes as root (r varies from i to j in second term).
// -> When we make rth node as root, we recursively calculate optimal cost from i to r-1 and r+1 to j.
// -> We add sum of frequencies from i to j (see first term in the above formula),
// -> this is added because every search will go through root and one comparison will be done for every search.

// 2) Overlapping Subproblems
// -> Following is recursive implementation that simply follows the recursive structure mentioned above.

// Since same subproblems are called again, this problem has Overlapping Subproblems property.
// So optimal BST problem has both properties (see this and this) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of same subproblems can be avoided by constructing a temporary array cost[][] in bottom up manner.

// Dynamic Programming Solution
// Following is C/C++ implementation for optimal BST problem using Dynamic Programming.
// We use an auxiliary array cost[n][n] to store the solutions of subproblems.
// cost[0][n-1] will hold the final result.
// The challenge in implementation is, all diagonal values must be filled first,
// then the values which lie on the line just above the diagonal.
// In other words, we must first fill all cost[i][i] values, then all cost[i][i+1] values, then all cost[i][i+2] values.
// So how to fill the 2D array in such manner:
// The idea used in the implementation is same as Matrix Chain Multiplication problem,
// we use a variable ‘L’ for chain length and increment ‘L’, one by one.
// We calculate column number ‘j’ using the values of ‘i’ and ‘L’.

// Notes
// 1) The time complexity of the tabular solution is O(n^3).
// -> The time complexity is reduced to O(n^3) by pre-calculating sum of frequencies instead of calling sum() again and again.
// 2) In the above solutions, we have computed optimal cost only.
// -> The solutions can be easily modified to store the structure of BSTs also.
// -> We can create another auxiliary array of size n to store the structure of tree.
// -> All we need to do is, store the chosen ‘r’ in the innermost loop.



