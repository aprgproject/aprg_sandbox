#pragma once

#include <cstdint>

namespace alba {

template <typename UnderlyingType, unsigned int numberOfBits>
struct AlbaSingleBitField {
    UnderlyingType value : numberOfBits;
};

}  // namespace alba
