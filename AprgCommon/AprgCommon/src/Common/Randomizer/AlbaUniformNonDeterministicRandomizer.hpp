#pragma once

#include <Common/Randomizer/EntropySources/AlbaCombinedEntropySource.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <cassert>
#include <random>

namespace alba {

template <typename ValueType>
class AlbaUniformNonDeterministicRandomizer {
public:
    static_assert(typeHelper::isArithmeticType<ValueType>(), "Value should be an arithmetic type");
    static_assert(sizeof(ValueType) != 0, "C++ standard does not allow char-types.");

    // Using std::random_device will NOT guarantee non determinism (see notes and tests)
    // using EntropySeedSource = std::random_device;
    // using EntropySeedSource = AlbaEntropySourceBasedOnTime; // there might be a random device
    using EntropySeedSource = AlbaCombinedEntropySource;

    // Assumption: Lets use the size of ValueType as basis for a better engine (not proven)
    using RandomEngine = typeHelper::ConditionalType<sizeof(ValueType) <= 4, std::mt19937, std::mt19937_64>;

    using Distribution = typeHelper::ConditionalType<
        typeHelper::isIntegralType<ValueType>(), std::uniform_int_distribution<ValueType>,
        std::uniform_real_distribution<ValueType>>;

    AlbaUniformNonDeterministicRandomizer(ValueType const minimum, ValueType const maximum)
        : m_entropySeedSource(), m_randomEngine(m_entropySeedSource()), m_randomNumberDistribution(minimum, maximum) {}

    ValueType getRandomValue() { return m_randomNumberDistribution(m_randomEngine); }

    void resetRandomSeed() { m_randomEngine.seed(m_entropySeedSource()); }

private:
    EntropySeedSource m_entropySeedSource;
    RandomEngine m_randomEngine;    Distribution m_randomNumberDistribution;
};

}  // namespace alba
// Notes:

// On std::random_device:
// -> Non determinism is not guaranteed
// ---> std::random_device is a uniformly-distributed integer random number generator
// -----> that produces non-deterministic random numbers.
// ---> std::random_device may be implemented in terms of an implementation-defined pseudo-random number engine
// -----> if a non-deterministic source (e.g. a hardware device) is not available to the implementation.
// ---> In this case each std::random_device object may generate the same number sequence.
// -> Possibly Slow:
// ---> Performance is strongly platform-dependent
// -> Possibly crypto-secure (check compiler/implementors documentation)
// -> Not seedable, non-reproducible
