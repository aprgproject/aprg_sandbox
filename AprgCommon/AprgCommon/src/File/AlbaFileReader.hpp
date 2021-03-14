#pragma once

#include <Memory/AlbaMemoryBuffer.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace alba
{

class AlbaFileReader
{
public:
    explicit AlbaFileReader(std::ifstream& stream);
    bool isNotFinished();
    char getCharacter();
    char* getCharacters(unsigned int& numberOfCharacters);
    template<typename NumberType> NumberType getTwoByteData();
    template<typename NumberType> NumberType getFourByteData();
    template<typename NumberType> NumberType getEightByteData();
    template<typename NumberType> NumberType getTwoByteSwappedData();
    template<typename NumberType> NumberType getFourByteSwappedData();
    template<typename NumberType> NumberType getEightByteSwappedData();
    template<typename NumberType, unsigned int numberOfBytesToRead> NumberType getData();
    void saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, unsigned int numberOfBytesToRead);
    std::string getLineAndIgnoreWhiteSpaces();
    std::string getLine();
    double getCurrentLocation() const;
    double getFileSize() const;
    void moveToTheBeginning() const;
    void moveLocation(unsigned long long const location) const;
    void setMaxBufferSize(unsigned int const bufferSize);
    unsigned int getMaxBufferSize() const;
private:
    char* getCharacterBufferPointer();
    static constexpr unsigned int INITIAL_MAX_BUFFER_SIZE = 10000;
    std::vector<char> m_characterBuffer;
    std::ifstream& m_stream;
};

}//namespace alba
