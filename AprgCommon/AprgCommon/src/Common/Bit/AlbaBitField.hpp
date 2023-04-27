#pragma once

#include <cstdint>

namespace alba {

template <typename UnderlyingType, size_t numberOfBits>
struct AlbaSingleBitField {
    UnderlyingType value : numberOfBits;
};

}  // namespace alba
