#include "AlbaStreamBitReader.hpp"

#include <algorithm>
#include <vector>

using namespace std;

namespace alba {

AlbaStreamBitReader::AlbaStreamBitReader(istream& stream) : m_stream(stream) {}

bool AlbaStreamBitReader::noRemainingBitsInBuffer() const { return m_bitBuffer.empty(); }

bool AlbaStreamBitReader::readBoolData() {
    readIfNeeded(1U);
    bool result(m_bitBuffer.front());
    eraseBitsInBitBuffer(1U);
    return result;
}

char AlbaStreamBitReader::readCharData() { return AlbaStreamBitReader::readBigEndianNumberData<char>(); }

string AlbaStreamBitReader::readStringData(size_t const numberOfCharacters) {
    string result;
    for (size_t i = 0; i < numberOfCharacters; i++) {
        char c(readCharData());
        if (!m_stream.eof()) {
            result += c;
        } else {
            break;
        }
    }
    return result;
}

string AlbaStreamBitReader::readWholeStreamAsStringData() {
    string result;
    while (true) {
        char c(readCharData());
        if (!m_stream.eof()) {
            result += c;
        } else {
            break;
        }
    }
    return result;
}

istream& AlbaStreamBitReader::getInputStream() { return m_stream; }

void AlbaStreamBitReader::readIfNeeded(size_t const numberOfBitsRequired) {
    if (m_bitBuffer.size() < numberOfBitsRequired) {
        size_t numberOfBytesToRead = static_cast<size_t>(
            ceil(static_cast<double>(numberOfBitsRequired - m_bitBuffer.size()) / AlbaBitConstants::BYTE_SIZE_IN_BITS));
        vector<char> characterBuffer(numberOfBytesToRead, {});
        m_stream.read(&(characterBuffer.front()), numberOfBytesToRead);
        for (char const c : characterBuffer) {
            bitset<8> charByte(c);
            m_bitBuffer.emplace_back(charByte[7]);
            m_bitBuffer.emplace_back(charByte[6]);
            m_bitBuffer.emplace_back(charByte[5]);
            m_bitBuffer.emplace_back(charByte[4]);
            m_bitBuffer.emplace_back(charByte[3]);
            m_bitBuffer.emplace_back(charByte[2]);
            m_bitBuffer.emplace_back(charByte[1]);
            m_bitBuffer.emplace_back(charByte[0]);
        }
    }
}

void AlbaStreamBitReader::eraseBitsInBitBuffer(size_t const numberOfBitsToErase) {
    m_bitBuffer.erase(begin(m_bitBuffer), begin(m_bitBuffer) + numberOfBitsToErase);
}

}  // namespace alba
