#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/NewSamplesBuilder.hpp>
#include <AudioManipulator/Utilities.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\FilesForTests\SampleAudioFiles\)"

namespace alba {

namespace AprgAudio {

TEST(UtilitiesTest, RetrieveDeltasWorks) {
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "AChannel_AOpeningSong_001.wav");
    AudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    AudioInDouble const& audio(audioManipulator.getAudio());
    Samples deltaSamplesInChannel0;
    retrieveDeltas(deltaSamplesInChannel0, audio.getSamplesAtChannel(0), 10000);
}

TEST(UtilitiesTest, DISABLED_SearchForBestSampleIndexesWorksWithReplacingSamples) {
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "John Mayer-Neon.wav");
    AlbaLocalPathHandler audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "AChannel_AOpeningSong_001.wav");  // AChannel_AOpeningSong_001
    AudioManipulator audioToReplicateManipulator(audioToReplicateFilePathHandler.getFullPath());
    AudioManipulator audioToSearchManipulator(audioToSearchFilePathHandler.getFullPath());

    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());

    SearchResultsDetails searchResults;
    Samples const& samplesToReplicate(audioToReplicate.getSamplesAtChannel(0));
    Samples const& samplesToSearch(audioToSearch.getSamplesAtChannel(0));
    searchForBestSampleIndexes(searchResults, 24000, 48000, 100, samplesToReplicate, samplesToSearch);

    AudioInDouble& audioToChange(audioToReplicateManipulator.getAudioReference());
    Samples& samplesToChange(audioToChange.getSamplesReferenceAtChannel(0));

    NewSamplesBuilder newSamplesBuilder(samplesToChange);
    newSamplesBuilder.putSamplesBasedOnSearchResultAndSamples(samplesToChange, searchResults, samplesToSearch, true);

    audioToReplicateManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateSamplesWorks) {
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "John Mayer-Neon.wav");
    AlbaLocalPathHandler audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler audioToChangeFilePathHandler(audioDirectoryPathHandler.getDirectory() + "John Mayer-Neon.wav");
    AudioManipulator audioToReplicateManipulator(audioToReplicateFilePathHandler.getFullPath());
    AudioManipulator audioToSearchManipulator(audioToSearchFilePathHandler.getFullPath());
    AudioManipulator audioToChangeManipulator(audioToChangeFilePathHandler.getFullPath());
    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());
    AudioInDouble& audioToChange(audioToChangeManipulator.getAudioReference());

    int numberOfChannels =
        max(max(audioToReplicate.getNumChannels(), audioToSearch.getNumChannels()), audioToChange.getNumChannels());
    for (int i = 0; i < numberOfChannels; i++) {
        searchAndTryToReplicateSamples(
            audioToChange, audioToReplicate, audioToSearch, clampHigherBound(i, audioToChange.getNumChannels()),
            clampHigherBound(i, audioToReplicate.getNumChannels()), clampHigherBound(i, audioToSearch.getNumChannels()),
            true);
    }
    audioToChangeManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateWorks) {
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "John Mayer-Neon.wav");
    AlbaLocalPathHandler audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler audioToChangeFilePathHandler(audioDirectoryPathHandler.getDirectory() + "output.wav");
    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getFullPath(), audioToReplicateFilePathHandler.getFullPath(),
        audioToSearchFilePathHandler.getFullPath(), true);
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateTwoFilesWorks) {
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "John Mayer-Neon.wav");
    AlbaLocalPathHandler audioToSearch1FilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler audioToSearch2FilePathHandler(
        audioDirectoryPathHandler.getDirectory() + "FullMetalAlchemistBrotherhood_AOpeningSong_003.wav");
    AlbaLocalPathHandler audioToChangeFilePathHandler(audioDirectoryPathHandler.getDirectory() + "output.wav");

    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getFullPath(), audioToReplicateFilePathHandler.getFullPath(),
        audioToSearch1FilePathHandler.getFullPath(), true);
    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getFullPath(), audioToReplicateFilePathHandler.getFullPath(),
        audioToSearch2FilePathHandler.getFullPath(), false);
}

}  // namespace AprgAudio

}  // namespace alba
