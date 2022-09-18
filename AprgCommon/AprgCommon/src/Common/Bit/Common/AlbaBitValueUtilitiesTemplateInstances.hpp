#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>

namespace alba
{

// Non class functions

constexpr unsigned int getNumberOfOnesForOneByte(uint8_t const value)
{
    constexpr std::array<uint8_t, 256> savedValues
    {0U, 1U, 1U, 2U, 1U, 2U, 2U, 3U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U,
        1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U,
        1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U,
        2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U,
        1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U,
        2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U,
        2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U,
        3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 5U, 6U, 6U, 7U, 6U, 7U, 7U, 8U};
    return savedValues.at(value);
}

constexpr unsigned int getNumberOfConsecutiveZerosFromMsbForOneByte(uint8_t const value)
{
    constexpr std::array<uint8_t, 256> savedValues
    {8U, 7U, 6U, 6U, 5U, 5U, 5U, 5U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U,
        2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U,
        1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
        1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
    return savedValues.at(value);
}

constexpr unsigned int getNumberOfConsecutiveZerosFromLsbForOneByte(uint8_t const value)
{
    constexpr std::array<uint8_t, 256> savedValues
    {8U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        5U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        6U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        5U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        7U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        5U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        6U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U,
        5U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 4U, 0U, 1U, 0U, 2U, 0U, 1U, 0U, 3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U};
    return savedValues.at(value);
}

template <typename BitType, typename BitHalfType>
constexpr inline unsigned int getNumberOfConsecutiveZerosFromMsbFromHalfSize(BitType const value)
{
    static_assert(std::is_integral<BitType>::value, "BitType must be an integer");
    static_assert(std::is_integral<BitHalfType>::value, "BitHalfType must be an integer");

    using BitHalfTypeUtilities = AlbaBitValueUtilities<BitHalfType>;

    constexpr unsigned int halfSize = BitHalfTypeUtilities::getNumberOfBits();    unsigned int result = BitHalfTypeUtilities::getNumberOfConsecutiveZerosFromMsb(static_cast<BitHalfType>(value >> halfSize));
    if(result == halfSize)
    {
        result += BitHalfTypeUtilities::getNumberOfConsecutiveZerosFromMsb(static_cast<BitHalfType>(value));    }
    return result;
}

template <typename BitType, typename BitHalfType>
constexpr inline unsigned int getNumberOfConsecutiveZerosFromLsbFromHalfSize(BitType const value)
{
    static_assert(std::is_integral<BitType>::value, "BitType must be an integer");
    static_assert(std::is_integral<BitHalfType>::value, "BitHalfType must be an integer");

    using BitHalfTypeUtilities = AlbaBitValueUtilities<BitHalfType>;

    constexpr unsigned int halfSize = BitHalfTypeUtilities::getNumberOfBits();    unsigned int result = BitHalfTypeUtilities::getNumberOfConsecutiveZerosFromLsb(static_cast<BitHalfType>(value));
    if(result == halfSize)
    {
        result += BitHalfTypeUtilities::getNumberOfConsecutiveZerosFromLsb(static_cast<BitHalfType>(value >> halfSize));    }
    return result;
}




// Class functions

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint8_t>::getNumberOfOnes(uint8_t const value)
{
    return getNumberOfOnesForOneByte(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint16_t>::getNumberOfOnes(uint16_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8));
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint32_t>::getNumberOfOnes(uint32_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 24));
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint64_t>::getNumberOfOnes(uint64_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 24))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 32))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 40))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 48))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 56));
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(uint8_t const value)
{
    return getNumberOfConsecutiveZerosFromMsbForOneByte(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(uint16_t const value)
{
    return getNumberOfConsecutiveZerosFromMsbFromHalfSize<uint16_t, uint8_t>(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(uint32_t const value)
{
    return getNumberOfConsecutiveZerosFromMsbFromHalfSize<uint32_t, uint16_t>(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(uint64_t const value)
{
    return getNumberOfConsecutiveZerosFromMsbFromHalfSize<uint64_t, uint32_t>(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(uint8_t const value)
{
    return getNumberOfConsecutiveZerosFromLsbForOneByte(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(uint16_t const value)
{
    return getNumberOfConsecutiveZerosFromLsbFromHalfSize<uint16_t, uint8_t>(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(uint32_t const value)
{
    return getNumberOfConsecutiveZerosFromLsbFromHalfSize<uint32_t, uint16_t>(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(uint64_t const value)
{
    return getNumberOfConsecutiveZerosFromLsbFromHalfSize<uint64_t, uint32_t>(value);
}

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
    return 0xFFFFFFFFU;
}

template <>
constexpr inline uint64_t AlbaBitValueUtilities<uint64_t>::getAllOnes()
{
    return 0xFFFFFFFFFFFFFFFFU;
}

}
