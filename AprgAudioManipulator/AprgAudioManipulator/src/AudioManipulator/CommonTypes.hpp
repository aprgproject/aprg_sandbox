#pragma once

#include <Audio/Audio.hpp>
#include <Common/Optional/AlbaOptional.hpp>

#include <map>
#include <utility>
#include <vector>

namespace alba
{

namespace AprgAudio
{

struct SearchResultDetails
{
    bool isSampleFound;
    unsigned int replicationIndex;
    unsigned int searchIndex;
    unsigned int numberOfSamples;
    double multiplierForSearch;
    double minDifference;
};
using SearchResultsDetails=std::vector<SearchResultDetails>;

using Indexes=std::vector<unsigned int>;

using DoubleOptional=AlbaOptional<double>;
using Samples=std::vector<double>;
using AudioInDouble=Audio<double>;

using ValuesToIndexes=std::multimap<double, unsigned int>;

}

}
