#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <random>

namespace alba {

template <typename ValueType>
class AlbaUniformDeterministicRandomizer {
public:
    static_assert(typeHelper::isArithmeticType<ValueType>(), "Value should be an arithmetic type");
    static_assert(sizeof(ValueType) != 0, "C++ standard does not allow char-types.");

    // Assumption: Lets use the size of ValueType as basis for a better engine (not proven)
    using RandomEngine = typeHelper::ConditionalType<sizeof(ValueType) <= 4, std::mt19937, std::mt19937_64>;

    using Distribution = typeHelper::ConditionalType<
        typeHelper::isIntegralType<ValueType>(), std::uniform_int_distribution<ValueType>,
        std::uniform_real_distribution<ValueType>>;

    AlbaUniformDeterministicRandomizer() : m_randomEngine(), m_randomNumberDistribution() {}

    explicit AlbaUniformDeterministicRandomizer(
        ValueType const minimum, ValueType const maximum, ValueType const customSeed)
        : m_randomEngine(customSeed), m_randomNumberDistribution(minimum, maximum) {}

    ValueType getRandomValue() { return m_randomNumberDistribution(m_randomEngine); }

    void setMinimumAndMaximum(ValueType const minimum, ValueType const maximum) {
        m_randomNumberDistribution = Distribution(minimum, maximum);
    }

    void setRandomSeed(ValueType const customSeed) { m_randomEngine.seed(customSeed); }

private:
    RandomEngine m_randomEngine;
    Distribution m_randomNumberDistribution;
};

}  // namespace alba

// Notes:

// On std::mt19937:
// -> Fast
// ---> Although generating numbers is fast, copying and constructing it isn't fast
// -> Extremely high quality, but not cryptographically secure
// -> Seedable (with more than 32 bits if you want)
// -> Reproducible (standard-mandated algorithm)
// -> Cannot be invoked with multiple threads (not thread safe)

// On std::uniform_int_distribution:
// -> "If the random number is not [0, 2^N), you are bad and you should feel bad." -> Stephan Lavavej
// ---> But still the C++ standard requires perfect uniformity
// -> Note: C++ standard does not allow char-types.
// -> Deterministic, but not invariant
// ---> Will vary across platforms, may vary across compilers/compiler versions

// On std::mt19937 vs std::mt19937_64:
// -> From: https://stackoverflow.com/questions/39154516/is-stdmt19937-64-faster-than-stdmt19937/39170215
// ---> It clearly depends on your compiler and their implementation.
// ---> I just tested and the 64bit version takes about 60% longer call-for-call,
// -----> so that makes the 64bit version about 25% fast bit-for-bit.
