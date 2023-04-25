#pragma once

#include <Audio/Audio.hpp>
#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/CommonTypes.hpp>
#include <AudioManipulator/NewSamplesBuilder.hpp>

namespace alba {

namespace AprgAudio {

void retrieveDeltas(Samples& deltaSamples, Samples const& pointerOfSampleToCheck, unsigned int const numberOfSamples);

double getSumInRange(
    Samples const& samples, unsigned int const startIndexIncluded, unsigned int const endIndexExcluded);
double getAverageOfSamples(Samples const& samples);
double getAverageInRange(
    Samples const& samples, unsigned int const startIndexIncluded, unsigned int const endIndexExcluded);
double getCommonMultiplierForDeltaSamples(
    Samples const& samples, unsigned int const startIndexIncluded, unsigned int const endIndexExcluded);
double getCommonMultiplierUsingSumAndNumberOfItems(double const sum, unsigned int const numberOfItems);
void multiplyValueToAllSamples(Samples& samples, double const value);
DoubleOptional compareDeltasAndGetDifference(
    Samples const& deltaSamples1, Samples const& deltaSamples2, double const multiplierToSample2,
    unsigned int const startOfDeltaSamples1, unsigned int const startOfDeltaSamples2,
    unsigned int const numberOfSamples);

void searchForBestSampleIndexes(
    SearchResultsDetails& replicateAndSearchIndexes, unsigned int const sampleIntervalForReplication,
    unsigned int const numberOfSamplesForReplication, unsigned int const numberOfSearchSamplesPerReplication,
    Samples const& samplesToReplicate, Samples const& samplesToSearch);

void searchAndTryToReplicateSamples(
    AudioInDouble& audioToChange, AudioInDouble const& audioToReplicate, AudioInDouble const& audioToSearch,
    unsigned channelIndexInAudioToChange, unsigned channelIndexInAudioToReplicate, unsigned channelIndexInAudioToSearch,
    bool const alwaysPutNewValue);

void searchAndTryToReplicate(
    std::string const& filePathForAudioToChange, std::string const& filePathForAudioToReplicate,
    std::string const& filePathForAudioToSearch, bool const alwaysPutNewValue);
}  // namespace AprgAudio

}  // namespace alba
