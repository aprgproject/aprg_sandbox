#include "Utilities.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

namespace Audio
{

void retrieveDeltas(
        Samples & deltaSamples,
        double const* pointerOfSampleToCheck,
        unsigned int const numberOfSamples)
{
    deltaSamples.reserve(numberOfSamples);
    double previousValue(0);
    for(unsigned int i=0; i<numberOfSamples; i++)
    {
        deltaSamples.emplace_back(pointerOfSampleToCheck[i]-previousValue);
        previousValue=pointerOfSampleToCheck[i];
    }
}

double getAverageOfSamples(Samples const& samples)
{
    return accumulate(samples.cbegin(), samples.cend(), 0.0) / samples.size();
}

}

}
