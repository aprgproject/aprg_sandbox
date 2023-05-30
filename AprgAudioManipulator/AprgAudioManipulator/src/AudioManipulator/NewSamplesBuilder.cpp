#include "NewSamplesBuilder.hpp"

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace AprgAudio {

NewSamplesBuilder::SampleMergingDetails::SampleMergingDetails() : isChanged(false), totalValue(0), weight(0) {}

NewSamplesBuilder::NewSamplesBuilder(Samples const& oldSamples) : m_oldSamples(oldSamples) {}

void NewSamplesBuilder::putSamplesBasedOnSearchResultAndSamples(
    Samples& samplesToChange, SearchResultsDetails const& searchResultDetails, Samples const& searchSamples,
    bool const alwaysPutNewValue) {
    SamplesMergingDetails samplesMergingDetails;
    retrieveSampleMergingDetails(samplesMergingDetails, searchResultDetails, searchSamples);
    saveToNewSamples(samplesToChange, samplesMergingDetails, alwaysPutNewValue);
}

void NewSamplesBuilder::retrieveSampleMergingDetails(
    SamplesMergingDetails& samplesMergingDetails, SearchResultsDetails const& details, Samples const& searchSamples) {
    int searchSamplesSize = searchSamples.size();
    for (SearchResultDetails const& detail : details) {
        double midpoint = static_cast<double>(detail.numberOfSamples) / 2;
        for (int i = 0; i < detail.numberOfSamples && (i + detail.searchIndex) < searchSamplesSize; i++) {
            double distanceFromMidpoint = getPositiveDelta(midpoint, static_cast<double>(i));
            double weightForPosition = 1 - distanceFromMidpoint / midpoint;
            double searchSampleValue(searchSamples[i + detail.searchIndex]);
            SampleMergingDetails& newSampleDetail(samplesMergingDetails[i + detail.replicationIndex]);
            newSampleDetail.isChanged = true;
            newSampleDetail.totalValue += searchSampleValue * weightForPosition;
            newSampleDetail.weight += weightForPosition;
        }
    }
}

void NewSamplesBuilder::saveToNewSamples(
    Samples& newSamples, SamplesMergingDetails const& samplesMergingDetails, bool const alwaysPutNewValue) {
    int sampleSize = min(samplesMergingDetails.size(), newSamples.size());
    for (int i = 0; i < sampleSize; i++) {
        SampleMergingDetails const& mergingDetails(samplesMergingDetails.at(i));
        if (mergingDetails.isChanged) {
            double mergedValue(mergingDetails.totalValue / mergingDetails.weight);
            double oldSample(m_oldSamples[i]);
            double& currentSample(newSamples[i]);
            double newValue = mergedValue * 0.5 + oldSample * 0.5;
            if (alwaysPutNewValue ||
                getPositiveDelta(newValue, oldSample) < getPositiveDelta(currentSample, oldSample)) {
                currentSample = newValue;
            }
        }
    }
}

}  // namespace AprgAudio

}  // namespace alba
