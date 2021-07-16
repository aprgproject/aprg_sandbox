#include <Audio/AprgAudioManipulator.hpp>
#include <Audio/Utilities.hpp>

#include <gtest/gtest.h>


#include <Debug/AlbaDebug.hpp>

using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\SampleAudioFiles\)"
namespace alba
{

namespace AprgAudio
{

TEST(AprgAudioManipulatorTest, DISABLED_AddSamplesWithValueWorks)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");
    AprgAudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    audioManipulator.addSamplesWithValue(100);
    ALBA_PRINT1(audioManipulator.getAudio().getNumSamplesPerChannel());
    ALBA_PRINT1(audioManipulator.getAudio().getSampleRate());

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(AprgAudioManipulatorTest, DISABLED_MultiplySamplesWithValueWorks)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");    AprgAudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    audioManipulator.multiplySamplesWithValue(0.30);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(AprgAudioManipulatorTest, RetrieveDeltas)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");
    AprgAudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    AprgAudioManipulator::Audio const& audio(audioManipulator.getAudio());
    Samples deltaSamples;
    retrieveDeltas(deltaSamples, audio.getSamplePointerAtChannel(0), audio.getNumSamplesPerChannel());

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

}

}