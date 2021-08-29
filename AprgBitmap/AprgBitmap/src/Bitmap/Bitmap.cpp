#include "Bitmap.hpp"

using namespace std;

namespace alba
{

namespace AprgBitmap
{

Bitmap::Bitmap(string const& path)
{
    m_configuration.readBitmap(path);
}

BitmapConfiguration Bitmap::getConfiguration() const
{
    return m_configuration;
}

BitmapSnippet Bitmap::createColorFilledSnippetWithSizeOfWholeBitmap(uint8_t const colorByte) const
{
    BitmapSnippet snippet(m_configuration.getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint(), m_configuration);
    snippet.clearAndPutOneColorOnWholeSnippet(colorByte);    return snippet;
}

BitmapSnippet Bitmap::getSnippetReadFromFileWholeBitmap() const{
    return getSnippetReadFromFile(m_configuration.getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint());
}

BitmapSnippet Bitmap::getSnippetReadFromFileWithOutOfRangeCoordinates(int outOfRangeLeft, int outOfRangeTop, int outOfRangeRight, int outOfRangeBottom) const
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

BitmapSnippet Bitmap::getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY const center, unsigned int const numberOfBytesToRead) const
{
    BitmapSnippet snippet;
    if(m_configuration.isPositionWithinTheBitmap(center))
    {
        BitmapXY topLeftCorner;
        BitmapXY bottomRightCorner;
        calculateNewCornersBasedOnCenterAndNumberOfBytes(topLeftCorner, bottomRightCorner, center, numberOfBytesToRead);
        snippet = getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
    }
    return snippet;
}

BitmapSnippet Bitmap::getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const
{
    int byteOffsetInXForStart = static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(topLeftCorner.getX()));
    int byteOffsetInXForEnd = static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(bottomRightCorner.getX()));
    int startPixelInX = static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(
                    static_cast<int>(m_configuration.convertBytesToPixels(byteOffsetInXForStart))));
    int endPixelInX = static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(
                static_cast<int>(m_configuration.convertBytesToPixels(byteOffsetInXForEnd) + m_configuration.getMaximumNumberOfPixelsBeforeOneByte())));

    return BitmapSnippet(BitmapXY(startPixelInX, topLeftCorner.getY()), BitmapXY(endPixelInX, bottomRightCorner.getY()), m_configuration);
}
void Bitmap::setSnippetWriteToFile(BitmapSnippet const& snippet) const
{
    if(areBitmapConfigurationsCompatibleForChangingPixelData(m_configuration, snippet.getConfiguration()))    {
        if(m_configuration.isPositionWithinTheBitmap(snippet.getTopLeftCorner()) && m_configuration.isPositionWithinTheBitmap(snippet.getBottomRightCorner()))
        {
            fstream streamFile(m_configuration.getPath(), fstream::in | fstream::out | fstream::binary);
            if(streamFile.is_open())
            {
                int byteOffsetInXForStart = static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(snippet.getTopLeftCorner().getX()));
                int byteOffsetInXForEnd = static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(snippet.getBottomRightCorner().getX()));
                int offsetInYForStart = static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(snippet.getTopLeftCorner().getY()) -1;
                int offsetInYForEnd = static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(snippet.getBottomRightCorner().getY()) -1;
                int numberOfBytesToBeCopiedForX = static_cast<int>(m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));
                unsigned int snippetSize = snippet.getPixelDataSize();
                unsigned int snippetIndex = 0;

                for(int y=offsetInYForStart; y>=offsetInYForEnd && snippetIndex<snippetSize; y--)
                {
                    unsigned long long fileOffsetForStart = m_configuration.getPixelArrayAddress()
                            + ((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile()*y)
                            + byteOffsetInXForStart;
                    char const* pixelDataPointer = static_cast<char const*>(snippet.getPixelDataConstReference().getConstantBufferPointer()) + snippetIndex;
                    streamFile.seekg(fileOffsetForStart, streamFile.beg);
                    streamFile.write(pixelDataPointer, numberOfBytesToBeCopiedForX);
                    snippetIndex += numberOfBytesToBeCopiedForX;                }
                streamFile.flush();
            }
        }    }
}

void Bitmap::calculateNewCornersBasedOnCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const
{
    int side(static_cast<int>(m_configuration.getEstimatedSquareSideInPixels(numberOfBytes)));
    int halfSide(side/2);
    int left(static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(static_cast<int>(center.getX()) - halfSide)));
    int right(static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(static_cast<int>(center.getX()) + halfSide)));
    adjustToTargetLength(left, right, side, m_configuration.getBitmapWidth());

    int xSizeInBytes(static_cast<int>(m_configuration.getOneRowSizeInBytesFromPixels(left, right)));
    xSizeInBytes = (xSizeInBytes > 0) ? xSizeInBytes : 1;
    int ySizeInBytes(static_cast<int>(numberOfBytes/xSizeInBytes));
    int halfYSizeInBytes(ySizeInBytes/2);
    int top(static_cast<int>(m_configuration.getYCoordinateWithinTheBitmap(static_cast<int>(center.getY()) - halfYSizeInBytes)));
    int bottom(static_cast<int>(m_configuration.getYCoordinateWithinTheBitmap(static_cast<int>(center.getY()) + halfYSizeInBytes)));
    adjustToTargetLength(top, bottom, ySizeInBytes, m_configuration.getBitmapHeight());

    topLeftCorner.setX(left);    topLeftCorner.setY(top);
    bottomRightCorner.setX(right);
    bottomRightCorner.setY(bottom);
}
void Bitmap::adjustToTargetLength(int & low, int & high, int const targetLength, unsigned int const maxLength) const
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

}
