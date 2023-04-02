#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba
{
#ifdef __has_builtin
#define INLINE_WITHOUT_BUILT_IN
#define INLINE_WITH_BUILT_IN inline
#else
#define INLINE_WITHOUT_BUILT_IN inline
#define INLINE_WITH_BUILT_IN
#endif


namespace BitUtilitiesBuiltIn
{

INLINE_WITHOUT_BUILT_IN namespace BitUtilitiesWithoutBuiltIn
{
    template <typename DataType>
    constexpr inline unsigned int getNumberOfOnes(DataType const value)
    {
        unsigned int result(0);
        for(auto temporary(value); temporary!=0; temporary>>=1)
        {
            if((temporary&1) != 0)
            {
                ++result;
            }
        }
        return result;
    }
    template <typename DataType>
    constexpr inline bool isEvenParity(DataType const value)
    {
        return (getNumberOfOnes(value)&1) == 0; // AND implementation because we sure that its unsigned
    }
    template <typename DataType>
    constexpr inline unsigned int getNumberOfConsecutiveZerosFromMsb(
                DataType const value)
    {
        unsigned int result(0);
        for(DataType mask = DataType(1)<<((sizeof(DataType)*AlbaBitConstants::BYTE_SIZE_IN_BITS)-1); mask!=0; mask>>=1)
        {
            if((value&mask) == 0)
            {
                ++result;
            }
            else
            {
                break;
            }
        }
        return result;
    }
    template <typename DataType>
    constexpr inline unsigned int getNumberOfConsecutiveZerosFromLsb(
                DataType const value)
    {
        unsigned int result(0);
        for(DataType mask=1; mask!=0; mask<<=1)
        {
            if((value&mask) == 0)
            {
                ++result;
            }
            else
            {
                break;
            }
        }
        return result;
    }
}

INLINE_WITH_BUILT_IN namespace BitUtilitiesWithBuiltIn
{
#ifdef __has_builtin
    template <typename DataType>
    constexpr inline std::enable_if_t<sizeof(DataType) <= 4, bool> isEvenParity(DataType const value)
    {
        return __builtin_parity(value)==0;
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<4 < sizeof(DataType), bool> isEvenParity(DataType const value)
    {
        return __builtin_parityll(value)==0;
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<sizeof(DataType) <= 4, unsigned int> getNumberOfOnes(DataType const value)
    {
        return __builtin_popcount(value);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<4 < sizeof(DataType), unsigned int> getNumberOfOnes(DataType const value)
    {
        return __builtin_popcountll(value);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<sizeof(DataType) < 4, unsigned int>  getNumberOfConsecutiveZerosFromMsb(
                DataType const value)
    {
        static_assert(typeHelper::isUnsignedType<DataType>(), "There might a problem when DataType is signed because of conversion.");
        return __builtin_clz(value) - ((4-sizeof(DataType))*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<sizeof(DataType) == 4, unsigned int>  getNumberOfConsecutiveZerosFromMsb(
                DataType const value)
    {
        return __builtin_clz(value);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<4 < sizeof(DataType), unsigned int>  getNumberOfConsecutiveZerosFromMsb(
                DataType const value)
    {
        return __builtin_clzll(value);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<sizeof(DataType) <= 4, unsigned int>  getNumberOfConsecutiveZerosFromLsb(
                DataType const value)
    {
        return __builtin_ctz(value);
    }
    template <typename DataType>
    constexpr inline std::enable_if_t<4 < sizeof(DataType), unsigned int>  getNumberOfConsecutiveZerosFromLsb(
                DataType const value)
    {
        return __builtin_ctzll(value);
    }
#endif
}

}

#undef INLINE_WITH_BUILT_IN
#undef INLINE_WITHOUT_BUILT_IN

}
