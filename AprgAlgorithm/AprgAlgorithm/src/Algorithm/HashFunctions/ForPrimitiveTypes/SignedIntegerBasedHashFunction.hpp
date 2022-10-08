#pragma once

#include <bitset>
#include <limits>

namespace alba
{

namespace algorithm
{

template <typename Input, typename HashValue>
class SignedIntegerBasedHashFunction
{
public:
    static HashValue getHashCode(Input const& input)
    {
        // note we are including sign bit because its better distributed
        return static_cast<HashValue>(input);
    }

    static HashValue getHash(Input const& input, HashValue const hashSize)
    {
        return getHashCode(input) % hashSize;
    }
};

}

}
