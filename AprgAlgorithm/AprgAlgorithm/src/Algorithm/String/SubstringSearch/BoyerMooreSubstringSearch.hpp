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

    BoyerMooreSubstringSearch(std::string const& query) : m_query(query), m_rightMostLetterIndex{} { initialize(); }

    Index search(std::string const& searchSpace) const {
        Index result(static_cast<Index>(std::string::npos));
        Index searchSpaceLength(searchSpace.length());
        Index queryLength(m_query.length());
        int skipValue(0);
        for (Index searchIndex = 0; searchIndex + queryLength <= searchSpaceLength; searchIndex += skipValue) {
            skipValue = 0;
            for (Index rightMostMismatch = queryLength - 1; rightMostMismatch >= 0; --rightMostMismatch) {
                // if mismatch
                if (m_query[rightMostMismatch] != searchSpace[searchIndex + rightMostMismatch]) {
                    Index letterIndex(m_rightMostLetterIndex[searchSpace[searchIndex + rightMostMismatch]]);
                    if (letterIndex + 1 < static_cast<Index>(rightMostMismatch)) {
                        // (Case 1: "Mismatch character is not in pattern")
                        // This happens if letterIndex is -1.
                        // -> In this case, use the skip value to move past the mismatch character
                        // (Case 2a: "Mismatch character is in the pattern")
                        // -> In this case, use the skip value to align what was previously mismatched
                        skipValue = rightMostMismatch - letterIndex;
                    } else {
                        // (Case 2b: "Mismatch character is in the pattern (but heuristic no help)")
                        // ->  In this case, The skip value should just be one to maintain forward progress
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
        for (RadixType i = 0; i < RADIX; ++i) {
            m_rightMostLetterIndex[i] = INVALID_POSITION;  // assign negative one for case 1
        }
        Index substringIndex = 0;
        for (char const c : m_query) {
            // if there are multiple instances of letter, it overwrites (right most position is taken)
            m_rightMostLetterIndex[c] = substringIndex++;
        }
    }

    std::string m_query;
    SkipTable m_rightMostLetterIndex;
};

}  // namespace algorithm

}  // namespace alba

// Intuition:
// -> Scan characters in pattern from right to left
// -> Can skip as many as M text chars when finding one not in the pattern

// How much to skip?
// Case 1: Mismatch character not in the pattern
// -> increment starting index with one character beyond the mismatch (move past the mismatch)
// ---> Before:
// .......TLE.......
// ....NEEDLE.......
// ---> After (move past the T in the mainstring):
// .......TLE.......
// ........NEEDLE...
// Case 2a: Mismatch character is in the pattern
// -> align text character with right most pattern character
// ---> Before:
// .......NLE.......
// ....NEEDLE.......
// ---> After (N is aligned in the substring and mainstring):
// .......NLE.......
// .......NEEDLE....
// Case 2b: Mismatch character is in the pattern (but heuristic no help)
// -> increment staring index by 1 (to guarantee forward progress)
// ---> Before:
// .......ELE.......
// ....NEEDLE.......
// ---> After (just add one to guarantee forward progress):
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

// Other Discussions:
// Bad Character Heuristic
// -> The idea of bad character heuristic is simple (like the algorithm above).
// -> The character of the text which doesn’t match with the current character of the pattern is called the Bad
// Character.
// -> Upon mismatch, we shift the pattern until:
// ---> The mismatch becomes a match
// ---> Pattern P moves past the mismatched character.
