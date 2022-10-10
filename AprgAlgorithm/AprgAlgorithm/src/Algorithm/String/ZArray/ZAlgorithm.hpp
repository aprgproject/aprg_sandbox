#pragma once

#include <string>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Index>
class ZAlgorithm
{
public:
    using Indexes = std::vector<Index>;

    ZAlgorithm() = delete;
    ZAlgorithm(ZAlgorithm const&) = delete;
    ZAlgorithm & operator= (ZAlgorithm const&) = delete;

    static constexpr Indexes getZArray(std::string const& mainString)
    {
        Index n = mainString.size();
        Indexes result(n, Index{});
        Index x = 0, y = 0;
        for (Index i = 1; i < n; i++)
        {
            result[i] = std::max(0U, std::min(result.at(i-x), y-i+1));
            while (i+result.at(i) < n && mainString.at(result.at(i)) == mainString.at(i+result.at(i)))
            {
                x = i;
                y = i+result.at(i);
                result[i]++;
            }
        }
        return result;
    }
};

// The Z-array z of a string s of length n contains for each k = 0,1, ... ,n-1
// the length of the longest substring of s that begins at position k and is a prefix of s.
// Thus, z[k]=p tells us that s[0... p-1] equals s[k...k+p-1].
// Many string processing problems can be efficiently solved using the Z-array.

// Algorithm description
// Next we describe an algorithm, called the Z-algorithm, that efficiently constructs the Z-array in O(n) time.
// The algorithm calculates the Z-array values from left to right by both using information already stored in the Z-array
// and comparing substrings character by character.
// To efficiently calculate the Z-array values, the algorithm maintains a range [x, y]
// such that s[x... y] is a prefix of s and y is as large as possible.
// Since we know that s[0... y-x] and s[x... y] are equal, we can use this information when calculating Z-values for positions x+1, x+2,..., y.
// At each position k, we first check the value of z[k-x].
// If k+z[k-x] < y, we know that z[k] = z[k-x].
// However, if k+z[k-x] ¸ y, s[0... y-k] equals s[k... y],
// and to determine the value of z[k] we need to compare the substrings character by character.
// Still, the algorithm works in O(n) time, because we start comparing at positions y-k+1 and y+1.

// Using the Z-array
// It is often a matter of taste whether to use string hashing or the Z-algorithm.
// Unlike hashing, the Z-algorithm always works and there is no risk for collisions.
// On the other hand, the Z-algorithm is more difficult to implement and some problems can only be solved using hashing.
// As an example, consider again the pattern matching problem, where our task is to find the occurrences of a pattern p in a string s.
// We already solved this problem efficiently using string hashing, but the Z-algorithm provides another way to solve the problem.
// A usual idea in string processing is to construct a string that consists of multiple strings separated by special characters.
// In this problem, we can construct a string p#s, where p and s are separated by a special character # that does not occur in the strings.
// The Z-array of p#s tells us the positions where p occurs in s, because such positions contain the length of p.
// NOTE MAYBE TRANSFER THIS TO SubstringSearchUsingZArray


}

}
