#include "AprgBitmap.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <cmath>
#include <fstream>
#include <sstream>

#include <iostream>

using namespace std;

namespace alba
{
AprgBitmap::XY::XY()
    : x(0)
    , y(0){}

AprgBitmap::XY::XY(unsigned int xValue, unsigned int yValue)
    : x(xValue)
    , y(yValue)
{}

bool AprgBitmap::XY::operator==(AprgBitmap::XY const& xy) const
{
    return (x == xy.x) && (y == xy.y);
}

string AprgBitmap::XY::getDisplayableString() const
{
    stringstream ss;
    ss<<"("<<x<<","<<y<<")";
    return ss.str();
}


AprgBitmap::RectangularPixelsSnippet::RectangularPixelsSnippet()
    : noPositionIsAddedYet(true)
{}

void AprgBitmap::RectangularPixelsSnippet::addPosition(AprgBitmap::XY const position)
{
    if(noPositionIsAddedYet)
    {
        topLeftCorner = position;
        bottomRightCorner = position;
        noPositionIsAddedYet = false;
    }
    else
    {
        if(topLeftCorner.x > position.x)
        {
            topLeftCorner.x = position.x;
        }
        if(topLeftCorner.y > position.y)
        {
            topLeftCorner.y = position.y;
        }
        if(bottomRightCorner.x < position.x)
        {
            bottomRightCorner.x = position.x;
        }
        if(bottomRightCorner.y < position.y)
        {
            bottomRightCorner.y = position.y;
        }
    }
}

void AprgBitmap::RectangularPixelsSnippet::setCorners(AprgBitmap::XY const topLeftCornerPosition, AprgBitmap::XY const bottomRightCornerPosition)
{
    topLeftCorner = topLeftCornerPosition;
    bottomRightCorner = bottomRightCornerPosition;
}

void AprgBitmap::RectangularPixelsSnippet::clear()
{
    pixelData.clear();
    noPositionIsAddedYet = true;
}
unsigned int AprgBitmap::RectangularPixelsSnippet::getDeltaX() const
{
    return bottomRightCorner.x - topLeftCorner.x;}

unsigned int AprgBitmap::RectangularPixelsSnippet::getDeltaY() const
{
    return bottomRightCorner.y - topLeftCorner.y;
}

unsigned int AprgBitmap::RectangularPixelsSnippet::getNumberOfPixelsInSnippet() const
{
    return getDeltaX()*getDeltaY();
}

bool AprgBitmap::RectangularPixelsSnippet::isPositionInsideTheSnippet(AprgBitmap::XY const position) const
{
    return topLeftCorner.x <= position.x && topLeftCorner.y <= position.y && bottomRightCorner.x >= position.x && bottomRightCorner.y >= position.y;}

AprgBitmap::AprgBitmap(string const& path)
    : m_maximumMemoryConsumption(DEFAULT_MAXIMUM_MEMORY_CONSUMPTION)
    , m_path(AlbaLocalPathHandler(path).getFullPath())
{
    loadBitmapHeaders();
}
bool AprgBitmap::isValid() const
{
    return isSignatureValid() && isHeaderValid() && isNumberOfColorPlanesValid() && isNumberOfBitsPerPixelValid();}

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

bool AprgBitmap::isPositionWithinTheBitmap(AprgBitmap::XY const position) const
{
    return position.x < m_bitmapWidth && position.y < m_bitmapHeight;
}

BitmapCompressedMethodType AprgBitmap::getCompressedMethodType() const
{
    return m_compressionMethodType;
}

unsigned int AprgBitmap::getMemoryConsumption() const
{
    return m_snippetStoredInMemory.pixelData.getSize();
}

AprgBitmap::XY AprgBitmap::getPositionOfTopLeftCornerInMemory() const
{
    return m_snippetStoredInMemory.topLeftCorner;}

AprgBitmap::XY AprgBitmap::getPositionOfBottomRightCornerInMemory() const
{
    return m_snippetStoredInMemory.bottomRightCorner;
}

unsigned int AprgBitmap::getPixelInSnippet(AprgBitmap::XY const position) const
{
    unsigned int result(0);
    if(isPositionWithinTheBitmap(position))
    {
        unsigned int xPartInIndex = convertPixelsToBytesRoundToFloor(position.x)-convertPixelsToBytesRoundToFloor(m_snippetStoredInMemory.topLeftCorner.x);
        unsigned int oneRowOffset = convertPixelsToBytesRoundToFloor(m_snippetStoredInMemory.bottomRightCorner.x)-convertPixelsToBytesRoundToFloor(m_snippetStoredInMemory.topLeftCorner.x)+getMinimumNumberOfBytesForOnePixel();
        unsigned int yPartInIndex = oneRowOffset*(position.y-m_snippetStoredInMemory.topLeftCorner.y);
        unsigned int index = xPartInIndex + yPartInIndex;
        unsigned char const* reader = (unsigned char const*)m_snippetStoredInMemory.pixelData.getConstantBufferPointer();
        if(m_numberOfBitsPerPixel <= 8)
        {
            result = getPixelInSnippetForPixelInAByte(reader, index, position);
        }
        else
        {
            result = getPixelInSnippetForMultipleBytePixels(reader, index);
        }
    }
    return result;
}

unsigned int AprgBitmap::getColorUsingPixelValue(unsigned int pixelValue) const
{
    unsigned int color(0);
    switch(m_numberOfBitsPerPixel)
    {
    case 1:
    case 2:
    case 4:
    case 8:
        if(pixelValue<m_colors.size())
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

AprgBitmap::ColorTable AprgBitmap::getColorTable() const
{
    return m_colors;
}

AprgBitmap::PixelData AprgBitmap::getPixelsInMemory() const
{
    return m_snippetStoredInMemory.pixelData;
}

void AprgBitmap::setMaximumMemoryConsumption(unsigned int const maximumMemoryConsumption)
{
    m_maximumMemoryConsumption = maximumMemoryConsumption;
}

unsigned int AprgBitmap::getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY const position)
{
    unsigned int result(0);
    if(isPositionWithinTheBitmap(position))
    {
        if(!m_snippetStoredInMemory.isPositionInsideTheSnippet(position))
        {
            addPositionInSnippet(position);
            cout<<"m_snippetStoredInMemory.topLeftCorner"<<m_snippetStoredInMemory.topLeftCorner.getDisplayableString()<<endl;
            cout<<"m_snippetStoredInMemory.bottomRightCorner"<<m_snippetStoredInMemory.bottomRightCorner.getDisplayableString()<<endl;
            loadPixels();
            cout<<"m_snippetStoredInMemory.topLeftCorner"<<m_snippetStoredInMemory.topLeftCorner.getDisplayableString()<<endl;
            cout<<"m_snippetStoredInMemory.bottomRightCorner"<<m_snippetStoredInMemory.bottomRightCorner.getDisplayableString()<<endl;
            cout<<"m_bitmapWidth"<<m_bitmapWidth<<endl;
            cout<<"m_bitmapHeight"<<m_bitmapHeight<<endl;
        }
        result = getPixelInSnippet(position);
    }
    return result;
}

void AprgBitmap::addPositionInSnippet(AprgBitmap::XY const position)
{
    if(isPositionWithinTheBitmap(position))
    {
        m_snippetStoredInMemory.addPosition(position);
        if(isSnippetBeyondTheMaximumMemoryAllowed())
        {
            updateCornersInSnippetForMemoryConsumptionUsage(position);
        }
    }
}

void AprgBitmap::loadPixels()
{
    ifstream inputStream(m_path, ios::binary);
    AlbaFileReader fileReader(inputStream);
    m_snippetStoredInMemory.pixelData.clear();

    int byteOffsetInXForStart = (int)convertPixelsToBytesRoundToFloor(m_snippetStoredInMemory.topLeftCorner.x);
    int byteOffsetInXForEnd = (int)convertPixelsToBytesRoundToFloor(m_snippetStoredInMemory.bottomRightCorner.x);
    int offsetInYForStart = m_bitmapHeight-m_snippetStoredInMemory.topLeftCorner.y-1;
    int offsetInYForEnd = m_bitmapHeight-m_snippetStoredInMemory.bottomRightCorner.y-1;
    int numberOfBytesToBeCopiedForX = byteOffsetInXForEnd - byteOffsetInXForStart + getMinimumNumberOfBytesForOnePixel();

    for(int y=offsetInYForStart; y>=offsetInYForEnd; y--)
    {
        unsigned long long fileOffsetForStart = m_pixelArrayAddress+((unsigned long long)m_numberOfBytesPerRow*y)+byteOffsetInXForStart;
        fileReader.moveLocation(fileOffsetForStart);
        fileReader.saveDataToMemoryBuffer(m_snippetStoredInMemory.pixelData, numberOfBytesToBeCopiedForX);
    }

    m_snippetStoredInMemory.topLeftCorner.x = convertBytesToPixels(byteOffsetInXForStart);
    m_snippetStoredInMemory.bottomRightCorner.x = convertBytesToPixels(byteOffsetInXForEnd)+getMaximumNumberOfPixelsBeforeOneByte();
}

void AprgBitmap::updateCornersInSnippetForMemoryConsumptionUsage(AprgBitmap::XY const center)
{
   computeCornersForMaximumMemory(m_snippetStoredInMemory.topLeftCorner, m_snippetStoredInMemory.bottomRightCorner, center);
}

void AprgBitmap::clearSnippetInMemory(){
    m_snippetStoredInMemory.clear();
}

unsigned int AprgBitmap::getPixelInSnippetForPixelInAByte(unsigned char const* reader, unsigned int index, AprgBitmap::XY const position) const
{
    unsigned int result(0);
    if(index < m_snippetStoredInMemory.pixelData.getSize())
    {
        result = (unsigned int)(*(reader+index));
        unsigned int numberOfPixelsInOneByte = convertBytesToPixels(1);
        unsigned int positionRemainder = position.x%numberOfPixelsInOneByte;
        unsigned int loopAround = numberOfPixelsInOneByte-positionRemainder-1;
        unsigned int shiftValue = m_numberOfBitsPerPixel*loopAround;
        result = (result >> shiftValue) & AlbaBitManipulation<unsigned int>::generateOnesWithNumberOfBits(m_numberOfBitsPerPixel);
    }
    return result;
}

unsigned int AprgBitmap::getPixelInSnippetForMultipleBytePixels(unsigned char const* reader, unsigned int index) const
{
    unsigned int result(0);
    unsigned int minimumNumberOfBytesForOnePixel = getMinimumNumberOfBytesForOnePixel();
    if(index+minimumNumberOfBytesForOnePixel-1 < m_snippetStoredInMemory.pixelData.getSize())
    {
        for(int indexForMultipleBytePixel=minimumNumberOfBytesForOnePixel-1; indexForMultipleBytePixel>=0; indexForMultipleBytePixel--)
        {
            result <<= BYTE_SIZE_IN_BITS;
            result = result | (unsigned int)(*(reader+index+indexForMultipleBytePixel));
        }
    }
    return result;
}

void AprgBitmap::loadBitmapHeaders()
{
    //https://en.wikipedia.org/wiki/BMP_file_format
    ifstream inputStream(m_path, ios::binary);
    AlbaFileReader fileReader(inputStream);
    loadBitmapFileHeader(fileReader);
    loadDibHeader(fileReader);
    loadColorTable(fileReader);
    calculateOtherValues();
}

void AprgBitmap::loadBitmapFileHeader(AlbaFileReader& fileReader)
{
    fileReader.moveLocation(0);
    m_signature += fileReader.getCharacter();
    m_signature += fileReader.getCharacter();

    fileReader.moveLocation(2);
    m_fileSize = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(10);
    m_pixelArrayAddress = fileReader.getFourByteSwappedData<unsigned int>();
}

void AprgBitmap::loadDibHeader(AlbaFileReader& fileReader) // only supports BITMAPINFOHEADER format
{
    fileReader.moveLocation(14);
    m_sizeOfHeader = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(18);
    m_bitmapWidth = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(22);
    m_bitmapHeight = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(26);
    m_numberOfColorPlanes = fileReader.getTwoByteSwappedData<unsigned int>();

    fileReader.moveLocation(28);
    m_numberOfBitsPerPixel = fileReader.getTwoByteSwappedData<unsigned int>();

    m_bitmapSize = (unsigned long)m_bitmapWidth*m_bitmapHeight;

    fileReader.moveLocation(30);
    m_compressionMethodType = determineCompressedMethodType(fileReader.getFourByteData<unsigned int>());

    fileReader.moveLocation(34);
    m_imageSize = fileReader.getFourByteData<unsigned int>();

    fileReader.moveLocation(38);
    m_horizontalResolutionPixelInAMeter = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(42);
    m_verticalResolutionPixelInAMeter = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(46);
    m_numberOfColors = fileReader.getFourByteSwappedData<unsigned int>();

    fileReader.moveLocation(50);
    m_numberImportantOfColors = fileReader.getFourByteSwappedData<unsigned int>();
}

void AprgBitmap::loadColorTable(AlbaFileReader& fileReader)
{
    fileReader.moveLocation(54);
    while(fileReader.getCurrentLocation()<m_pixelArrayAddress)
    {
        m_colors.push_back(fileReader.getFourByteSwappedData<unsigned int>());
    }
}

void AprgBitmap::calculateOtherValues()
{
    m_numberOfBytesForDataInRow = convertPixelsToBytesRoundToCeil(m_bitmapWidth);
    m_paddingForRowMemoryAlignment = (4 - (m_numberOfBytesForDataInRow%4))%4;
    m_numberOfBytesPerRow = m_numberOfBytesForDataInRow + m_paddingForRowMemoryAlignment;
}

unsigned int AprgBitmap::convertPixelsToBytesRoundToFloor(unsigned int pixels) const
{
    return (pixels*m_numberOfBitsPerPixel)/BYTE_SIZE_IN_BITS;
}

unsigned int AprgBitmap::convertPixelsToBytesRoundToCeil(unsigned int pixels) const
{
    return ((pixels*m_numberOfBitsPerPixel)+BYTE_SIZE_IN_BITS-1)/BYTE_SIZE_IN_BITS;
}

unsigned int AprgBitmap::convertBytesToPixels(unsigned int bytes) const
{
    return (bytes*BYTE_SIZE_IN_BITS)/m_numberOfBitsPerPixel;
}

unsigned int AprgBitmap::getMaximumNumberOfPixelsBeforeOneByte() const
{
    unsigned int numberOfPixelsInOneByte(convertBytesToPixels(1));
    return (numberOfPixelsInOneByte>0) ? numberOfPixelsInOneByte-1 : 0;
}

unsigned int AprgBitmap::getMinimumNumberOfBytesForOnePixel() const
{
    unsigned int numberOfBytesInOnePixel(convertPixelsToBytesRoundToFloor(1));
    return (numberOfBytesInOnePixel>0) ? numberOfBytesInOnePixel : 1;
}

bool AprgBitmap::isSnippetBeyondTheMaximumMemoryAllowed() const
{
    unsigned long long possibleSnippetSize = convertPixelsToBytesRoundToCeil(m_snippetStoredInMemory.getNumberOfPixelsInSnippet());
    return possibleSnippetSize>m_maximumMemoryConsumption || m_snippetStoredInMemory.pixelData.getSize()>m_maximumMemoryConsumption;
}

AprgBitmap::XY AprgBitmap::computeSquareSideSizeForMaximumMemory() const
{
    unsigned int numberOfPixels = (unsigned int)round(convertBytesToPixels(m_maximumMemoryConsumption));
    unsigned int xSize = convertPixelsToBytesRoundToCeil((unsigned int)sqrt((double)numberOfPixels));
    unsigned int ySize =  m_maximumMemoryConsumption/xSize;
    cout<<"numberOfPixels"<<numberOfPixels<<endl;
    cout<<"xSize"<<xSize<<endl;
    cout<<"ySize"<<ySize<<endl;

    //think of a better way!!!!//this is your to do
    return XY(xSize, ySize);
}

void AprgBitmap::computeCornersForMaximumMemory(AprgBitmap::XY & topLeftCornerPosition, AprgBitmap::XY & bottomRightCornerPosition, AprgBitmap::XY const center) const
{
   AprgBitmap::XY rectangularSize(computeSquareSideSizeForMaximumMemory());
   int sideLeftInX = center.x - (rectangularSize.x/2);
   int sideTopInY = center.y - (rectangularSize.y/2);
   int sideRightInX = center.x + (rectangularSize.x/2);
   int sideBottomInY = center.y + (rectangularSize.y/2);
   sideLeftInX = (sideLeftInX < 0) ? 0 : sideLeftInX;
   sideTopInY = (sideTopInY < 0) ? 0 : sideTopInY;
   sideRightInX = ((unsigned int)sideRightInX >= m_bitmapWidth) ? m_bitmapWidth-1 : sideRightInX;
   sideBottomInY = ((unsigned int)sideBottomInY >= m_bitmapHeight) ? m_bitmapHeight-1 : sideBottomInY;

   if(sideRightInX-sideLeftInX+1 < (int)rectangularSize.x)
   {
       int additionalSizeInX = rectangularSize.x - (sideRightInX-sideLeftInX+1);
       if((sideLeftInX - additionalSizeInX) >= 0)
       {
           sideLeftInX = sideLeftInX - additionalSizeInX;
       }
       else if((unsigned int)(sideRightInX + additionalSizeInX) < m_bitmapWidth)
       {
           sideRightInX = sideRightInX + additionalSizeInX;
       }
   }

   if(sideBottomInY-sideTopInY+1 < (int)rectangularSize.y)
   {
       int additionalSizeInY = rectangularSize.y - (sideBottomInY-sideTopInY+1);
       if((sideTopInY - additionalSizeInY) >= 0)
       {
           sideTopInY = sideTopInY - additionalSizeInY;
       }
       else if((unsigned int)(sideBottomInY + additionalSizeInY) < m_bitmapHeight)
       {
           sideBottomInY = sideBottomInY + additionalSizeInY;
       }
   }
   topLeftCornerPosition.x = (unsigned int) sideLeftInX;
   topLeftCornerPosition.y = (unsigned int) sideTopInY;
   bottomRightCornerPosition.x = (unsigned int) sideRightInX;
   bottomRightCornerPosition.y = (unsigned int) sideBottomInY;
}

BitmapCompressedMethodType AprgBitmap::determineCompressedMethodType(unsigned int compressedMethodValue) const
{
    BitmapCompressedMethodType compressedMethodType;    switch(compressedMethodValue)
    {
    case 0: compressedMethodType = BitmapCompressedMethodType::BI_RGB; break;
    case 1: compressedMethodType = BitmapCompressedMethodType::BI_RLE8; break;    case 2: compressedMethodType = BitmapCompressedMethodType::BI_RLE4; break;
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
