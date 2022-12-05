#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Value>
class FindSmallestValueWithTrue
{
public:

    // Finding the smallest solution
    // An important use for binary search is to find the position where the value of a function changes.
    // Suppose that we wish to find the smallest value k that is a valid solution for a problem.
    // We are given a function ok(x) that returns true if x is a valid solution and false otherwise.
    // In addition, we know that ok(x) is false when x<k and true when x>=k.

    // The situation looks as follows:
    // x     | 0     | 1     | ... | k-1   | k    | k+1 | ...
    // ok(x) | false | false | ... | false | true | true| ...

    // The search finds the largest value of x for which ok(x) is false.
    // Thus, the next value k=x+1 is the smallest possible value for which ok(k) is true.
    // The initial jump length z has to be large enough, for example some value for which we know beforehand that ok(z) is true.
    // The algorithm calls the function ok O(log z) times, so the total time complexity depends on the function ok.
    // For example, if the function works in O(n) time, the total time complexity is O(nlogz)

    using BoolFunction = std::function<bool(Value)>;

    FindSmallestValueWithTrue(BoolFunction const& boolFunction)
        : m_boolFunction(boolFunction)
    {}

    Value getSmallestValueWithTrue(Value const& startValue, Value const& endValue) const
    {
        // Binary search with skip
        Value result(startValue);
        for(Value forwardSkip = (endValue-startValue)/2; forwardSkip>=1; forwardSkip/=2) // start from half of delta, then quarter of size, then eighth of size and so on
        {
            while(!m_boolFunction(result+forwardSkip))
            {
                result += forwardSkip;
            }
        }
        result++;
        return result;
    }

private:

    BoolFunction const& m_boolFunction;
};

}

}

// An alternative method to implement binary search is based on an efficient way to iterate through the elements of the array.
// The idea is to make jumps and slow the speed when we get closer to the target element.

// The search goes through the array from left to right, and the initial jump length is n/2.
// At each step, the jump length will be halved: first n/4, then n/8, n/16, etc., until finally the length is 1.
// After the jumps, either the target element has been found or we know that it does not appear in the array.

// During the search, the variable b contains the current jump length.
// The time complexity of the algorithm is O(logn), because the code in the while loop is performed at most twice for each jump length.
