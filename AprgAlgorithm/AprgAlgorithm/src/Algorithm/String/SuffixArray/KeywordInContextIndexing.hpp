#pragma once

#include <Algorithm/String/SuffixArray/SuffixArray.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba
{

namespace algorithm
{

template <typename DataType>
class KeywordInContextIndexing
{
public:
    KeywordInContextIndexing(std::string const& mainString)
        : m_mainString(mainString)
        , m_suffixArray(mainString)
    {}

    stringHelper::strings getKeywordInContextIndexing(std::string const& stringToCheck, DataType const lengthOfContext)
    {
        stringHelper::strings result;
        DataType totalLength(m_mainString.length());
        for(DataType i = m_suffixArray.getRank(stringToCheck); i<totalLength && doesItStartWith(m_suffixArray.getSuffixAt(i), stringToCheck); i++)
        {
            DataType start = std::max(DataType(0), m_suffixArray.getIndexOnMainStringOfSuffixAt(i) - lengthOfContext);
            DataType end = std::min(totalLength-1, start+stringToCheck.length() + 2*lengthOfContext);
            result.emplace_back(m_mainString.substr(start, end-start));
        }
        return result;
    }

private:
    bool doesItStartWith(std::string const& mainString, std::string const& stringToCheck)
    {
        return mainString.length() >= stringToCheck.length() && mainString.substr(0, stringToCheck.length()) == stringToCheck;
    }
    std::string m_mainString;
    SuffixArray<DataType> m_suffixArray;
};

// Applications: Linguistics, databases, web search, word processing

}

}