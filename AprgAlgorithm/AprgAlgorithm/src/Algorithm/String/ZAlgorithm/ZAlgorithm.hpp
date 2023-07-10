#pragma once

#include <string>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Index>
class ZAlgorithm {
public:
    using Indexes = std::vector<Index>;

    ZAlgorithm() = delete;
    ~ZAlgorithm() = delete;
    ZAlgorithm(ZAlgorithm const &) = delete;
    ZAlgorithm &operator=(ZAlgorithm const &) = delete;
    ZAlgorithm(ZAlgorithm &&) = delete;
    ZAlgorithm &operator=(ZAlgorithm &&) = delete;

    // The Z-array z of a string s of length n contains for each k = 0,1,...,n-1
    // the length of the longest substring of s that begins at position k and is a prefix of s.
    // Thus, z[k]=p tells us that s[0... p-1] equals s[k...k+p-1].
    // Many string processing problems can be efficiently solved using the Z-array.

    static constexpr Indexes getPrefixLengthsUsingTheZAlgorithm(std::string const &mainString) {
        Index mainStringLength = mainString.length();
        Indexes prefixLengths(mainStringLength, Index{});
        Index startOfPrefix = 0, endOfPrefix = 0;
        for (Index index = 1; index < mainStringLength; index++) {
            // compute prefix length from previous prefix lengths
            Index previousPrefixLength = prefixLengths[index - startOfPrefix];
            Index maxPreviousPrefixSubLength = endOfPrefix - index + 1;
            Index &prefixLength(prefixLengths[index]);
            prefixLength = std::max(0, std::min(previousPrefixLength, maxPreviousPrefixSubLength));
            // set new a prefix range, or extend the prefix length if possible
            for (int newEndIndex = index + prefixLength; mainString[prefixLength] == mainString[newEndIndex];
                 ++prefixLength, ++newEndIndex) {
                endOfPrefix = newEndIndex;
            }
            if (prefixLength > 0) {
                startOfPrefix = endOfPrefix - prefixLength + 1;
            }
        }
        return prefixLengths;
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Z Algorithm
// --->  The algorithm finds all occurrences of a pattern in a text in linear time.
// --->  Let length of text be n and of pattern be m, then total time taken is O(m + n) with linear space complexity.
// --->  Now we can see that both time and space complexity is same as KMP algorithm but this algorithm is simpler to
// understand.
// --->  In this algorithm, we construct a Z array.
// ->  What is Z Array?
// --->  For a string str[0..n-1], Z array is of same length as string.
// --->  An element Z[i] of Z array stores length of the longest substring starting from str[i] which is also a prefix
// of str[0..n-1].
// --->  The first entry of Z array is meaning less as complete string is always prefix of itself.
// --->  Example:
// -----> | Index    | 0   1   2   3   4   5   6   7   8   9  10  11
// -----> | Text     | a   a   b   c   a   a   b   x   a   a   a   z
// -----> | Z values | X   1   0   0   3   1   0   0   2   2   1   0
// ->  More Examples:
// --->  str  = "aaaaaa", Z[]  = {x, 5, 4, 3, 2, 1}
// --->  str = "aabaacd", Z[] = {x, 1, 0, 2, 1, 0, 0}
// --->  str = "abababab", Z[] = {x, 0, 6, 0, 4, 0, 2, 0}
// ->  How is Z array helpful in Searching Pattern in Linear time?
// --->  The idea is to concatenate pattern and text, and create a string “P$T” where P is pattern,
// --->  $ is a special character should not be present in pattern and text, and T is text.
// --->  Build the Z array for concatenated string.
// --->  In Z array, if Z value at any point is equal to pattern length, then pattern is present at that point.
// --->  Example:
// ----->  Pattern P = "aab",  Text T = "baabaa"
// ----->  The concatenated string is = "aab$baabaa"
// ----->  Z array for above concatenated string is {x, 1, 0, 0, 0, 3, 1, 0, 2, 1}.
// ----->  Since length of pattern is 3, the value 3 in Z array
// ----->  indicates presence of pattern.
// -> How to construct Z array?
// ---> A simple solution is to run two nested loops, the outer loop goes to every index
// ---> and the inner loop finds length of the longest prefix that matches the substring starting at the current index.
// -----> The time complexity of this solution is O(n^2).
// -----> We can construct Z array in linear time.
// ---> Algorithm description:
// -----> Next we describe an algorithm, called the Z-algorithm, that efficiently constructs the Z-array in O(n) time.
// -----> The algorithm calculates the Z-array values from left to right by both using information already stored in the
// -----> Z-array and comparing substrings character by character.
// -----> To efficiently calculate the Z-array values, the algorithm maintains a range [x, y]
// -----> such that s[x... y] is a prefix of s and y is as large as possible.
// -----> Since we know that s[0... y-x] and s[x... y] are equal,
// -----> we can use this information when calculating Z-values for positions x+1, x+2,..., y.
// -----> At each position k, we first check the value of z[k-x]. If k+z[k-x] < y, we know that z[k] = z[k-x].
// -----> However, if k+z[k-x] ¸ y, s[0... y-k] equals s[k... y],
// -----> and to determine the value of z[k] we need to compare the substrings character by character.
// -----> Still, the algorithm works in O(n) time, because we start comparing at positions y-k+1 and y+1.
