#pragma once

#include <Audio/AprgAudio.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

namespace alba
{

class AprgAudioManipulator
{
public:
    using Audio=AprgAudio<double>;
    AprgAudioManipulator(std::string const& audioFilePath);

    Audio const& getAudio() const;
    Audio & getAudioReference();

    void multiplySamplesWithValue(double const multiplier);
    void multiplySamplesAtChannelWithValue(
            unsigned int const channelIndex,
            double const multiplier);

    void saveAudioIntoCurrentFile();
    void saveAudioIntoFileInTheSameDirectory(
            std::string const& filename);
    void saveAudioIntoFileWithFullFilePath(
            std::string const& newFilePath);

private:
    AlbaLocalPathHandler m_filePathHandler;
    Audio m_audio;
};

}
