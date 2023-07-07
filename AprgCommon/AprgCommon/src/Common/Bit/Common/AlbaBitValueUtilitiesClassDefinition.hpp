#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/Common/AlbaBitUtilitiesBuiltIn.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <cmath>

namespace alba {

template <typename DataType>
class AlbaBitValueUtilities {
public:
    static_assert(typeHelper::isIntegralType<DataType>(), "DataType must be an integer");

    // rule of five or six
    AlbaBitValueUtilities() = delete;
    // disallow allocation on stack, only on heap(but no constructor so not possible as well)
    ~AlbaBitValueUtilities() = delete;
    AlbaBitValueUtilities(AlbaBitValueUtilities const &) = delete;
    AlbaBitValueUtilities &operator=(AlbaBitValueUtilities const &) = delete;
    AlbaBitValueUtilities(AlbaBitValueUtilities &&) = delete;
    AlbaBitValueUtilities &operator=(AlbaBitValueUtilities &&) = delete;

    static constexpr inline bool isPowerOfTwo(DataType const value) { return getValueWithLastBitOneAsZero(value) == 0; }

    static inline constexpr bool isEvenParity(DataType const value) { return BitUtilitiesBuiltIn::isEvenParity(value); }

    static constexpr inline bool areAllOnesStartingFromTheFirstOne(DataType const value) {
        // These values also follow this formula: (2^n)-1.
        return getValueWithTrailingOnesAsZeros(value) == 0;
    }

    static constexpr inline size_t getNumberOfBits() {
        // Approach based on numeric limits and if its signed
        // return std::numeric_limits<DataType>::digits + (std::numeric_limits<DataType>::is_signed ? 1 : 0);

        // Approach based on sizeof
        // -> sizeof: Yields the size in bytes of the object representation of type.
        return sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
    }

    static inline constexpr size_t getNumberOfOnes(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfOnes(value);
    }

    static inline constexpr size_t getNumberOfConsecutiveZerosFromMsb(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb(value);
    }

    static inline constexpr size_t getNumberOfConsecutiveZerosFromLsb(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb(value);
    }

    static constexpr inline size_t getHammingDistance(DataType const value1, DataType const value2) {
        // The Hamming distance hamming(a,b) between two bitstrings a and b of equal length is the number of positions
        // where the bitstrings differ.

        return getNumberOfOnes(value1 ^ value2);
    }

    static constexpr inline DataType generateOnesWithNumberOfBits(size_t const numberOfOnes) {
        return (DataType(1) << numberOfOnes) - 1;
    }

    static constexpr inline DataType getAllOnes() {
        if constexpr (sizeof(DataType) == 1) {
            return 0xFF;
        } else if constexpr (sizeof(DataType) == 2) {
            return 0xFFFF;
        } else if constexpr (sizeof(DataType) == 4) {
            return 0xFFFFFFFF;
        } else if constexpr (sizeof(DataType) == 8) {
            return 0xFFFFFFFF'FFFFFFFF;
        }
        static_assert(true, "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline DataType getAbsoluteValue(DataType const value) {
        // There is also an implementation on Math

        static_assert(typeHelper::isSignedType<DataType>(), "DataType must be a signed type");
        auto const signedBitMoved = value >> (getNumberOfBits() - 1);
        return (value ^ signedBitMoved) - signedBitMoved;
        // return (value + signedBitMoved) ^ signedBitMoved; // This formula works as well
    }

    static constexpr inline DataType getSign(DataType const value) {
        // There is also an implementation on Math
        // This is same as the signum function

        static_assert(typeHelper::isSignedType<DataType>(), "DataType must be a signed type");
        constexpr auto numberOfBitsMinus1 = (getNumberOfBits() - 1);
        return -(-(value >> numberOfBitsMinus1) | (-value >> numberOfBitsMinus1));
    }

    static constexpr inline DataType get2ToThePowerOf(DataType const exponent) { return DataType(1) << exponent; }

    static constexpr inline DataType getLogarithmWithBase2Of(DataType const value) {
        DataType result = getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value);
        result = (result == 0) ? 0 : result - 1;
        return result;
    }

    static constexpr inline DataType getCeilOfLogarithmWithBase2Of(DataType const value) {
        DataType result = getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value);
        result = (result == 0) ? 0 : isPowerOfTwo(value) ? result - 1 : result;
        return result;
    }

    static constexpr inline DataType getOnesComplement(DataType const value) { return ~value; }

    static constexpr inline DataType getTwosComplement(DataType const value) { return value * -1; }

    static constexpr inline DataType getGreatestPowerOf2Factor(DataType const value) {
        return getLastBitOneOnly(value);
    }

    static constexpr inline DataType getValueWithLastBitOneAsZero(DataType const value) {
        // Hackers Delight: Turn off the rightmost 1-bit in a word, producing 0 if none
        // (e.g., 01011000 ⇒ 01010000)
        return value & (value - 1);
    }

