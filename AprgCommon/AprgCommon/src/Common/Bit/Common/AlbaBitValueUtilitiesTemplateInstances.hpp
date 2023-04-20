#pragma once

#include <Common/Bit/Common/AlbaBitValueUtilitiesClassDefinition.hpp>

namespace alba
{

template <>
constexpr inline uint8_t AlbaBitValueUtilities<uint8_t>::getAllOnes()
{
    return 0xFFU;
}

template <>
constexpr inline uint16_t AlbaBitValueUtilities<uint16_t>::getAllOnes()
{
    return 0xFFFFU;
}

template <>
constexpr inline uint32_t AlbaBitValueUtilities<uint32_t>::getAllOnes()
{
    return 0xFFFF'FFFFU;
}

template <>
constexpr inline uint64_t AlbaBitValueUtilities<uint64_t>::getAllOnes()
{
    return 0xFFFF'FFFF'FFFF'FFFFU;
}

}
