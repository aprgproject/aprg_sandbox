#pragma once

#include <fstream>
#include <string>

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
    std::string getLineAndIgnoreWhiteSpaces();
    std::string getLine();    double getCurrentLocation() const;
    double getFileSize() const;
    void moveToTheBeginning() const;
    void moveLocation(unsigned long long location) const;
    void setMaxBufferSize(unsigned int bufferSize);
private:
    static const unsigned int MAX_BUFFER_SIZE = 10001;
    unsigned int m_bufferSize = MAX_BUFFER_SIZE;
    char m_characterBuffer[MAX_BUFFER_SIZE];
    std::ifstream& m_stream;
};

}//namespace alba
