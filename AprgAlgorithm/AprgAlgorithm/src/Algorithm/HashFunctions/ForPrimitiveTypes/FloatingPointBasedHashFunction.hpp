#pragma once

#include <Common/Memory/AlbaCast.hpp>

#include <cstdint>

namespace alba{

namespace algorithm
{
template <typename Input, typename HashValue>
class FloatingPointBasedHashFunction
{
public:

    FloatingPointBasedHashFunction() = delete;
    ~FloatingPointBasedHashFunction() = delete;
    FloatingPointBasedHashFunction(FloatingPointBasedHashFunction const&) = delete;
    FloatingPointBasedHashFunction & operator= (FloatingPointBasedHashFunction const&) = delete;
    FloatingPointBasedHashFunction(FloatingPointBasedHashFunction &&) = delete;
    FloatingPointBasedHashFunction & operator= (FloatingPointBasedHashFunction &&) = delete;

    static HashValue getHashCode(Input const& input)
    {
        uint64_t integerValue = getFloatingPointMemoryRepresentation<uint64_t>(input);
        return static_cast<HashValue>((sharedValue.integerValue >> 32) ^ sharedValue.integerValue);
    }
    static HashValue getHash(Input const& input, HashValue const hashSize)
    {
        return getHashCode(input) % hashSize;    }
};


}

}
