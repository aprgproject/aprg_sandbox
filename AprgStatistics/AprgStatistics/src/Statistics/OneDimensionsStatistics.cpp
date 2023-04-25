#include <Statistics/OneDimensionsStatistics.hpp>

#include <algorithm>

namespace alba {

OneDimensionsStatistics::PairOfDoubles OneDimensionsStatistics::getMinMaxFromSamples(Samples const& samples) {
    PairOfDoubles result;
    result.first = 0;
    result.second = 0;
    auto const minMaxElement = std::minmax_element(
        samples.cbegin(), samples.cend(),
        [](Sample const& sample1, Sample const& sample2) { return sample1.getValueAt(0) < sample2.getValueAt(0); });
    if (minMaxElement.first != samples.cend()) {
        result.first = minMaxElement.first->getValueAt(0);
    }
    if (minMaxElement.second != samples.cend()) {
        result.second = minMaxElement.second->getValueAt(0);
    }
    return result;
}

}  // namespace alba
