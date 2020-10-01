#include <AlbaFileReader.hpp>

#include <AlbaStringHelper.hpp>
#include <fstream>
#include <string>
using namespace std;

namespace alba{

AlbaFileReader::AlbaFileReader(ifstream& stream) : m_stream(stream){}

bool AlbaFileReader::isNotFinished()
{
    //return (!m_stream.eof()) && (m_stream.peek()!=EOF);
    return !m_stream.eof();
}

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

string AlbaFileReader::simpleGetLine()
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
    m_stream.seekg(0, m_stream.beg);
    return fileSize;
}

void AlbaFileReader::setMaxBufferSize(int bufferSize)
{
    if(bufferSize+1 < MAX_BUFFER_SIZE && bufferSize > 0)
    {
        m_bufferSize = bufferSize+1;
    }
}

}//namespace alba
