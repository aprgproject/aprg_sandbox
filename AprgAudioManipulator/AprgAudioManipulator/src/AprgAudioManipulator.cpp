#include "AprgAudioManipulator.hpp"

#include <String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

AprgAudioManipulator::AprgAudioManipulator(std::string const& audioFilePath)
    : m_filePathHandler(audioFilePath)
    , m_audio()
{
    m_audio.load(m_filePathHandler.getFullPath());
}

AprgAudioManipulator::Audio const& AprgAudioManipulator::getAudio() const
{
    return m_audio;
}

AprgAudioManipulator::Audio & AprgAudioManipulator::getAudioReference()
{
    return m_audio;
}

void AprgAudioManipulator::multiplySamplesWithValue(double const multiplier)
{
    for(unsigned int i=0; i<m_audio.getNumChannels(); i++)
    {
        multiplySamplesAtChannelWithValue(i, multiplier);
    }
}

void AprgAudioManipulator::multiplySamplesAtChannelWithValue(
        unsigned int const channelIndex,
        double const multiplier)
{
    double* sampleAtChannel1(m_audio.getSamplesAtChannel(channelIndex));
    for(unsigned int i=0; i<m_audio.getNumSamplesPerChannel(); i++)
    {
        sampleAtChannel1[i]*=multiplier;
    }
}

void AprgAudioManipulator::saveAudioIntoCurrentFile()
{
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getFullPath());
}

void AprgAudioManipulator::saveAudioIntoFileInTheSameDirectory(
        string const& filename)
{
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getDirectory()+filename);
}

void AprgAudioManipulator::saveAudioIntoFileWithFullFilePath(
        string const& newFilePath)
{
    AlbaLocalPathHandler newFilePathHandler(newFilePath);
    string extension(getStringWithCapitalLetters(newFilePathHandler.getExtension()));
    if(extension=="WAV")
    {
        m_audio.save(newFilePathHandler.getFullPath(), AprgAudioFormat::Wave);
    }
    else if(extension=="AIFF")
    {
        m_audio.save(newFilePathHandler.getFullPath(), AprgAudioFormat::Aiff);
    }
}

}
