#pragma once

#include <map>
#include <vector>

namespace alba {

namespace FrequencyStatistics {

using FrequencySamples = std::map<int, unsigned int>;
using FrequencyPair = std::pair<int, unsigned int>;
using MultipleValues = std::vector<int>;
unsigned int calculateNumberOfSamples(FrequencySamples const& samples);
double calculateSum(FrequencySamples const& samples);
double calculateMean(FrequencySamples const& samples);
double calculateMedian(FrequencySamples const& samples);
MultipleValues calculateMode(FrequencySamples const& samples);

}  // namespace FrequencyStatistics

}  // namespace alba
