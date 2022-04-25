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
    using DfaMatrix = matrix::AlbaMatrix<Index>;
    static constexpr Index RADIX=256U;

    KnuthMorrisPrattSubstringSearch(std::string const& subStringToSearch)
        : m_subStringToSearch(subStringToSearch)
        , m_dfaMatrix(RADIX, subStringToSearch.length())
    {
        initialize();
    }

    Index search(std::string const& mainString)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index mainStringLength(mainString.size());
        Index subStringLength(m_subStringToSearch.size());
        Index i=0, j=0;
        for(; i<mainStringLength && j<subStringLength; i++)
        {
            j = m_dfaMatrix.getEntry(mainString.at(i), j);
        }
        if(j == subStringLength)
        {
            result = i-subStringLength;
        }
        return result;
    }

private:

    void initialize()
    {
        if(!m_subStringToSearch.empty())
        {
            m_dfaMatrix.setEntry(m_subStringToSearch.at(0), 0, 1);
            Index subStringLength(m_subStringToSearch.size());
            Index lastIndex(0);
            for(Index i=1; i<subStringLength; i++)
            {
                for(Index c=0; c<RADIX; c++) // copy mismatch cases
                {
                    m_dfaMatrix.setEntry(c, i, m_dfaMatrix.getEntry(c, lastIndex));
                }
                m_dfaMatrix.setEntry(m_subStringToSearch.at(i), i, i+1); // set match case
                lastIndex = m_dfaMatrix.getEntry(m_subStringToSearch.at(i), lastIndex); // update restart state
            }
        }
    }
    std::string m_subStringToSearch;
    DfaMatrix m_dfaMatrix;
};

}

}
