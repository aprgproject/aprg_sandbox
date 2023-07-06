#pragma once

#include <Common/Memory/AlbaCast.hpp>

namespace alba {

namespace algorithm {

template <typename IntegerType, typename HashKey>
HashKey getHashKeyForInteger(IntegerType const input) {
    return static_cast<HashKey>(input);
}

template <typename FloatingPointType, typename HashKey>
HashKey getHashKeyForFloatingPointType(FloatingPointType const input) {
    return getFloatingPointMemoryRepresentation<FloatingPointType, HashKey>(input);
}

}  // namespace algorithm

}  // namespace alba
