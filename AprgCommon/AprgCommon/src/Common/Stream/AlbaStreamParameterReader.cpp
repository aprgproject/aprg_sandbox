#include "AlbaStreamParameterReader.hpp"

using namespace std;

namespace alba
{

AlbaStreamParameterReader::AlbaStreamParameterReader(istream& stream) : m_stream(stream){}

template <>
string AlbaStreamParameterReader::readData<string>() const
{
    string data;
    bool isExisting(false);
    m_stream >> isExisting;
    if(isExisting)
    {
        while(m_stream.peek()=='\r' || m_stream.peek()=='\n') { m_stream.ignore(1); }
        getline(m_stream, data);
    }
    return data;
}

}//namespace alba
