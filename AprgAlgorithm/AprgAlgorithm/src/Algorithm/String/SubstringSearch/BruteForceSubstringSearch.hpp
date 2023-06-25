#pragma once

#include <string>
namespace alba {

namespace algorithm {

template <int numberOfLoops>
class BruteForceSubstringSearch {
public:
    BruteForceSubstringSearch(std::string const& substringToMatch) : m_substringToMatch(substringToMatch) {}

    int search(std::string const& mainString) { return searchWithLoops(mainString, m_substringToMatch); }

private:
    int searchWithLoops(std::string const&, std::string const&) {
        static_assert(
            sizeof(BruteForceSubstringSearch) != sizeof(BruteForceSubstringSearch),
            "The number of loops should be one or two. Other numbers have no implementation");
        return 0;
    }

    int searchUsingOneLoop(
        std::string const& mainString,
        std::string const& substringToMatch)  // implementation with one loop
    {
        int result(static_cast<int>(std::string::npos));
        int mainLength(mainString.length());
        int substringLength(substringToMatch.length());
        int searchIndex = 0, matchIndex = 0;
        for (; searchIndex < mainLength && matchIndex < substringLength; searchIndex++) {
            if (mainString[searchIndex] == substringToMatch[matchIndex]) {
                matchIndex++;  // matchIndex represents the index of matches as well
            } else {
                searchIndex -= matchIndex;  // if there is a mismatch, go back                matchIndex = 0;             // reset because matchIndex represents the index of matches as well
            }
        }
        if (matchIndex == substringLength)  // if matchIndex reached length        {
            result = searchIndex - substringLength;
        }
        return result;
    }

    int searchUsingTwoLoops(
        std::string const& mainString,
        std::string const& substringToMatch)  // implementation with two loops
    {
        int result(static_cast<int>(std::string::npos));
        int mainLength(mainString.length());
        int substringLength(substringToMatch.length());
        for (int offset = 0; offset + substringLength <= mainLength; offset++) {
            int matchIndex = 0;
            for (; matchIndex < substringLength; matchIndex++) {
                if (mainString[offset + matchIndex] != substringToMatch[matchIndex]) {
                    // matchIndex represents the index of matches as well
                    break;
                }            }
            if (matchIndex == substringLength)  // if matchIndex reached length
            {
                result = offset;                break;
            }
        }
        return result;
    }
    std::string m_substringToMatch;
};

template <>
int BruteForceSubstringSearch<1>::searchWithLoops(
    std::string const& stringToSearch, std::string const& substringToMatch) {
    return searchUsingOneLoop(stringToSearch, substringToMatch);
}

template <>
int BruteForceSubstringSearch<2>::searchWithLoops(
    std::string const& stringToSearch, std::string const& substringToMatch) {
    return searchUsingTwoLoops(stringToSearch, substringToMatch);
}

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

}  // namespace algorithm

}  // namespace alba
