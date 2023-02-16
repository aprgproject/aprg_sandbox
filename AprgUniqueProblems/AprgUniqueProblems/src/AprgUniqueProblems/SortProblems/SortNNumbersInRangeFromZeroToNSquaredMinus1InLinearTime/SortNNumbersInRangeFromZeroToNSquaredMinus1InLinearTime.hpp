#pragma once

#include <Algorithm/Sort/RadixSorter/RadixSorterUsingQuickSortWith3WayPartitioning.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba
{

namespace algorithm
{

template <typename Integers>
class SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime
{
public:
    using Integer = typename Integers::value_type;
    using RadixSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Integers, Integer>;
    using GetDigitAtFunction = typename RadixSorter::GetDigitAtFunction;
    using IsDigitFunction = typename RadixSorter::IsDigitFunction;

    SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime() = default;

    void sort(Integers & valuesToSort) const
    {
        static_assert(typeHelper::isIntegralType<Integer>(), "Data type must be an integer");

        unsigned int size = valuesToSort.size();
        if(size > 1U)
        {
            // If we set b as n, the value of O(logb(n)) becomes O(1) and overall time complexity becomes O(n).
            unsigned int numberOfBitsInDigit = AlbaBitValueUtilities<unsigned int>::getCeilOfLogarithmWithBase2Of(size);
            unsigned int numberOfDigits = (AlbaBitValueUtilities<Integer>::getNumberOfBits()+numberOfBitsInDigit-1)/numberOfBitsInDigit;
            Integer mask = AlbaBitValueUtilities<Integer>::generateOnesWithNumberOfBits(numberOfBitsInDigit);

            GetDigitAtFunction getDigitAt = [&](Integer const& value, unsigned int const mostSignificantDigitIndex) -> Integer
            {
                return (value >> ((numberOfDigits-mostSignificantDigitIndex-1U)*numberOfBitsInDigit)) & mask;
            };
            IsDigitFunction isDigitIndexValid = [numberOfDigits](Integer const&, unsigned int const digitIndex) -> bool
            {
                return digitIndex < numberOfDigits;
            };

            RadixSorter radixSorter(getDigitAt, isDigitIndexValid);
            radixSorter.sort(valuesToSort);
        }
    }
};

}

}

// Given an array of numbers of size n.
// It is also given that the array elements are in range from 0 to n2 – 1.
// Sort the given array in linear time.

// Examples:
// 1) Since there are 5 elements, the elements can be from 0 to 24.
// ---> Input: arr[] = {0, 23, 14, 12, 9}
// ---> Output: arr[] = {0, 9, 12, 14, 23}
// 2) Since there are 3 elements, the elements can be from 0 to 8.
// ---> Input: arr[] = {7, 0, 2}
// ---> Output: arr[] = {0, 2, 7}


// Solution: If we use Counting Sort, it would take O(n^2) time as the given range is of size n^2.
// Using any comparison based sorting like Merge Sort, Heap Sort, .. etc would take O(nLogn) time.

// Now question arises how to do this in 0(n)?
// -> Firstly, is it possible?
// ->Can we use data given in question? n numbers in range from 0 to n2 – 1?

// The idea is to use Radix Sort. Following is standard Radix Sort algorithm.
// 1) Do following for each digit i where i varies from least significant digit to the most significant digit.
// a) Sort input array using counting sort (or any stable sort) according to the i’th digit

// Let there be d digits in input integers.
// Radix Sort takes O(d*(n+b)) time where b is the base for representing numbers, for example, for decimal system, b is 10.
// Since n2-1 is the maximum possible value, the value of d would be O(logb(n)).
// So overall time complexity is O((n+b)*O(logb(n)).
// Which looks more than the time complexity of comparison based sorting algorithms for a large k.
// The idea is to change base b.
// If we set b as n, the value of O(logb(n)) becomes O(1) and overall time complexity becomes O(n).

// How to sort if range is from 1 to n2?
// If range is from 1 to n n2, the above process can not be directly applied, it must be changed.
// Consider n = 100 and range from 1 to 10000.
// Since the base is 100, a digit must be from 0 to 99 and there should be 2 digits in the numbers.
// But the number 10000 has more than 2 digits. So to sort numbers in a range from 1 to n2, we can use following process.
// 1) Subtract all numbers by 1.
// 2) Since the range is now 0 to n2, do counting sort twice as done in the above implementation.
// 3) After the elements are sorted, add 1 to all numbers to obtain the original numbers.

// How to sort if range is from 0 to n^3 -1?
// Since there can be 3 digits in base n, we need to call counting sort 3 times.


