#pragma once

namespace alba {

class AlbaOldRandomizer {
public:
    AlbaOldRandomizer();
    void resetRandomSeed();
    int getRandomIntegerInUniformDistribution(int const minimum, int const maximum) const;
    double getRandomFloatingValueInUniformDistribution(double const minimum, double const maximum) const;
};

}  // namespace alba
