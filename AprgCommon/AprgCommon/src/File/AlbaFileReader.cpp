#include "AlbaFileReader.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>
#include <numeric>
#include <string>

using namespace std;

namespace alba
{

AlbaFileReader::AlbaFileReader(ifstream& stream)
    : m_characterBuffer()
    , m_stream(stream)
{
    setMaxBufferSize(INITIAL_MAX_BUFFER_SIZE);
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
    m_stream.read(getCharacterBufferPointer(), numberOfCharacters);
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
    result = accumulate(m_characterBuffer.cbegin(), m_characterBuffer.cbegin()+numberOfCharacters, static_cast<NumberType>(0u), [&](NumberType partialSum, NumberType newValue)
    {
        partialSum = static_cast<NumberType>(partialSum << 8);
        partialSum |= (0xFF & newValue);
        return partialSum;
    });
    return result;
}

template unsigned int AlbaFileReader::getTwoByteData<unsigned int>();
template unsigned int AlbaFileReader::getFourByteData<unsigned int>();
template unsigned long long AlbaFileReader::getEightByteData<unsigned long long>();
template unsigned int AlbaFileReader::getTwoByteSwappedData<unsigned int>();
template unsigned int AlbaFileReader::getFourByteSwappedData<unsigned int>();
template unsigned long long AlbaFileReader::getEightByteSwappedData<unsigned long long>();
template unsigned int AlbaFileReader::getData<unsigned int, 2>();
template unsigned int AlbaFileReader::getData<unsigned int, 4>();
template unsigned int AlbaFileReader::getData<unsigned int, 8>();

void AlbaFileReader::saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, unsigned int numberOfBytesToRead)
{
    char* writer = static_cast<char*>(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(numberOfBytesToRead));
    m_stream.read(writer, numberOfBytesToRead);
}

string AlbaFileReader::getLineAndIgnoreWhiteSpaces()
{
    while(!m_stream.eof())
    {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<unsigned int>(m_characterBuffer.size()));
        string result(getCharacterBufferPointer());
        result = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(result);
        if(""!=result){ return result; }
    }
    return "";
}

string AlbaFileReader::getLine()
{
    if(!m_stream.eof())
    {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<unsigned int>(m_characterBuffer.size()));
        return string(getCharacterBufferPointer());
    }
    return "";
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
