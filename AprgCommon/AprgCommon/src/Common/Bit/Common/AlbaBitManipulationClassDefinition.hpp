#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>

#include <type_traits>

namespace alba
{

template <typename DataTypeToManipulate>
class AlbaBitManipulation
{
public:

    // rule of five or six
    AlbaBitManipulation() = delete;
    ~AlbaBitManipulation() = delete; // disallow allocation on stack, only on heap(but no constructor so not possible as well)
    AlbaBitManipulation(AlbaBitManipulation const&) = delete;
    AlbaBitManipulation & operator= (AlbaBitManipulation const&) = delete;
    AlbaBitManipulation(AlbaBitManipulation &&) = delete;
    AlbaBitManipulation & operator= (AlbaBitManipulation &&) = delete;


    template <typename ArgumentType, typename... Arguments>    static constexpr inline DataTypeToManipulate concatenateBytes(ArgumentType const currentByte, Arguments const... arguments)
    {        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");        static_assert(sizeof(DataTypeToManipulate) > sizeof...(Arguments), "concatenateBytes: sizeof(DataTypeToManipulate) size is greater than Arguments size");

        return shiftBytesToTheLeft<sizeof...(Arguments)>(currentByte) | concatenateBytes(arguments...);
    }

    template <typename ArgumentType, typename... Arguments>
    static constexpr inline DataTypeToManipulate concatenateNibbles(ArgumentType const currentByte, Arguments const... arguments)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(ArgumentType) == 1, "concatenateNibbles: ArgumentType size is greater than a byte");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > sizeof...(Arguments),
                      "concatenateNibbles: sizeof(DataTypeToManipulate) size is greater than two times the Arguments size");

        return shiftNibblesToTheLeft<sizeof...(Arguments)>(currentByte & AlbaBitConstants::NIBBLE_MASK) | concatenateNibbles(arguments...);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftBytesToTheLeft(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate) > shiftValue,
                      "shiftBytesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");

        return static_cast<DataTypeToManipulate>(static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftBytesToTheRight(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate) > shiftValue,
                      "shiftBytesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");

        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftNibblesToTheLeft(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
                      "shiftNibblesToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");

        return (static_cast<DataTypeToManipulate>(value) << shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftNibblesToTheRight(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
                      "shiftNibblesToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");

        return (static_cast<DataTypeToManipulate>(value) >> shiftValue*AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftBitsToTheLeft(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
                      "shiftBitsToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");

        return (static_cast<DataTypeToManipulate>(value) << shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate shiftBitsToTheRight(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
                      "shiftBitsToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");

        return (static_cast<DataTypeToManipulate>(value) >> shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate rotateBitToTheLeft(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");

        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue!=0,
                      "rotateBitToTheLeft: shiftValue is zero, so there should be nothing to do");
        static_assert(NUMBER_OF_BITS > shiftValue,
                      "rotateBitToTheLeft: sizeof(DataTypeToManipulate) size is greater than shift value");

        return rotateBitToTheLeftWithShiftValue(value, shiftValue);
    }

    template <unsigned char shiftValue, typename ArgumentType>
    static constexpr inline DataTypeToManipulate rotateBitToTheRight(ArgumentType const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");

        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue!=0,
                      "rotateBitToTheRight: shiftValue is zero, so there should be nothing to do");
        static_assert(NUMBER_OF_BITS > shiftValue,
                      "rotateBitToTheRight: sizeof(DataTypeToManipulate) size is greater than shift value");

        return rotateBitToTheRightWithShiftValue(value, shiftValue);
    }

    template <typename ArgumentType>
    static constexpr inline DataTypeToManipulate rotateBitToTheLeftWithShiftValue(
            ArgumentType const value,
            unsigned char const shiftValue)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");

        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataTypeToManipulate newValue = static_cast<DataTypeToManipulate>(value);
        return (newValue << shiftValue) | (newValue >> (NUMBER_OF_BITS-shiftValue));
    }

    template <typename ArgumentType>
    static constexpr inline DataTypeToManipulate rotateBitToTheRightWithShiftValue(
            ArgumentType const value,
            unsigned char const shiftValue)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(std::is_integral<ArgumentType>::value, "ArgumentType must be an integer");

        constexpr unsigned char NUMBER_OF_BITS = sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataTypeToManipulate newValue = static_cast<DataTypeToManipulate>(value);

        return (newValue >> shiftValue) | (newValue << (NUMBER_OF_BITS-shiftValue));
    }

    template <unsigned char position>
    static constexpr inline unsigned char getByteAt(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) > position,
                      "getByteAt: position is greater than DataTypeToManipulate size");

        return static_cast<unsigned char>(shiftBytesToTheRight<position>(value));
    }

    template <unsigned char position>
    static constexpr inline unsigned char getNibbleAt(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > position,
                      "getNibbleAt: position is greater than two times DataTypeToManipulate size");

        return shiftNibblesToTheRight<position>(value) & AlbaBitConstants::NIBBLE_MASK;
    }

    template <unsigned char position>
    static constexpr inline unsigned char getBitAt(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate)*AlbaBitConstants::BYTE_SIZE_IN_BITS > position,
                      "getBitAt: position is greater than BYTE_SIZE_IN_BITS times DataTypeToManipulate size");

        return shiftBitsToTheRight<position>(value) & AlbaBitConstants::BIT_MASK;
    }

    template <unsigned char size>
    static constexpr inline DataTypeToManipulate swapWithBytes(DataTypeToManipulate const)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(size != size, "This size or type is not supported. Please add a specialization if needed.");

        return 0;
    }

    static constexpr inline DataTypeToManipulate swap(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return swapWithBytes<sizeof(DataTypeToManipulate)>(value);
    }

    static constexpr inline DataTypeToManipulate swapForTwoBytes(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return swapWithBytes<2>(value);
    }

    static constexpr inline DataTypeToManipulate swapForFourBytes(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return swapWithBytes<4>(value);
    }

    static constexpr inline DataTypeToManipulate swapForEightBytes(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return swapWithBytes<8>(value);
    }

private:
    template <typename ArgumentType>
    static constexpr inline DataTypeToManipulate concatenateBytes(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        return arg;
    }

    template <typename ArgumentType>
    static constexpr inline DataTypeToManipulate concatenateNibbles(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateNibbles: ArgumentType size is greater than a byte");
        return arg & AlbaBitConstants::NIBBLE_MASK;
    }
};

}
