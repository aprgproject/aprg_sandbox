#pragma once

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Stream/AlbaStreamBitEndianType.hpp>

#include <bitset>
#include <deque>
#include <istream>
#include <string>

namespace alba {

class AlbaStreamBitReader {
public:
    explicit AlbaStreamBitReader(std::istream& stream);
    ~AlbaStreamBitReader() = default;

    bool noRemainingBitsInBuffer() const;

    bool readBoolData();
    char readCharData();
    std::string readStringData(size_t const numberOfCharacters);
    std::string readWholeStreamAsStringData();
    template <typename TypeToWrite>
    TypeToWrite readNumberData(AlbaStreamBitEndianType const endianType);
    template <typename TypeToWrite>
    TypeToWrite readBigEndianNumberData();
    template <typename TypeToWrite>
    TypeToWrite readLittleEndianNumberData();
    template <auto BITSET_SIZE>
    std::bitset<BITSET_SIZE> readBitsetData(size_t const startBitsetIndex, size_t const endBitsetIndex);

    std::istream& getInputStream();

private:
    void readIfNeeded(size_t const numberOfBitsRequired);
    void eraseBitsInBitBuffer(size_t const numberOfBitsToErase);
    std::istream& m_stream;
    std::deque<bool> m_bitBuffer;
};

template <typename TypeToWrite>
TypeToWrite AlbaStreamBitReader::readNumberData(AlbaStreamBitEndianType const endianType) {
    TypeToWrite result{};
    if (AlbaStreamBitEndianType::BigEndian == endianType) {
        result = readBigEndianNumberData<TypeToWrite>();
    } else if (AlbaStreamBitEndianType::LittleEndian == endianType) {
        result = readLittleEndianNumberData<TypeToWrite>();
    }
    return result;
}

template <typename TypeToWrite>
TypeToWrite AlbaStreamBitReader::readBigEndianNumberData() {
    constexpr size_t numberOfBits(AlbaBitValueUtilities<TypeToWrite>::getNumberOfBits());
    readIfNeeded(numberOfBits);
    std::bitset<numberOfBits> dataBitset;
    for (size_t i = 0; i < numberOfBits; i++) {
        dataBitset.set(numberOfBits - 1 - i, m_bitBuffer[i]);
    }
    eraseBitsInBitBuffer(numberOfBits);
    return static_cast<TypeToWrite>(dataBitset.to_ullong());
}

template <typename TypeToWrite>
TypeToWrite AlbaStreamBitReader::readLittleEndianNumberData() {
    constexpr size_t numberOfBits(AlbaBitValueUtilities<TypeToWrite>::getNumberOfBits());
    readIfNeeded(numberOfBits);
    std::bitset<numberOfBits> dataBitset;
    size_t byteSize = round(numberOfBits / AlbaBitConstants::BYTE_SIZE_IN_BITS);
    size_t bitBufferIndex = 0;
    for (size_t byteIndex = 1; byteIndex <= byteSize; byteIndex++) {
        for (size_t i = 0; i < AlbaBitConstants::BYTE_SIZE_IN_BITS; i++) {
            dataBitset.set((byteIndex * AlbaBitConstants::BYTE_SIZE_IN_BITS) - 1 - i, m_bitBuffer[bitBufferIndex++]);
        }
    }
    eraseBitsInBitBuffer(numberOfBits);
    return static_cast<TypeToWrite>(dataBitset.to_ullong());
}

template <auto BITSET_SIZE>
std::bitset<BITSET_SIZE> AlbaStreamBitReader::readBitsetData(
    size_t const startBitsetIndex, size_t const endBitsetIndex) {
    std::bitset<BITSET_SIZE> result;
    size_t const numberOfBitsToRead = std::min(endBitsetIndex - startBitsetIndex + 1, static_cast<size_t>(BITSET_SIZE));
    readIfNeeded(numberOfBitsToRead);
    AlbaValueRange<int> bitsetRange(static_cast<int>(startBitsetIndex), static_cast<int>(endBitsetIndex), 1U);
    size_t bitBufferIndex = 0;
    bitsetRange.traverse([&](int const bitsetIndex) { result.set(bitsetIndex, m_bitBuffer[bitBufferIndex++]); });
    eraseBitsInBitBuffer(numberOfBitsToRead);
    return result;
}

}  // namespace alba
