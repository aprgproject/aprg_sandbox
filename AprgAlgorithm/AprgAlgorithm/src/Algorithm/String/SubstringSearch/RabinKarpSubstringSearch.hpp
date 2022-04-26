#pragma once

#include <string>

namespace alba
{

namespace algorithm
{

template <typename Index, typename HashValue>
class RabinKarpSubstringSearch
{
public:
    using RadixType = unsigned int;
    static constexpr RadixType RADIX=256U;
    static constexpr HashValue A_LARGE_PRIME=1229952067U; // hard coded for now (think of an implementation later)

    RabinKarpSubstringSearch(std::string const& substringToSearch)
        : m_substringToSearch(substringToSearch)
        , m_substringLength(substringToSearch.length())
        , m_largeRandomPrime(A_LARGE_PRIME)
        , m_startValueFromRadixAndLength(calculateStartValueFromRadixAndLength(m_substringLength))
        , m_substringHash(getHash(m_substringToSearch, m_substringLength))
    {}

    Index search(std::string const& mainString)
    {
        Index result(static_cast<Index>(std::string::npos));
        Index mainStringLength(mainString.size());
        HashValue mainStringHash(getHash(mainString, m_substringLength));
        if(m_substringHash == mainStringHash)
        {
            result = 0;
        }
        else
        {
            for(Index i=m_substringLength; i<mainStringLength; i++)
            {
                mainStringHash
                        = (mainStringHash + m_largeRandomPrime
                           - m_startValueFromRadixAndLength * mainString.at(i-m_substringLength) % m_largeRandomPrime)
                        % m_largeRandomPrime;
                mainStringHash = (mainStringHash * RADIX + mainString.at(i)) % m_largeRandomPrime;
                if(m_substringHash == mainStringHash)
                {
                    result = i-m_substringLength+1;
                    break;
                }
            }
        }
        return result;
    }

private:

    HashValue getHash(std::string const& key, Index const length)
    {
        HashValue result(0);
        for(unsigned int j=0; j<length; j++)
        {
            result = (RADIX * result + key.at(j)) % m_largeRandomPrime;
        }
        return result;
    }

    HashValue calculateStartValueFromRadixAndLength(Index const& length)
    {
        HashValue result(1);
        for(unsigned int i=1; i<length; i++)
        {
            result = (result*RADIX) % m_largeRandomPrime;
        }
        return result;
    }

    std::string m_substringToSearch;
    Index m_substringLength;
    HashValue m_largeRandomPrime;
    HashValue m_startValueFromRadixAndLength;
    HashValue m_substringHash;
};

}

}
