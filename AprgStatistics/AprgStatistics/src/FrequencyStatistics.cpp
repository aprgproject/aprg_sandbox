#include <FrequencyStatistics.hpp>

#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

namespace alba
{

unsigned int FrequencyStatistics::calculateNumberOfSamples(FrequencySamples const& samples)
{
    return accumulate(samples.begin(), samples.end(), (unsigned int)0, [](unsigned int partialResult, FrequencyPair const& frequencyPair)
    {
        return partialResult + ((unsigned int)frequencyPair.second);
    });}

double FrequencyStatistics::calculateSum(FrequencySamples const& samples)
{
    return accumulate(samples.begin(), samples.end(), (double)0, [](double partialResult, FrequencyPair const& frequencyPair)
    {
        return partialResult + (frequencyPair.first*frequencyPair.second);
    });}

double FrequencyStatistics::calculateMean(FrequencySamples const& samples)
{    double result(0);
    unsigned int numberOfSamples = calculateNumberOfSamples(samples);
    if(numberOfSamples>0)
    {
        result = calculateSum(samples)/numberOfSamples;
    }
    return result;
}

double FrequencyStatistics::calculateMedian(FrequencySamples const& samples)
{
    unsigned int numberOfSamples = calculateNumberOfSamples(samples);
    double medianLocation = ((double)numberOfSamples+1)/2;
    unsigned int rangeOffsetForCurrentValue=0;
    unsigned int previousMinimumValue=0;
    double previousValue=0;
    double result(0);
    for(auto const& frequencyPair : samples)
    {
        unsigned int minimumValueOffset = (frequencyPair.second>0) ? 1 : 0;
        if(rangeOffsetForCurrentValue+minimumValueOffset <= medianLocation && medianLocation <= rangeOffsetForCurrentValue+frequencyPair.second)        {
            result = frequencyPair.first;
            break;
        }        else if(previousMinimumValue <= medianLocation && medianLocation <= rangeOffsetForCurrentValue+frequencyPair.second)
        {
            result = (((double)previousValue + frequencyPair.first)/2) ;
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

FrequencyStatistics::MultipleValues FrequencyStatistics::calculateMode(FrequencySamples const& samples)
{
    MultipleValues result;
    typename FrequencySamples::const_iterator iteratorForMaxFrequency = max_element(samples.begin(), samples.end(), [](FrequencyPair const& frequencyPair1, FrequencyPair const& frequencyPair2)
    {
        return frequencyPair1.second < frequencyPair2.second;
    });
    unsigned int maxFrequency = iteratorForMaxFrequency->second;

    for_each(samples.begin(), samples.end(), [&](FrequencyPair const& frequencyPair)
    {
        if(maxFrequency == frequencyPair.second)
        {            result.push_back(frequencyPair.first);
        }
    });
    return result;}

}
