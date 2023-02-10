#include "AlbaFileReader.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

AlbaFileReader::AlbaFileReader(ifstream& stream)
    : m_characterBuffer()
    , m_stream(stream)
{
    setMaxBufferSize(INITIAL_MAX_BUFFER_SIZE);
}

AlbaFileReader::AlbaFileReader(ifstream& stream, unsigned int const size)
    : m_characterBuffer()
    , m_stream(stream)
{
    setMaxBufferSize(size);
}

bool AlbaFileReader::isNotFinished()
{
    //return (!m_stream.eof()) && (m_stream.peek()!=EOF);
    return !m_stream.eof();
}

char AlbaFileReader::getCharacter()
{
    char tempChar(0);
    m_stream.get(tempChar);
    return tempChar;
}

char* AlbaFileReader::getCharacters(unsigned int& numberOfCharacters)
{
    unsigned int bufferSize = static_cast<unsigned int>(m_characterBuffer.size());
    if(bufferSize<=numberOfCharacters)
    {
        numberOfCharacters=bufferSize-1;
    }
    m_stream.read(getCharacterBufferPointer(), static_cast<streamsize>(numberOfCharacters));
    numberOfCharacters = static_cast<unsigned int>(m_stream.gcount());
    m_characterBuffer[numberOfCharacters] = '\0';
    return getCharacterBufferPointer();
}

void AlbaFileReader::saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, unsigned int numberOfBytesToRead)
{
    char* writer = static_cast<char*>(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(numberOfBytesToRead));
    m_stream.read(writer, static_cast<streamsize>(numberOfBytesToRead));
}

string AlbaFileReader::getLineAndIgnoreWhiteSpaces()
{
    string result;
    while(!m_stream.eof())
    {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        string stringFromBuffer(getCharacterBufferPointer());
        result = getStringWithoutStartingAndTrailingWhiteSpace(stringFromBuffer);
        if(!result.empty())
        {
            break;
        }
    }
    return result;
}

string AlbaFileReader::getLine()
{
    string result;
    if(!m_stream.eof())
    {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        result = string(getCharacterBufferPointer());
    }
    return result;
}

double AlbaFileReader::getCurrentLocation() const
{
    double location = m_stream.tellg();
    return location;
}

double AlbaFileReader::getFileSize() const
{
    m_stream.seekg(0, std::ifstream::end);
    double fileSize = m_stream.tellg();
    moveToTheBeginning();
    return fileSize;
}

void AlbaFileReader::moveToTheBeginning() const
{
    m_stream.seekg(0, std::ifstream::beg);
}

void AlbaFileReader::moveLocation(unsigned long long const location) const
{
    m_stream.seekg(static_cast<long>(location), std::ifstream::beg);
}

void AlbaFileReader::setMaxBufferSize(unsigned int const bufferSize)
{
    //This is ensuring that buffer always contains one.
    //1) This is for "front()".
    //2) This is for null terminator.
    m_characterBuffer.resize(bufferSize+1);
}

unsigned int AlbaFileReader::getMaxBufferSize() const
{
    unsigned int bufferSize = static_cast<unsigned int>(m_characterBuffer.size());
    if(bufferSize>0)
    {
        bufferSize--;
    }
    return bufferSize;
}

char* AlbaFileReader::getCharacterBufferPointer()
{
    return &(m_characterBuffer.front());
}

}//namespace alba
