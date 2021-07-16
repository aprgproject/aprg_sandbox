#pragma once

#include <Audio/CommonTypes.hpp>

namespace alba
{

namespace Audio
{

void retrieveDeltas(
        Samples & deltaSamples,
        double const* pointerOfSampleToCheck,
        unsigned int const numberOfSamples);

double getAverageOfSamples(Samples const& samples);

}

}
