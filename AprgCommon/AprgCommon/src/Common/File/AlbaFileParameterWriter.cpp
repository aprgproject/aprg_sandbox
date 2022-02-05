#include "AlbaFileParameterWriter.hpp"

using namespace std;

namespace alba
{

AlbaFileParameterWriter::AlbaFileParameterWriter(ostream& stream) : m_stream(stream){}

template<>
void AlbaFileParameterWriter::writeData(string const& data) const
{
    bool isExisting(!data.empty());
    m_stream << isExisting << endl;
    if(isExisting)
    {
        m_stream << data << endl;
    }
}

}//namespace alba
