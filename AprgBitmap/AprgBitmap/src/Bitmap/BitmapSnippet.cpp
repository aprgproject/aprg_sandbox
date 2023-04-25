#include "BitmapSnippet.hpp"

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

namespace AprgBitmap {

BitmapSnippet::BitmapSnippet() {}

BitmapSnippet::BitmapSnippet(
    BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition,
    BitmapConfiguration const& configuration)
    : m_topLeftCorner(topLeftCornerPosition),
      m_bottomRightCorner(bottomRightCornerPosition),
      m_configuration(configuration) {
    loadPixelDataFromFileInConfiguration();
}

BitmapConfiguration BitmapSnippet::getConfiguration() const { return m_configuration; }

bool BitmapSnippet::isPositionInsideTheSnippet(BitmapXY const position) const {
    return m_topLeftCorner.getX() <= position.getX() && m_topLeftCorner.getY() <= position.getY() &&
           m_bottomRightCorner.getX() >= position.getX() && m_bottomRightCorner.getY() >= position.getY();
}

BitmapXY BitmapSnippet::getTopLeftCorner() const { return m_topLeftCorner; }

BitmapXY BitmapSnippet::getBottomRightCorner() const { return m_bottomRightCorner; }

unsigned int BitmapSnippet::getDeltaX() const { return m_bottomRightCorner.getX() - m_topLeftCorner.getX(); }

unsigned int BitmapSnippet::getDeltaY() const { return m_bottomRightCorner.getY() - m_topLeftCorner.getY(); }

unsigned int BitmapSnippet::getNumberOfPixelsInSnippet() const { return getDeltaX() * getDeltaY(); }

unsigned int BitmapSnippet::getPixelDataSize() const { return m_pixelData.getSize(); }

void BitmapSnippet::clear() { m_pixelData.clear(); }

void BitmapSnippet::clearAndPutOneColorOnWholeSnippet(unsigned char const colorByte) {
    clear();

    int byteOffsetInXForStart =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX()));
    int byteOffsetInXForEnd =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_bottomRightCorner.getX()));
    int numberOfBytesToBeCopiedForX =
        static_cast<int>(m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));
    int yDifference = static_cast<int>(m_bottomRightCorner.getY()) - static_cast<int>(m_topLeftCorner.getY()) + 1;
    m_pixelData.resize(numberOfBytesToBeCopiedForX * yDifference, colorByte);
}

void BitmapSnippet::loadPixelDataFromFileInConfiguration() {
    if (m_configuration.isPositionWithinTheBitmap(m_topLeftCorner) &&
        m_configuration.isPositionWithinTheBitmap(m_bottomRightCorner)) {
        ifstream inputStream(m_configuration.getPath(), ios::binary);
        AlbaFileReader fileReader(inputStream);
        if (inputStream.is_open()) {
            int byteOffsetInXForStart =
                static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX()));
            int byteOffsetInXForEnd =
                static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_bottomRightCorner.getX()));
            int offsetInYForStart =
                static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(m_topLeftCorner.getY()) - 1;
            int offsetInYForEnd =
                static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(m_bottomRightCorner.getY()) - 1;
            int numberOfBytesToBeCopiedForX = static_cast<int>(
                m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));

            for (int y = offsetInYForStart; y >= offsetInYForEnd; y--) {
                unsigned long long fileOffsetForStart =
                    m_configuration.getPixelArrayAddress() +
                    ((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile() * y) + byteOffsetInXForStart;
                fileReader.moveLocation(fileOffsetForStart);
                fileReader.saveDataToMemoryBuffer(m_pixelData, numberOfBytesToBeCopiedForX);
            }
        }
    }
}

PixelData& BitmapSnippet::getPixelDataReference() { return m_pixelData; }

PixelData const& BitmapSnippet::getPixelDataConstReference() const { return m_pixelData; }

uint32_t BitmapSnippet::getPixelAt(BitmapXY const position) const {
    uint32_t result(0);
    if (isPositionInsideTheSnippet(position)) {
        unsigned int index = calculateIndexInPixelData(position);
        uint8_t const* reader = static_cast<uint8_t const*>(m_pixelData.getConstantBufferPointer());
        if (m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS) {
            result = getPixelAtForPixelInAByte(reader, index, position);
        } else {
            result = getPixelAtForMultipleBytePixels(reader, index);
        }
    }
    return result;
}

uint32_t BitmapSnippet::getColorAt(BitmapXY const position) const {
    return m_configuration.getColorUsingPixelValue(getPixelAt(position));
}

bool BitmapSnippet::isBlackAt(BitmapXY const position)
    const  // this is the only assumption, colors can depend on numberofbits of pixel and color table
{
    return (m_configuration.getColorUsingPixelValue(getPixelAt(position)) == 0x00000000);
}

