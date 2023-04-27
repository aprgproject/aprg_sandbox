#include "AlbaFileReader.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaFileReader::AlbaFileReader(ifstream& stream) : m_characterBuffer(), m_stream(stream) {
    setMaxBufferSize(INITIAL_MAX_BUFFER_SIZE);
}

AlbaFileReader::AlbaFileReader(ifstream& stream, size_t const size) : m_characterBuffer(), m_stream(stream) {
    setMaxBufferSize(size);
}

bool AlbaFileReader::isNotFinished() {
    // return (!m_stream.eof()) && (m_stream.peek()!=EOF);
    return !m_stream.eof();
}

char AlbaFileReader::getCharacter() {
    char tempChar(0);
    m_stream.get(tempChar);
    return tempChar;
}

char* AlbaFileReader::getCharacters(size_t& numberOfCharacters) {
    size_t bufferSize = m_characterBuffer.size();
    if (bufferSize <= numberOfCharacters) {
        numberOfCharacters = bufferSize - 1;
    }
    m_stream.read(getCharacterBufferPointer(), static_cast<streamsize>(numberOfCharacters));
    numberOfCharacters = static_cast<size_t>(m_stream.gcount());
    m_characterBuffer[numberOfCharacters] = '\0';
    return getCharacterBufferPointer();
}

void AlbaFileReader::saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, size_t numberOfBytesToRead) {
    char* writer =
        static_cast<char*>(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(numberOfBytesToRead));
    m_stream.read(writer, static_cast<streamsize>(numberOfBytesToRead));
}

string AlbaFileReader::getLineAndIgnoreWhiteSpaces() {
    string result;
    while (!m_stream.eof()) {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        string stringFromBuffer(getCharacterBufferPointer());
        result = getStringWithoutStartingAndTrailingWhiteSpace(stringFromBuffer);
        if (!result.empty()) {
            break;
        }
    }
    return result;
}

string AlbaFileReader::getLine() {
    string result;
    if (!m_stream.eof()) {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        result = string(getCharacterBufferPointer());
    }
    return result;
}

size_t AlbaFileReader::getCurrentLocation() const { return m_stream.tellg(); }

size_t AlbaFileReader::getFileSize() const {
    m_stream.seekg(0, std::ifstream::end);
    size_t fileSize = m_stream.tellg();
    moveToTheBeginning();
    return fileSize;
}

void AlbaFileReader::moveToTheBeginning() const { m_stream.seekg(0, std::ifstream::beg); }

void AlbaFileReader::moveLocation(size_t const location) const { m_stream.seekg(location, std::ifstream::beg); }

void AlbaFileReader::setMaxBufferSize(size_t const bufferSize) {
    // This is ensuring that buffer always contains one.
    // 1) This is for "front()".
    // 2) This is for null terminator.
    m_characterBuffer.resize(bufferSize + 1);
}

size_t AlbaFileReader::getMaxBufferSize() const {
    size_t bufferSize = static_cast<size_t>(m_characterBuffer.size());
    if (bufferSize > 0) {
        bufferSize--;
    }
    return bufferSize;
}

char* AlbaFileReader::getCharacterBufferPointer() { return &(m_characterBuffer.front()); }

}  // namespace alba
