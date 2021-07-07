#pragma once

#include <AprgAudio.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

namespace alba
{

class AprgAudioManipulator
{
public:
    AprgAudioManipulator(std::string const& audioFilePath);

private:
    AlbaLocalPathHandler m_filePathHandler;
    AprgAudio<double> m_audio;
};

}
