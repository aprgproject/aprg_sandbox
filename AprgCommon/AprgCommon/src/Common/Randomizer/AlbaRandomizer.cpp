#include "AlbaRandomizer.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

#include <cmath>

namespace alba
{

AlbaRandomizer::AlbaRandomizer()
{
    resetRandomSeed();
}

void AlbaRandomizer::resetRandomSeed()
{
    srand(getCurrentDateTime().getMicroSeconds());
}

int AlbaRandomizer::getRandomValueInUniformDistribution(int const first, int const second) const
{
    int minimum = (first<second) ? first : second;
    int maximum = (first>second) ? first : second;
    int numberOfRandomValues(maximum-minimum+1);

    double randomRealValue = static_cast<double>(rand())*numberOfRandomValues / (static_cast<double>(RAND_MAX)+1);
    return static_cast<int>(minimum+floor(randomRealValue));
}

}//namespace alba
