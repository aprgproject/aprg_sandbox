#pragma once

#include <Algorithm/String/SuffixArray/SuffixArray.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace algorithm {

template <typename Index>
class KeywordInContextIndexing {
public:
    KeywordInContextIndexing(std::string const& searchSpace) : m_searchSpace(searchSpace), m_suffixArray(searchSpace) {}

    stringHelper::strings getKeywordInContextIndexing(std::string const& stringToCheck, Index const lengthOfContext) {
        stringHelper::strings result;
        Index totalLength(m_searchSpace.length());
        for (Index i = m_suffixArray.getRank(stringToCheck);
             i < totalLength && doesItStartWith(m_suffixArray.getSuffixViewAt(i), stringToCheck); i++) {
            Index start = std::max(Index(0), m_suffixArray.getIndexOnMainStringOfSuffixAt(i) - lengthOfContext);
            Index end =
                std::min(totalLength - 1, start + static_cast<Index>(stringToCheck.length()) + 2 * lengthOfContext);
            result.emplace_back(m_searchSpace.substr(start, end - start));
        }
        return result;
    }

private:
    bool doesItStartWith(std::string_view searchSpace, std::string_view stringToCheck) {
        return searchSpace.length() >= stringToCheck.length() &&
               searchSpace.substr(0, stringToCheck.length()) == stringToCheck;
    }
    std::string m_searchSpace;
    SuffixArray<Index> m_suffixArray;
};
}  // namespace algorithm
}  // namespace alba
// Applications: Linguistics, databases, web search, word processing