#pragma once

#include <string>

namespace alba
{

namespace algorithm
{

template <typename HashValue>
class HornerHashFunction // horners rule: continuously mod to keep the value
{
public:
    HornerHashFunction(HashValue const radix, HashValue const largeRandomPrime)
        : m_radix(radix)
        , m_largeRandomPrime(largeRandomPrime)
    {}

    HashValue getHashCode(std::string const& input)
    {
        return getHashCode(input, 0, input.size()-1);
    }

    HashValue getHashCode(
            std::string const& input,
            unsigned int const startIndex,
            unsigned int const endIndex)
    {
        HashValue result(0);
        for(unsigned int i=startIndex; i<=endIndex; i++) // linear time
        {
            result = (m_radix * result + input.at(i)) % m_largeRandomPrime; // continuously mod
        }
        return result;
    }

private:
    HashValue m_radix;
    HashValue m_largeRandomPrime;
};

}

}
