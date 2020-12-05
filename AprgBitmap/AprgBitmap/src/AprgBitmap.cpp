#include "AprgBitmap.hpp"

using namespace std;

namespace alba
{

AprgBitmap::AprgBitmap(string const& path)
{
    m_configuration.readBitmap(path);
}

AprgBitmapConfiguration AprgBitmap::getConfiguration() const
{
    return m_configuration;
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFileWholeBitmap() const
{
    return getSnippetReadFromFile(getUpLeftCornerPoint(), getDownRightCornerPoint());
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFileWithOutOfRangeCoordinates(int outOfRangeLeft, int outOfRangeTop, int outOfRangeRight, int outOfRangeBottom) const
{
    if(outOfRangeLeft > outOfRangeRight)
    {
        swap(outOfRangeLeft, outOfRangeRight);
    }
    if(outOfRangeTop > outOfRangeBottom)
    {
        swap(outOfRangeTop, outOfRangeBottom);
    }
    BitmapXY const topLeftCorner = getPointWithinTheBitmap(outOfRangeLeft, outOfRangeTop);
    BitmapXY const bottomRightCorner = getPointWithinTheBitmap(outOfRangeRight, outOfRangeBottom);
    return getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY const center, unsigned int const numberOfBytesToRead) const
{
    AprgBitmapSnippet snippet;
    if(m_configuration.isPositionWithinTheBitmap(center))
    {
        BitmapXY topLeftCorner;
        BitmapXY bottomRightCorner;
        calculateNewCornersBasedOnCenterAndNumberOfBytes(topLeftCorner, bottomRightCorner, center, numberOfBytesToRead);
        snippet = getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
    }
    return snippet;
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const
{
    AprgBitmapSnippet snippet;
    if(m_configuration.isPositionWithinTheBitmap(topLeftCorner) && m_configuration.isPositionWithinTheBitmap(bottomRightCorner))
    {
        ifstream inputStream(m_configuration.getPath(), ios::binary);
        AlbaFileReader fileReader(inputStream);
        if(inputStream.is_open())
        {
            int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(topLeftCorner.getX());
            int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(bottomRightCorner.getX());
            int offsetInYForStart = m_configuration.getBitmapHeight()-topLeftCorner.getY()-1;
            int offsetInYForEnd = m_configuration.getBitmapHeight()-bottomRightCorner.getY()-1;
            int numberOfBytesToBeCopiedForX = m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd);

            int startPixelInX = getXCoordinateWithinTheBitmap((int)m_configuration.convertBytesToPixels(byteOffsetInXForStart));
            int endPixelInX = getXCoordinateWithinTheBitmap((int)m_configuration.convertBytesToPixels(byteOffsetInXForEnd)+m_configuration.getMaximumNumberOfPixelsBeforeOneByte());

            snippet = AprgBitmapSnippet(BitmapXY(startPixelInX, topLeftCorner.getY()), BitmapXY(endPixelInX, bottomRightCorner.getY()), m_configuration);

            for(int y=offsetInYForStart; y>=offsetInYForEnd; y--)
            {
                unsigned long long fileOffsetForStart = m_configuration.getPixelArrayAddress()+((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile()*y)+byteOffsetInXForStart;
                fileReader.moveLocation(fileOffsetForStart);
                fileReader.saveDataToMemoryBuffer(snippet.getPixelDataReference(), numberOfBytesToBeCopiedForX);
            }
        }
    }
    return snippet; //RVO takes care of this
}

void AprgBitmap::setSnippetWriteToFile(AprgBitmapSnippet const& snippet) const
{
    if(m_configuration == snippet.getConfiguration())
    {
        if(m_configuration.isPositionWithinTheBitmap(snippet.getTopLeftCorner()) && m_configuration.isPositionWithinTheBitmap(snippet.getBottomRightCorner()))
        {
            fstream streamFile(m_configuration.getPath(), fstream::in | fstream::out | fstream::binary);
            if(streamFile.is_open())
            {
                int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(snippet.getTopLeftCorner().getX());
                int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(snippet.getBottomRightCorner().getX());
                int offsetInYForStart = m_configuration.getBitmapHeight()-snippet.getTopLeftCorner().getY()-1;
                int offsetInYForEnd = m_configuration.getBitmapHeight()-snippet.getBottomRightCorner().getY()-1;
                int numberOfBytesToBeCopiedForX = m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd);
                unsigned int snippetSize = snippet.getPixelDataSize();
                unsigned int snippetIndex = 0;

                for(int y=offsetInYForStart; y>=offsetInYForEnd && snippetIndex<snippetSize; y--)
                {
                    unsigned long long fileOffsetForStart = m_configuration.getPixelArrayAddress()+((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile()*y)+byteOffsetInXForStart;
                    char const* pixelDataPointer = (char const*)snippet.getPixelDataConstReference().getConstantBufferPointer()+snippetIndex;
                    streamFile.seekg(fileOffsetForStart, streamFile.beg);
                    streamFile.write(pixelDataPointer, numberOfBytesToBeCopiedForX);
                    snippetIndex += numberOfBytesToBeCopiedForX;
                }
                streamFile.flush();
            }
        }
    }
}

BitmapXY AprgBitmap::getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const
{
    return BitmapXY(getXCoordinateWithinTheBitmap(xCoordinate), getYCoordinateWithinTheBitmap(yCoordinate));
}

unsigned int AprgBitmap::getXCoordinateWithinTheBitmap(int const coordinate) const
{
    return getCoordinateWithinRange(coordinate, m_configuration.getBitmapWidth());
}

unsigned int AprgBitmap::getYCoordinateWithinTheBitmap(int const coordinate) const
{
    return getCoordinateWithinRange(coordinate, m_configuration.getBitmapHeight());
}

unsigned int AprgBitmap::getCoordinateWithinRange(int const coordinate, int maxLength) const
{
    return (coordinate < 0) ? 0 : (coordinate >= maxLength) ? maxLength-1 : coordinate;
}

BitmapXY AprgBitmap::getUpLeftCornerPoint() const
{
    return BitmapXY(0,0);
}

BitmapXY AprgBitmap::getDownRightCornerPoint() const
{
    return BitmapXY(m_configuration.getBitmapWidth()-1, m_configuration.getBitmapHeight()-1);
}

void AprgBitmap::calculateNewCornersBasedOnCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const
{
    int side(m_configuration.estimateSquareSideInPixels(numberOfBytes));
    int halfSide(side/2);
    int left(getXCoordinateWithinTheBitmap(center.getX()-halfSide));
    int right(getXCoordinateWithinTheBitmap(center.getX()+halfSide));
    adjustToTargetLength(left, right, side, m_configuration.getBitmapWidth());

    int xSizeInBytes(m_configuration.getOneRowSizeInBytesFromPixels(left, right));
    xSizeInBytes = (xSizeInBytes > 0) ? xSizeInBytes : 1;
    int ySizeInBytes(numberOfBytes/xSizeInBytes);
    int halfYSizeInBytes(ySizeInBytes/2);
    int top(getYCoordinateWithinTheBitmap(center.getY()-halfYSizeInBytes));
    int bottom(getYCoordinateWithinTheBitmap(center.getY()+halfYSizeInBytes));
    adjustToTargetLength(top, bottom, ySizeInBytes, m_configuration.getBitmapHeight());

    topLeftCorner.setX(left);
    topLeftCorner.setY(top);
    bottomRightCorner.setX(right);
    bottomRightCorner.setY(bottom);
}

void AprgBitmap::adjustToTargetLength(int & low, int & high, int const targetLength, unsigned int const maxLength) const
{
    if(high-low+1 < (int)targetLength)
    {
        int additionalSizeInX = targetLength - (high-low+1);
        if((low - additionalSizeInX) >= 0)
        {
            low = low - additionalSizeInX;
        }
        else if((unsigned int)(high + additionalSizeInX) < maxLength)
        {
            high = high + additionalSizeInX;
        }
    }
}


}
