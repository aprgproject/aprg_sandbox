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
    m_fileSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(10);
    m_rasterPadSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(14);
    m_sizeOfHeader = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(18);
    m_bitmapWidth = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(22);
    m_bitmapHeight = m_fileReader.getFourByteData<unsigned int>();

    cout<<hex<<m_bitmapWidth<<endl;// you need to fix endianess
    cout<<hex<<m_bitmapHeight<<endl;

    m_fileReader.moveLocation(26);
    m_numberOfColorPlanes = m_fileReader.getTwoByteData<unsigned int>();

    m_fileReader.moveLocation(28);
    m_numberOfBitsPerPixel = m_fileReader.getTwoByteData<unsigned int>();

    m_bitmapSize = m_bitmapWidth*m_bitmapHeight;

    m_fileReader.moveLocation(30);
    m_compressionMethodType = determineCompressedMethodType(m_fileReader.getFourByteData<unsigned int>());

    m_fileReader.moveLocation(34);
    m_imageSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(38);
    m_horizontalResolutionPixelInAMeter = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(42);
    m_verticalResolutionPixelInAMeter = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(46);
    m_numberOfColors = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(50);
    m_numberImportantOfColors = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(54);
    m_defaultColor = (unsigned int) m_fileReader.getCharacter();

    //m_rasterPadSize =( 4-(rasterRound((double)nCols/8)%4) ) % 4;
}

bool AprgBitmap::isValid() const
{
    return isHeaderValid() && isNumberOfColorPlanesValid() && isNumberOfBitsPerPixelValid();
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
    return false;
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
