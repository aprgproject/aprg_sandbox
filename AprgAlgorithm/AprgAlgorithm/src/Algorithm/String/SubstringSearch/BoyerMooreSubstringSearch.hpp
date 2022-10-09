#pragma once

#include <array>
#include <string>

namespace alba
{

namespace algorithm
{

template <typename Index>
class BoyerMooreSubstringSearch
{
public:
    using RadixType = unsigned int;
    using Position = int; // allows negative position
    static constexpr RadixType RADIX=256U;
    using SkipTable = std::array<Position, RADIX>;

    BoyerMooreSubstringSearch(std::string const& substringToMatch)
        : m_substringToMatch(substringToMatch)
        , m_rightMostLetterPosition{}
    {
        initialize();
    }

    Index search(std::string const& mainString)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index mainLength(mainString.size());
        Index substringLength(m_substringToMatch.size());
        int skipValue;
        for(Index searchIndex=0; searchIndex<mainLength-substringLength; searchIndex+=skipValue)
        {
            skipValue=0;
            for(Index matchIndex=0; matchIndex<substringLength; matchIndex++)
            {
                Index matchReverseIndex(substringLength-matchIndex-1);
                if(m_substringToMatch.at(matchReverseIndex) != mainString.at(searchIndex+matchReverseIndex)) // if mismatch
                {
                    Position positionOfLetter(m_rightMostLetterPosition.at(mainString.at(searchIndex+matchReverseIndex)));
                    // (Case 1) happens if positionOfLetter is -1
                    if(static_cast<Position>(matchReverseIndex) > positionOfLetter+1) // there should be at least 1 difference to maintain forward progress
                    {
                        skipValue = matchReverseIndex - positionOfLetter; // (Case 2a) // align letter position for skip value
                    }
                    else
                    {
                        skipValue = 1; // (Case 2b) guarantee forward progress
                    }
                    break;
                }
            }
            if(skipValue == 0) // all letters matched
            {
                result = searchIndex;
                break;
            }
        }
        return result;
    }

private:

    void initialize()
    {
        char i(0U);
        for(RadixType i=0; i<RADIX; i++)
        {
            m_rightMostLetterPosition[i] = -1; // assign negative one for case 1
        }
        for(char const c : m_substringToMatch)
        {
            m_rightMostLetterPosition[c] = i++;
            // if there are multiple instances of letter, it overwrites (right most position is taken)
        }
    }

    std::string m_substringToMatch;
    SkipTable m_rightMostLetterPosition;
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


}

}
