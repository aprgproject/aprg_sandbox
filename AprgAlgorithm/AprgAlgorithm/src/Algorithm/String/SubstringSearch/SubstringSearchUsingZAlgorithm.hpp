#pragma once

#include <Algorithm/String/ZAlgorithm/ZAlgorithm.hpp>

#include <string>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Index, char UNIQUE_DIVIDING_CHARACTER>
class SubstringSearchUsingZAlgorithm {
public:
    using Indexes = std::vector<Index>;

    SubstringSearchUsingZAlgorithm(std::string const& query) : m_query(query) {}

    Index search(std::string const& searchSpace) const { return searchForFirstSubstring(searchSpace); }

    Index searchForFirstSubstring(std::string const& searchSpace) const {
        Index result = static_cast<Index>(std::string::npos);
        std::string stringForZAlgorithm = createStringForZAlgorithm(searchSpace);
        Indexes prefixLengths = calculatePrefixLengths(stringForZAlgorithm);
        Index queryLength = m_query.length();
        Index i = queryLength;
        for (; i < static_cast<Index>(prefixLengths.size()); i++) {
            if (prefixLengths[i] >= queryLength) {
                result = i - queryLength - 1;
                break;
            }
        }
        return result;
    }

    Indexes searchForAllSubstrings(std::string const& searchSpace) const {
        Indexes result{};
        std::string stringForZAlgorithm = createStringForZAlgorithm(searchSpace);
        Indexes prefixLengths = calculatePrefixLengths(stringForZAlgorithm);
        Index queryLength = m_query.length();
        Index i = queryLength;
        for (; i < static_cast<int>(prefixLengths.size()); i++) {
            if (prefixLengths[i] >= queryLength) {
                result.emplace_back(i - queryLength - 1);
            }
        }
        return result;
    }

private:
    std::string createStringForZAlgorithm(std::string const& searchSpace) const {
        return m_query + UNIQUE_DIVIDING_CHARACTER + searchSpace;
    }

    Indexes calculatePrefixLengths(std::string const& stringForZAlgorithm) const {
        return ZAlgorithm<Index>::getPrefixLengthsUsingTheZAlgorithm(stringForZAlgorithm);
    }

    std::string m_query;
};

}  // namespace algorithm

}  // namespace alba

// Using the Z-array
// It is often a matter of taste whether to use string hashing or the Z-algorithm.
// Unlike hashing, the Z-algorithm always works and there is no risk for collisions.
// On the other hand, the Z-algorithm is more difficult to implement and some problems can only be solved using hashing.
// As an example, consider again the pattern matching problem, where our task is to find the occurrences of a pattern p
// in a string s. We already solved this problem efficiently using string hashing, but the Z-algorithm provides another
// way to solve the problem. A usual idea in string processing is to construct a string that consists of multiple
// strings separated by special characters. In this problem, we can construct a concatenated string p#s, where p and s
// are separated by a special character # that does not occur in the strings. The Z-array of p#s tells us the positions
// where p occurs in s, because such positions contain the length of p.
