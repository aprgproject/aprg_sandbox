#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>

namespace alba
{

namespace algorithm
{

template <typename Input, typename HashValue>
class UnsignedIntegerBasedHashFunction
{
public:

    UnsignedIntegerBasedHashFunction() = delete;
    ~UnsignedIntegerBasedHashFunction() = delete;
    UnsignedIntegerBasedHashFunction(UnsignedIntegerBasedHashFunction const&) = delete;
    UnsignedIntegerBasedHashFunction & operator= (UnsignedIntegerBasedHashFunction const&) = delete;
    UnsignedIntegerBasedHashFunction(UnsignedIntegerBasedHashFunction &&) = delete;
    UnsignedIntegerBasedHashFunction & operator= (UnsignedIntegerBasedHashFunction &&) = delete;

    static HashValue getHashCode(Input const& input)
    {        return static_cast<HashValue>(input);    }

    static HashValue getHash(Input const& input, HashValue const hashSize)
    {
        return getHashCode(input) % hashSize;
    }
};

// Idealistic goal:
// -> Efficiently computable
// -> Each table index equally likely for each key (thoroughly researched problem, still problematic in practical applications)

// Basic rule: Need to use all the information (all the bits) to compute the hash


}

}
