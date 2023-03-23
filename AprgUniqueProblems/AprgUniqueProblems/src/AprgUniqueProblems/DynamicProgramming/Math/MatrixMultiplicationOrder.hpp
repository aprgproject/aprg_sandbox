#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class MatrixMultiplicationOrder
{
public:

    using Count = unsigned int;
    using Index = unsigned int;
    using Dimension = unsigned int;
    using Dimensions = std::vector<Dimension>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count MAX_COUNT=std::numeric_limits<Count>::max();

    MatrixMultiplicationOrder(Dimensions const& dimensions);

    Count getMinimumNumberOfOperationsUsingNaiveRecursion() const;
    Count getMinimumNumberOfOperationsUsingMemoizationDP() const;
    Count getMinimumNumberOfOperationsUsingIterativeDP() const;

private:
    Count getMinimumNumberOfOperationsUsingNaiveRecursion(Index const left, Index const right) const;
    Count getMinimumNumberOfOperationsUsingMemoizationDP(CountMatrix & countMatrix, Index const left, Index const right) const;
    Dimensions m_dimensions;
};
}

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "leftParenthesis" and "rightParenthesis" has a "count"
// -> Start recursion at the "leftParenthesis" as 0 and "rightParenthesis" as last index.
// -> Each "count" (with inputs "rightParenthesis" and "rightParenthesis") can be computed by:
// ---> If "leftParenthesis"+2 <= "rightParenthesis" (distance should be two for at least three elements):
// -----> Traverse "inBetween" from "leftParenthesis"+1 to "rightParenthesis"-1 (inclusive)
// -------> Get minimum of the counts of each "inBetween"
// ---------> The count of using an "inBetween" is the sum of this three parts:
// -----------> Recursively call "leftParenthesis" and "inBetween"
// -----------> Recursively call "inBetween" and "rightParenthesis"
// -----------> (get dimension at leftParenthesis) * (get dimension at inBetween) * (get dimension at rightParenthesis)
// -----> Result is minimum of the counts of each "inBetween"
// ---> Else
// -----> Result is 0

// 2) Dynamic Programming by Iterative method:
// -> Create an matrix of counts with size of columns as size of "dimensions" and size of rows as size of "dimensions"
// -> Thus each "leftParenthesis" and "rightParenthesis" has a count.
// -> Traverse "length" from 3 to size of "dimensions" (inclusive)
// ---> Traverse all possible "leftParenthesis"
// -----> Set "rightParenthesis" based on "leftParenthesis" and "length"
// -------> Traverse all possible "inBetween"
// ---------> Get minimum of the counts of each "inBetween"
// -----------> The count of using an "inBetween" is the sum of this three parts:
// -------------> Get matrix value at "leftParenthesis" and "inBetween"
// -------------> Get matrix value at "inBetween" and "rightParenthesis"
// -------------> (get dimension at leftParenthesis) * (get dimension at inBetween) * (get dimension at rightParenthesis)



// Matrix Chain Multiplication

// Given a sequence of matrices, find the most efficient way to multiply these matrices together.
// The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications.
// We have many options to multiply a chain of matrices because matrix multiplication is associative.
// In other words, no matter how we parenthesize the product, the result will be the same.

// For example, if we had four matrices A, B, C, and D, we would have:
// (ABC)D = (AB)(CD) = A(BCD) = ....
// However, the order in which we parenthesize the product affects
// the number of simple arithmetic operations needed to compute the product, or the efficiency.

// For example, suppose A is a 10 × 30 matrix, B is a 30 × 5 matrix, and C is a 5 × 60 matrix. Then,
// (AB)C = (10×30×5) + (10×5×60) = 1500 + 3000 = 4500 operations
// A(BC) = (30×5×60) + (10×30×60) = 9000 + 18000 = 27000 operations.

// Clearly the first parenthesization requires less number of operations.
// Given an array p[] which represents the chain of matrices such that the ith matrix Ai is of dimension p[i-1] x p[i].
// We need to write a function MatrixChainOrder() that should return the minimum number of multiplications needed to multiply the chain.

// -> Input: p[] = {40, 20, 30, 10, 30}
// ---> Output: 26000
// ---> There are 4 matrices of dimensions 40x20, 20x30, 30x10 and 10x30.
// ---> Let the input 4 matrices be A, B, C and D.
// ---> The minimum number of multiplications are obtained by putting parenthesis in following way
// ---> (A(BC))D --> 20*30*10 + 40*20*10 + 40*10*30
// -> Input: p[] = {10, 20, 30, 40, 30}
// ---> Output: 30000
// ---> There are 4 matrices of dimensions 10x20, 20x30, 30x40 and 40x30.
// ---> Let the input 4 matrices be A, B, C and D.
// ---> The minimum number of multiplications are obtained by putting parenthesis in following way
// ---> ((AB)C)D --> 10*20*30 + 10*30*40 + 10*40*30
// -> Input: p[] = {10, 20, 30}
// ---> Output: 6000
// ---> There are only two matrices of dimensions 10x20 and 20x30.
// ---> So there is only one way to multiply the matrices, cost of which is 10*20*30

// 1) Optimal Substructure:
// A simple solution is to place parenthesis at all possible places,
// calculate the cost for each placement and return the minimum value.
// In a chain of matrices of size n, we can place the first set of parenthesis in n-1 ways.
// For example, if the given chain is of 4 matrices. let the chain be ABCD,
// then there are 3 ways to place first set of parenthesis outer side: (A)(BCD), (AB)(CD) and (ABC)(D).
// So when we place a set of parenthesis, we divide the problem into subproblems of smaller size.
// Therefore, the problem has optimal substructure property and can be easily solved using recursion.
// Minimum number of multiplication needed to multiply a chain of size n = Minimum of all n-1 placements
// (these placements create subproblems of smaller size)

// The time complexity of the above naive recursive approach is exponential.
// It should be noted that the above function computes the same subproblems again and again.
// We can see that there are many subproblems being called more than once.

// Since same subproblems are called again, this problem has Overlapping Subproblems property.
// So Matrix Chain Multiplication problem has both properties (Overlapping Subproblems and Optimal Substructure) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of same subproblems can be avoided by constructing a temporary array m[][] in bottom up manner.

