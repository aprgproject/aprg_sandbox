#pragma once

#include <string>

namespace alba
{

namespace algorithm
{

template <unsigned int numberOfLoops>
class BruteForceSubstringSearch
{
public :

    BruteForceSubstringSearch(std::string const& substringToMatch)
        : m_substringToMatch(substringToMatch)
    {}

    unsigned int search(std::string const& stringToSearch)
    {
        return searchWithLoops(stringToSearch, m_substringToMatch);
    }

private:
    unsigned int searchWithLoops(std::string const& , std::string const&)
    {
        static_assert(sizeof(BruteForceSubstringSearch) != sizeof(BruteForceSubstringSearch),
                      "The number of loops should be one or two. Other numbers have no implementation");
        return 0;
    }

    unsigned int searchUsingOneLoop(
            std::string const& stringToSearch,
            std::string const& substringToMatch) // implementation with one loop
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int searchLength(stringToSearch.length());
        unsigned int matchLength(substringToMatch.length());
        unsigned int searchIndex=0, matchIndex=0;
        for(; searchIndex<searchLength && matchIndex<matchLength; searchIndex++)
        {
            if(stringToSearch.at(searchIndex) == substringToMatch.at(matchIndex))
            {
                matchIndex++; // matchIndex represents the index of matches as well
            }
            else
            {
                searchIndex-=matchIndex; // if there is a mismatch, go back
                matchIndex=0; // reset because matchIndex represents the index of matches as well
            }
        }
        if(matchIndex == matchLength) // if matchIndex reached length
        {
            result = searchIndex-matchLength;
        }
        return result;
    }

    unsigned int searchUsingTwoLoops(
            std::string const& stringToSearch,
            std::string const& substringToMatch) // implementation with two loops
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int searchLength(stringToSearch.length());
        unsigned int matchLength(substringToMatch.length());
        for(unsigned int offset=0; offset <= searchLength-matchLength; offset++)
        {
            unsigned int matchIndex=0;
            for(; matchIndex < matchLength; matchIndex++)
            {
                if(stringToSearch.at(offset+matchIndex) != substringToMatch.at(matchIndex))
                {
                    // matchIndex represents the index of matches as well
                    break;
                }
            }
            if(matchIndex == matchLength) // if matchIndex reached length
            {
                result = offset;
                break;
            }
        }
        return result;
    }
    std::string m_substringToMatch;
};

template <>
unsigned int BruteForceSubstringSearch<1U>::searchWithLoops(std::string const& stringToSearch, std::string const& substringToMatch)
{
    return searchUsingOneLoop(stringToSearch, substringToMatch);
}

template <>
unsigned int BruteForceSubstringSearch<2U>::searchWithLoops(std::string const& stringToSearch, std::string const& substringToMatch)
{
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

}

}