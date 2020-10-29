#include "AprgBitmap.hpp"

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace std;

namespace alba
{

AprgBitmap::AprgBitmap(string const& path)
    : m_inputStream(AlbaLocalPathHandler(path).getFullPath(), ios::binary)
    , m_fileReader(m_inputStream)
{
    loadBitmap();
}

void AprgBitmap::loadBitmap()
{
    m_fileReader.moveLocation(0);
    m_signature += m_fileReader.getCharacter();
    m_signature += m_fileReader.getCharacter();

    m_fileReader.moveLocation(2);
    m_fileSize = m_fileReader.getEightByteSwappedData<unsigned long long>();

    m_fileReader.moveLocation(10);
    m_rasterPadSize = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(14);
    m_sizeOfHeader = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(18);
    m_bitmapWidth = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(22);
    m_bitmapHeight = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(26);
    m_numberOfColorPlanes = m_fileReader.getTwoByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(28);
    m_numberOfBitsPerPixel = m_fileReader.getTwoByteSwappedData<unsigned int>();

    m_bitmapSize = (unsigned long)m_bitmapWidth*m_bitmapHeight;

    m_fileReader.moveLocation(30);
    m_compressionMethodType = determineCompressedMethodType(m_fileReader.getFourByteData<unsigned int>());

    m_fileReader.moveLocation(34);
    m_imageSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(38);
    m_horizontalResolutionPixelInAMeter = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(42);
    m_verticalResolutionPixelInAMeter = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(46);
    m_numberOfColors = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(50);
    m_numberImportantOfColors = m_fileReader.getFourByteSwappedData<unsigned int>();

    m_fileReader.moveLocation(54);
    m_defaultColor = (unsigned int) m_fileReader.getCharacter();

    //m_rasterPadSize =( 4-(rasterRound((double)nCols/8)%4) ) % 4;
}

bool AprgBitmap::isValid() const
{
    return isSignatureValid() && isHeaderValid() && isNumberOfColorPlanesValid() && isNumberOfBitsPerPixelValid();
}

bool AprgBitmap::isSignatureValid() const
{
    return (m_signature == "BM");
}

bool AprgBitmap::isHeaderValid() const
{
    return (m_sizeOfHeader == 40);
}

bool AprgBitmap::isNumberOfColorPlanesValid() const
{
    return (m_numberOfColorPlanes == 1);
}

bool AprgBitmap::isNumberOfBitsPerPixelValid() const
{
    return (m_numberOfBitsPerPixel == 1) ||
            (m_numberOfBitsPerPixel == 4) ||
            (m_numberOfBitsPerPixel == 8) ||
            (m_numberOfBitsPerPixel == 16) ||
            (m_numberOfBitsPerPixel == 24) ||
            (m_numberOfBitsPerPixel == 32);
}

bool AprgBitmap::isCompressedMethodSupported() const
{
    return (m_compressionMethodType == BitmapCompressedMethodType::BI_RGB);
}

BitmapCompressedMethodType AprgBitmap::getCompressedMethodType() const
{
    return m_compressionMethodType;
}

BitmapCompressedMethodType AprgBitmap::determineCompressedMethodType(unsigned int compressedMethodValue) const
{
    BitmapCompressedMethodType compressedMethodType;
    switch(compressedMethodValue)
    {
    case 0: compressedMethodType = BitmapCompressedMethodType::BI_RGB; break;
    case 1: compressedMethodType = BitmapCompressedMethodType::BI_RLE8; break;
    case 2: compressedMethodType = BitmapCompressedMethodType::BI_RLE4; break;
    case 3: compressedMethodType = BitmapCompressedMethodType::BI_BITFIELDS; break;
    case 4: compressedMethodType = BitmapCompressedMethodType::BI_JPEG; break;
    case 5: compressedMethodType = BitmapCompressedMethodType::BI_PNG; break;
    case 6: compressedMethodType = BitmapCompressedMethodType::BI_ALPHABITFIELDS; break;
    case 11: compressedMethodType = BitmapCompressedMethodType::BI_CMYK; break;
    case 12: compressedMethodType = BitmapCompressedMethodType::BI_CMYKRLE8; break;
    case 13: compressedMethodType = BitmapCompressedMethodType::BI_CMYKRLE4; break;
    default: compressedMethodType = BitmapCompressedMethodType::Unknown; break;
    }
    return compressedMethodType;
}



}
