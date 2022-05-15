#pragma once

#include <Algorithm/HashFunctions/HornerHashFunction.hpp>

#include <string>

namespace alba{

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
        , m_hornerHashFunction(RADIX, A_LARGE_PRIME)
        , m_largeRandomPrime(A_LARGE_PRIME)
        , m_startValueFromRadixAndLength(getStartValue())
        , m_substringHash(getHash(m_substringToSearch))
    {}

    Index search(std::string const& stringToCheck)    {
        Index result(static_cast<Index>(std::string::npos));
        Index stringToCheckLength(stringToCheck.size());
        HashValue stringToCheckHash(getHash(stringToCheck));
        if(m_substringHash == stringToCheckHash)
        {
            result = 0;        }
        else
        {
            for(Index i=m_substringLength; i<stringToCheckLength; i++)            {
                stringToCheckHash
                        = (stringToCheckHash + m_largeRandomPrime
                           - m_startValueFromRadixAndLength * stringToCheck.at(i-m_substringLength) % m_largeRandomPrime)
                        % m_largeRandomPrime;
                stringToCheckHash = (stringToCheckHash * RADIX + stringToCheck.at(i)) % m_largeRandomPrime;
                if(m_substringHash == stringToCheckHash)
                {
                    result = i-m_substringLength+1;
                    break;
                }
            }
        }
        return result;
    }

private:

    HashValue getHash(std::string const& key)
    {
        return m_hornerHashFunction.getHash(key, 0, m_substringLength-1);
    }

    HashValue getStartValue()
    {
        return m_hornerHashFunction.getStartValue(m_substringLength);
    }

    std::string const m_substringToSearch;
    Index const m_substringLength;
    HornerHashFunction<HashValue> m_hornerHashFunction;
    HashValue m_largeRandomPrime;
    HashValue m_startValueFromRadixAndLength;
    HashValue m_substringHash;};

}
}
