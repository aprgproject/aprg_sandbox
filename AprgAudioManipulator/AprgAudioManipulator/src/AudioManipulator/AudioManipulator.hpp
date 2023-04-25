#pragma once

#include <Audio/Audio.hpp>
#include <AudioManipulator/CommonTypes.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

namespace alba {

namespace AprgAudio {

class AudioManipulator {
public:
    AudioManipulator(std::string const& audioFilePath);

    AudioInDouble const& getAudio() const;
    AudioInDouble& getAudioReference();

    void addSamplesWithValue(double const value);
    void addSamplesAtChannelWithValue(unsigned int const channelIndex, double const value);
    void multiplySamplesWithValue(double const value);
    void multiplySamplesAtChannelWithValue(unsigned int const channelIndex, double const value);

    void saveAudioIntoCurrentFile();
    void saveAudioIntoFileInTheSameDirectory(std::string const& filename);
    void saveAudioIntoFileWithFullFilePath(std::string const& newFilePath);

private:
    AlbaLocalPathHandler m_filePathHandler;
    AudioInDouble m_audio;
};

}  // namespace AprgAudio

}  // namespace alba
