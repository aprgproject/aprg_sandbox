#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <array>
#include <string>

namespace alba {

namespace algorithm {

template <typename Index>
class BoyerMooreSubstringSearch {
public:
    static_assert(typeHelper::isIntegralType<Index>(), "Index must be signed (to handle -1)");
    using RadixType = int;
    static constexpr RadixType RADIX = 256;
    static constexpr Index INVALID_POSITION = -1;
    using SkipTable = std::array<Index, RADIX>;

    BoyerMooreSubstringSearch(std::string const& substringToMatch)
        : m_substringToMatch(substringToMatch), m_rightMostLetterIndex{} {
        initialize();
    }

    Index search(std::string const& mainString) {
        Index result(static_cast<Index>(std::string::npos));
        Index mainLength(mainString.size());
        Index substringLength(m_substringToMatch.size());
        int skipValue(0);
        for (Index searchIndex = 0; searchIndex + substringLength <= mainLength; searchIndex += skipValue) {
            skipValue = 0;
            for (Index matchStartIndex = 0; matchStartIndex < substringLength; matchStartIndex++) {
                Index matchEndIndex(substringLength - 1 - matchStartIndex);
                // if mismatch
                if (m_substringToMatch[matchEndIndex] != mainString[searchIndex + matchEndIndex]) {
                    Index letterIndex(m_rightMostLetterIndex[mainString[searchIndex + matchEndIndex]]);
                    // (Case 1) happens if positionOfLetter is -1
                    // there should be at least 1 difference to maintain forward progress
                    if (letterIndex + 1 < static_cast<Index>(matchEndIndex)) {
                        // (Case 2a) align letter position for skip value
                        skipValue = matchEndIndex - letterIndex;
                    } else {
                        // (Case 2b) guarantee forward progress
                        skipValue = 1;
                    }
                    break;
                }
            }
            if (skipValue == 0)  // all letters matched
            {
                result = searchIndex;
                break;
            }
        }
        return result;
    }

private:
    void initialize() {
        for (RadixType i = 0; i < RADIX; i++) {
            m_rightMostLetterIndex[i] = INVALID_POSITION;  // assign negative one for case 1
        }
        Index substringIndex = 0;
        for (char const c : m_substringToMatch) {
            // if there are multiple instances of letter, it overwrites (right most position is taken)
            m_rightMostLetterIndex[c] = substringIndex++;
        }
    }

    std::string m_substringToMatch;
    SkipTable m_rightMostLetterIndex;
};

// Intuition:
// -> Scan characters in pattern from right to left
// -> Can skip as many as M text chars when finding one not in the pattern

// How much to skip?
// Case 1: Mismatch character not in pattern
// -> increment starting index with one character beyond the mismatch
// ---> Before:
// .......TLE.......
// ....NEEDLE.......
// ---> After:
// .......TLE.......
// ........NEEDLE...
// Case 2a: Mismatch character in pattern
// -> align text character with right most pattern character
// ---> Before:
// .......NLE.......
// ....NEEDLE.......
// ---> After:
// .......NLE.......
// .......NEEDLE....
// Case 2b: Mismatch character in pattern (but heuristic no help)
// -> increment staring index by 1 (to guarantee forward progress)
// ---> Before:
// .......ELE.......
// ....NEEDLE.......
// ---> After:
// .......ELE.......
// .....NEEDLE......

// Property
// -> Substring search with the Boyer-Moore mismatch character heuristic takes about
// ~N/M (sublinear) character compares to search for a pattern of length M in a test of length N.
// The longer the pattern gets the faster the search gets.
// Sublinear? Amazing! Sedgewick: "Thats kind of amazing."

// However worst case can be as bad as ~M*N.
// -> For example, "ABBBB" as the pattern to match with would search on "BBBBBBBBBB"

// Improvement:
// -> Boyer-Moore variant: Can improve worst case to ~3N by adding a KMP-like rule to guard against repetitive patterns.

}  // namespace algorithm

}  // namespace alba
