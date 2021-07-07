#include "AprgAudioManipulator.hpp"

namespace alba
{

AprgAudioManipulator::AprgAudioManipulator(std::string const& audioFilePath)
    : m_filePathHandler(audioFilePath)
    , m_audio()
{
    m_audio.load(m_filePathHandler.getFullPath());
}

}
