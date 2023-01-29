#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <cmath>
#include <type_traits>

namespace alba
{
template <typename DataTypeToManipulate>
class AlbaBitValueUtilities
{public:

    // rule of five or six
    AlbaBitValueUtilities() = delete;
    ~AlbaBitValueUtilities() = delete; // disallow allocation on stack, only on heap(but no constructor so not possible as well)
    AlbaBitValueUtilities(AlbaBitValueUtilities const&) = delete;
    AlbaBitValueUtilities & operator= (AlbaBitValueUtilities const&) = delete;
    AlbaBitValueUtilities(AlbaBitValueUtilities &&) = delete;
    AlbaBitValueUtilities & operator= (AlbaBitValueUtilities &&) = delete;

    static constexpr inline bool isPowerOfTwo(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return (value & (value-1))==0;
    }

    static constexpr inline bool isEvenParity(DataTypeToManipulate const value)
    {
        // This is similar with __builtin_parity(x)

        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return mathHelper::isEven(getNumberOfOnes(value));
    }

    static constexpr inline unsigned int getNumberOfBits()
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        // return std::numeric_limits<DataTypeToManipulate>::digits + (std::numeric_limits<DataTypeToManipulate>::is_signed ? 1 : 0);

        // Use sizeof instead.
        // -> sizeof: Yields the size in bytes of the object representation of type.
        return sizeof(DataTypeToManipulate) * AlbaBitConstants::BYTE_SIZE_IN_BITS;
    }

    static constexpr inline unsigned int getNumberOfOnes(DataTypeToManipulate const)    {
        // This is similar with __builtin_popcount(x)
        // std::bitset can be used here but it would no longer be constexpr
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate), "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline unsigned int getNumberOfConsecutiveZerosFromMsb(DataTypeToManipulate const)
    {
        // Think about this
        // This is similar with __builtin_clz(x)

        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate), "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline unsigned int getNumberOfConsecutiveZerosFromLsb(DataTypeToManipulate const)
    {
        // Think about this
        // This is similar with __builtin_ctz(x)

        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");
        return 0;
    }

    static constexpr inline unsigned int getHammingDistance(DataTypeToManipulate const value1, DataTypeToManipulate const value2)
    {
        // The Hamming distance hamming(a,b) between two bitstrings a and b of equal length is the number of positions where the bitstrings differ.

        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

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
        static_assert(sizeof(DataTypeToManipulate) != sizeof(DataTypeToManipulate),
                      "This size or type is not supported. Please add a specialization if needed.");

        return 0;
    }

    static constexpr inline DataTypeToManipulate get2ToThePowerOf(DataTypeToManipulate const exponent)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return DataTypeToManipulate(1) << exponent;
    }

    static constexpr inline DataTypeToManipulate getLogarithmWithBase2Of(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        DataTypeToManipulate result = getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value);
        result = (result == 0) ? 0 : result-1;
        return result;
    }

    static constexpr inline DataTypeToManipulate getCeilOfLogarithmWithBase2Of(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        DataTypeToManipulate result = getNumberOfBits() - getNumberOfConsecutiveZerosFromMsb(value);
        result = (result == 0) ? 0 : isPowerOfTwo(value) ? result-1 : result;
        return result;
    }

    static constexpr inline DataTypeToManipulate getOnesComplement(DataTypeToManipulate const value)
    {
        static_assert(std::is_integral<DataTypeToManipulate>::value, "DataTypeToManipulate must be an integer");

        return ~value;
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

}
