#pragma once

#include <Audio/CommonTypes.hpp>

namespace alba
{

namespace AprgAudio
{

class NearestSamples
{
public:
    NearestSamples(Samples const& samples);

    Indexes getNearestSamplesIndexes(
            double const value,
            unsigned int const recommendedNumberOfSamples);

private:
    void saveToValuesToIndexes();
    Samples const& m_samples;
    ValuesToIndexes m_valuesToIndexes;
};
}

}
