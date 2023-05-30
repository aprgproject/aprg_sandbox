#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <Common/File/AlbaFileReader.hpp>

#include <cstdint>
#include <string>

namespace alba {

namespace AprgBitmap {

enum class CompressedMethodType {
    RGB,
    RLE8,
    RLE4,
    BITFIELDS,
    JPEG,
    PNG,
    ALPHABITFIELDS,
    CMYK,
    CMYKRLE8,
    CMYKRLE4,
    Unknown
};

class BitmapConfiguration {
public:
    BitmapConfiguration();
    bool isValid() const;
    bool isSignatureValid() const;
    bool isHeaderValid() const;
    bool isNumberOfColorPlanesValid() const;
    bool isNumberOfBitsPerPixelValid() const;
    bool isCompressedMethodSupported() const;
    bool isPositionWithinTheBitmap(BitmapXY const position) const;
    bool isPositionWithinTheBitmap(int x, int y) const;

    CompressedMethodType getCompressedMethodType() const;
    std::string getPath() const;
    uint32_t getPixelArrayAddress() const;
    uint32_t getBitmapWidth() const;
    uint32_t getBitmapHeight() const;
    uint16_t getNumberOfBitsPerPixel() const;
    uint32_t getNumberOfBytesPerRowInFile() const;
    uint32_t getBitMaskForValue() const;

    BitmapXY getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const;
    int getXCoordinateWithinTheBitmap(int const coordinate) const;
    int getYCoordinateWithinTheBitmap(int const coordinate) const;
    int getCoordinateWithinRange(int const coordinate, int maxLength) const;
    BitmapXY getUpLeftCornerPoint() const;
    BitmapXY getDownRightCornerPoint() const;

    uint32_t getColorUsingPixelValue(uint32_t const pixelValue) const;
    int convertPixelsToBytesRoundedToFloor(int pixels) const;
    int convertPixelsToBytesRoundedToCeil(int pixels) const;
    int convertBytesToPixels(int bytes) const;
    int getNumberOfPixelsForOneByte() const;
    int getMaximumNumberOfPixelsBeforeOneByte() const;
    int getMinimumNumberOfBytesForOnePixel() const;
    int getEstimatedSquareSideInPixels(int const numberOfBytesToRead) const;
    int getOneRowSizeInBytesFromPixels(
        int const leftPixelInclusive, int const rightPixelInclusive) const;
    int getOneRowSizeInBytesFromBytes(
        int const leftByteInclusive, int const rightByteInclusive) const;

    Colors getColorTable() const;

    void readBitmap(std::string const& path);

private:
    void readBitmapFileHeader(AlbaFileReader& fileReader);
    void readDibHeader(AlbaFileReader& fileReader);
    void readColors(AlbaFileReader& fileReader);
    void calculateOtherValuesAfterReading();
    CompressedMethodType determineCompressedMethodType(uint32_t compressedMethodValue) const;
    uint32_t m_fileSize;
    uint32_t m_pixelArrayAddress;
    uint32_t m_sizeOfHeader;
    uint32_t m_bitmapWidth;
    uint32_t m_bitmapHeight;
    uint16_t m_numberOfColorPlanes;
    uint16_t m_numberOfBitsPerPixel;
    CompressedMethodType m_compressionMethodType;
    uint32_t m_imageSize;
    uint64_t m_bitmapSize;
    uint32_t m_horizontalResolutionPixelInAMeter;
    uint32_t m_verticalResolutionPixelInAMeter;
    uint32_t m_numberOfColors;
    uint32_t m_numberImportantOfColors;
    uint32_t m_numberOfBytesForDataInRow;
    uint32_t m_paddingForRowMemoryAlignment;
    uint32_t m_numberOfBytesPerRowInFile;
    uint32_t m_bitMaskForValue;
    std::string m_path;
    std::string m_signature;
    Colors m_colors;
};

bool areBitmapConfigurationsCompatibleForChangingPixelData(
    BitmapConfiguration const& configuration1, BitmapConfiguration const& configuration2);

}  // namespace AprgBitmap

}  // namespace alba
