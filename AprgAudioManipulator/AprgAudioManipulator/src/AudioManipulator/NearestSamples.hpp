#pragma once

#include <AudioManipulator/CommonTypes.hpp>

namespace alba {

namespace AprgAudio {

class NearestSamples {
public:
    NearestSamples(Samples const& samples);

    Indexes getNearestSamplesIndexes(double const value, int const recommendedNumberOfSamples);

private:
    void saveToValuesToIndexes();
    Samples const& m_samples;
    ValuesToIndexes m_valuesToIndexes;
};
}  // namespace AprgAudio

}  // namespace alba
