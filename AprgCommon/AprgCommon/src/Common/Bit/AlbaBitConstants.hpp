#pragma once

#include <climits>
#include <cstdint>

namespace alba::AlbaBitConstants {

// defined in climits
constexpr std::size_t BYTE_SIZE_IN_BITS = CHAR_BIT;  // 8
constexpr std::size_t BYTE_MASK = UCHAR_MAX;         // 0xFF or 255

// user defined constants:
constexpr std::size_t NIBBLE_SIZE_IN_BITS = 4;
constexpr std::size_t NUMBER_OF_NIBBLES_IN_BYTE = 2;
constexpr uint8_t NIBBLE_MASK = 0B00001111;  // digit separator carat ' cannot be used for binary literal
constexpr uint8_t BIT_MASK = 0B00000001;
}  // namespace alba::AlbaBitConstants