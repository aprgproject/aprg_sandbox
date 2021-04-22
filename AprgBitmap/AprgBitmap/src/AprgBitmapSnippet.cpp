#include "AprgBitmapSnippet.hpp"

#include <Bit/AlbaBitConstants.hpp>
#include <Bit/AlbaBitManipulation.hpp>

using namespace std;

namespace alba
{

AprgBitmapSnippet::AprgBitmapSnippet()
{}

AprgBitmapSnippet::AprgBitmapSnippet(BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition, AprgBitmapConfiguration const& configuration)
    : m_topLeftCorner(topLeftCornerPosition)
    , m_bottomRightCorner(bottomRightCornerPosition)
    , m_configuration(configuration)
{
    loadPixelDataFromFileInConfiguration();
}

AprgBitmapConfiguration AprgBitmapSnippet::getConfiguration() const
{    return m_configuration;
}

bool AprgBitmapSnippet::isPositionInsideTheSnippet(BitmapXY const position) const
{
    return m_topLeftCorner.getX() <= position.getX() && m_topLeftCorner.getY() <= position.getY() && m_bottomRightCorner.getX() >= position.getX() && m_bottomRightCorner.getY() >= position.getY();
}
BitmapXY AprgBitmapSnippet::getTopLeftCorner() const
{
    return m_topLeftCorner;}

BitmapXY AprgBitmapSnippet::getBottomRightCorner() const
{
    return m_bottomRightCorner;
}

unsigned int AprgBitmapSnippet::getDeltaX() const
{
    return m_bottomRightCorner.getX() - m_topLeftCorner.getX();}

unsigned int AprgBitmapSnippet::getDeltaY() const
{    return m_bottomRightCorner.getY() - m_topLeftCorner.getY();
}

unsigned int AprgBitmapSnippet::getNumberOfPixelsInSnippet() const
{
    return getDeltaX()*getDeltaY();
}

unsigned int AprgBitmapSnippet::getPixelDataSize() const
{
    return m_pixelData.getSize();
}

void AprgBitmapSnippet::clear()
{
    m_pixelData.clear();
}

void AprgBitmapSnippet::clearAndPutOneColorOnWholeSnippet(unsigned char const colorByte)
{
    clear();

    int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(m_topLeftCorner.getX());
    int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(m_bottomRightCorner.getX());
    int numberOfBytesToBeCopiedForX = m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd);
    int yDifference = m_bottomRightCorner.getY()-m_topLeftCorner.getY()+1;
    m_pixelData.resize(numberOfBytesToBeCopiedForX*yDifference, colorByte);
}

void AprgBitmapSnippet::loadPixelDataFromFileInConfiguration()
{
    if(m_configuration.isPositionWithinTheBitmap(m_topLeftCorner) && m_configuration.isPositionWithinTheBitmap(m_bottomRightCorner))
    {
        ifstream inputStream(m_configuration.getPath(), ios::binary);
        AlbaFileReader fileReader(inputStream);
        if(inputStream.is_open())
        {
            int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(m_topLeftCorner.getX());
            int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(m_bottomRightCorner.getX());
            int offsetInYForStart = m_configuration.getBitmapHeight()-m_topLeftCorner.getY()-1;
            int offsetInYForEnd = m_configuration.getBitmapHeight()-m_bottomRightCorner.getY()-1;
            int numberOfBytesToBeCopiedForX = m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd);

            for(int y=offsetInYForStart; y>=offsetInYForEnd; y--)
            {
                unsigned long long fileOffsetForStart = m_configuration.getPixelArrayAddress()+((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile()*y)+byteOffsetInXForStart;
                fileReader.moveLocation(fileOffsetForStart);
                fileReader.saveDataToMemoryBuffer(m_pixelData, numberOfBytesToBeCopiedForX);
            }
        }
    }
}

PixelData& AprgBitmapSnippet::getPixelDataReference()
{
    return m_pixelData;}

PixelData const& AprgBitmapSnippet::getPixelDataConstReference() const
{
    return m_pixelData;}

unsigned int AprgBitmapSnippet::getPixelAt(BitmapXY const position) const
{
    unsigned int result(0);
    if(isPositionInsideTheSnippet(position))
    {
        unsigned int index = calculateIndexInPixelData(position);
        unsigned char const* reader = (unsigned char const*)m_pixelData.getConstantBufferPointer();        if(m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS)
        {
            result = getPixelAtForPixelInAByte(reader, index, position);
        }        else
        {
            result = getPixelAtForMultipleBytePixels(reader, index);
        }
    }
    return result;
}

unsigned int AprgBitmapSnippet::getColorAt(BitmapXY const position) const
{
    return m_configuration.getColorUsingPixelValue(getPixelAt(position));
}

bool AprgBitmapSnippet::isBlackAt(BitmapXY const position) const //this is the only assumption, colors can depend on numberofbits of pixel and color table
{
    return (m_configuration.getColorUsingPixelValue(getPixelAt(position))==0x00000000);
}

