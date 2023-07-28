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

    static constexpr inline bool isPowerOfTwo(DataType const value) {
        // NOTE: Zero is not really a power of two but this function returns true.
        // Add this check if needed: (value != 0)
        return getValueWithLastBitOneAsZero(value) == 0;
    }

    static inline constexpr bool isEvenParity(DataType const value) { return BitUtilitiesBuiltIn::isEvenParity(value); }

    static constexpr inline bool areAllOnesStartingFromTheFirstOne(DataType const value) {
        // These values also follow this formula: (2^n)-1.
        return getValueWithTrailingOnesAsZeros(value) == 0;
    }

    static constexpr inline bool isMultipleOfThree(DataType const value) {
        // Explanation:
        // Let the binary representation of the number be: "abcde".
        // In decimal form this number will be:  2^4*a + 2^3*b + 2^2*c + 2^1*d + 2^0*e
        // Every even power of 2 can be represented as 3n + 1,
        // and every odd power of 2 can be represented as 3n – 1.
        // For example:
        // -> 2^0 = 3 * 0 + 1
        // -> 2^1 = 3 * 1 - 1
        // -> 2^2 = 3 * 1 + 1
        // -> 2^3 = 3 * 3 - 1
        // -> and so on...
        // Therefore, the decimal form becomes:
        // -> (3n+1)*a + (3n-1)*b + (3n+1)*c + (3n-1)*d + (3n+1)*e
        // To have this number divisible by 3, the term (a+c+e)-(b+d) should be divisible by 3.
        // Therefore for the number to be divisible by,
        // the difference between the count of odd set bits (a+c+e)
        // and even set bits (b+d) should be divisible by 3.

        if (value == 0) {
            return true;
        } else if (value == 1) {
            return false;
        } else if (value < 0) {
            return isMultipleOfThree(-value);
        } else {
            DataType countAtOddPositions = getNumberOfOnes(value & getAlternatingOnesAndZerosFromLsb());
            DataType countAtEvenPositions = getNumberOfOnes(value & getAlternatingZerosAndOnesFromLsb());
            if (countAtOddPositions >= countAtEvenPositions) {
                return isMultipleOfThree(static_cast<DataType>(countAtOddPositions - countAtEvenPositions));
            } else {
                return isMultipleOfThree(static_cast<DataType>(countAtEvenPositions - countAtOddPositions));
            }
        }
    }

    static constexpr inline bool isMultipleOfNine(DataType const value) {
        // How does this work?
        // -> n/9 can be written in terms of n/8 using the following simple formula.
        // -> n/9 = n/8 - n/72
        // Since we need to use bitwise operators,
        // we get the value of floor(n/8) using n>>3 and get value of n%8 using n&7.
        // We need to write above expression in terms of floor(n/8) and n%8.
        // -> n/8 is equal to “floor(n/8) + (n%8)/8”.
        // Let us write the above expression in terms of floor(n/8) and n%8
        // -> n/9 = floor(n/8) + (n%8)/8 - [floor(n/8) + (n%8)/8]/9
        // -> n/9 = floor(n/8) - [floor(n/8) - 9(n%8)/8 + (n%8)/8]/9
        // -> n/9 = floor(n/8) - [floor(n/8) - n%8]/9
        // From above equation,
        // n is a multiple of 9 only if the expression
        // floor(n/8) – [floor(n/8) – n%8]/9 is an integer.
        // This expression can only be an integer if the sub-expression [floor(n/8) – n%8]/9 is an integer.
        // The subexpression can only be an integer if [floor(n/8) – n%8] is a multiple of 9.
        // So the problem reduces to a smaller value which can be written in terms of bitwise operators.

        if (value < 0) {
            return isMultipleOfNine(-value);
        } else if (value == 0 || value == 9) {
            return true;
        } else if (value < 9) {
            return false;
        } else {
            DataType dividedBy8 = value >> 3;
            DataType remainderBy8 = value & 7;
            if (dividedBy8 >= remainderBy8) {
                return isMultipleOfThree(static_cast<DataType>(dividedBy8 - remainderBy8));
            }
            return false;
        }
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

    static constexpr inline DataType getAlternatingZerosAndOnesFromLsb() {
        if constexpr (sizeof(DataType) == 1) {
            return 0xAA;
        } else if constexpr (sizeof(DataType) == 2) {
            return 0xAAAA;
        } else if constexpr (sizeof(DataType) == 4) {
            return 0xAAAAAAAA;
        } else if constexpr (sizeof(DataType) == 8) {
            return 0xAAAAAAAA'AAAAAAAA;
        }
        static_assert(true, "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline DataType getAlternatingOnesAndZerosFromLsb() {
        if constexpr (sizeof(DataType) == 1) {
            return 0x55;
        } else if constexpr (sizeof(DataType) == 2) {
            return 0x5555;
        } else if constexpr (sizeof(DataType) == 4) {
            return 0x55555555;
        } else if constexpr (sizeof(DataType) == 8) {
            return 0x55555555'55555555;
        }
        static_assert(true, "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline DataType getAbsoluteValue(DataType const value) {
        // There is also a different implementation on Math

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

    static constexpr inline DataType multiplyBySeven(DataType const value) { return (value << 3) - value; }

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
        return value == 0 ? 0 : 1 << (getNumberOfBits() - 1 - getNumberOfConsecutiveZerosFromMsb(value));
        // This formulas works as well:
        // return 1 << ((getNumberOfBits() - 1) ^ getNumberOfConsecutiveZerosFromMsb(value));
        // return (1 << (getNumberOfBits() - 1)) >> getNumberOfConsecutiveZerosFromMsb(value);    }

    static constexpr inline DataType roundUpToAPowerOf2(DataType const value) {
        return 1 << (getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value - 1));
        // This formulas works as well:
        // return (1 << (getNumberOfBits() - 1)) >> (getNumberOfConsecutiveZerosFromMsb(value - 1) - 1);
        // DataType result = value;
        // --result;
        // result |= result >> 1;
        // result |= result >> 2;
        // result |= result >> 4;
        // result |= result >> 8;
        // result |= result >> 16;
        // ++result;
        // return result;
    }

    static constexpr inline DataType getMinOfTwoValues(DataType const value1, DataType const value2) {
        return value2 ^ ((value1 ^ value2) & -(value1 < value2));
    }

    static constexpr inline DataType getMaxOfTwoValues(DataType const value1, DataType const value2) {
        return value1 ^ ((value1 ^ value2) & -(value1 < value2));
    }

    static constexpr inline DataType getModuloOfPowerOfTwo(
        DataType const value, DataType const divisorOfPowerOfTwoExponent) {
        return value & ((DataType(1) << divisorOfPowerOfTwoExponent) - 1);
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
