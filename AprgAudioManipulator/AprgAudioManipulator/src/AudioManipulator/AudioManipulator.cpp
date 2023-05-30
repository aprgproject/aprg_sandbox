#include "AudioManipulator.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace AprgAudio {

AudioManipulator::AudioManipulator(std::string const& audioFilePath) : m_filePathHandler(audioFilePath), m_audio() {
    m_audio.load(m_filePathHandler.getFullPath());
}

AudioInDouble const& AudioManipulator::getAudio() const { return m_audio; }

AudioInDouble& AudioManipulator::getAudioReference() { return m_audio; }

void AudioManipulator::addSamplesWithValue(double const value) {
    for (int i = 0; i < m_audio.getNumChannels(); i++) {
        addSamplesAtChannelWithValue(i, value);
    }
}

void AudioManipulator::addSamplesAtChannelWithValue(int const channelIndex, double const value) {
    Samples& samplesAtChannel(m_audio.getSamplesReferenceAtChannel(channelIndex));
    for (double& sampleAtChannel : samplesAtChannel) {
        sampleAtChannel += value;
    }
}

void AudioManipulator::multiplySamplesWithValue(double const value) {
    for (int i = 0; i < m_audio.getNumChannels(); i++) {
        multiplySamplesAtChannelWithValue(i, value);
    }
}

void AudioManipulator::multiplySamplesAtChannelWithValue(int const channelIndex, double const value) {
    Samples& samplesAtChannel(m_audio.getSamplesReferenceAtChannel(channelIndex));
    for (double& sampleAtChannel : samplesAtChannel) {
        sampleAtChannel *= value;
    }
}

void AudioManipulator::saveAudioIntoCurrentFile() {
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getFullPath());
}

void AudioManipulator::saveAudioIntoFileInTheSameDirectory(string const& filename) {
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getDirectory() + filename);
}

void AudioManipulator::saveAudioIntoFileWithFullFilePath(string const& newFilePath) {
    AlbaLocalPathHandler newFilePathHandler(newFilePath);
    string extension(getStringWithCapitalLetters(newFilePathHandler.getExtension()));
    if (extension == "WAV") {
        m_audio.save(newFilePathHandler.getFullPath(), AudioFormat::Wave);
    } else if (extension == "AIFF") {
        m_audio.save(newFilePathHandler.getFullPath(), AudioFormat::Aiff);
    }
}

}  // namespace AprgAudio

}  // namespace alba