void BitmapSnippet::setPixelAt(BitmapXY const position, uint32_t const value) {
    if (isPositionInsideTheSnippet(position)) {
        unsigned int index = calculateIndexInPixelData(position);
        uint8_t* writer = static_cast<uint8_t*>(m_pixelData.getBufferPointer());
        if (m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS) {
            setPixelAtForPixelInAByte(writer, index, position, value);
        } else {
            setPixelAtForMultipleBytePixels(writer, index, value);
        }
    }
}

void BitmapSnippet::traverse(TraverseFunction const& traverseFunction) const {
    for (unsigned int y = m_topLeftCorner.getY(); y <= m_bottomRightCorner.getY(); y++) {
        for (unsigned int x = m_topLeftCorner.getX(); x <= m_bottomRightCorner.getX(); x++) {
            BitmapXY currentPoint(x, y);
            traverseFunction(currentPoint, getPixelAt(currentPoint));
        }
    }
}

void BitmapSnippet::traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction) {
    for (unsigned int x = m_topLeftCorner.getX(); x <= m_bottomRightCorner.getX(); x++) {
        for (unsigned int y = m_topLeftCorner.getY(); y <= m_bottomRightCorner.getY(); y++) {
            BitmapXY currentPoint(x, y);
            unsigned int colorToBeUpdated(getPixelAt(currentPoint));
            traverseAndUpdateFunction(currentPoint, colorToBeUpdated);
            setPixelAt(currentPoint, colorToBeUpdated);
        }
    }
}

unsigned int BitmapSnippet::calculateShiftValue(BitmapXY const position) const {
    unsigned int numberOfPixelsInOneByte = m_configuration.getNumberOfPixelsForOneByte();
    unsigned int numberOfBitsPerPixel = m_configuration.getNumberOfBitsPerPixel();
    unsigned int positionRemainder = position.getX() % numberOfPixelsInOneByte;
    unsigned int loopAround = numberOfPixelsInOneByte - positionRemainder - 1;
    return numberOfBitsPerPixel * loopAround;
}

unsigned int BitmapSnippet::calculateIndexInPixelData(BitmapXY const position) const {
    unsigned int xPartInIndex = m_configuration.convertPixelsToBytesRoundedToFloor(position.getX()) -
                                m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX());
    unsigned int oneRowOffset =
        m_configuration.getOneRowSizeInBytesFromPixels(m_topLeftCorner.getX(), m_bottomRightCorner.getX());
    unsigned int yPartInIndex = oneRowOffset * (position.getY() - m_topLeftCorner.getY());
    return xPartInIndex + yPartInIndex;
}

uint32_t BitmapSnippet::getPixelAtForPixelInAByte(
    uint8_t const* reader, unsigned int const index, BitmapXY const position) const {
    uint32_t result(0);
    if (index < m_pixelData.getSize()) {
        result = static_cast<uint32_t>(*(reader + index));
        unsigned int shiftValue = calculateShiftValue(position);
        result = (result >> shiftValue) & m_configuration.getBitMaskForValue();
    }
    return result;
}

uint32_t BitmapSnippet::getPixelAtForMultipleBytePixels(uint8_t const* reader, unsigned int const index) const {
    uint32_t result(0);
    unsigned int minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if (index + minimumNumberOfBytesForOnePixel - 1 < m_pixelData.getSize()) {
        for (int indexForMultipleBytePixel = static_cast<int>(minimumNumberOfBytesForOnePixel) - 1;
             indexForMultipleBytePixel >= 0; indexForMultipleBytePixel--) {
            result <<= AlbaBitConstants::BYTE_SIZE_IN_BITS;
            result = result | static_cast<uint32_t>(*(reader + index + indexForMultipleBytePixel));
        }
    }
    return result;
}

void BitmapSnippet::setPixelAtForPixelInAByte(
    uint8_t* writer, unsigned int const index, BitmapXY const position, uint32_t const value) {
    if (index < m_pixelData.getSize()) {
        uint32_t oldValue = static_cast<uint32_t>(*(writer + index));
        unsigned int shiftValue = calculateShiftValue(position);
        uint32_t replacePart = (m_configuration.getBitMaskForValue() & value) << shiftValue;
        uint32_t retainMask =
            (m_configuration.getBitMaskForValue() << shiftValue) ^ AlbaBitValueUtilities<uint32_t>::getAllOnes();
        uint32_t retainPart = (retainMask & oldValue);
        *(writer + index) = replacePart | retainPart;
    }
}

void BitmapSnippet::setPixelAtForMultipleBytePixels(uint8_t* writer, unsigned int const index, uint32_t const value) {
    uint32_t valueToSave(value);
    unsigned int minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if (index + minimumNumberOfBytesForOnePixel - 1 < m_pixelData.getSize()) {
        for (int indexForMultipleBytePixel = 0; indexForMultipleBytePixel < (int)minimumNumberOfBytesForOnePixel;
             indexForMultipleBytePixel++) {
            *(writer + index + indexForMultipleBytePixel) = valueToSave & AlbaBitConstants::BYTE_MASK;
            valueToSave >>= AlbaBitConstants::BYTE_SIZE_IN_BITS;
        }
    }
}

}  // namespace AprgBitmap

}  // namespace alba
