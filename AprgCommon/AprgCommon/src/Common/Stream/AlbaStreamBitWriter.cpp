#include "AlbaStreamBitWriter.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaStreamBitWriter::AlbaStreamBitWriter(ostream& stream) : m_stream(stream) {}

AlbaStreamBitWriter::~AlbaStreamBitWriter() { transferAllToStream(); }

void AlbaStreamBitWriter::writeBoolData(bool const data) {
    putBoolDataToBuffer(data);
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeCharData(char const data) {
    putCharDataToBuffer(data);
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeStringData(string_view data) {
    for (char const c : data) {
        putCharDataToBuffer(c);
    }
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeHexDigitData(string_view hexDigitsData) {
    for (char const c : hexDigitsData) {
        bitset<4> hexDigitBitset(convertHexCharacterToNumber<char>(c));
        putBoolDataToBuffer(hexDigitBitset[3]);
        putBoolDataToBuffer(hexDigitBitset[2]);
        putBoolDataToBuffer(hexDigitBitset[1]);
        putBoolDataToBuffer(hexDigitBitset[0]);
    }
    transferBytesAsMuchAsPossibleToStream();
}

ostream& AlbaStreamBitWriter::getOutputStream() { return m_stream; }

void AlbaStreamBitWriter::flush() { transferAllToStream(); }

void AlbaStreamBitWriter::putBoolDataToBuffer(bool const boolValue) { m_bitBuffer.emplace_back(boolValue); }

void AlbaStreamBitWriter::putCharDataToBuffer(char const data) { putBigEndianNumberDataInBuffer<char>(data); }

void AlbaStreamBitWriter::transferBytesAsMuchAsPossibleToStream() {
    if (m_bitBuffer.size() >= 8) {
        size_t i = 0;
        for (; i + 8 <= m_bitBuffer.size(); i += 8) {
            bitset<8> byte;
            byte.set(0, m_bitBuffer[i + 7]);
            byte.set(1, m_bitBuffer[i + 6]);
            byte.set(2, m_bitBuffer[i + 5]);
            byte.set(3, m_bitBuffer[i + 4]);
            byte.set(4, m_bitBuffer[i + 3]);
            byte.set(5, m_bitBuffer[i + 2]);
            byte.set(6, m_bitBuffer[i + 1]);
            byte.set(7, m_bitBuffer[i]);
            m_stream << static_cast<char>(byte.to_ulong());
        }
        m_bitBuffer.erase(begin(m_bitBuffer), begin(m_bitBuffer) + i);
    }
}

void AlbaStreamBitWriter::transferAllToStream() {
    bitset<8> byte;
    size_t i = 0;
    for (; i < m_bitBuffer.size(); i++) {
        size_t remainder(i % 8);
        byte.set(7 - remainder, m_bitBuffer[remainder]);
        if (remainder == 7) {
            m_stream << static_cast<char>(byte.to_ulong());
            byte.reset();
        }
    }
    if (i % 8 != 0) {
        m_stream << static_cast<char>(byte.to_ulong());
    }
    m_bitBuffer.clear();
}

}  // namespace alba
