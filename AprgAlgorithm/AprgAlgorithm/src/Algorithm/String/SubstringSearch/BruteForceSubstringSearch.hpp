#pragma once

#include <string>
namespace alba {

namespace algorithm {

template <int numberOfLoops>
class BruteForceSubstringSearch {
public:
    BruteForceSubstringSearch(std::string const& query) : m_query(query) {}

    int search(std::string const& searchSpace) const { return searchWithLoops(searchSpace, m_query); }

private:
    int searchWithLoops(std::string const&, std::string const&) const {
        static_assert(
            sizeof(BruteForceSubstringSearch) != sizeof(BruteForceSubstringSearch),
            "The number of loops should be one or two. Other numbers have no implementation");
        return 0;
    }

    int searchUsingOneLoop(std::string const& searchSpace, std::string const& query) const {
        int result(static_cast<int>(std::string::npos));
        int searchSpaceLength(searchSpace.length());
        int queryLength(query.length());
        int searchIndex = 0, matchIndex = 0;
        for (; searchIndex < searchSpaceLength && matchIndex < queryLength; searchIndex++) {
            if (searchSpace[searchIndex] == query[matchIndex]) {
                matchIndex++;  // matchIndex represents the index of matches as well
            } else {
                searchIndex -= matchIndex;  // if there is a mismatch, go back
                matchIndex = 0;             // reset because matchIndex represents the index of matches as well
            }
        }
        if (matchIndex == queryLength)  // if matchIndex reached length
        {
            result = searchIndex - queryLength;
        }
        return result;
    }

    int searchUsingTwoLoops(std::string const& searchSpace, std::string const& query) const {
        int result(static_cast<int>(std::string::npos));
        int searchSpaceLength(searchSpace.length());
        int queryLength(query.length());
        for (int offset = 0; offset + queryLength <= searchSpaceLength; offset++) {
            int matchIndex = 0;
            for (; matchIndex < queryLength; matchIndex++) {
                if (searchSpace[offset + matchIndex] != query[matchIndex]) {
                    // matchIndex represents the index of matches as well
                    break;
                }
            }
            if (matchIndex == queryLength)  // if matchIndex reached length
            {
                result = offset;
                break;
            }
        }
        return result;
    }
    std::string m_query;
};

template <>
int BruteForceSubstringSearch<1>::searchWithLoops(std::string const& searchSpace, std::string const& query) const {
    return searchUsingOneLoop(searchSpace, query);
}

template <>
int BruteForceSubstringSearch<2>::searchWithLoops(std::string const& searchSpace, std::string const& query) const {
    return searchUsingTwoLoops(searchSpace, query);
}

}  // namespace algorithm

}  // namespace alba

// Brute-force substring search: worst case
// -> Brute force algorithm can be slow if test and pattern are repetitive.
// -> Worst case: ~MN char compares

// Backup:
// -> In many applications we want to avoid backup in text stream
// ---> Treat input as stream of data
// ---> Abstract model: standard input
// -> Brute-force algorithm beeds to backup for every mismatch

// Brute force is not always good enough:
// -> Theoretical challenge: Linear time guarantee.
// -> Avoid backup in the text stream.
