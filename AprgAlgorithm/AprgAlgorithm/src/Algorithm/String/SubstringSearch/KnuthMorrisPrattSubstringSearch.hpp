#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template <typename Index>
class KnuthMorrisPrattSubstringSearch
{
public:
    using RadixType = unsigned int;
    using DfaMatrix = matrix::AlbaMatrix<Index>;
    static constexpr RadixType RADIX=256U;

    KnuthMorrisPrattSubstringSearch(std::string const& substringToSearch)
        : m_substringToSearch(substringToSearch)
        , m_dfaMatrix(RADIX, substringToSearch.length())
    {
        initialize();
    }

    Index search(std::string const& stringToCheck)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index stringToCheckLength(stringToCheck.size());
        Index substringLength(m_substringToSearch.size());
        Index i=0, j=0;
        for(; i<stringToCheckLength && j<substringLength; i++)
        {
            j = m_dfaMatrix.getEntry(stringToCheck.at(i), j);
        }
        if(j == substringLength)
        {            result = i-substringLength;
        }
        return result;
    }
private:

    void initialize()
    {
        if(!m_substringToSearch.empty())
        {
            m_dfaMatrix.setEntry(m_substringToSearch.at(0), 0, 1);
            Index substringLength(m_substringToSearch.size());
            Index lastIndex(0);
            for(Index i=1; i<substringLength; i++)
            {
                for(RadixType c=0; c<RADIX; c++) // copy mismatch cases
                {
                    m_dfaMatrix.setEntry(c, i, m_dfaMatrix.getEntry(c, lastIndex));
                }
                m_dfaMatrix.setEntry(m_substringToSearch.at(i), i, i+1); // set match case
                lastIndex = m_dfaMatrix.getEntry(m_substringToSearch.at(i), lastIndex); // update restart state
            }
        }
    }
    std::string m_substringToSearch;
    DfaMatrix m_dfaMatrix;
};

}

}
