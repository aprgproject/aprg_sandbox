#pragma once

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

namespace alba{

class AlbaFileReader{
public:
    explicit AlbaFileReader(ifstream& stream);
    string getLineAndIgnoreWhiteSpaces();
    string simpleGetLine();
    double getCurrentLocation() const;
    double getFileSize() const;
    void setMaxBufferSize(int bufferSize);
    bool isNotFinished();
private:
    static const int MAX_BUFFER_SIZE = 10001;
    int m_bufferSize = MAX_BUFFER_SIZE;
    char m_characterBuffer[MAX_BUFFER_SIZE];
    ifstream& m_stream;
};

}//namespace alba
