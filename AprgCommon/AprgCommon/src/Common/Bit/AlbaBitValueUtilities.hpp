#pragma once

#include <array>
#include <cmath>
#include <limits>

namespace alba
{

template <typename DataTypeToManipulate>
class AlbaBitValueUtilities
{
public:

    static constexpr DataTypeToManipulate generateOnesWithNumberOfBits(unsigned int const numberOfOnes)
    {
        return static_cast<DataTypeToManipulate>(round(pow(2, numberOfOnes))-1);
    }

    static constexpr DataTypeToManipulate getAllBitsAsserted()
    {
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr unsigned int getNumberOfBits()
    {
        unsigned int result(std::numeric_limits<DataTypeToManipulate>::digits);
        result += std::numeric_limits<DataTypeToManipulate>::is_signed ? 1 : 0;
        return result;
    }

    static constexpr unsigned int getNumberOfBitsAsserted(DataTypeToManipulate const)
    {
        // std::bitset can be used here but it would no longer be constexpr
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }
};

constexpr unsigned int getNumberOfBitsAssertedForOneByte(uint8_t const value)
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

template <>
constexpr unsigned int AlbaBitValueUtilities<uint8_t>::getNumberOfBitsAsserted(uint8_t const value)
{
    return getNumberOfBitsAssertedForOneByte(value);
}

template <>
constexpr unsigned int AlbaBitValueUtilities<uint16_t>::getNumberOfBitsAsserted(uint16_t const value)
{
    return getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 8));
}

template <>
constexpr unsigned int AlbaBitValueUtilities<uint32_t>::getNumberOfBitsAsserted(uint32_t const value)
{
    return getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 8))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 24));
}

template <>
constexpr unsigned int AlbaBitValueUtilities<uint64_t>::getNumberOfBitsAsserted(uint64_t const value)
{
    return getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 8))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 24))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 32))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 40))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 48))
            + getNumberOfBitsAssertedForOneByte(static_cast<uint8_t>(value >> 56));
}

template <>
constexpr uint8_t AlbaBitValueUtilities<uint8_t>::getAllBitsAsserted()
{
    return 0xFFU;
}

template <>
constexpr uint16_t AlbaBitValueUtilities<uint16_t>::getAllBitsAsserted()
{
    return 0xFFFFU;
}

template <>
constexpr uint32_t AlbaBitValueUtilities<uint32_t>::getAllBitsAsserted()
{
    return 0xFFFFFFFFU;
}

template <>
constexpr uint64_t AlbaBitValueUtilities<uint64_t>::getAllBitsAsserted()
{
    return 0xFFFFFFFFFFFFFFFFU;
}

}
