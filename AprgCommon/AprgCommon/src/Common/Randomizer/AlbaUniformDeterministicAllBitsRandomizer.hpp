#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <random>

namespace alba {

template <typename ValueType>
class AlbaUniformDeterministicAllBitsRandomizer {
public:
    static_assert(typeHelper::isArithmeticType<ValueType>(), "Value should be an arithmetic type");
    static_assert(sizeof(ValueType) != 0, "C++ standard does not allow char-types.");

    // Assumption: Lets use the size of ValueType as basis for a better engine (not proven)
    using RandomEngine = typeHelper::ConditionalType<sizeof(ValueType) <= 4, std::mt19937, std::mt19937_64>;

    using Distribution = typeHelper::ConditionalType<
        typeHelper::isIntegralType<ValueType>(), std::uniform_int_distribution<ValueType>,
        std::uniform_real_distribution<ValueType>>;

    AlbaUniformDeterministicAllBitsRandomizer(ValueType const customSeed) : m_randomEngine(customSeed) {}

    ValueType getRandomValue() { return m_randomEngine(); }

private:
    RandomEngine m_randomEngine;
};

}  // namespace alba

// Notes:

// When is it safe to skip uniform_int_distribution?
// -> mt19937 outputs: [0, 2^32)
// -> mt19937_64 outputs: [0, 2^64)
// -> So when random values range from [0, 2^N) or you can use bit masks.
// ---> In this case, masking is safe, simple, and efficient (very fast)
// ---> In all other cases, use uniform_int_distribution
