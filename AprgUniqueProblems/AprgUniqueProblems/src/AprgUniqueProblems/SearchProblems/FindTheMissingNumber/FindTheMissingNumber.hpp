#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <algorithm>
#include <functional>
#include <numeric>

namespace alba
{
namespace algorithm
{
template <typename Values>
class FindTheMissingNumber
{
public:
    using Count = unsigned int;
    using Index = unsigned int;
    using Value = typename Values::value_type;

    FindTheMissingNumber() = default;

    Value getTheMissingNumberUsingSum(Values const& values) // values can be unsorted because of xor
    {
        static_assert(typeHelper::isIntegralType<Value>(), "Value needs to be an integer.");

        // There is only one loop here.
        Value totalCountOfNumbers(values.size()+1);        Value actualSum = std::accumulate(values.cbegin(), values.cend(), static_cast<Value>(0), std::plus<Value>());
        Value expectedSum = (totalCountOfNumbers+1)*totalCountOfNumbers/2;

        return expectedSum-actualSum;    }

    Value getTheMissingNumberUsingXor(Values const& values) // values can be unsorted because of xor
    {
        static_assert(typeHelper::isIntegralType<Value>(), "Value needs to be an integer.");

        // There are two loops here (std::accumulate and for loop)
        Value totalCountOfNumbers(values.size()+1);        Value accumulatedXor = std::accumulate(values.cbegin(), values.cend(), static_cast<Value>(1), std::bit_xor<Value>());
        for(Value number(2); number<=totalCountOfNumbers; number++) // start with 2 (skip 1 because its processed in accumulate)
        {
            accumulatedXor ^= number;        }
        return accumulatedXor;
    }
};

}

}

// Find the Missing Number

// You are given a list of n-1 integers and these integers are in the range of 1 to n.
// There are no duplicates in the list.
// One of the integers is missing in the list.
// Write an efficient code to find the missing integer.

// Examples:
// -> Input: arr[] = {1, 2, 4, 6, 3, 7, 8}
// ---> Output: 5
// ---> Explanation: The missing number from 1 to 8 is 5
// -> Input: arr[] = {1, 2, 3, 5}
// ---> Output: 4
// ---> Explanation: The missing number from 1 to 5 is 4

// This method uses the technique of XOR to solve the problem.

// Approach:
// -> XOR has certain properties
// ---> Assume a1 ^ a2 ^ a3 ^...^ an = a and a1 ^ a2 ^ a3 ^ …^ an-1 = b
// ---> Then a ^ b = an

// Algorithm:
// -> Step 1: Create two variables a = 0 and b = 0
// -> Step 2: Run a loop from 1 to n with i as counter.
// -> Step 3: For every index update a as a = a ^ i
// -> Step 4: Now traverse the array from start to end.
// -> Step 5: For every index update b as b = b ^ array[i]
// -> Step 6: Print the missing number as a ^ b.

// Complexity Analysis:
// Time Complexity: O(n).
// -> Only one traversal of the array is needed.
// Auxiliary Space Complexity: O(1).
// -> No extra space is needed.
