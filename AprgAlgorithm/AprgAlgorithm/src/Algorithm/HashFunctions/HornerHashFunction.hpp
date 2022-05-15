#pragma once

#include <string>

namespace alba
{

namespace algorithm
{

template <typename HashValue>
class HornerHashFunction
{
public:
    HornerHashFunction(HashValue const radix, HashValue const largeRandomPrime)
        : m_radix(radix)
        , m_largeRandomPrime(largeRandomPrime)
    {}

    HashValue getHash(
            std::string const& key,
            unsigned int const start,
            unsigned int const end)
    {
        // Horner's method
        HashValue result(0);
        for(unsigned int i=start; i<=end; i++)
        {
            result = (m_radix * result + key.at(i)) % m_largeRandomPrime;
        }
        return result;
    }

    HashValue getStartValue(unsigned int const length)
    {
        // Horner's method
        HashValue result(1);
        for(unsigned int i=1; i<length; i++)
        {
            result = (result*m_radix) % m_largeRandomPrime;
        }
        return result;
    }
private:
    HashValue m_radix;
    HashValue m_largeRandomPrime;
};

}

}
