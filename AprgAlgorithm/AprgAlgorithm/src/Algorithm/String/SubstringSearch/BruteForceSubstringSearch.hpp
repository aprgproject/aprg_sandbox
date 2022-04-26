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

    BruteForceSubstringSearch(std::string const& substringToSearch)
        : m_substringToSearch(substringToSearch)
    {}

    unsigned int search(std::string const& stringToCheck)
    {
        return searchWithLoops(stringToCheck, m_substringToSearch);
    }

private:

    unsigned int searchWithLoops(std::string const& , std::string const&)
    {
        static_assert(sizeof(BruteForceSubstringSearch) != sizeof(BruteForceSubstringSearch),
                      "The number of loops should be one or two. Other numbers are have no implementation");
        return 0;
    }

    unsigned int searchUsingOneLoop(
            std::string const& stringToCheck,
            std::string const& substringToSearch)
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int mainLength(stringToCheck.length());
        unsigned int substringLength(substringToSearch.length());
        unsigned int i=0, j=0;
        for(; i<mainLength && j<substringLength; i++)
        {
            if(stringToCheck.at(i) == substringToSearch.at(j))
            {
                j++;
            }
            else
            {
                i-=j;
                j=0;
            }
        }
        if(j == substringLength)
        {
            result = i-substringLength;
        }
        return result;
    }

    unsigned int searchUsingTwoLoops(
            std::string const& stringToCheck,
            std::string const& substringToSearch)
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int mainLength(stringToCheck.length());
        unsigned int substringLength(substringToSearch.length());
        for(unsigned int i=0; i <= mainLength-substringLength; i++)
        {
            unsigned int j=0;
            for(; j < substringLength; j++)
            {
                if(stringToCheck.at(i+j) != substringToSearch.at(j))
                {
                    break;
                }
            }
            if(j == substringLength)
            {
                result = i;
                break;
            }
        }
        return result;
    }
    std::string m_substringToSearch;
};

template <>
unsigned int BruteForceSubstringSearch<1U>::searchWithLoops(std::string const& stringToCheck, std::string const& substringToSearch)
{
    return searchUsingOneLoop(stringToCheck, substringToSearch);
}

template <>
unsigned int BruteForceSubstringSearch<2U>::searchWithLoops(std::string const& stringToCheck, std::string const& substringToSearch)
{
    return searchUsingTwoLoops(stringToCheck, substringToSearch);
}


}

}
