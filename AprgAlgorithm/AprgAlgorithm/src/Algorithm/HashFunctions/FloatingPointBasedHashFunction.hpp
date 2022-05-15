#pragma once

#include <cstdint>

namespace alba
{

namespace algorithm
{

template <typename Input, typename HashValue>
class FloatingPointBasedHashFunction
{
public:
    static HashValue getHashCode(Input const& input)
    {
        union SharedValue
        {
            uint64_t integerValue;
            Input floatingPointValue;
        };
        SharedValue sharedValue;
        sharedValue.floatingPointValue = input;
        return static_cast<HashValue>((sharedValue.integerValue >> 32) ^ sharedValue.integerValue);
    }

    static HashValue getHash(Input const& input, HashValue const hashSize)
    {
        return getHashCode(input) % hashSize;
    }
};


}

}
