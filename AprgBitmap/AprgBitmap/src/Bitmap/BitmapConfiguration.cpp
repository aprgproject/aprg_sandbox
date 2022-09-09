#include "BitmapConfiguration.hpp"

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

BitmapConfiguration::BitmapConfiguration()
    : m_fileSize(0)
    , m_pixelArrayAddress(0)
    , m_sizeOfHeader(0)
    , m_bitmapWidth(0)
    , m_bitmapHeight(0)
    , m_numberOfColorPlanes(0)
    , m_numberOfBitsPerPixel(8)
    , m_compressionMethodType(CompressedMethodType::Unknown)
    , m_imageSize(0)
    , m_bitmapSize(0)
    , m_horizontalResolutionPixelInAMeter(0)
    , m_verticalResolutionPixelInAMeter(0)
    , m_numberOfColors(0)
    , m_numberImportantOfColors(0)
    , m_numberOfBytesForDataInRow(0)
    , m_paddingForRowMemoryAlignment(0)
    , m_numberOfBytesPerRowInFile(0)
    , m_bitMaskForValue(0)
    , m_path()
    , m_signature()
    , m_colors()
{}

bool BitmapConfiguration::isValid() const
{
    return isSignatureValid() && isHeaderValid() && isNumberOfColorPlanesValid() && isNumberOfBitsPerPixelValid();
}

bool BitmapConfiguration::isSignatureValid() const
{
    return (m_signature == "BM");
}

bool BitmapConfiguration::isHeaderValid() const
{
    return (m_sizeOfHeader == 40);
}

bool BitmapConfiguration::isNumberOfColorPlanesValid() const
{
    return (m_numberOfColorPlanes == 1);
}

bool BitmapConfiguration::isNumberOfBitsPerPixelValid() const
{
    return (m_numberOfBitsPerPixel == 1) ||
            (m_numberOfBitsPerPixel == 4) ||
            (m_numberOfBitsPerPixel == 8) ||
            (m_numberOfBitsPerPixel == 16) ||
            (m_numberOfBitsPerPixel == 24) ||
            (m_numberOfBitsPerPixel == 32);
}

bool BitmapConfiguration::isCompressedMethodSupported() const
{
    return (m_compressionMethodType == CompressedMethodType::BI_RGB);
}

bool BitmapConfiguration::isPositionWithinTheBitmap(BitmapXY const position) const
{
    return position.getX() < m_bitmapWidth && position.getY() < m_bitmapHeight;
}

bool BitmapConfiguration::isPositionWithinTheBitmap(int x, int y) const
{
    return x < (int)m_bitmapWidth && y < (int)m_bitmapHeight && x >= 0 && y >= 0;
}

CompressedMethodType BitmapConfiguration::getCompressedMethodType() const
{
    return m_compressionMethodType;
}

std::string BitmapConfiguration::getPath() const
{
    return m_path;
}

uint32_t BitmapConfiguration::getPixelArrayAddress() const
{
    return m_pixelArrayAddress;
}

uint32_t BitmapConfiguration::getBitmapWidth() const
{
    return m_bitmapWidth;
}

uint32_t BitmapConfiguration::getBitmapHeight() const
{
    return m_bitmapHeight;
}

uint16_t BitmapConfiguration::getNumberOfBitsPerPixel() const
{
    return m_numberOfBitsPerPixel;
}

uint32_t BitmapConfiguration::getNumberOfBytesPerRowInFile() const
{
    return m_numberOfBytesPerRowInFile;
}

uint32_t BitmapConfiguration::getBitMaskForValue() const
{
    return m_bitMaskForValue;
}

BitmapXY BitmapConfiguration::getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const
{
    return BitmapXY(getXCoordinateWithinTheBitmap(xCoordinate), getYCoordinateWithinTheBitmap(yCoordinate));
}

unsigned int BitmapConfiguration::getXCoordinateWithinTheBitmap(int const coordinate) const
{
    return getCoordinateWithinRange(coordinate, m_bitmapWidth);
}

unsigned int BitmapConfiguration::getYCoordinateWithinTheBitmap(int const coordinate) const
{
    return getCoordinateWithinRange(coordinate, m_bitmapHeight);
}

unsigned int BitmapConfiguration::getCoordinateWithinRange(int const coordinate, int maxLength) const
{
    return (coordinate < 0 || maxLength <= 0) ? 0 : (coordinate >= maxLength) ? maxLength-1 : coordinate;
}

BitmapXY BitmapConfiguration::getUpLeftCornerPoint() const
{
    return BitmapXY(0,0);
}

