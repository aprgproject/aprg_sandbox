#pragma once

#include <Bit/AlbaBitConstants.hpp>

#include <cmath>

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
        static_assert(sizeof(DataTypeToManipulate) > shiftValue, "shiftBytesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return static_cast<DataTypeToManipulate>(static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftBytesToTheRight(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > shiftValue, "shiftBytesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftNibblesToTheLeft(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue, "shiftNibblesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr DataTypeToManipulate shiftNibblesToTheRight(ArgumentType const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue, "shiftNibblesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");
        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char position>
    static constexpr unsigned char getByteAt(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > position, "getByteAt: position is greater than DataTypeToManipulate size");
        return static_cast<unsigned char>(shiftBytesToTheRight<position>(value));
    }

    template <unsigned char position>    static constexpr unsigned char getNibbleAt(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > position, "getNibbleAt: position is greater than two times DataTypeToManipulate size");
        return shiftNibblesToTheRight<position>(value) & AlbaBitConstants::NIBBLE_MASK;
    }

    template <unsigned char size>
    static constexpr DataTypeToManipulate swapWithBytes(DataTypeToManipulate const)
    {
        static_assert(size != size, "The swapWithSize with this size or type is not supported. Please add a specialization.");
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

    static constexpr DataTypeToManipulate generateOnesWithNumberOfBits(unsigned int numberOfOnes)
    {
        return static_cast<DataTypeToManipulate>(round(pow(static_cast<double>(2), static_cast<double>(numberOfOnes)))-1);
    }

    static constexpr DataTypeToManipulate getAllBitsAsserted()    {
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate), "The swapWithSize with this size or type is not supported. Please add a specialization.");
        return 0;
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
constexpr short unsigned int AlbaBitManipulation<short unsigned int>::swapWithBytes<2>(short unsigned int const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value));
}

template <>
template <>
constexpr unsigned int AlbaBitManipulation<unsigned int>::swapWithBytes<2>(unsigned int const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value));
}

template <>
template <>
constexpr unsigned int AlbaBitManipulation<unsigned int>::swapWithBytes<4>(unsigned int const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value));
}

template <>
template <>
constexpr unsigned long long AlbaBitManipulation<unsigned long long>::swapWithBytes<8>(unsigned long long const value)
{
    return concatenateBytes(getByteAt<0>(value), getByteAt<1>(value),
                            getByteAt<2>(value), getByteAt<3>(value),
                            getByteAt<4>(value), getByteAt<5>(value),
                            getByteAt<6>(value), getByteAt<7>(value));
}

template <>
constexpr short unsigned int AlbaBitManipulation<short unsigned int>::getAllBitsAsserted()
{
    return 0xFFFF;
}

template <>
constexpr unsigned int AlbaBitManipulation<unsigned int>::getAllBitsAsserted()
{
    return 0xFFFFFFFF;
}

template <>
constexpr unsigned long long AlbaBitManipulation<unsigned long long>::getAllBitsAsserted()
{
    return 0xFFFFFFFFFFFFFFFF;
}

}
