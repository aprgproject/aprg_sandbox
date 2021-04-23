#pragma once

#include <CommonTypes.hpp>
#include <File/AlbaFileReader.hpp>

#include <string>

namespace alba
{

enum class CompressedMethodType
{
    BI_RGB,
    BI_RLE8,
    BI_RLE4,
    BI_BITFIELDS,
    BI_JPEG,
    BI_PNG,
    BI_ALPHABITFIELDS,
    BI_CMYK,
    BI_CMYKRLE8,
    BI_CMYKRLE4,
    Unknown
};

class AprgBitmapConfiguration
{
public:
    AprgBitmapConfiguration();
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
    unsigned int getPixelArrayAddress() const;
    unsigned int getBitmapWidth() const;
    unsigned int getBitmapHeight() const;
    unsigned int getNumberOfBitsPerPixel() const;
    unsigned int getNumberOfBytesPerRowInFile() const;
    unsigned int getBitMaskForValue() const;

    BitmapXY getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const;
    unsigned int getXCoordinateWithinTheBitmap(int const coordinate) const;
    unsigned int getYCoordinateWithinTheBitmap(int const coordinate) const;
    unsigned int getCoordinateWithinRange(int const coordinate, int maxLength) const;
    BitmapXY getUpLeftCornerPoint() const;
    BitmapXY getDownRightCornerPoint() const;

    unsigned int getColorUsingPixelValue(unsigned int pixelValue) const;
    unsigned int convertPixelsToBytesRoundToFloor(unsigned int pixels) const;
    unsigned int convertPixelsToBytesRoundToCeil(unsigned int pixels) const;
    unsigned int convertBytesToPixels(unsigned int bytes) const;
    unsigned int getNumberOfPixelsForOneByte() const;
    unsigned int getMaximumNumberOfPixelsBeforeOneByte() const;
    unsigned int getMinimumNumberOfBytesForOnePixel() const;
    unsigned int estimateSquareSideInPixels(unsigned int const numberOfBytesToRead) const;
    unsigned int getOneRowSizeInBytesFromPixels(unsigned int const leftPixelInclusive, unsigned int const rightPixelInclusive) const;
    unsigned int getOneRowSizeInBytesFromBytes(unsigned int const leftByteInclusive, unsigned int const rightByteInclusive) const;

    Colors getColorTable() const;

    void readBitmap(std::string const& path);
    bool operator==(AprgBitmapConfiguration const& configuration) const;

private:
    void readBitmapFileHeader(AlbaFileReader& fileReader);
    void readDibHeader(AlbaFileReader& fileReader);
    void readColors(AlbaFileReader& fileReader);
    void calculateOtherValuesAfterReading();
    CompressedMethodType determineCompressedMethodType(unsigned int compressedMethodValue) const;
    unsigned int m_fileSize;
    unsigned int m_pixelArrayAddress;
    unsigned int m_sizeOfHeader;
    unsigned int m_bitmapWidth;
    unsigned int m_bitmapHeight;
    unsigned int m_numberOfColorPlanes;
    unsigned int m_numberOfBitsPerPixel;
    CompressedMethodType m_compressionMethodType;
    unsigned int m_imageSize;
    unsigned long m_bitmapSize;
    unsigned int m_horizontalResolutionPixelInAMeter;
    unsigned int m_verticalResolutionPixelInAMeter;
    unsigned long m_numberOfColors;
    unsigned long m_numberImportantOfColors;
    unsigned int m_numberOfBytesForDataInRow;
    unsigned int m_paddingForRowMemoryAlignment;
    unsigned int m_numberOfBytesPerRowInFile;
    unsigned int m_bitMaskForValue;
    std::string m_path;
    std::string m_signature;
    Colors m_colors;
};

}
