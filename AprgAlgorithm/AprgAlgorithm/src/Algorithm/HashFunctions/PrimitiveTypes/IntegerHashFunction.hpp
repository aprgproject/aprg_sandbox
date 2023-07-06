#pragma once

#include <Algorithm/HashFunctions/PrimitiveTypes/HashKeyUtilities.hpp>
#include <Algorithm/HashFunctions/PrimitiveTypes/HashValueUtilities.hpp>

namespace alba {

namespace algorithm {

template <typename HashKey, typename HashValue, HashValue HASH_TABLE_SIZE>
class IntegerHashFunction {
public:
    static HashValue getHash(HashKey const hashKey) {
        return getHashUsingDivisionMethod(getHashKeyForInteger<HashKey, HashValue>(hashKey), HASH_TABLE_SIZE);
    }
};

}  // namespace algorithm

}  // namespace alba
