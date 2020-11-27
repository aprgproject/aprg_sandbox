#pragma once

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

namespace alba
{

template <typename DataType>
class FrequencyStatistics
{
public:
    using FrequencySamples = std::map<DataType, unsigned int>;
    using FrequencyPair = std::pair<DataType, unsigned int>;
    using MultipleValues = std::vector<DataType>;

    static unsigned int calculateNumberOfSamples(FrequencySamples const& samples)
    {
        return std::accumulate(samples.begin(), samples.end(), (unsigned int)0, [](unsigned int partialResult, FrequencyPair const& frequencyPair)
        {
            return partialResult + ((unsigned int)frequencyPair.second);
        });
    }

    static DataType calculateSum(FrequencySamples const& samples)
    {
        return std::accumulate(samples.begin(), samples.end(), (DataType)0, [](DataType partialResult, FrequencyPair const& frequencyPair)
        {
            return partialResult + (frequencyPair.first*frequencyPair.second);
        });
    }

    static DataType calculateMean(FrequencySamples const& samples)
    {
        DataType result(0);
        unsigned int numberOfSamples = calculateNumberOfSamples(samples);
        if(numberOfSamples>0)
        {
            result = calculateSum(samples)/numberOfSamples;
        }
        return result;
    }

    static DataType calculateMedian(FrequencySamples const& samples)
    {
        unsigned int numberOfSamples = calculateNumberOfSamples(samples);
        double medianLocation = ((double)numberOfSamples+1)/2;
        unsigned int rangeOffsetForCurrentValue=0;
        unsigned int previousMinimumValue=0;
        DataType previousValue=0;
        DataType result(0);
        for(FrequencyPair const& frequencyPair : samples)
        {
            unsigned int minimumValueOffset = (frequencyPair.second>0) ? 1 : 0;
            if(rangeOffsetForCurrentValue+minimumValueOffset <= medianLocation && medianLocation <= rangeOffsetForCurrentValue+frequencyPair.second)
            {
                result = frequencyPair.first;
                break;
            }
            else if(previousMinimumValue <= medianLocation && medianLocation <= rangeOffsetForCurrentValue+frequencyPair.second)
            {
                result = (DataType)(((double)previousValue + frequencyPair.first)/2) ;
                break;
            }
            if(frequencyPair.second>0)
            {
                previousValue = frequencyPair.first;
                previousMinimumValue = minimumValueOffset + rangeOffsetForCurrentValue;
                rangeOffsetForCurrentValue += frequencyPair.second;
            }
        }
        return result;
    }

    static MultipleValues calculateMode(FrequencySamples const& samples)
    {
        MultipleValues result;
        typename FrequencySamples::const_iterator iteratorForMaxFrequency = std::max_element(samples.begin(), samples.end(), [](FrequencyPair const& frequencyPair1, FrequencyPair const& frequencyPair2)
        {
            return frequencyPair1.second < frequencyPair2.second;
        });
        unsigned int maxFrequency = iteratorForMaxFrequency->second;

        std::for_each(samples.begin(), samples.end(), [&](FrequencyPair const& frequencyPair)
        {
            if(maxFrequency == frequencyPair.second)
            {
                result.push_back(frequencyPair.first);
            }
        });
        return result;
    }
};

}