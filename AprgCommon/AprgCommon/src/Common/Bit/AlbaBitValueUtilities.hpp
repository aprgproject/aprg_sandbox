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

    static constexpr inline bool isPowerOfTwo(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return (value & (value-1))==0;
    }

    static constexpr inline bool isEvenParity(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        // This is similar with __builtin_parity(x)
        return getNumberOfOnes(value)%2 == 0;
    }

    static constexpr inline unsigned int getNumberOfBits()
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return std::numeric_limits<DataTypeToManipulate>::digits
                + (std::numeric_limits<DataTypeToManipulate>::is_signed ? 1 : 0);
    }

    /*static constexpr inline unsigned int getNumberOfConsecutiveZerosFromMostSignificantDigit(DataTypeToManipulate const value)
    {
        // Think about this
        // This is similar with __builtin_clz(x)        return 0;
    }

    static constexpr inline unsigned int getNumberOfConsecutiveZerosFromLeastSignificantDigit(DataTypeToManipulate const value)
    {
        // Think about this
        // This is similar with __builtin_clz(x)        return 0;
    }*/

    static constexpr inline unsigned int getNumberOfOnes(DataTypeToManipulate const)
    {
        // This is similar with __builtin_popcount(x)
        // std::bitset can be used here but it would no longer be constexpr        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline unsigned int getHammingDistance(DataTypeToManipulate const value1, DataTypeToManipulate const value2)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        // The Hamming distance hamming(a,b) between two bitstrings a and b of equal length is the number of positions where the bitstrings differ.
        return getNumberOfOnes(value1 ^ value2);
    }

    static constexpr inline DataTypeToManipulate generateOnesWithNumberOfBits(unsigned int const numberOfOnes)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return (DataTypeToManipulate(1) << numberOfOnes)-1;
    }

    static constexpr inline DataTypeToManipulate getAllOnes()
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),                      "This size or type is not supported. Please add a specialization if needed.");

        return 0;
    }

    static constexpr inline DataTypeToManipulate get2ToThePowerOf(DataTypeToManipulate const exponent)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return DataTypeToManipulate(1) << exponent;
    }

    static constexpr inline DataTypeToManipulate getTwosComplement(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return value * -1;
    }

    static constexpr inline DataTypeToManipulate getGreatestPowerOf2Factor(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        return value & (-value);
    }
};
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

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint8_t>::getNumberOfOnes(uint8_t const value)
{
    return getNumberOfOnesForOneByte(value);
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint16_t>::getNumberOfOnes(uint16_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8));}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint32_t>::getNumberOfOnes(uint32_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8))            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 24));
}

template <>
constexpr inline unsigned int AlbaBitValueUtilities<uint64_t>::getNumberOfOnes(uint64_t const value)
{
    return getNumberOfOnesForOneByte(static_cast<uint8_t>(value))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 8))            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 16))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 24))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 32))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 40))            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 48))
            + getNumberOfOnesForOneByte(static_cast<uint8_t>(value >> 56));
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