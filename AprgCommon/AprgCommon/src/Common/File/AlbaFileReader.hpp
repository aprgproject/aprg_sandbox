#pragma once

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <fstream>
#include <numeric>
#include <string>
#include <vector>
namespace alba
{
class AlbaFileReader
{
public:
    explicit AlbaFileReader(std::ifstream& stream);
    explicit AlbaFileReader(std::ifstream& stream, unsigned int const size);
    bool isNotFinished();
    char getCharacter();
    char* getCharacters(unsigned int& numberOfCharacters);
    template <typename NumberType> NumberType getOneByteData();
    template <typename NumberType> NumberType getTwoByteData();
    template <typename NumberType> NumberType getFourByteData();
    template <typename NumberType> NumberType getEightByteData();    template <typename NumberType> NumberType getTwoByteSwappedData();
    template <typename NumberType> NumberType getFourByteSwappedData();
    template <typename NumberType> NumberType getEightByteSwappedData();
    template <typename NumberType, unsigned int numberOfBytesToRead> NumberType getData();    void saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, unsigned int numberOfBytesToRead);
    std::string getLineAndIgnoreWhiteSpaces();
    std::string getLine();    double getCurrentLocation() const;
    double getFileSize() const;
    void moveToTheBeginning() const;
    void moveLocation(unsigned long long const location) const;    void setMaxBufferSize(unsigned int const bufferSize);
    unsigned int getMaxBufferSize() const;
private:
    char* getCharacterBufferPointer();
    static constexpr unsigned int INITIAL_MAX_BUFFER_SIZE = 10000;
    std::vector<char> m_characterBuffer;
    std::ifstream& m_stream;
};

template <typename NumberType>
NumberType AlbaFileReader::getOneByteData()
{
    return getData<NumberType, 1>();
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
    result = std::accumulate(m_characterBuffer.cbegin(), m_characterBuffer.cbegin()+numberOfCharacters,
                        static_cast<NumberType>(0U),
                        [&](NumberType partialSum, NumberType newValue)
    {
        partialSum = static_cast<NumberType>(partialSum << 8);
        partialSum |= (0xFF & newValue);
        return partialSum;
    });
    return result;
}

}//namespace alba