#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/CountingSorter/CountingSorterUsingNewPositions.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values, unsigned int MAX_NUMBER_OF_DIGIT_VALUES>
class RadixSorterUsingCountingSorter : public BaseSorter<Values>
{
public:
    using Value = typename Values::value_type;
    using DigitValue = unsigned int; // this needs to be indexable as its used on CountingSorter
    using GetNumberOfDigitsFunction = std::function<unsigned int(Values const&)>;
    using GetDigitAtFunction = std::function<DigitValue(Value const&, unsigned int const)>;

    RadixSorterUsingCountingSorter() = delete;
    RadixSorterUsingCountingSorter(
            GetNumberOfDigitsFunction const& getNumberOfDigitsFunction,
            GetDigitAtFunction const& getDigitAtFunction)
        : m_getNumberOfDigitsFunction(getNumberOfDigitsFunction)
        , m_getDigitAtFunction(getDigitAtFunction)
    {}

    void sort(Values & valuesToSort) const override
    {
        unsigned int numberOfDigits(m_getNumberOfDigitsFunction(valuesToSort));
        for(unsigned int digitIndex=0; digitIndex<numberOfDigits; digitIndex++) // start at least significant digit
        {
            auto getDigitFunction = [&](Value const& value)
            {
                return m_getDigitAtFunction(value, digitIndex);
            };
            CountingSorterUsingNewPositions<Values, MAX_NUMBER_OF_DIGIT_VALUES> countingSorter(getDigitFunction);
            countingSorter.sort(valuesToSort);
        }
    }
private:
    GetNumberOfDigitsFunction m_getNumberOfDigitsFunction;
    GetDigitAtFunction m_getDigitAtFunction;};

}

}

// The lower bound for Comparison based sorting algorithm (Merge Sort, Heap Sort, Quick-Sort .. etc) is Ω(nLogn), i.e., they cannot do better than nLogn.
// Counting sort is a linear time sorting algorithm that sort in O(n+k) time when elements are in the range from 1 to k.

// What if the elements are in the range from 1 to n2?
// We can’t use counting sort because counting sort will take O(n2) which is worse than comparison-based sorting algorithms. Can we sort such an array in linear time?
// Radix Sort is the answer. The idea of Radix Sort is to do digit by digit sort starting from least significant digit to most significant digit. Radix sort uses counting sort as a subroutine to sort.

// The Radix Sort Algorithm
// -> Do following for each digit i where i varies from least significant digit to the most significant digit.
// ---> Sort input array using counting sort (or any stable sort) according to the i’th digit.

// Example:
// Original, unsorted list: 170, 45, 75, 90, 802, 24, 2, 66

// Sorting by least significant digit (1s place) gives:
// [*Notice that we keep 802 before 2, because 802 occurred before 2 in the original list, and similarly for pairs 170 & 90 and 45 & 75.]
// 170, 90, 802, 2, 24, 45, 75, 66

// Sorting by next digit (10s place) gives:
// [*Notice that 802 again comes before 2 as 802 comes before 2 in the previous list.]
// 802, 2, 24, 45, 66, 170, 75, 90

// Sorting by the most significant digit (100s place) gives:
// 2, 24, 45, 66, 75, 90, 170, 802

// What is the running time of Radix Sort?
// -> Radix Sort takes O(("size of input" + "number of digit values") * "number of digits")
// ---> Or it can be expressed as O((n+b)*d)
// -> Let the "size of input" be "n".
// -> Let the "maximum possible value" be "k".
// ---> In a 32-bit unsigned integer its 0xFFFFFFFF or 4294967295.
// -> Let the "number of digit values" be "b".
// ---> The "number of digit values" is also the BASE for digit value.
// -----> For example, in the decimal system the "number of digit values" is 10.
// -----> For example, in the hexadecimal system the "number of digit values" is 16.
// -> Let the "number of digits" be "d".
// ---> The "number of digits" is also equal to O(log"number of digit values"("maximum possible value")).
// So overall time complexity is O(("size of input"+"number of digit values") * log"number of digit values"("maximum possible value")).
// -> Or it can be expressed as O((n+b) * logb(k))

// The time complexity for a large k ("maximum possible value"), would be similar to comparison-based sorting algorithms.
// Let us first limit k. Let k <= nc where c is a constant. In that case, the complexity becomes O(nLogb(n)).
// So its still doesn’t beat comparison-based sorting algorithms.

// What if we make the value of b ("number of digit values") larger?
// What should be the value of b to make the time complexity linear?
// If we set b as scalable with n, we get the time complexity as O(n).
// -> So its linear/O(n) if the "number of digit values" is scalable with the "size of input".
// In other words, we can sort an array of integers with a range from 1 to nc if the numbers are represented in base n (or every digit takes log2(n) bits).
// -> So if there are 16 numbers (with range 1 to 16c), its better to have base 16 (where every digit is four bits).
// -> So if there are 100 numbers (with range 1 to 100c), its better to have base 64 (where every digit is six bits).
// -> So if there are 1000000 numbers (with range 1 to 1000000c), its better to have base 1048576 (where every digit is 20 bits).
// -> Interview question: Sort a million 32-bit integers?
// ---> Radix sort is better because of fixed width.
// ---> For each digit, we can use 20 bits (or 16 bits which is more practical).
// -----> If we use 16 bits: O((n+b) * logb(k)) = 1000000+65536 * log65536(2^32) = 1065536 * 2 = 2131072
// -----> In comparison for a comparison based algorithm: O(n*lg(n)) = 1000000*lg(1000000) = 1000000*19.931568.... = 19931568.
// -----> So Radix sort is better.

// Applications of Radix Sort :// -> In a typical computer, which is a sequential random-access machine, where the records are keyed by multiple fields radix sort is used.
// ---> For eg., you want to sort on three keys month, day and year.
// ---> You could compare two records on year, then on a tie on month and finally on the date.
// ---> Alternatively, sorting the data three times using Radix sort first on the date, then on month, and finally on year could be used.// -> It was used in card sorting machines that had 80 columns, and in each column, the machine could punch a hole only in 12 places.
// ---> The sorter was then programmed to sort the cards, depending upon which place the card had been punched.
// ---> This was then used by the operator to collect the cards which had the 1st row punched, followed by the 2nd row, and so on.

// Is Radix Sort preferable to Comparison based sorting algorithms like Quick-Sort?
// -> If we have log2n bits for every digit, the running time of Radix appears to be better than Quick Sort for a wide range of input numbers.
// ---> The constant factors hidden in asymptotic notation are higher for Radix Sort and Quick-Sort uses hardware caches more effectively.
// ---> Also, Radix sort uses counting sort as a subroutine and counting sort takes extra space to sort numbers.


