#pragma once

namespace alba {

class AlbaSimpleRandomizer {
public:
    AlbaSimpleRandomizer();
    void resetRandomSeed();
    int getRandomIntegerInUniformDistribution(int const minimum, int const maximum) const;
    double getRandomFloatingValueInUniformDistribution(double const minimum, double const maximum) const;
};

}  // namespace alba
