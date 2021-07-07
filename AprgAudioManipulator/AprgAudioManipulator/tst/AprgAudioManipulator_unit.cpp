#include <AprgAudioManipulator.hpp>

#include <gtest/gtest.h>

using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\SampleAudioFiles\)"

namespace alba
{

TEST(SampleTest, SampleTest1)
{
    AlbaLocalPathHandler audioDirectory(SAMPLE_AUDIO_FILES_DIRECTORY);
    AprgAudioManipulator audioManipulator(audioDirectory.getDirectory()+"AChannel_AOpeningSong_001.wav");
}

}

