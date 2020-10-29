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
    using ColorTable = std::vector<unsigned int>;
    using Pixels = AlbaMemoryBuffer;
    struct XY
    {
        XY();
        XY(unsigned int xValue, unsigned int yValue);
        bool operator==(XY const& xy) const;
        std::string getDisplayableString() const;
        unsigned int x;
        unsigned int y;
    };

private:
    struct RectangularPixelsSnippet
    {
        RectangularPixelsSnippet();
        void addPosition(AprgBitmap::XY const position);
        void clear();
        unsigned int getDeltaX() const;
        unsigned int getDeltaY() const;
        bool isPositionInsideTheSnippet(AprgBitmap::XY const position) const;
        bool noPositionIsAddedYet;
        AprgBitmap::XY topLeftCorner;
        AprgBitmap::XY bottomRightCorner;
        AprgBitmap::XY retangularSize;
        Pixels pixels;
    };

public:

    AprgBitmap(std::string const& path);
    bool isValid() const;
    bool isSignatureValid() const;
    bool isHeaderValid() const;
    bool isNumberOfColorPlanesValid() const;
    bool isNumberOfBitsPerPixelValid() const;
    bool isCompressedMethodSupported() const;
    BitmapCompressedMethodType getCompressedMethodType() const;
    XY getPositionOfTopLeftCornerInMemory() const;
    XY getPositionOfBottomRightCornerInMemory()const;
    void addPositionToLoadInMemory(AprgBitmap::XY const position);

    void loadPixels();
    void clearSnippetInMemory();
    unsigned int getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY const position) const;
    unsigned int getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY const position);
    unsigned int getColorUsingPixelValue(unsigned int pixelValue) const;

    ColorTable getColorTable() const;
    Pixels getPixelsInMemory() const;

private:
    void loadBitmapHeaders();
    void loadBitmapFileHeader(AlbaFileReader& fileReader);
    void loadDibHeader(AlbaFileReader& fileReader);
    void loadColorTable(AlbaFileReader& fileReader);
    void calculateOtherValues();
    unsigned int convertPixelsToBytesRoundToFloor(unsigned int pixels) const;
    unsigned int convertPixelsToBytesRoundToCeil(unsigned int pixels) const;
    unsigned int convertBytesToPixels(unsigned int bytes) const;
    unsigned int getMaximumNumberOfPixelsBeforeOneByte() const;
    BitmapCompressedMethodType determineCompressedMethodType(unsigned int compressedMethodValue) const;
    std::string m_path;
    std::string m_signature;
    unsigned int m_fileSize;
    unsigned int m_pixelArrayAddress;
    unsigned int m_sizeOfHeader;
    unsigned int m_bitmapWidth;
    unsigned int m_bitmapHeight;
    unsigned int m_numberOfColorPlanes;
    unsigned int m_numberOfBitsPerPixel;
    BitmapCompressedMethodType m_compressionMethodType;
    unsigned int m_imageSize;
    unsigned long m_bitmapSize;
    unsigned int m_horizontalResolutionPixelInAMeter;
    unsigned int m_verticalResolutionPixelInAMeter;
    unsigned long m_numberOfColors;
    unsigned long m_numberImportantOfColors;
    unsigned int m_numberOfBytesForDataInRow;
    unsigned int m_paddingForRowMemoryAlignment;
    unsigned int m_numberOfBytesPerRow;
    ColorTable m_colors;
    RectangularPixelsSnippet m_snippetStoredInMemory;
};

}
