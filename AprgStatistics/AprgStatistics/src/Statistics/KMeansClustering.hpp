#pragma once

#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatistics.hpp>

#include <algorithm>
#include <iterator>

namespace alba {

template <int DIMENSIONS>
class KMeansClustering {
public:
    using Statistics = DataStatistics<DIMENSIONS>;    using StatisticsUtilities = DataStatisticsUtilities<DIMENSIONS>;
    using Sample = DataSample<DIMENSIONS>;
    using Samples = std::vector<Sample>;
    using GroupOfSamples = std::vector<Samples>;
    using SamplesGroupPair = std::pair<Sample, int>;
    using SamplesGroupPairs = std::vector<std::pair<Sample, int>>;

    KMeansClustering() {}
    void clear() { m_samples.clear(); }

    void addSample(Sample const& sample) { m_samples.emplace_back(sample); }
    void addSamples(Samples const& samples) {
        m_samples.reserve(m_samples.size() + samples.size());
        std::copy(samples.cbegin(), samples.cend(), std::back_inserter(m_samples));
    }

    Samples getSamples() const { return m_samples; }

    Samples& getSamplesReference() { return m_samples; }

    GroupOfSamples getGroupOfSamplesUsingKMeans(int const numberOfGroups) const {
        SamplesGroupPairs samplesGroupPairs(calculateInitialSamplesGroupPairsFromSavedSamples(numberOfGroups));
        bool isSamplesGroupPairsChanged(true);
        while (isSamplesGroupPairsChanged) {            isSamplesGroupPairsChanged = false;
            GroupOfSamples groupOfSamples(
                calculateGroupOfSamplesFromSamplesGroupPairs(samplesGroupPairs, numberOfGroups));
            Samples meanForEachGroup(calculateMeanForEachGroup(groupOfSamples));

            for (SamplesGroupPair& samplesGroupPair : samplesGroupPairs) {
                int nearestGroup(0);
                double nearestDistance(0);
                for (int groupIndex = 0; groupIndex < numberOfGroups; groupIndex++) {
                    double currentDistance(
                        StatisticsUtilities::calculateDistance(samplesGroupPair.first, meanForEachGroup[groupIndex]));
                    if (groupIndex == 0 || nearestDistance > currentDistance) {                        nearestGroup = groupIndex;
                        nearestDistance = currentDistance;
                    }
                }                isSamplesGroupPairsChanged = isSamplesGroupPairsChanged || (nearestGroup != samplesGroupPair.second);
                samplesGroupPair.second = nearestGroup;
            }
        }
        return calculateGroupOfSamplesFromSamplesGroupPairs(samplesGroupPairs, numberOfGroups);
    }

private:
    GroupOfSamples calculateGroupOfSamplesFromSamplesGroupPairs(
        SamplesGroupPairs const& samplesGroupPairs, int const numberOfGroups) const {
        GroupOfSamples result;
        for (int groupIndex = 0; groupIndex < numberOfGroups; groupIndex++) {
            result.emplace_back();
        }
        for (SamplesGroupPair const& samplesGroupPair : samplesGroupPairs) {            result[samplesGroupPair.second].emplace_back(samplesGroupPair.first);
        }
        return result;
    }

    SamplesGroupPairs calculateInitialSamplesGroupPairsFromSavedSamples(int const numberOfGroups) const {
        SamplesGroupPairs result;
        int count(0);
        int numberSamplesPerGroup((m_samples.size() / numberOfGroups) + 1);
        for (Sample const& sample : m_samples) {
            result.emplace_back(sample, count++ / numberSamplesPerGroup);
        }        return result;
    }

    Samples calculateMeanForEachGroup(GroupOfSamples const& groupOfSamples) const {
        Samples meanForEachGroup;
        for (int groupIndex = 0; groupIndex < static_cast<int>(groupOfSamples.size()); groupIndex++) {
            Statistics statistics(groupOfSamples[groupIndex]);
            meanForEachGroup.emplace_back(statistics.getMean());
        }        return meanForEachGroup;
    }
    Samples m_samples;
};
}  // namespace alba
