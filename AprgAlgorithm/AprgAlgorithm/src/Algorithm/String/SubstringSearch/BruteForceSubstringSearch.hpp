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

    BruteForceSubstringSearch(std::string const& subStringToSearch)
        : m_subStringToSearch(subStringToSearch)
    {}

    unsigned int search(std::string const& mainString)
    {
        return searchWithLoops(mainString, m_subStringToSearch);
    }

private:
    unsigned int searchWithLoops(std::string const& , std::string const&)
    {
        static_assert(sizeof(BruteForceSubstringSearch) != sizeof(BruteForceSubstringSearch),                      "The number of loops should be one or two. Other numbers are have no implementation");
        return 0;
    }

    unsigned int searchUsingOneLoop(
            std::string const& mainString,
            std::string const& subStringToSearch)
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int mainLength(mainString.length());
        unsigned int subStringLength(subStringToSearch.length());
        unsigned int i=0, j=0;
        for(; i<mainLength && j<subStringLength; i++)
        {
            if(mainString.at(i) == subStringToSearch.at(j))
            {
                j++;
            }
            else
            {
                i-=j;
                j=0;
            }
        }
        if(j == subStringLength)
        {
            result = i-subStringLength;
        }
        return result;
    }

    unsigned int searchUsingTwoLoops(
            std::string const& mainString,
            std::string const& subStringToSearch)
    {
        unsigned int result(static_cast<unsigned int>(std::string::npos));
        unsigned int mainLength(mainString.length());
        unsigned int subStringLength(subStringToSearch.length());
        for(unsigned int i=0; i <= mainLength-subStringLength; i++)
        {
            unsigned int j=0;
            for(; j < subStringLength; j++)
            {
                if(mainString.at(i+j) != subStringToSearch.at(j))
                {
                    break;
                }
            }
            if(j == subStringLength)
            {
                result = i;
                break;
            }
        }
        return result;
    }
    std::string m_subStringToSearch;
};

template <>unsigned int BruteForceSubstringSearch<1U>::searchWithLoops(std::string const& mainString, std::string const& subStringToSearch)
{
    return searchUsingOneLoop(mainString, subStringToSearch);
}
template <>
unsigned int BruteForceSubstringSearch<2U>::searchWithLoops(std::string const& mainString, std::string const& subStringToSearch)
{
    return searchUsingTwoLoops(mainString, subStringToSearch);
}


}

}
