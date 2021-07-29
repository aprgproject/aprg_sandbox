#pragma once

#include <DataSample.hpp>
#include <DataStatistics.hpp>

#include <algorithm>
#include <iterator>

namespace alba
{

template <unsigned int dimensions>
class KMeansClustering
{
public:
    using Statistics = DataStatistics<dimensions>;
    using StatisticsUtilities = DataStatisticsUtilities<dimensions>;
    using Sample = DataSample<dimensions>;
    using Samples = std::vector<Sample>;
    using GroupOfSamples = std::vector<Samples>;
    using SamplesToGroupPair = std::pair<Sample, unsigned int>;
    using SamplesToGroupPairs = std::vector<std::pair<Sample, unsigned int>>;

    KMeansClustering()
    {}

    void clear()
    {
        m_samples.clear();
    }

    void addSample(Sample sample)
    {
        m_samples.emplace_back(sample);
    }

    void addSamples(Samples samples)
    {
        m_samples.reserve(m_samples.size() + samples.size());
        std::copy(samples.cbegin(), samples.cend(), std::back_inserter(m_samples));
    }

    Samples getSamples() const
    {
        return m_samples;
    }

    GroupOfSamples getGroupOfSamplesUsingKMeans(unsigned int const numberOfGroups) const
    {
        SamplesToGroupPairs samplesToGroupPairs(calculateInitialSamplesToGroupPairsFromSavedSamples(numberOfGroups));
        bool isSamplesToGroupPairsChanged(true);
        while(isSamplesToGroupPairsChanged)
        {
            isSamplesToGroupPairsChanged=false;
            GroupOfSamples groupOfSamples(calculateGroupOfSamplesFromSamplesToGroupPairs(samplesToGroupPairs, numberOfGroups));
            Samples meanForEachGroup(calculateMeanForEachGroup(groupOfSamples));

            for(SamplesToGroupPair & samplesToGroupPair : samplesToGroupPairs)
            {
                unsigned int nearestGroup(0);
                double nearestDistance(0);
                for(unsigned int groupIndex=0; groupIndex<numberOfGroups; groupIndex++)
                {
                    double currentDistance(StatisticsUtilities::calculateDistance(samplesToGroupPair.first, meanForEachGroup[groupIndex]));
                    if(groupIndex==0  || nearestDistance>currentDistance)
                    {
                        nearestGroup = groupIndex;
                        nearestDistance = currentDistance;
                    }
                }
                isSamplesToGroupPairsChanged = isSamplesToGroupPairsChanged||(nearestGroup!=samplesToGroupPair.second);
                samplesToGroupPair.second = nearestGroup;
            }
        }
        return calculateGroupOfSamplesFromSamplesToGroupPairs(samplesToGroupPairs, numberOfGroups);
    }

private:
    GroupOfSamples calculateGroupOfSamplesFromSamplesToGroupPairs(SamplesToGroupPairs const& samplesToGroupPairs, unsigned int const numberOfGroups) const
    {
        GroupOfSamples result;
        for(unsigned int groupIndex=0; groupIndex<numberOfGroups; groupIndex++)
        {
            result.emplace_back();
        }
        for(SamplesToGroupPair const& samplesToGroupPair : samplesToGroupPairs)
        {
            result[samplesToGroupPair.second].emplace_back(samplesToGroupPair.first);
        }
        return result;
    }

    SamplesToGroupPairs calculateInitialSamplesToGroupPairsFromSavedSamples(unsigned int const numberOfGroups) const
    {
        SamplesToGroupPairs result;
        unsigned int count(0);
        unsigned int numberSamplesPerGroup((m_samples.size()/numberOfGroups)+1);
        for(Sample const& sample : m_samples)
        {
            result.emplace_back(sample, count++/numberSamplesPerGroup);
        }
        return result;
    }

    Samples calculateMeanForEachGroup(GroupOfSamples const& groupOfSamples) const
    {
        Samples meanForEachGroup;
        for(unsigned int groupIndex=0; groupIndex<groupOfSamples.size(); groupIndex++)
        {
            Statistics statistics(groupOfSamples[groupIndex]);
            meanForEachGroup.emplace_back(statistics.getMean());
        }
        return meanForEachGroup;
    }
    Samples m_samples;
};

}
