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

AprgBitmapSnippet AprgBitmap::createColorFilledSnippetWithSizeOfWholeBitmap(unsigned char const colorByte) const
{
    AprgBitmapSnippet snippet(m_configuration.getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint(), m_configuration);
    snippet.clearAndPutOneColorOnWholeSnippet(colorByte);
    return snippet;
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFileWholeBitmap() const
{
    return getSnippetReadFromFile(m_configuration.getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint());
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
    BitmapXY const topLeftCorner = m_configuration.getPointWithinTheBitmap(outOfRangeLeft, outOfRangeTop);
    BitmapXY const bottomRightCorner = m_configuration.getPointWithinTheBitmap(outOfRangeRight, outOfRangeBottom);
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
    int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(topLeftCorner.getX());
    int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(bottomRightCorner.getX());
    int startPixelInX = m_configuration.getXCoordinateWithinTheBitmap((int)m_configuration.convertBytesToPixels(byteOffsetInXForStart));
    int endPixelInX = m_configuration.getXCoordinateWithinTheBitmap((int)m_configuration.convertBytesToPixels(byteOffsetInXForEnd)+m_configuration.getMaximumNumberOfPixelsBeforeOneByte());

    return AprgBitmapSnippet(BitmapXY(startPixelInX, topLeftCorner.getY()), BitmapXY(endPixelInX, bottomRightCorner.getY()), m_configuration);
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

void AprgBitmap::calculateNewCornersBasedOnCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const
{
    int side(m_configuration.estimateSquareSideInPixels(numberOfBytes));
    int halfSide(side/2);
    int left(m_configuration.getXCoordinateWithinTheBitmap(center.getX()-halfSide));
    int right(m_configuration.getXCoordinateWithinTheBitmap(center.getX()+halfSide));
    adjustToTargetLength(left, right, side, m_configuration.getBitmapWidth());

    int xSizeInBytes(m_configuration.getOneRowSizeInBytesFromPixels(left, right));
    xSizeInBytes = (xSizeInBytes > 0) ? xSizeInBytes : 1;
    int ySizeInBytes(numberOfBytes/xSizeInBytes);
    int halfYSizeInBytes(ySizeInBytes/2);
    int top(m_configuration.getYCoordinateWithinTheBitmap(center.getY()-halfYSizeInBytes));
    int bottom(m_configuration.getYCoordinateWithinTheBitmap(center.getY()+halfYSizeInBytes));
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