BitmapXY BitmapConfiguration::getDownRightCornerPoint() const
{
    unsigned int maxX = m_bitmapWidth==0 ? 0 : m_bitmapWidth-1;
    unsigned int maxY = m_bitmapHeight==0 ? 0 : m_bitmapHeight-1;
    return BitmapXY(maxX, maxY);
}

uint32_t BitmapConfiguration::getColorUsingPixelValue(uint32_t const pixelValue) const
{
    uint32_t color(0);
    switch(m_numberOfBitsPerPixel)
    {
    case 1:
    case 2:
    case 4:
    case 8:
        if(pixelValue < m_colors.size())
        {
            color = m_colors[pixelValue];
        }
        break;
    default:
        color = pixelValue;
        break;
    }
    return color;
}

unsigned int BitmapConfiguration::convertPixelsToBytesRoundedToFloor(unsigned int pixels) const
{
    return (pixels*m_numberOfBitsPerPixel)/AlbaBitConstants::BYTE_SIZE_IN_BITS;
}

unsigned int BitmapConfiguration::convertPixelsToBytesRoundedToCeil(unsigned int pixels) const
{
    return ((pixels*m_numberOfBitsPerPixel)+AlbaBitConstants::BYTE_SIZE_IN_BITS-1)/AlbaBitConstants::BYTE_SIZE_IN_BITS;
}

unsigned int BitmapConfiguration::convertBytesToPixels(unsigned int bytes) const
{
    return (bytes*AlbaBitConstants::BYTE_SIZE_IN_BITS)/m_numberOfBitsPerPixel;
}

unsigned int BitmapConfiguration::getNumberOfPixelsForOneByte() const
{
    return convertBytesToPixels(1);
}

unsigned int BitmapConfiguration::getMaximumNumberOfPixelsBeforeOneByte() const
{
    unsigned int numberOfPixelsInOneByte(convertBytesToPixels(1));
    return (numberOfPixelsInOneByte>0) ? numberOfPixelsInOneByte-1 : 0;
}

unsigned int BitmapConfiguration::getMinimumNumberOfBytesForOnePixel() const
{
    unsigned int numberOfBytesInOnePixel(convertPixelsToBytesRoundedToFloor(1));
    return (numberOfBytesInOnePixel>0) ? numberOfBytesInOnePixel : 1;
}

unsigned int BitmapConfiguration::getEstimatedSquareSideInPixels(unsigned int const numberOfBytesToRead) const
{
    // Quadratic equation: side*side*m_numberOfBitsPerPixel
    //+ side*(1+getMinimumNumberOfBytesForOnePixel())*AlbaBitConstants::BYTE_SIZE_IN_BITS
    //- numberOfBytesToRead*AlbaBitConstants::BYTE_SIZE_IN_BITS
    double a = m_numberOfBitsPerPixel;
    double b = (1+getMinimumNumberOfBytesForOnePixel())*AlbaBitConstants::BYTE_SIZE_IN_BITS;
    double c = -1 * static_cast<int>(numberOfBytesToRead*AlbaBitConstants::BYTE_SIZE_IN_BITS);
    unsigned int result(0);
    AlbaNumbers roots(getQuadraticRoots(RootType::RealRootsOnly, AlbaNumber(a), AlbaNumber(b), AlbaNumber(c)));
    if(!roots.empty())
    {
        result = static_cast<unsigned int>(roots.front().getInteger());
    }
    return result;
}

unsigned int BitmapConfiguration::getOneRowSizeInBytesFromPixels(unsigned int const leftPixelInclusive, unsigned int const rightPixelInclusive) const
{
    return getOneRowSizeInBytesFromBytes(convertPixelsToBytesRoundedToFloor(leftPixelInclusive), convertPixelsToBytesRoundedToFloor(rightPixelInclusive));
}

unsigned int BitmapConfiguration::getOneRowSizeInBytesFromBytes(unsigned int const leftByteInclusive, unsigned int const rightByteInclusive) const
{
    return rightByteInclusive-leftByteInclusive+getMinimumNumberOfBytesForOnePixel();
}

Colors BitmapConfiguration::getColorTable() const
{
    return m_colors;
}

