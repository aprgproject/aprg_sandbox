#include <AudioManipulator/AudioManipulator.hpp>

#include <gtest/gtest.h>

using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\SampleAudioFiles\)"

namespace alba
{

namespace AprgAudio
{

TEST(AudioManipulatorTest, DISABLED_AddSamplesWithValueWorks)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");
    AudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    audioManipulator.addSamplesWithValue(100);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(AudioManipulatorTest, DISABLED_MultiplySamplesWithValueWorks)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");
    AudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    audioManipulator.multiplySamplesWithValue(0.30);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}



}

}
