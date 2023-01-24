#pragma once

#include <limits>
#include <vector>

namespace alba
{

class LongestBitonicSubsequence
{
public:
    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;
    using IndexToIndex = std::vector<Index>;

    LongestBitonicSubsequence(Values const& sequence);

    Index getLongestLength() const;
    Values getLongestSubsequence() const;
    
private:
    void computeSubIncreasingLengths(IndexToIndex & subIncreasingLengths, IndexToIndex & indexToIncreasingPreviousIndex) const;
    void computeSubDecreasingLengths(IndexToIndex & subDecreasingLengths, IndexToIndex & indexToDecreasingPreviousIndex) const;

    Values getLongestSubsequence(
            IndexToIndex & subIncreasingLengths,
            IndexToIndex & subDecreasingLengths,
            IndexToIndex & indexToIncreasingPreviousIndex,
            IndexToIndex & indexToDecreasingPreviousIndex) const;
    Values m_sequence;

};

}

//
