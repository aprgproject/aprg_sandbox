#include <Randomizer/AlbaRandomizer.hpp>

#include <math.h>
#include <windows.h>

namespace alba{

AlbaRandomizer::AlbaRandomizer()
{
    resetRandomSeed();
}

void AlbaRandomizer::resetRandomSeed()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    srand(time.wMilliseconds);
}

int AlbaRandomizer::getRandomValueInUniformDistribution(int const first, int const second) const
{
    int minimum = (first<second) ? first : second;
    int maximum = (first>second) ? first : second;
    int numberOfRandomValues(maximum-minimum+1);

    double randomRealValue((double)rand()*numberOfRandomValues/(RAND_MAX+1));
    return minimum+floor(randomRealValue);
}

}//namespace alba
