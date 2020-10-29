#pragma once

#include <File/AlbaFileReader.hpp>

#include <fstream>

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
    AprgBitmap(std::string const& path);
    bool isValid() const;
    bool isSignatureValid() const;
    bool isHeaderValid() const;
    bool isNumberOfColorPlanesValid() const;
    bool isNumberOfBitsPerPixelValid() const;
    bool isCompressedMethodSupported() const;
    BitmapCompressedMethodType getCompressedMethodType() const;

private:
    void loadBitmap();    BitmapCompressedMethodType determineCompressedMethodType(unsigned int compressedMethodValue) const;
    std::ifstream m_inputStream;
    AlbaFileReader m_fileReader;
    std::string m_signature;
    unsigned long m_fileSize;
    unsigned int m_rasterPadSize;
    unsigned int m_sizeOfHeader;
    unsigned int m_rasterDataAddress;
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
    unsigned int m_defaultColor;
};

}
