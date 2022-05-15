#pragma once

namespace alba
{

namespace algorithm
{

template <typename HashValue, typename Key>
class ValueBasedHashFunction
{
public:
    static unsigned int getHash(Key const& key, unsigned int const hashSize)
    {
        return static_cast<unsigned int>(key) % hashSize;
    }
};

}

}
