#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Stream/AlbaStreamBitEndianType.hpp>

#include <bitset>
#include <deque>
#include <ostream>
#include <string>

namespace alba
{

class AlbaStreamBitWriter
{
public:
    explicit AlbaStreamBitWriter(std::ostream& stream);
    ~AlbaStreamBitWriter();

    void writeBoolData(bool const data);
    void writeCharData(char const data);
    void writeStringData(std::string const& data);
    template <typename TypeToWrite> void writeNumberData(AlbaStreamBitEndianType const endianType, TypeToWrite const& data);

    void flush();

private:
    template <typename TypeToWrite> void putBigEndianNumberDataInBuffer(TypeToWrite const& data);
    template <typename TypeToWrite> void putLittleEndianNumberDataInBuffer(TypeToWrite const& data);
    void writeBytesAsMuchAsPossibleToStream();
    void writeAllToStream();
    AlbaStreamBitEndianType m_endianType;
    std::ostream& m_stream;
    std::deque<bool> m_bitBuffer;
};

template <typename TypeToWrite>
void AlbaStreamBitWriter::writeNumberData(AlbaStreamBitEndianType const endianType, TypeToWrite const& data)
{
    if(AlbaStreamBitEndianType::BigEndian == endianType)
    {
        putBigEndianNumberDataInBuffer<TypeToWrite>(data);
    }
    else if(AlbaStreamBitEndianType::LittleEndian == endianType)
    {
        putLittleEndianNumberDataInBuffer<TypeToWrite>(data);
    }
    writeBytesAsMuchAsPossibleToStream();
}

template <typename TypeToWrite>
void AlbaStreamBitWriter::putBigEndianNumberDataInBuffer(TypeToWrite const& data)
{
    constexpr unsigned int numberOfBits(AlbaBitValueUtilities<TypeToWrite>::getNumberOfBits());
    std::bitset<numberOfBits> dataBitset(data);
    for(int i=numberOfBits-1; i>=0; i--)
    {
        m_bitBuffer.emplace_back(dataBitset[i]);
    }
}

template <typename TypeToWrite>
void AlbaStreamBitWriter::putLittleEndianNumberDataInBuffer(TypeToWrite const& data)
{
    constexpr unsigned int numberOfBits(AlbaBitValueUtilities<TypeToWrite>::getNumberOfBits());
    std::bitset<numberOfBits> dataBitset(data);
    unsigned int byteSize = static_cast<unsigned int>(ceil(static_cast<double>(numberOfBits)/AlbaBitConstants::BYTE_SIZE_IN_BITS));
    for(unsigned int byteIndex=0; byteIndex<byteSize; byteIndex++)
    {
        for(int i=AlbaBitConstants::BYTE_SIZE_IN_BITS-1; i>=0; i--)
        {
            m_bitBuffer.emplace_back(dataBitset[(byteIndex*AlbaBitConstants::BYTE_SIZE_IN_BITS) + i]);
        }
    }
}

}//namespace alba
