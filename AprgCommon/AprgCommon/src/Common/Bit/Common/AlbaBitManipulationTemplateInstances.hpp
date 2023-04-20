#pragma once

#include <Common/Bit/Common/AlbaBitManipulationClassDefinition.hpp>

namespace alba
{

template <>
template <>
constexpr inline uint16_t AlbaBitManipulation<uint16_t>::swapWithBytes<2>(uint16_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value));
}

template <>
template <>
constexpr inline uint32_t AlbaBitManipulation<uint32_t>::swapWithBytes<4>(uint32_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value));
}

template <>
template <>
constexpr inline uint64_t AlbaBitManipulation<uint64_t>::swapWithBytes<8>(uint64_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value),
                            getByteAt<4>(value), getByteAt<5>(value),
                            getByteAt<6>(value), getByteAt<7>(value));
}

}
