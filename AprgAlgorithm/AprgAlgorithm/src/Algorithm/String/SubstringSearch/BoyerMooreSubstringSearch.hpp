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
    static constexpr Index RADIX=256U;
    using RightArray = std::array<char, RADIX>;

    BoyerMooreSubstringSearch(std::string const& subStringToSearch)
        : m_subStringToSearch(subStringToSearch)
        , m_right{}
    {
        initialize();
    }

    Index search(std::string const& mainString)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index mainStringLength(mainString.size());
        Index subStringLength(m_subStringToSearch.size());
        int skip(0);
        for(Index i=0; i<mainStringLength-subStringLength; i+=skip)
        {
            skip=0;
            for(int j=subStringLength-1 ; j>=0; j--)
            {
                if(m_subStringToSearch.at(j) != mainString.at(i+j))
                {
                    skip = j - m_right.at(mainString.at(i+j));
                    skip = (skip < 1) ? 1 : skip;
                    break;
                }
            }
            if(skip == 0)
            {
                result = i;
                break;
            }
        }
        return result;
    }

private:

    void initialize()
    {
        char i(0U);
        for(char const c : m_subStringToSearch)
        {
            m_right[c] = i++;
        }
    }

    std::string m_subStringToSearch;
    RightArray m_right;
};

}

}
