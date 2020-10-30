#pragma once

#include <File/AlbaFileReader.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

#include <string>
#include <vector>

namespace alba
{

enum class BitmapCompressedMethodType
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

class AprgBitmap
{
public:
    static unsigned char const BYTE_SIZE_IN_BITS = 8;
    static unsigned int const DEFAULT_MAXIMUM_MEMORY_CONSUMPTION = 100000;
    using ColorTable = std::vector<unsigned int>;
    using PixelData = AlbaMemoryBuffer;
    struct XY
    {
        XY();        XY(unsigned int xValue, unsigned int yValue);
        bool operator==(XY const& xy) const;
        std::string getDisplayableString() const;
        unsigned int x;        unsigned int y;
    };

private:
    struct RectangularPixelsSnippet
    {
        RectangularPixelsSnippet();
        void addPosition(XY const position);
        void clear();
        unsigned int getDeltaX() const;
        unsigned int getDeltaY() const;
        unsigned int getNumberOfPixelsInSnippet() const;
        void setCorners(XY const topLeftCornerPosition, XY const bottomRightCornerPosition);
        bool isPositionInsideTheSnippet(XY const position) const;
        bool noPositionIsAddedYet;
        XY topLeftCorner;
        XY bottomRightCorner;
        XY retangularSize;
        PixelData pixelData;
    };

public:
    AprgBitmap(std::string const& path);
    bool isValid() const;
    bool isSignatureValid() const;    bool isHeaderValid() const;
    bool isNumberOfColorPlanesValid() const;
    bool isNumberOfBitsPerPixelValid() const;
    bool isCompressedMethodSupported() const;
    bool isPositionWithinTheBitmap(XY const position) const;
    BitmapCompressedMethodType getCompressedMethodType() const;
    unsigned int getMemoryConsumption() const;
    XY getPositionOfTopLeftCornerInMemory() const;
    XY getPositionOfBottomRightCornerInMemory()const;
    unsigned int getPixelInSnippet(XY const position) const;
    unsigned int getColorUsingPixelValue(unsigned int pixelValue) const;
    ColorTable getColorTable() const;
    PixelData getPixelsInMemory() const;

    void setMaximumMemoryConsumption(unsigned int const maximumMemoryConsumption);
    unsigned int getPixelWithAutomaticChangesToSnippet(XY const position);
    void addPositionInSnippet(XY const position);
    void loadPixels();
    void updateCornersInSnippetForMemoryConsumptionUsage(XY const center);
    void clearSnippetInMemory();

private:
    unsigned int getPixelInSnippetForPixelInAByte(unsigned char const* reader, unsigned int index, XY const position) const;
    unsigned int getPixelInSnippetForMultipleBytePixels(unsigned char const* reader, unsigned int index) const;
    void loadBitmapHeaders();
    void loadBitmapFileHeader(AlbaFileReader& fileReader);
    void loadDibHeader(AlbaFileReader& fileReader);    void loadColorTable(AlbaFileReader& fileReader);
    void calculateOtherValues();
    unsigned int convertPixelsToBytesRoundToFloor(unsigned int pixels) const;
    unsigned int convertPixelsToBytesRoundToCeil(unsigned int pixels) const;
    unsigned int convertBytesToPixels(unsigned int bytes) const;
    unsigned int getMaximumNumberOfPixelsBeforeOneByte() const;
    unsigned int getMinimumNumberOfBytesForOnePixel() const;
    bool isSnippetBeyondTheMaximumMemoryAllowed() const;
    XY computeSquareSideSizeForMaximumMemory() const;
    void computeCornersForMaximumMemory(XY & topLeftCornerPosition, XY & bottomRightCornerPosition, XY const center) const;
    BitmapCompressedMethodType determineCompressedMethodType(unsigned int compressedMethodValue) const;
    unsigned int m_fileSize;
    unsigned int m_pixelArrayAddress;
    unsigned int m_sizeOfHeader;    unsigned int m_bitmapWidth;
    unsigned int m_bitmapHeight;
    unsigned int m_numberOfColorPlanes;
    unsigned int m_numberOfBitsPerPixel;    BitmapCompressedMethodType m_compressionMethodType;
    unsigned int m_imageSize;
    unsigned long m_bitmapSize;
    unsigned int m_horizontalResolutionPixelInAMeter;
    unsigned int m_verticalResolutionPixelInAMeter;
    unsigned long m_numberOfColors;
    unsigned long m_numberImportantOfColors;
    unsigned int m_numberOfBytesForDataInRow;
    unsigned int m_paddingForRowMemoryAlignment;
    unsigned int m_numberOfBytesPerRow;
    unsigned int m_maximumMemoryConsumption;
    std::string m_path;
    std::string m_signature;
    ColorTable m_colors;
    RectangularPixelsSnippet m_snippetStoredInMemory;
};
}