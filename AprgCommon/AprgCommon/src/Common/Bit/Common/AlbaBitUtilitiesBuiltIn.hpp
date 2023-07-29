#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba {

#ifdef __has_builtin  // you could also use __has_include as well
#define INLINE_WITHOUT_BUILT_IN
#define INLINE_WITH_BUILT_IN inline
#else
#define INLINE_WITHOUT_BUILT_IN inline
#define INLINE_WITH_BUILT_IN
#endif

namespace BitUtilitiesBuiltIn {

INLINE_WITHOUT_BUILT_IN namespace BitUtilitiesWithoutBuiltIn {
    template <typename DataType>
    constexpr inline std::size_t getNumberOfOnes(DataType const value) {
        std::size_t result(0);
        for (auto temporary(value); temporary != 0; temporary >>= 1) {
            if (temporary & 1) {
                ++result;
            }
        }
        return result;
    }
    template <typename DataType>
    constexpr inline bool isEvenParity(DataType const value) {
        return (getNumberOfOnes(value) & 1) == 0;  // AND implementation because we sure that its Unsigned
    }
    template <typename DataType>
    constexpr inline std::size_t getNumberOfConsecutiveZerosFromMsb(DataType const value) {
        std::size_t result(0);
        for (DataType mask = DataType(1) << ((sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS) - 1); mask != 0;
             mask >>= 1) {
            if ((value & mask) == 0) {
                ++result;
            } else {
                break;
            }
        }
        return result;
    }
    template <typename DataType>
    constexpr inline std::size_t getNumberOfConsecutiveZerosFromLsb(DataType const value) {
        std::size_t result(0);
        for (DataType mask = 1; mask != 0; mask <<= 1) {
            if ((value & mask) == 0) {
                ++result;
            } else {
                break;
            }
        }
        return result;
    }
}

INLINE_WITH_BUILT_IN namespace BitUtilitiesWithBuiltIn {
#ifdef __has_builtin

    // check this documentation: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html

    template <typename DataType>
    constexpr inline bool isEvenParity(DataType const value) {
        if constexpr (sizeof(DataType) <= sizeof(unsigned int)) {
            return __builtin_parity(value) == 0;
        } else if constexpr (sizeof(DataType) <= sizeof(unsigned long)) {
            return __builtin_parityl(value) == 0;
        } else if constexpr (sizeof(DataType) <= sizeof(unsigned long long)) {
            return __builtin_parityll(value) == 0;
        } else {
            return false;  // just return something if size is too large
        }
    }
    template <typename DataType>
    constexpr inline std::size_t getNumberOfOnes(DataType const value) {
        if constexpr (sizeof(DataType) <= sizeof(unsigned int)) {
            return __builtin_popcount(value);
        } else if constexpr (sizeof(DataType) <= sizeof(unsigned long)) {
            return __builtin_popcountl(value);
        } else if constexpr (sizeof(DataType) <= sizeof(unsigned long long)) {
            return __builtin_popcountll(value);
        } else {
            return 0;  // just return something if size is too large
        }
    }
    template <typename DataType>
    constexpr inline std::size_t getNumberOfConsecutiveZerosFromMsb(DataType const value) {
        if (value == 0) {
            return sizeof(DataType) * AlbaBitConstants::BYTE_SIZE_IN_BITS;  // covers undefined behavior
        } else {
            if constexpr (sizeof(DataType) < sizeof(unsigned int)) {
                return __builtin_clz(value) -
                       ((sizeof(unsigned int) - sizeof(DataType)) * AlbaBitConstants::BYTE_SIZE_IN_BITS);
                ;
            } else if constexpr (sizeof(DataType) == sizeof(unsigned int)) {
                return __builtin_clz(value);
            } else if constexpr (sizeof(DataType) <= sizeof(unsigned long)) {
                return __builtin_clzl(value);
            } else if constexpr (sizeof(DataType) <= sizeof(unsigned long long)) {
                return __builtin_clzll(value);
            } else {
                return BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb(value);
            }
        }
    }
    template <typename DataType>
    constexpr inline std::size_t getNumberOfConsecutiveZerosFromLsb(DataType const value) {
        if (value == 0) {
            return 0;  // covers undefined behavior
        } else {
            if constexpr (sizeof(DataType) <= sizeof(unsigned int)) {
                return __builtin_ctz(value);
            } else if constexpr (sizeof(DataType) <= sizeof(unsigned long)) {
                return __builtin_ctzl(value);
            } else if constexpr (sizeof(DataType) <= sizeof(unsigned long long)) {
                return __builtin_ctzll(value);
            } else {
                return BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb(value);
            }
        }
    }
#endif
}

}  // namespace BitUtilitiesBuiltIn

#undef INLINE_WITH_BUILT_IN
#undef INLINE_WITHOUT_BUILT_IN

}  // namespace alba
