#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace alba{

class AlbaFileReader
{
public:
    explicit AlbaFileReader(std::ifstream& stream);
    bool isNotFinished();
    char getCharacter();
    char* getCharacters(unsigned int& numberOfCharacters);
    template<typename NumberType> NumberType getFourByteData();
    std::string getLineAndIgnoreWhiteSpaces();
    std::string getLine();
    double getCurrentLocation() const;
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