void AprgBitmapSnippet::setPixelAt(BitmapXY const position, unsigned int const value)
{
    if(isPositionInsideTheSnippet(position))
    {
        unsigned int index = calculateIndexInPixelData(position);
        unsigned char* writer = (unsigned char *)m_pixelData.getConstantBufferPointer();        if(m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS)
        {
            setPixelAtForPixelInAByte(writer, index, position, value);
        }        else
        {
            setPixelAtForMultipleBytePixels(writer, index, value);
        }
    }
}

void AprgBitmapSnippet::traverse(TraverseFunction const& traverseFunction) const
{
    for(unsigned int x=m_topLeftCorner.getX(); x<=m_bottomRightCorner.getX(); x++)
    {
        for(unsigned int y=m_topLeftCorner.getY(); y<=m_bottomRightCorner.getY(); y++)
        {
            BitmapXY currentPoint(x,y);
            traverseFunction(currentPoint, getPixelAt(currentPoint));
        }
    }
}

void AprgBitmapSnippet::traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction)
{
    for(unsigned int x=m_topLeftCorner.getX(); x<=m_bottomRightCorner.getX(); x++)
    {
        for(unsigned int y=m_topLeftCorner.getY(); y<=m_bottomRightCorner.getY(); y++)
        {
            BitmapXY currentPoint(x,y);
            unsigned int colorToBeUpdated(getPixelAt(currentPoint));
            traverseAndUpdateFunction(currentPoint, colorToBeUpdated);
            setPixelAt(currentPoint, colorToBeUpdated);
        }
    }
}

unsigned int AprgBitmapSnippet::calculateShiftValue(BitmapXY const position) const
{
    unsigned int numberOfPixelsInOneByte = m_configuration.getNumberOfPixelsForOneByte();    unsigned int numberOfBitsPerPixel = m_configuration.getNumberOfBitsPerPixel();
    unsigned int positionRemainder = position.getX()%numberOfPixelsInOneByte;
    unsigned int loopAround = numberOfPixelsInOneByte-positionRemainder-1;
    return numberOfBitsPerPixel*loopAround;}

unsigned int AprgBitmapSnippet::calculateIndexInPixelData(BitmapXY const position) const
{
    unsigned int xPartInIndex = m_configuration.convertPixelsToBytesRoundToFloor(position.getX())-m_configuration.convertPixelsToBytesRoundToFloor(m_topLeftCorner.getX());
    unsigned int oneRowOffset = m_configuration.getOneRowSizeInBytesFromPixels(m_topLeftCorner.getX(), m_bottomRightCorner.getX());
    unsigned int yPartInIndex = oneRowOffset*(position.getY()-m_topLeftCorner.getY());
    return xPartInIndex + yPartInIndex;
}

unsigned int AprgBitmapSnippet::getPixelAtForPixelInAByte(unsigned char const* reader, unsigned int const index, BitmapXY const position) const
{
    unsigned int result(0);
    if(index < m_pixelData.getSize())
    {
        result = (unsigned int)(*(reader+index));
        unsigned int shiftValue = calculateShiftValue(position);
        result = (result >> shiftValue) & m_configuration.getBitMaskForValue();
    }
    return result;
}

unsigned int AprgBitmapSnippet::getPixelAtForMultipleBytePixels(unsigned char const* reader, unsigned int const index) const
{
    unsigned int result(0);
    unsigned int minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if(index+minimumNumberOfBytesForOnePixel-1 < m_pixelData.getSize())
    {
        for(int indexForMultipleBytePixel=minimumNumberOfBytesForOnePixel-1; indexForMultipleBytePixel>=0; indexForMultipleBytePixel--)
        {
            result <<= AlbaBitConstants::BYTE_SIZE_IN_BITS;
            result = result | (unsigned int)(*(reader+index+indexForMultipleBytePixel));
        }
    }
    return result;
}

void AprgBitmapSnippet::setPixelAtForPixelInAByte(unsigned char* writer, unsigned int const index, BitmapXY const position, unsigned int const value)
{
    if(index < m_pixelData.getSize())
    {
        unsigned int oldValue = (unsigned int)(*(writer+index));
        unsigned int shiftValue = calculateShiftValue(position);
        unsigned int replacePart = (m_configuration.getBitMaskForValue() & value) << shiftValue;
        unsigned int retainMask = (m_configuration.getBitMaskForValue() << shiftValue) ^ AlbaBitManipulation<unsigned int>::getAllBitsAsserted();
        unsigned int retainPart = (retainMask & oldValue);
        *(writer+index) = replacePart | retainPart;
    }
}

void AprgBitmapSnippet::setPixelAtForMultipleBytePixels(unsigned char* writer, unsigned int const index, unsigned int const value)
{
    unsigned int valueToSave(value);
    unsigned int minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if(index+minimumNumberOfBytesForOnePixel-1 < m_pixelData.getSize())
    {
        for(int indexForMultipleBytePixel=0; indexForMultipleBytePixel<(int)minimumNumberOfBytesForOnePixel; indexForMultipleBytePixel++)
        {
            *(writer+index+indexForMultipleBytePixel) = valueToSave & AlbaBitConstants::BYTE_MASK;
            valueToSave >>= AlbaBitConstants::BYTE_SIZE_IN_BITS;
        }
    }
}

}
