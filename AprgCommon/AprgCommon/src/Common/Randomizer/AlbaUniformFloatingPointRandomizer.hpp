#pragma once

#include <random>

namespace alba {

template <typename FloatingPointType>
class AlbaUniformFloatingPointRandomizer {
public:
    AlbaUniformFloatingPointRandomizer(FloatingPointType const minimum, FloatingPointType const maximum)
        : m_randomNumberGenerator(),
          m_randomNumberEngine(m_randomNumberGenerator()),
          m_randomNumberDistribution(minimum, maximum) {}

    FloatingPointType getRandomFloatingPointValue() { return m_randomNumberDistribution(m_randomNumberEngine); }

private:
    std::random_device m_randomNumberGenerator;
    std::mt19937 m_randomNumberEngine;
    std::uniform_real_distribution<FloatingPointType> m_randomNumberDistribution;
};

}  // namespace alba
