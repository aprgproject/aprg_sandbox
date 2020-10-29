#pragma once

#include <cassert>
#include <cmath>

namespace alba
{

template <typename DataTypeToManipulate>
class AlbaBitManipulation
{

public:

    static unsigned char const BYTE_SIZE_IN_BITS = 8;

    AlbaBitManipulation() = delete;

    template <typename ArgumentType, typename... Arguments>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType const currentByte, Arguments const... arguments)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        static_assert(sizeof(DataTypeToManipulate) > sizeof...(Arguments), "concatenateBytes: sizeof(DataTypeToManipulate) size is greater than Arguments size");
        return ((DataTypeToManipulate)currentByte << (sizeof...(Arguments) * BYTE_SIZE_IN_BITS)) | concatenateBytes(arguments...);
    }

    template <unsigned char position>
    static constexpr unsigned char getByteAtLeastSignificantPosition(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > position, "getByteAtLeastSignificantPosition: position is greater than DataTypeToManipulate size");
        return value >> (position * BYTE_SIZE_IN_BITS);
    }

    template <unsigned char size>
    static constexpr DataTypeToManipulate swapWithBytes(DataTypeToManipulate const)
    {
        static_assert(size != size, "The swapWithSize with this size or type is not supported. Please add a specialization.");
        return 0;
    }

    static DataTypeToManipulate swap(DataTypeToManipulate const value)
    {
        return swapWithBytes<sizeof(DataTypeToManipulate)>(value);
    }

    static DataTypeToManipulate swapForTwoBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<2>(value);
    }

    static DataTypeToManipulate swapForFourBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<4>(value);
    }

    static DataTypeToManipulate swapForEightBytes(DataTypeToManipulate const value)
    {
        return swapWithBytes<8>(value);
    }

    static DataTypeToManipulate generateOnesWithNumberOfBits(unsigned int numberOfOnes)
    {
        return (DataTypeToManipulate)(round(pow((double)2, (double)numberOfOnes))-1);
    }

private:
    template <typename ArgumentType>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        return arg;
    }
};


template <>
template <>
constexpr short unsigned int AlbaBitManipulation<short unsigned int>::swapWithBytes<2>(short unsigned int const value)
{
    return concatenateBytes(getByteAtLeastSignificantPosition<0>(value), getByteAtLeastSignificantPosition<1>(value));
}

template <>
template <>
constexpr unsigned int AlbaBitManipulation<unsigned int>::swapWithBytes<2>(unsigned int const value)
{
    return concatenateBytes(getByteAtLeastSignificantPosition<0>(value), getByteAtLeastSignificantPosition<1>(value));
}

template <>
template <>
constexpr unsigned int AlbaBitManipulation<unsigned int>::swapWithBytes<4>(unsigned int const value)
{
    return concatenateBytes(getByteAtLeastSignificantPosition<0>(value), getByteAtLeastSignificantPosition<1>(value),
                            getByteAtLeastSignificantPosition<2>(value), getByteAtLeastSignificantPosition<3>(value));
}

template <>
template <>
constexpr unsigned long long AlbaBitManipulation<unsigned long long>::swapWithBytes<8>(unsigned long long const value)
{
    return concatenateBytes(getByteAtLeastSignificantPosition<0>(value), getByteAtLeastSignificantPosition<1>(value),
                            getByteAtLeastSignificantPosition<2>(value), getByteAtLeastSignificantPosition<3>(value),
                            getByteAtLeastSignificantPosition<4>(value), getByteAtLeastSignificantPosition<5>(value),
                            getByteAtLeastSignificantPosition<6>(value), getByteAtLeastSignificantPosition<7>(value));
}


}
