#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>

#include <cmath>
#include <cstdint>
#include <limits>

namespace alba
{

template <typename DataTypeToManipulate>
class AlbaBitManipulation
{

public:

    AlbaBitManipulation() = delete;

    template <typename ArgumentType, typename... Arguments>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType const currentByte, Arguments const... arguments)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        static_assert(sizeof(DataTypeToManipulate) > sizeof...(Arguments), "concatenateBytes: sizeof(DataTypeToManipulate) size is greater than Arguments size");
        return shiftBytesToTheLeft<sizeof...(Arguments)>(currentByte) | concatenateBytes(arguments...);
    }

    template <typename ArgumentType, typename... Arguments>
    static constexpr DataTypeToManipulate concatenateNibbles(ArgumentType const currentByte, Arguments const... arguments)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateNibbles: ArgumentType size is greater than a byte");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > sizeof...(Arguments), "concatenateNibbles: sizeof(DataTypeToManipulate) size is greater than two times the Arguments size");
        return shiftNibblesToTheLeft<sizeof...(Arguments)>(currentByte & AlbaBitConstants::NIBBLE_MASK) | concatenateNibbles(arguments...);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftBytesToTheLeft(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > shiftValue,
                      "shiftBytesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return static_cast<DataTypeToManipulate>(static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftBytesToTheRight(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > shiftValue,
                      "shiftBytesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftNibblesToTheLeft(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
                      "shiftNibblesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftNibblesToTheRight(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
                      "shiftNibblesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftBitsToTheLeft(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
                      "shiftBitsToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) << shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftBitsToTheRight(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
                      "shiftBitsToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) >> shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate rotateBitToTheLeft(ArgumentType const value)
    {
        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue!=0,
                      "rotateBitToTheLeft: shiftValue is zero, so there should be nothing to do");
        static_assert(NUMBER_OF_BITS > shiftValue,
                      "rotateBitToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return rotateBitToTheLeftWithShiftValue(value, shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate rotateBitToTheRight(ArgumentType const value)
    {
        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue!=0,
                      "rotateBitToTheRight: shiftValue is zero, so there should be nothing to do");
        static_assert(NUMBER_OF_BITS > shiftValue,
                      "rotateBitToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return rotateBitToTheRightWithShiftValue(value, shiftValue);
    }

    template <typename ArgumentType>
    static constexpr DataTypeToManipulate rotateBitToTheLeftWithShiftValue(
            ArgumentType const value,
            unsigned char const shiftValue)
    {
        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataTypeToManipulate newValue = static_cast<DataTypeToManipulate>(value);
        return (newValue << shiftValue) | (newValue >> (NUMBER_OF_BITS-shiftValue));
    }

    template <typename ArgumentType>
    static constexpr DataTypeToManipulate rotateBitToTheRightWithShiftValue(
            ArgumentType const value,
            unsigned char const shiftValue)
    {
        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataTypeToManipulate newValue = static_cast<DataTypeToManipulate>(value);
        return (newValue >> shiftValue) | (newValue << (NUMBER_OF_BITS-shiftValue));
    }

    template <unsigned char position>
    static constexpr unsigned char getByteAt(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > position,
                      "getByteAt: position is greater than DataTypeToManipulate size");
        return static_cast<unsigned char>(shiftBytesToTheRight<position>(value));
    }

    template <unsigned char position>
    static constexpr unsigned char getNibbleAt(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > position,
                      "getNibbleAt: position is greater than two times DataTypeToManipulate size");
        return shiftNibblesToTheRight<position>(value) & AlbaBitConstants::NIBBLE_MASK;
    }

    template <unsigned char position>
    static constexpr unsigned char getBitAt(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > position,
                      "getBitAt: position is greater than BYTE_SIZE_IN_BITS times DataTypeToManipulate size");
        return shiftBitsToTheRight<position>(value) & AlbaBitConstants::BIT_MASK;
    }

    template <unsigned char size>
    static constexpr DataTypeToManipulate swapWithBytes(DataTypeToManipulate const)
    {
        static_assert(size != size, "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr DataTypeToManipulate swap(DataTypeToManipulate const value)
    {
        return swapWithBytes<sizeof(DataTypeToManipulate)>(value);
    }

    static constexpr DataTypeToManipulate swapForTwoBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<2>(value);
    }

    static constexpr DataTypeToManipulate swapForFourBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<4>(value);
    }

    static constexpr DataTypeToManipulate swapForEightBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<8>(value);
    }

    static constexpr DataTypeToManipulate generateOnesWithNumberOfBits(unsigned int const numberOfOnes)
    {
        return static_cast<DataTypeToManipulate>(round(pow(static_cast<double>(2), static_cast<double>(numberOfOnes)))-1);
    }

    static constexpr DataTypeToManipulate getAllBitsAsserted()
    {
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr unsigned int getNumberOfBits()
    {
        return static_cast<unsigned int>(std::numeric_limits<DataTypeToManipulate>::digits);
    }

    static unsigned int getNumberOfBitsAsserted(DataTypeToManipulate const value)
    {
        unsigned int result(0U);
        DataTypeToManipulate shiftedValue(value);
        for(unsigned int i=0; i<getNumberOfBits(); i++)
        {
            if((shiftedValue & AlbaBitConstants::BIT_MASK) == 1)
            {
                result++;
            }
            shiftedValue >>= 1;
        }
        return result;
    }

private:
    template <typename ArgumentType>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        return arg;
    }

    template <typename ArgumentType>
    static constexpr DataTypeToManipulate concatenateNibbles(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateNibbles: ArgumentType size is greater than a byte");
        return arg & AlbaBitConstants::NIBBLE_MASK;
    }
};


template <>
template <>
constexpr uint16_t AlbaBitManipulation<uint16_t>::swapWithBytes<2>(uint16_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value));
}

template <>
template <>
constexpr uint32_t AlbaBitManipulation<uint32_t>::swapWithBytes<4>(uint32_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value));
}

template <>
template <>
constexpr uint64_t AlbaBitManipulation<uint64_t>::swapWithBytes<8>(uint64_t const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value),
                            getByteAt<4>(value), getByteAt<5>(value),
                            getByteAt<6>(value), getByteAt<7>(value));
}

template <>
constexpr uint16_t AlbaBitManipulation<uint16_t>::getAllBitsAsserted()
{
    return 0xFFFFU;
}

template <>
constexpr uint32_t AlbaBitManipulation<uint32_t>::getAllBitsAsserted()
{
    return 0xFFFFFFFFU;
}

template <>
constexpr uint64_t AlbaBitManipulation<uint64_t>::getAllBitsAsserted()
{
    return 0xFFFFFFFFFFFFFFFFU;
}

}
