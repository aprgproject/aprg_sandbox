#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <set>
#include <vector>

namespace alba {

class FibonacciExample {
public:
    using Number = int;
    using Numbers = std::vector<Number>;
    using NumberSet = std::set<Number>;
    using NumberMatrix = matrix::AlbaMatrix<Number>;
    static constexpr Number UNUSED_VALUE = std::numeric_limits<Number>::max();

    Number getNthFibonacciUsingNaiveRecursion(Number const number) const;
    Number getNthFibonacciUsingMemoizationDP(Number const number);
    Number getNthFibonacciUsingIterativeDP(Number const number);
    Number getNthFibonacciUsingIterativeDPAndSpaceEfficient(Number const number);
    Number getNthFibonacciNumberUsingBinetsFormula(Number const number);
    Number getNthFibonacciUsingMatrixMultiplication(Number const number);
    Number getNthFibonacciUsingMatrixPowerWithLogarithmicTime(Number const number);
    Number getNthFibonacciUsingLogarithmicMemoizationDP(Number const number);
    Number getNthFibonacciUsingLogarithmicIterativeDP(Number const number);

private:
    Number getNthFibonacciUsingMemoizationDP(Numbers& memoizationData, Number const number);
    Number getNthFibonacciUsingLogarithmicMemoizationDP(Numbers& memoizationData, Number const number);
};

}  // namespace alba

// The Fibonacci numbers are the numbers in the following integer sequence.
// -> 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...

// In mathematical terms, the sequence Fn of Fibonacci numbers is defined by the recurrence relation:
// -> Fn = Fn-1 + Fn-2
// with seed values:
// -> F0 = 0 and F1 = 1.

// Examples:
// -> Input  : n = 2
// ---> Output : 1
// -> Input  : n = 9
// ---> Output : 34

// Logarithmic version of Fibonacci:

// Below is one more interesting recurrence formula that can be used to find n’th Fibonacci Number in O(Log n) time.
// If n is even then k = n/2:
// -> F(n) = [2*F(k-1) + F(k)]*F(k)
// If n is odd then k = (n + 1)/2
// -> F(n) = F(k)*F(k) + F(k-1)*F(k-1)

// How does this formula work?
// ---> The formula can be derived from above matrix equation.
// -> Taking determinant on both sides, we get
// ---> (-1)n = F(n+1)*F(n-1) - F(n)^2
// -> Moreover, since A^n * A^m = A^(n+m) for any square matrix A,
// -> the following identities can be derived (they are obtained form two different coefficients of the matrix product)
// ---> F(m)*F(n) + F(m-1)*F(n-1) = F(m+n-1)         // equation(1)
// -> By putting n = n+1 in equation(1),
// ---> F(m)*F(n+1) + F(m-1)*F(n) = F(m+n)           // equation(2)
// -> Putting m = n in equation(1).
// ---> F(2n-1) = F(n)^2 + F(n-1)^2
// -> Putting m = n in equation(2)
// ---> F(2n) = (F(n-1) + F(n+1))F(n) = (2F(n-1) + F(n))F(n)
// -> ( By putting F(n+1) = F(n) + F(n-1))
// -> To get the formula to be proved, we simply need to do the following
// ---> If n is even, we can put k = n/2
// ---> If n is odd, we can put k = (n+1)/2
