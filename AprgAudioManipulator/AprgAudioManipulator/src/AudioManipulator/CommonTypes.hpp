#pragma once

#include <Audio/Audio.hpp>

#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace alba {

namespace AprgAudio {

struct SearchResultDetails {
    bool isSampleFound;
    int replicationIndex;
    int searchIndex;
    int numberOfSamples;
    double multiplierForSearch;
    double minDifference;
};
using SearchResultsDetails = std::vector<SearchResultDetails>;

using Indexes = std::vector<int>;

using DoubleOptional = std::optional<double>;
using Samples = std::vector<double>;
using AudioInDouble = Audio<double>;

using ValuesToIndexes = std::multimap<double, int>;

}  // namespace AprgAudio

}  // namespace alba
