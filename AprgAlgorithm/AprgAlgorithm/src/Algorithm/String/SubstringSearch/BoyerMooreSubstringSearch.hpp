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
    static constexpr RadixType RADIX=256U;
    using RightArray = std::array<char, RADIX>;

    BoyerMooreSubstringSearch(std::string const& substringToSearch)
        : m_substringToSearch(substringToSearch)
        , m_right{}
    {
        initialize();
    }

    Index search(std::string const& mainString)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index mainStringLength(mainString.size());
        Index substringLength(m_substringToSearch.size());
        int skip(0);
        for(Index i=0; i<mainStringLength-substringLength; i+=skip)
        {
            skip=0;
            for(Index j=0; j<substringLength; j++)
            {
                Index reversedJ(substringLength-j-1);
                if(m_substringToSearch.at(reversedJ) != mainString.at(i+reversedJ))
                {
                    skip = reversedJ - m_right.at(mainString.at(i+reversedJ));
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
        for(char const c : m_substringToSearch)
        {
            m_right[c] = i++;
        }
    }

    std::string m_substringToSearch;
    RightArray m_right;
};

}

}
