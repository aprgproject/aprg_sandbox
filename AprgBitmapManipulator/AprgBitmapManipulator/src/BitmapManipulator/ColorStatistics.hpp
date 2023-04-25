#pragma once

#include <Statistics/DataStatistics.hpp>

#include <set>
#include <string>

namespace alba {

namespace AprgBitmap {

void gatherAndSaveColorStatistics(std::string const& bitmapPath);

class AprgColorStatistics {
public:
    using OneDimensionStatistics = DataStatistics<1>;

    void gatherStatistics(std::string const& bitmapPath);
    void saveColorData(std::string const& path);
    void saveColorStatistics(std::string const& path);

private:
    std::multiset<double> colorIntensitySet;
    std::multiset<double> luma601Set;
    std::multiset<double> luma709Set;
    std::multiset<double> hueDegreesSet;
    std::multiset<double> saturationLightnessSet;
    std::multiset<double> lightnessSet;
    std::multiset<double> saturationValueSet;
    std::multiset<double> valueSet;
    OneDimensionStatistics::Samples colorIntensitySamples;
    OneDimensionStatistics::Samples saturationLightnessSamples;
    OneDimensionStatistics::Samples lightnessSamples;
    OneDimensionStatistics::Samples saturationValueSamples;
    OneDimensionStatistics::Samples valueSamples;
    OneDimensionStatistics::Samples luma601Samples;
    OneDimensionStatistics::Samples luma709Samples;
};

}  // namespace AprgBitmap

}  // namespace alba
