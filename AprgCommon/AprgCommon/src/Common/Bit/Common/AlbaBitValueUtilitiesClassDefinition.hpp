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
    ~AlbaBitValueUtilities() =
        delete;  // disallow allocation on stack, only on heap(but no constructor so not possible as well)
    AlbaBitValueUtilities(AlbaBitValueUtilities const &) = delete;
    AlbaBitValueUtilities &operator=(AlbaBitValueUtilities const &) = delete;
    AlbaBitValueUtilities(AlbaBitValueUtilities &&) = delete;
    AlbaBitValueUtilities &operator=(AlbaBitValueUtilities &&) = delete;

    static constexpr inline bool isPowerOfTwo(DataType const value) { return (value & (value - 1)) == 0; }

    static constexpr inline unsigned int getNumberOfBits() {
        // numeric_limits<>::digits + numeric_limits<>::is_signed approach
        // return std::numeric_limits<DataType>::digits + (std::numeric_limits<DataType>::is_signed ? 1 : 0);

        // sizeof approach
        // -> sizeof: Yields the size in bytes of the object representation of type.
        return sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
    }

    static inline constexpr bool isEvenParity(DataType const value) { return BitUtilitiesBuiltIn::isEvenParity(value); }

    static inline constexpr unsigned int getNumberOfOnes(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfOnes(value);
    }

    static inline constexpr unsigned int getNumberOfConsecutiveZerosFromMsb(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb(value);
    }

    static inline constexpr unsigned int getNumberOfConsecutiveZerosFromLsb(DataType const value) {
        return BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb(value);
    }

    static constexpr inline unsigned int getHammingDistance(DataType const value1, DataType const value2) {
        // The Hamming distance hamming(a,b) between two bitstrings a and b of equal length is the number of positions
        // where the bitstrings differ.

        return getNumberOfOnes(value1 ^ value2);
    }

    static constexpr inline DataType generateOnesWithNumberOfBits(unsigned int const numberOfOnes) {
        return (DataType(1) << numberOfOnes) - 1;
    }

    static constexpr inline DataType getAllOnes() {
        static_assert(
            sizeof(DataType) == -1, "This size or type is not supported. Please add a specialization if needed.");

        return 0;
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

    static constexpr inline DataType getGreatestPowerOf2Factor(DataType const value) { return value & (-value); }
};

}  // namespace alba
