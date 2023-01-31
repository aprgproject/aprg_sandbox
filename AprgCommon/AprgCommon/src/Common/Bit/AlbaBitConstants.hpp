#pragma once

#include <climits>
#include <cstdint>

namespace alba
{

namespace AlbaBitConstants
{
    // defined in climits
    uint8_t const BYTE_SIZE_IN_BITS = CHAR_BIT; // 8
    uint8_t const BYTE_MASK = UCHAR_MAX; // 0xFF or 255

    // user defined constants:
    uint8_t const NIBBLE_SIZE_IN_BITS = 4;
    uint8_t const NIBBLE_MASK = 0x0F;
    uint8_t const BIT_MASK = 0x01;
    uint8_t const NUMBER_OF_NIBBLES_IN_BYTE = 2;
}

}
