#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba {

template <typename DataType>
class AlbaBitManipulation {
public:
    static_assert(typeHelper::isIntegralType<DataType>(), "DataType must be an integer");

    // rule of five or six
    AlbaBitManipulation() = delete;
    ~AlbaBitManipulation() =
        delete;  // disallow allocation on stack, only on heap(but no constructor so not possible as well)
    AlbaBitManipulation(AlbaBitManipulation const &) = delete;
    AlbaBitManipulation &operator=(AlbaBitManipulation const &) = delete;
    AlbaBitManipulation(AlbaBitManipulation &&) = delete;
    AlbaBitManipulation &operator=(AlbaBitManipulation &&) = delete;

    template <typename ArgumentType, typename... Arguments>
    static constexpr inline DataType concatenateBytes(ArgumentType const currentByte, Arguments const... arguments) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        static_assert(
            sizeof(DataType) > sizeof...(Arguments),
            "concatenateBytes: sizeof(DataType) size is greater than Arguments size");

        if constexpr (sizeof...(Arguments) > 0) {
            return shiftBytesToTheLeft<sizeof...(Arguments)>(currentByte) | concatenateBytes(arguments...);
        } else {
            return currentByte;
        }
    }

    template <typename ArgumentType, typename... Arguments>
    static constexpr inline DataType concatenateNibbles(ArgumentType const currentByte, Arguments const... arguments) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(sizeof(ArgumentType) == 1, "concatenateNibbles: ArgumentType size is greater than a byte");
        static_assert(
            sizeof(DataType) * AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > sizeof...(Arguments),
            "concatenateNibbles: sizeof(DataType) size is greater than two times the Arguments size");

        if constexpr (sizeof...(Arguments) > 0) {
            return shiftNibblesToTheLeft<sizeof...(Arguments)>(currentByte & AlbaBitConstants::NIBBLE_MASK) |
                   concatenateNibbles(arguments...);
        } else {
            return currentByte & AlbaBitConstants::NIBBLE_MASK;
        }
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftBytesToTheLeft(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) > shiftValue, "shiftBytesToTheLeft: sizeof(DataType) size is greater than shift value");

        return static_cast<DataType>(static_cast<DataType>(value) << shiftValue * AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftBytesToTheRight(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) > shiftValue, "shiftBytesToTheRight: sizeof(DataType) size is greater than shift value");

        return (static_cast<DataType>(value) >> shiftValue * AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftNibblesToTheLeft(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) * AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
            "shiftNibblesToTheLeft: sizeof(DataType) size is greater than shift value");

        return (static_cast<DataType>(value) << shiftValue * AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftNibblesToTheRight(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) * AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > shiftValue,
            "shiftNibblesToTheRight: sizeof(DataType) size is greater than shift value");

        return (static_cast<DataType>(value) >> shiftValue * AlbaBitConstants::NIBBLE_SIZE_IN_BITS);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftBitsToTheLeft(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
            "shiftBitsToTheLeft: sizeof(DataType) size is greater than shift value");

        return (static_cast<DataType>(value) << shiftValue);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType shiftBitsToTheRight(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");
        static_assert(
            sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS > shiftValue,
            "shiftBitsToTheRight: sizeof(DataType) size is greater than shift value");

        return (static_cast<DataType>(value) >> shiftValue);
    }

    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType rotateBitToTheLeft(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");

        constexpr std::size_t NUMBER_OF_BITS = sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue != 0, "rotateBitToTheLeft: shiftValue is zero, so there should be nothing to do");
        static_assert(
            NUMBER_OF_BITS > shiftValue, "rotateBitToTheLeft: sizeof(DataType) size is greater than shift value");
        return rotateBitToTheLeftWithShiftValue(value, shiftValue);
    }
    template <auto shiftValue, typename ArgumentType>
    static constexpr inline DataType rotateBitToTheRight(ArgumentType const value) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");

        constexpr std::size_t NUMBER_OF_BITS = sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
        static_assert(shiftValue != 0, "rotateBitToTheRight: shiftValue is zero, so there should be nothing to do");
        static_assert(
            NUMBER_OF_BITS > shiftValue, "rotateBitToTheRight: sizeof(DataType) size is greater than shift value");
        return rotateBitToTheRightWithShiftValue(value, shiftValue);
    }

    template <typename ArgumentType>
    static constexpr inline DataType rotateBitToTheLeftWithShiftValue(
        ArgumentType const value, std::size_t const shiftValue) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");

        constexpr std::size_t NUMBER_OF_BITS = sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataType newValue = static_cast<DataType>(value);
        return (newValue << shiftValue) | (newValue >> (NUMBER_OF_BITS - shiftValue));
    }

    template <typename ArgumentType>
    static constexpr inline DataType rotateBitToTheRightWithShiftValue(
        ArgumentType const value, std::size_t const shiftValue) {
        static_assert(typeHelper::isIntegralType<ArgumentType>(), "ArgumentType must be an integer");

        constexpr std::size_t NUMBER_OF_BITS = sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
        DataType newValue = static_cast<DataType>(value);

        return (newValue >> shiftValue) | (newValue << (NUMBER_OF_BITS - shiftValue));    }

    template <auto position>
    static constexpr inline uint8_t getByteAt(DataType const value) {        static_assert(sizeof(DataType) > position, "getByteAt: position is greater than DataType size");

        return static_cast<uint8_t>(shiftBytesToTheRight<position>(value));
    }

    template <auto position>
    static constexpr inline uint8_t getNibbleAt(DataType const value) {
        static_assert(
            sizeof(DataType) * AlbaBitConstants::NUMBER_OF_NIBBLES_IN_BYTE > position,
            "getNibbleAt: position is greater than two times DataType size");

        return shiftNibblesToTheRight<position>(value) & AlbaBitConstants::NIBBLE_MASK;
    }

    template <auto position>
    static constexpr inline uint8_t getBitAt(DataType const value) {
        static_assert(
            sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS > position,
            "getBitAt: position is greater than BYTE_SIZE_IN_BITS times DataType size");

        return shiftBitsToTheRight<position>(value) & AlbaBitConstants::BIT_MASK;
    }

    template <std::size_t size>
    static constexpr inline DataType swapWithBytes(DataType const) {
        static_assert(size != size, "This size or type is not supported. Please add a specialization if needed.");

        return 0;
    }

    static constexpr inline DataType swap(DataType const value) { return swapWithBytes<sizeof(DataType)>(value); }

    static constexpr inline DataType swapForTwoBytes(DataType const value) { return swapWithBytes<2>(value); }

    static constexpr inline DataType swapForFourBytes(DataType const value) { return swapWithBytes<4>(value); }

    static constexpr inline DataType swapForEightBytes(DataType const value) { return swapWithBytes<8>(value); }
};

}  // namespace alba