    static constexpr inline DataType getValueWithLastBitZeroAsOne(DataType const value) {
        // Hackers Delight: Turn on the rightmost 0-bit in a word, producing all 1’s if none
        // (e.g., 10100111 ⇒ 10101111):

        return value | (value + 1);
    }

    static constexpr inline DataType getValueWithTrailingOnesAsZeros(DataType const value) {
        // Hackers Delight: Turn off the trailing 1’s in a word, producing x if none
        // (e.g., 10100111 ⇒ 10100000):

        return value & (value + 1);
    }

    static constexpr inline DataType getValueWithASingleBitOneBeforeTrailingOnes(DataType const value) {
        // Hackers Delight: Create a word with a single 1-bit at the position of the rightmost 0-bit in x,
        // producing 0 if none
        // (e.g., 10100111 ⇒ 00001000)

        return ~value & (value + 1);
    }

    static constexpr inline DataType getValueWithASingleBitZeroBeforeTrailingZeros(DataType const value) {
        // Hackers Delight: Create a word with a single 0-bit at the position of the rightmost 1-bit in x,
        // producing all 1’s if none
        // (e.g., 10101000 ⇒ 11110111):

        return ~value | (value - 1);
    }

    static constexpr inline DataType getOnlyTrailingOnesAtTrailingZeros(DataType const value) {
        // Hackers Delight: Create a word with 1’s at the positions of the trailing 0’s in x, and 0’s elsewhere,
        // producing 0 if none
        // (e.g., 01011000 ⇒ 00000111):

        return ~value & (value - 1);  // This formula works as well
        // return ~(value | -value); // This formula works as well
        // return (value & -value) -1; // This formula works as well
    }

    static constexpr inline DataType getOnlyTrailingZerosAtTrailingOnes(DataType const value) {
        // Hackers Delight: Create a word with 0’s at the positions of the trailing 1’s in x, and 0’s elsewhere,
        // producing all 1’s if none :
        // (e.g., 10100111 ⇒ 11111000):

        return ~value & (value + 1);
    }

    static constexpr inline DataType getLastBitOneOnly(DataType const value) {
        // Hackers Delight: Isolate the rightmost 1-bit, producing 0 if none
        // (e.g., 01011000 ⇒ 00001000):

        return value & -value;
    }

    static constexpr inline DataType getOnlyTrailingOnesAtLastBitOne(DataType const value) {
        // Hackers Delight: Create a word with 1’s at the positions of the rightmost 1-bit
        // and the trailing 0’s in x, producing all 1’s if no 1-bit, and the integer 1 if no trailing 0’s
        // (e.g., 01011000 ⇒ 00001111):

        return value ^ (value - 1);
    }

    static constexpr inline DataType getOnlyTrailingOnesAtLastBitZero(DataType const value) {
        // Hackers Delight: Create a word with 1’s at the positions of the rightmost 0-bit
        // and the trailing 1’s in x, producing all 1’s if no 0-bit, and the integer 1 if no trailing 1’s
        // (e.g., 01010111 ⇒ 00001111):

        return value ^ (value + 1);
    }

    static constexpr inline DataType roundDownAt(DataType const value, size_t const lsbPosition) {
        return (value >> lsbPosition) << lsbPosition;
        // return value & (-1 << lsbPosition); // This formula works as well
    }

    static constexpr inline DataType roundUpAt(DataType const value, size_t const lsbPosition) {
        auto mask = (1 << lsbPosition) - 1;
        return (value + mask) & ~mask;
        // This formula works as well:
        // auto mask = (-1 << lsbPosition);
        // return (value - mask - 1) & mask;
    }

    static constexpr inline DataType roundDownToAPowerOf2(DataType const value) {
        return 1 << (getNumberOfBits() - 1 - getNumberOfConsecutiveZerosFromMsb(value));
        // This formula works as well:
        // return 1 << ((getNumberOfBits() - 1) ^ getNumberOfConsecutiveZerosFromLsb(value));
    }

    static constexpr inline DataType roundUpToAPowerOf2(DataType const value) {
        return 1 << (getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value - 1));
    }

    static constexpr inline DataType getTwoValuesInACycle(
        DataType const current, DataType const value1, DataType const value2) {
        return value1 ^ value2 ^ current;
        // return value1 + value2 - current; // This formula works as well
    }

    static constexpr inline void swap(DataType &value1, DataType &value2) {
        value1 ^= value2;
        value2 ^= value1;
        value1 ^= value2;
        // This also pattern also works:
        // 1) value1 += value2; value2 = value1 - value2; value1 -= value2;
        // 2) value1 -= value2; value2 += value1; value1 = value2 - value1;
        // 2) value1 = value2 - value1; value2 -= value1; value1 += value2;
    }
};

}  // namespace alba
