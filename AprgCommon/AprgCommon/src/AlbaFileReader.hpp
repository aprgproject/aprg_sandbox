#pragma once

#include <fstream>
#include <string>

namespace alba{

class AlbaFileReader
{
public:
    explicit AlbaFileReader(std::ifstream& stream);
    bool isNotFinished();
    std::string getLineAndIgnoreWhiteSpaces();
    std::string simpleGetLine();
    double getCurrentLocation() const;
    double getFileSize() const;
    void moveToTheBeginning() const;
    void moveLocation(unsigned long long location) const;
    void setMaxBufferSize(int bufferSize);
private:
    static const int MAX_BUFFER_SIZE = 10001;
    int m_bufferSize = MAX_BUFFER_SIZE;
    char m_characterBuffer[MAX_BUFFER_SIZE];
    std::ifstream& m_stream;
};

}//namespace alba
