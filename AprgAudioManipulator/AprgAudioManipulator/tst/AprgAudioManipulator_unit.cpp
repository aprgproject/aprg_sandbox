#include <AprgAudioManipulator.hpp>

#include <gtest/gtest.h>

using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\SampleAudioFiles\)"
namespace alba
{
TEST(SampleTest, SampleTest1)
{
    AlbaLocalPathHandler audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler audioFilePathHandler(audioDirectoryPathHandler.getDirectory()+"AChannel_AOpeningSong_001.wav");
    AprgAudioManipulator audioManipulator(audioFilePathHandler.getFullPath());

    audioManipulator.multiplySamplesWithValue(0.30);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");

}

}

