#pragma once

#include <AudioManipulator/CommonTypes.hpp>

#include <map>

namespace alba {

namespace AprgAudio {

class NewSamplesBuilder {
public:
    struct SampleMergingDetails {
        SampleMergingDetails();
        bool isChanged;
        double totalValue;
        double weight;
    };
    using SamplesMergingDetails = std::map<int, SampleMergingDetails>;

    NewSamplesBuilder(Samples const& oldSamples);
    void putSamplesBasedOnSearchResultAndSamples(
        Samples& samplesToChange, SearchResultsDetails const& details, Samples const& searchSamples,
        bool const alwaysPutNewValue);
private:
    void retrieveSampleMergingDetails(
        SamplesMergingDetails& samplesMergingDetails, SearchResultsDetails const& details,
        Samples const& searchSamples);
    void saveToNewSamples(
        Samples& newSamples, SamplesMergingDetails const& samplesMergingDetails, bool const alwaysPutNewValue);

    Samples const& m_oldSamples;
};

}  // namespace AprgAudio

}  // namespace alba
