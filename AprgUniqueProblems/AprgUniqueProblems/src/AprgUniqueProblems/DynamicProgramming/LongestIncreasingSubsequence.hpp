#pragma once

#include <map>
#include <vector>

namespace alba
{

class LongestIncreasingSubsequence
{
public:
    // Our first problem is to find the longest increasing subsequence in an array of n elements.
    // This is a maximum-length sequence of array elements that goes from left to right,
    // and each element in the sequence is larger than the previous element.

    using Length = unsigned int;
    using Value = unsigned int;
    using Sequence = std::vector<Value>;
    using LengthToIndexMap = std::multimap<Length, Length>;
    using Sequences = std::vector<Sequence>;

    LongestIncreasingSubsequence(Sequence const& sequenceToCheck);

    Length getLongestIncreasingSubsequenceLength();
    Sequence getLongestIncreasingSubsequence();
private:
    Sequence m_sequenceToCheck;

};

}
