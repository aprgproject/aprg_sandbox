#pragma once

#include <Algorithm/String/SuffixArray/SuffixArray.hpp>

namespace alba
{

namespace algorithm
{

template <typename DataType>
class LongestRepeatedSubstring
{
public:

static std::string getLongestRepeatedSubstring(std::string const& stringToCheck)
{
    SuffixArray<DataType> suffixArray(stringToCheck);
    std::string result;
    DataType length(stringToCheck.length());
    for(DataType i=1; i<length; i++)
    {
        std::string commonPrefix(suffixArray.getLongestCommonPrefixOfTwoSuffixes(i-1, i));
        if(result.size() < commonPrefix.size())
        {
            result = commonPrefix;
        }
    }
    return result;
}

};

}

}
