#pragma once

#include <Statistics/DataSample.hpp>

#include <numeric>
#include <vector>

namespace alba {

template <int DIMENSIONS>
class DataStatisticsUtilities {
public:
    using Sample = DataSample<DIMENSIONS>;    using Samples = std::vector<Sample>;

    static Sample calculateSum(Samples const& samples) {
        return (Sample)std::accumulate(samples.begin(), samples.end(), Sample(), std::plus<Sample>());    }

    static double calculateDistance(Sample const& sample1, Sample const& sample2) {
        Sample distanceCalculationTemp(sample1 - sample2);
        distanceCalculationTemp = distanceCalculationTemp.calculateRaiseToPower(2);
        return pow((double)distanceCalculationTemp.getSum(), 0.5);
    }
};

}  // namespace alba
