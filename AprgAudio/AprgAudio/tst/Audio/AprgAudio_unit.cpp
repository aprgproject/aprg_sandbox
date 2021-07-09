#include <Audio/AprgAudio.hpp>

#include <Audio/ExpectedValues/aiff_stereo_8bit_44100.hpp>
#include <Audio/ExpectedValues/aiff_stereo_16bit_44100.hpp>
#include <Audio/ExpectedValues/aiff_stereo_24bit_44100.hpp>
#include <Audio/ExpectedValues/aiff_stereo_8bit_48000.hpp>
#include <Audio/ExpectedValues/aiff_stereo_16bit_48000.hpp>
#include <Audio/ExpectedValues/aiff_stereo_24bit_48000.hpp>
#include <Audio/ExpectedValues/wav_mono_16bit_44100.hpp>
#include <Audio/ExpectedValues/wav_mono_16bit_48000.hpp>
#include <Audio/ExpectedValues/wav_stereo_8bit_44100.hpp>
#include <Audio/ExpectedValues/wav_stereo_16bit_44100.hpp>
#include <Audio/ExpectedValues/wav_stereo_24bit_44100.hpp>
#include <Audio/ExpectedValues/wav_stereo_8bit_48000.hpp>
#include <Audio/ExpectedValues/wav_stereo_16bit_48000.hpp>
#include <Audio/ExpectedValues/wav_stereo_24bit_48000.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(AiffLoadingTests, Stereo_8bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_8bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_8bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_8bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_8bit_44100::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_8bit_44100::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_8bit_44100::testBuffer[k][i]));
        }    }
}

TEST(AiffLoadingTests, Stereo_16bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_16bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_16bit_44100::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_16bit_44100::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_16bit_44100::testBuffer[k][i]));
        }    }
}

TEST(AiffLoadingTests, Stereo_24bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_24bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_24bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_24bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_24bit_44100::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_24bit_44100::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_24bit_44100::testBuffer[k][i]));
        }    }
}

TEST(AiffLoadingTests, Stereo_8bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_8bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_8bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_8bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_8bit_48000::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_8bit_48000::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_8bit_48000::testBuffer[k][i]));
        }    }
}

TEST(AiffLoadingTests, Stereo_16bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_16bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_16bit_48000::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_16bit_48000::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_16bit_48000::testBuffer[k][i]));
        }    }
}

TEST(AiffLoadingTests, Stereo_24bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\aiff_stereo_24bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_24bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_24bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), aiff_stereo_24bit_48000::numChannels);

    for (unsigned int i = 0; i < aiff_stereo_24bit_48000::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], aiff_stereo_24bit_48000::testBuffer[k][i]));
        }    }
}

TEST(WritingTest, WriteFromCopiedSampleBuffer)
{
    AprgAudio<float> audioFile1, audioFile2;

    bool isLoadingSuccessful = audioFile1.load (APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_16bit_44100.wav)");
    ASSERT_TRUE(isLoadingSuccessful);

    audioFile2.setAudioBuffer (audioFile1.samples);    audioFile2.save("audio-write-tests/copied_audio_file.aif", AprgAudioFormat::Aiff);
}

TEST(WavLoadingTests, Stereo_8bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_8bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_8bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_8bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_8bit_44100::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_8bit_44100::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_8bit_44100::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Stereo_16bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_16bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_16bit_44100::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_16bit_44100::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_16bit_44100::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Stereo_24bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_24bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_24bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_24bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_24bit_44100::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_24bit_44100::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_24bit_44100::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Mono_16bit_44100)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_mono_16bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_mono_16bit_44100::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_mono_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_mono_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_mono_16bit_44100::numChannels);

    for (unsigned int i = 0; i < wav_mono_16bit_44100::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_mono_16bit_44100::testBuffer[i]));
        }    }
}

TEST(WavLoadingTests, Stereo_8bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_8bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_8bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_8bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_8bit_48000::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_8bit_48000::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_8bit_48000::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Stereo_16bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_16bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_16bit_48000::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_16bit_48000::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_16bit_48000::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Stereo_24bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_stereo_24bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_24bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_24bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_stereo_24bit_48000::testBuffer.size());

    for (unsigned int i = 0; i < wav_stereo_24bit_48000::testBuffer[0].size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_stereo_24bit_48000::testBuffer[k][i]));
        }    }
}

TEST(WavLoadingTests, Mono_16bit_48000)
{
    AprgAudio<double> audioFile;
    bool isLoadingSuccessful = audioFile.load(APRG_AUDIO_DIR R"(\tst\Audio\ActualAudioFiles\wav_mono_16bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumSamplesPerChannel(), wav_mono_16bit_48000::numSamplesPerChannel);    EXPECT_EQ(audioFile.getBitDepth(), wav_mono_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_mono_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumChannels(), wav_mono_16bit_48000::numChannels);

    for (unsigned int i = 0; i < wav_mono_16bit_48000::testBuffer.size(); i++)
    {
        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
        {
            EXPECT_TRUE(isAlmostEqual(audioFile.samples[k][i], wav_mono_16bit_48000::testBuffer[i]));
        }    }
}

bool writeTest(int numChannels, int sampleRate, int bitDepth, AprgAudioFormat format)
{
    float sampleRateAsFloat = (float) sampleRate;

    AprgAudio<float> audioFile;

    audioFile.setAudioBufferSize (numChannels, sampleRate * 4);

    for (unsigned int i = 0; i < static_cast<unsigned int>(audioFile.getNumSamplesPerChannel()); i++)
    {
        float sample = sinf (2. * getPi() * ((float) i / sampleRateAsFloat) * 440.) ;

        for (unsigned int k = 0; k < static_cast<unsigned int>(audioFile.getNumChannels()); k++)
            audioFile.samples[k][i] = sample * 0.5;
    }
    audioFile.setSampleRate (sampleRate);
    audioFile.setBitDepth (bitDepth);

    std::string numChannelsAsString = numChannels == 1 ? "mono" : "stereo";
    std::string bitDepthAsString = std::to_string (bitDepth);
    std::string sampleRateAsString = std::to_string (sampleRate);

    if (format == AprgAudioFormat::Wave)
    {
        return audioFile.save (APRG_AUDIO_DIR R"(\tst\Audio\WrittenAudioFiles\)" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".wav");
    }

    else if (format == AprgAudioFormat::Aiff)
    {
        return audioFile.save (APRG_AUDIO_DIR R"(\tst\Audio\WrittenAudioFiles\)" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".aif");
    }

    return false;}


TEST(WritingTest, WriteSineToneToManyFormats)
{
    std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
    std::vector<int> bitDepths = {8, 16, 24};
    std::vector<int> numChannels = {1, 2};
    std::vector<AprgAudioFormat> audioFormats = {AprgAudioFormat::Wave, AprgAudioFormat::Aiff};

    for (auto& sampleRate : sampleRates)
    {
        for (auto& bitDepth : bitDepths)
        {
            for (auto& channels : numChannels)
            {
                for (auto& format : audioFormats)
                {
                    EXPECT_TRUE(writeTest(channels, sampleRate, bitDepth, format));
                }
            }
        }
    }
}

}