void BitmapConfiguration::readBitmap(string const& path)
{
    //https://en.wikipedia.org/wiki/BMP_file_format

    m_path = AlbaLocalPathHandler(path).getFullPath();
    ifstream inputStream(m_path, ios::binary);

    if(inputStream.is_open())
    {
        AlbaFileReader fileReader(inputStream);
        readBitmapFileHeader(fileReader);
        if(isSignatureValid()) // dont check further if its invalid
        {
            readDibHeader(fileReader);
            readColors(fileReader);
            calculateOtherValuesAfterReading();
        }
    }
}
void BitmapConfiguration::readBitmapFileHeader(AlbaFileReader& fileReader)
{
    fileReader.moveLocation(0);    m_signature += fileReader.getCharacter();
    m_signature += fileReader.getCharacter();

    fileReader.moveLocation(2);
    m_fileSize = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(10);
    m_pixelArrayAddress = fileReader.getFourByteSwappedData<uint32_t>();
}

void BitmapConfiguration::readDibHeader(AlbaFileReader& fileReader) // only supports BITMAPINFOHEADER format
{
    fileReader.moveLocation(14);
    m_sizeOfHeader = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(18);
    m_bitmapWidth = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(22);
    m_bitmapHeight = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(26);
    m_numberOfColorPlanes = fileReader.getTwoByteSwappedData<uint16_t>();

    fileReader.moveLocation(28);
    m_numberOfBitsPerPixel = fileReader.getTwoByteSwappedData<uint16_t>();

    m_bitmapSize = static_cast<uint64_t>(m_bitmapWidth) * static_cast<uint64_t>(m_bitmapHeight);

    fileReader.moveLocation(30);
    m_compressionMethodType = determineCompressedMethodType(fileReader.getFourByteData<uint32_t>());

    fileReader.moveLocation(34);
    m_imageSize = fileReader.getFourByteData<uint32_t>();

    fileReader.moveLocation(38);
    m_horizontalResolutionPixelInAMeter = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(42);
    m_verticalResolutionPixelInAMeter = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(46);
    m_numberOfColors = fileReader.getFourByteSwappedData<uint32_t>();

    fileReader.moveLocation(50);
    m_numberImportantOfColors = fileReader.getFourByteSwappedData<uint32_t>();
}

void BitmapConfiguration::readColors(AlbaFileReader& fileReader)
{
    fileReader.moveLocation(54);
    while(fileReader.getCurrentLocation() > 0 && fileReader.getCurrentLocation() < m_pixelArrayAddress)
    {
        m_colors.push_back(fileReader.getFourByteSwappedData<uint32_t>());
    }}

void BitmapConfiguration::calculateOtherValuesAfterReading()
{    m_numberOfBytesForDataInRow = convertPixelsToBytesRoundedToCeil(m_bitmapWidth);
    m_paddingForRowMemoryAlignment = (4 - (m_numberOfBytesForDataInRow%4))%4;
    m_numberOfBytesPerRowInFile = m_numberOfBytesForDataInRow + m_paddingForRowMemoryAlignment;
    m_bitMaskForValue = AlbaBitValueUtilities<uint32_t>::generateOnesWithNumberOfBits(m_numberOfBitsPerPixel);
}

CompressedMethodType BitmapConfiguration::determineCompressedMethodType(uint32_t compressedMethodValue) const
{
    CompressedMethodType compressedMethodType;
    switch(compressedMethodValue)
    {
    case 0: compressedMethodType = CompressedMethodType::BI_RGB; break;
    case 1: compressedMethodType = CompressedMethodType::BI_RLE8; break;
    case 2: compressedMethodType = CompressedMethodType::BI_RLE4; break;
    case 3: compressedMethodType = CompressedMethodType::BI_BITFIELDS; break;
    case 4: compressedMethodType = CompressedMethodType::BI_JPEG; break;
    case 5: compressedMethodType = CompressedMethodType::BI_PNG; break;
    case 6: compressedMethodType = CompressedMethodType::BI_ALPHABITFIELDS; break;
    case 11: compressedMethodType = CompressedMethodType::BI_CMYK; break;
    case 12: compressedMethodType = CompressedMethodType::BI_CMYKRLE8; break;
    case 13: compressedMethodType = CompressedMethodType::BI_CMYKRLE4; break;
    default: compressedMethodType = CompressedMethodType::Unknown; break;
    }
    return compressedMethodType;
}

bool areBitmapConfigurationsCompatibleForChangingPixelData(BitmapConfiguration const& configuration1, BitmapConfiguration const& configuration2)
{
    return configuration1.getNumberOfBitsPerPixel() == configuration2.getNumberOfBitsPerPixel() &&
            configuration1.getBitmapHeight() == configuration2.getBitmapHeight() &&
            configuration1.getBitmapWidth() == configuration2.getBitmapWidth();
}

}

}
