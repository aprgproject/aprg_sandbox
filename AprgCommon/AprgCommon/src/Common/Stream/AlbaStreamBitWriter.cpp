#include "AlbaStreamBitWriter.hpp"

using namespace std;

namespace alba
{

AlbaStreamBitWriter::AlbaStreamBitWriter(ostream& stream)
    : m_stream(stream)
{}

AlbaStreamBitWriter::~AlbaStreamBitWriter()
{
    writeAllToStream();
}

void AlbaStreamBitWriter::writeBoolData(bool const data)
{
    m_bitBuffer.emplace_back(data);
    writeAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeCharData(char const data)
{
    putBigEndianNumberDataInBuffer<char>(data);
    writeAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeStringData(string const& data)
{
    for(char const c : data)
    {        writeCharData(c);
    }
    writeAsMuchAsPossibleToStream();
}
void AlbaStreamBitWriter::writeAsMuchAsPossibleToStream()
{
    if(m_bitBuffer.size() >= 8)
    {
        unsigned int i=0;
        for(; i+8<=m_bitBuffer.size();  i+=8)
        {
            bitset<8> byte;
            byte.set(0, m_bitBuffer.at(i+7));
            byte.set(1, m_bitBuffer.at(i+6));
            byte.set(2, m_bitBuffer.at(i+5));
            byte.set(3, m_bitBuffer.at(i+4));
            byte.set(4, m_bitBuffer.at(i+3));
            byte.set(5, m_bitBuffer.at(i+2));
            byte.set(6, m_bitBuffer.at(i+1));
            byte.set(7, m_bitBuffer.at(i));
            m_stream << static_cast<char>(byte.to_ulong());
        }
        m_bitBuffer.erase(m_bitBuffer.begin(), m_bitBuffer.begin()+i);
    }
}

void AlbaStreamBitWriter::writeAllToStream()
{
    bitset<8> byte;
    unsigned int i=0;
    for(; i<m_bitBuffer.size();  i++)
    {
        unsigned int remainder(i%8);
        byte.set(remainder, m_bitBuffer.at(7-remainder));
        if(remainder)
        {
            m_stream << static_cast<char>(byte.to_ulong());
            byte.reset();
        }
    }
    if(i%8 != 0)
    {
        m_stream << static_cast<char>(byte.to_ulong());
    }
    m_bitBuffer.clear();
}

}//namespace alba
