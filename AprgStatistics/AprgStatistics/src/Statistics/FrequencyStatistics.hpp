#pragma once

#include <map>
#include <vector>

namespace alba {

namespace FrequencyStatistics {

using FrequencySamples = std::map<int, int>;
using FrequencyPair = std::pair<int, int>;
using MultipleValues = std::vector<int>;
int calculateNumberOfSamples(FrequencySamples const& samples);
double calculateSum(FrequencySamples const& samples);
double calculateMean(FrequencySamples const& samples);
double calculateMedian(FrequencySamples const& samples);
MultipleValues calculateMode(FrequencySamples const& samples);

}  // namespace FrequencyStatistics

}  // namespace alba
