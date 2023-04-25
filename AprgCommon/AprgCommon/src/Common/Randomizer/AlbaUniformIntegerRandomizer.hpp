#pragma once

#include <random>

namespace alba {

template <typename IntegerType>
class AlbaUniformIntegerRandomizer {
public:
    AlbaUniformIntegerRandomizer(IntegerType const minimum, IntegerType const maximum)
        : m_randomNumberGenerator(),
          m_randomNumberEngine(m_randomNumberGenerator()),
          m_randomNumberDistribution(minimum, maximum) {}

    IntegerType getRandomInteger() { return m_randomNumberDistribution(m_randomNumberEngine); }

private:
    std::random_device m_randomNumberGenerator;
    std::mt19937 m_randomNumberEngine;
    std::uniform_int_distribution<IntegerType> m_randomNumberDistribution;
};

}  // namespace alba
