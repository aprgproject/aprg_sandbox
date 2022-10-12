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
    ~ZAlgorithm() = delete;
    ZAlgorithm(ZAlgorithm const&) = delete;
    ZAlgorithm & operator= (ZAlgorithm const&) = delete;
    ZAlgorithm(ZAlgorithm &&) = delete;
    ZAlgorithm & operator= (ZAlgorithm &&) = delete;

    // The Z-array z of a string s of length n contains for each k = 0,1,...,n-1
    // the length of the longest substring of s that begins at position k and is a prefix of s.
    // Thus, z[k]=p tells us that s[0... p-1] equals s[k...k+p-1].
    // Many string processing problems can be efficiently solved using the Z-array.

    static constexpr Indexes getZArray(std::string const& mainString)
    {
        Index mainStringLength = mainString.length();
        Indexes result(mainStringLength, Index{});
        Index startOfPrefix=0, endOfPrefix=0;
        for (Index position=1; position<mainStringLength; position++)
        {
            result[position] = std::max(0U, std::min(result.at(position-startOfPrefix), endOfPrefix-position+1));
            while (position+result.at(position) < mainStringLength
                   && mainString.at(result.at(position)) == mainString.at(position+result.at(position)))
            {
                startOfPrefix = position;
                endOfPrefix = position+result.at(position);
                result[position]++;
            }
        }
        return result;
    }
};

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


}

}
