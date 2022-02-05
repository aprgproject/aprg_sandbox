#include "AlbaFileReader.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>
#include <fstream>
#include <numeric>
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
template <typename NumberType>
NumberType AlbaFileReader::getTwoByteData()
{
    return getData<NumberType, 2>();
}

template <typename NumberType>
NumberType AlbaFileReader::getFourByteData()
{
    return getData<NumberType, 4>();
}

template <typename NumberType>
NumberType AlbaFileReader::getEightByteData()
{
    return getData<NumberType, 8>();
}

template <typename NumberType>
NumberType AlbaFileReader::getTwoByteSwappedData()
{
    return AlbaBitManipulation<NumberType>::swapForTwoBytes(getData<NumberType, 2>());
}

template <typename NumberType>
NumberType AlbaFileReader::getFourByteSwappedData()
{
    return AlbaBitManipulation<NumberType>::swapForFourBytes(getData<NumberType, 4>());
}

template <typename NumberType>
NumberType AlbaFileReader::getEightByteSwappedData()
{
    return AlbaBitManipulation<NumberType>::swapForEightBytes(getData<NumberType, 8>());
}


template <typename NumberType, unsigned int numberOfBytesToRead>
NumberType AlbaFileReader::getData()
{
    NumberType result(0);
    m_stream.read(getCharacterBufferPointer(), numberOfBytesToRead);
    unsigned int numberOfCharacters = static_cast<unsigned int>(m_stream.gcount());
    result = accumulate(m_characterBuffer.cbegin(), m_characterBuffer.cbegin()+static_cast<int>(numberOfCharacters),
                        static_cast<NumberType>(0U),
                        [&](NumberType partialSum, NumberType newValue)
    {
        partialSum = static_cast<NumberType>(partialSum << 8);
        partialSum |= (0xFF & newValue);
        return partialSum;
    });
    return result;
}

template uint16_t AlbaFileReader::getTwoByteData<uint16_t>();

template uint32_t AlbaFileReader::getFourByteData<uint32_t>();

template uint64_t AlbaFileReader::getEightByteData<uint64_t>();

template uint16_t AlbaFileReader::getTwoByteSwappedData<uint16_t>();

template uint32_t AlbaFileReader::getFourByteSwappedData<uint32_t>();

template uint64_t AlbaFileReader::getEightByteSwappedData<uint64_t>();

template uint16_t AlbaFileReader::getData<uint16_t, 2>();
template uint32_t AlbaFileReader::getData<uint32_t, 4>();
template uint64_t AlbaFileReader::getData<uint64_t, 8>();

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
    m_stream.seekg(0, m_stream.end);
    double fileSize = m_stream.tellg();
    moveToTheBeginning();
    return fileSize;
}

void AlbaFileReader::moveToTheBeginning() const
{
    m_stream.seekg(0, m_stream.beg);
}

void AlbaFileReader::moveLocation(unsigned long long const location) const
{
    m_stream.seekg(static_cast<long>(location), m_stream.beg);
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
