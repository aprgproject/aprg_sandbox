#include "AprgAudioManipulator.hpp"

#include <String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace AprgAudio
{

AprgAudioManipulator::AprgAudioManipulator(std::string const& audioFilePath)
    : m_filePathHandler(audioFilePath)
    , m_audio(){
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

void AprgAudioManipulator::addSamplesWithValue(double const value)
{
    for(unsigned int i=0; i < m_audio.getNumChannels(); i++)
    {
        addSamplesAtChannelWithValue(i, value);
    }
}

void AprgAudioManipulator::addSamplesAtChannelWithValue(
        unsigned int const channelIndex,
        double const value)
{
    double* samplePointerAtChannel(m_audio.getSamplePointerAtChannel(channelIndex));
    for(unsigned int i=0; i<m_audio.getNumSamplesPerChannel(); i++)
    {
        samplePointerAtChannel[i]+=value;
    }
}

void AprgAudioManipulator::multiplySamplesWithValue(double const value)
{
    for(unsigned int i=0; i < m_audio.getNumChannels(); i++)
    {
        multiplySamplesAtChannelWithValue(i, value);
    }
}

void AprgAudioManipulator::multiplySamplesAtChannelWithValue(
        unsigned int const channelIndex,
        double const value)
{
    double* samplePointerAtChannel(m_audio.getSamplePointerAtChannel(channelIndex));
    for(unsigned int i=0; i<m_audio.getNumSamplesPerChannel(); i++)
    {
        samplePointerAtChannel[i]*=value;
    }
}
void AprgAudioManipulator::saveAudioIntoCurrentFile()
{
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getFullPath());}

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

}