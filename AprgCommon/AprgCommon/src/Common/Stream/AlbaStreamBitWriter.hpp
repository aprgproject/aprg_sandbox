#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Stream/AlbaStreamBitEndianType.hpp>

#include <bitset>
#include <deque>
#include <string>
#include <ostream>

namespace alba
{

class AlbaStreamBitWriter
{
public:
    explicit AlbaStreamBitWriter(std::ostream& stream);
    ~AlbaStreamBitWriter();

    // rule of zero

    void writeBoolData(bool const data);
    void writeCharData(char const data);
    void writeStringData(std::string const& data);
    void writeHexDigitData(std::string const& hexDigitsData);
    template <typename TypeToWrite> void writeNumberData(AlbaStreamBitEndianType const endianType, TypeToWrite const& data);
    template <typename TypeToWrite> void writeBigEndianNumberData(TypeToWrite const& data);
    template <typename TypeToWrite> void writeLittleEndianNumberData(TypeToWrite const& data);
    template <unsigned int BITSET_SIZE> void writeBitsetData(std::bitset<BITSET_SIZE> const& data, unsigned int const startBitsetIndex, unsigned int const endBitsetIndex);

    std::ostream& getOutputStream();
    void flush();

private:
    template <typename TypeToWrite> void putBigEndianNumberDataInBuffer(TypeToWrite const& data);
    template <typename TypeToWrite> void putLittleEndianNumberDataInBuffer(TypeToWrite const& data);
    void putBoolDataToBuffer(bool const boolValue);
    void putCharDataToBuffer(char const data);
    void transferBytesAsMuchAsPossibleToStream();
    void transferAllToStream();
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
    transferBytesAsMuchAsPossibleToStream();
}

template <typename TypeToWrite>
void AlbaStreamBitWriter::writeBigEndianNumberData(TypeToWrite const& data)
{
    putBigEndianNumberDataInBuffer<TypeToWrite>(data);
    transferBytesAsMuchAsPossibleToStream();
}

template <typename TypeToWrite>
void AlbaStreamBitWriter::writeLittleEndianNumberData(TypeToWrite const& data)
{
    putLittleEndianNumberDataInBuffer<TypeToWrite>(data);
    transferBytesAsMuchAsPossibleToStream();
}

template <unsigned int BITSET_SIZE>
void AlbaStreamBitWriter::writeBitsetData(std::bitset<BITSET_SIZE> const& data, unsigned int const startBitsetIndex, unsigned int const endBitsetIndex)
{
    AlbaValueRange<int> bitsetRange(static_cast<int>(startBitsetIndex), static_cast<int>(endBitsetIndex), 1U);
    bitsetRange.traverse([&](int const bitsetIndex)
    {
        m_bitBuffer.emplace_back(data[bitsetIndex]);
    });
    transferBytesAsMuchAsPossibleToStream();
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
