#include "AlbaFileReader.hpp"

#include <String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

namespace alba
{

AlbaFileReader::AlbaFileReader(ifstream& stream) : m_stream(stream){}

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
    m_stream.read(m_characterBuffer, numberOfCharacters);
    numberOfCharacters = m_stream.gcount();
    return (char*)m_characterBuffer;
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

template <typename NumberType, unsigned int numberOfBytesToRead>
NumberType AlbaFileReader::getData()
{
    NumberType result=0;
    m_stream.read(m_characterBuffer, numberOfBytesToRead);
    unsigned int numberOfCharacters = m_stream.gcount();
    result = accumulate(m_characterBuffer, m_characterBuffer+numberOfCharacters, 0, [&](NumberType partialSum, NumberType newValue)
    {
        partialSum <<= 8;
        partialSum |= (0xFF & newValue);
        return partialSum;
    });
    return result;
}

template unsigned int AlbaFileReader::getTwoByteData<unsigned int>();
template unsigned int AlbaFileReader::getFourByteData<unsigned int>();
template unsigned int AlbaFileReader::getData<unsigned int, 2>();
template unsigned int AlbaFileReader::getData<unsigned int, 4>();

string AlbaFileReader::getLineAndIgnoreWhiteSpaces()
{
    while(!m_stream.eof())
    {
        m_stream.clear();
        m_stream.getline(m_characterBuffer, m_bufferSize);
        string result(m_characterBuffer);
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
        m_stream.getline (m_characterBuffer, m_bufferSize);
        return string(m_characterBuffer);
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

void AlbaFileReader::moveLocation(unsigned long long location) const
{
    m_stream.seekg(location, m_stream.beg);
}

void AlbaFileReader::setMaxBufferSize(unsigned int bufferSize)
{
    if(bufferSize+1 < MAX_BUFFER_SIZE && bufferSize > 0)
    {
        m_bufferSize = bufferSize+1;
    }
}

}//namespace alba
