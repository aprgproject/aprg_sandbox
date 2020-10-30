#include "AprgBitmap.hpp"

using namespace std;

namespace alba
{

AprgBitmap::AprgBitmap(string const& path)
{
    m_configuration.readBitmapHeaders(path);
}

AprgBitmapConfiguration AprgBitmap::getConfiguration() const
{
    return m_configuration;
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const
{
    AprgBitmapSnippet snippet;
    if(m_configuration.isPositionWithinTheBitmap(topLeftCorner) && m_configuration.isPositionWithinTheBitmap(bottomRightCorner))
    {
        ifstream inputStream(m_configuration.getPath(), ios::binary);
        AlbaFileReader fileReader(inputStream);

        int byteOffsetInXForStart = (int)m_configuration.convertPixelsToBytesRoundToFloor(topLeftCorner.getX());
        int byteOffsetInXForEnd = (int)m_configuration.convertPixelsToBytesRoundToFloor(bottomRightCorner.getX());
        int offsetInYForStart = m_configuration.getBitmapHeight()-topLeftCorner.getY()-1;
        int offsetInYForEnd = m_configuration.getBitmapHeight()-bottomRightCorner.getY()-1;
        int numberOfBytesToBeCopiedForX = m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd);

        int xStartPixel = (int)m_configuration.convertBytesToPixels(byteOffsetInXForStart);
        int xEndPixel = (int)m_configuration.convertBytesToPixels(byteOffsetInXForEnd)+m_configuration.getMaximumNumberOfPixelsBeforeOneByte();
        m_configuration.adjustToCorrectCoordinate(xStartPixel, m_configuration.getBitmapWidth());
        m_configuration.adjustToCorrectCoordinate(xEndPixel, m_configuration.getBitmapWidth());

        snippet = AprgBitmapSnippet(BitmapXY(xStartPixel, topLeftCorner.getY()), BitmapXY(xEndPixel, bottomRightCorner.getY()), m_configuration);

        for(int y=offsetInYForStart; y>=offsetInYForEnd; y--)
        {
            unsigned long long fileOffsetForStart = m_configuration.getPixelArrayAddress()+((unsigned long long)m_configuration.getNumberOfBytesPerRowInFile()*y)+byteOffsetInXForStart;
            fileReader.moveLocation(fileOffsetForStart);
            fileReader.saveDataToMemoryBuffer(snippet.getPixelDataReference(), numberOfBytesToBeCopiedForX);
        }
    }
    return snippet; //RVO takes care of this
}

AprgBitmapSnippet AprgBitmap::getSnippetReadFromFile(BitmapXY const center, unsigned int const numberOfBytesToRead) const
{
    AprgBitmapSnippet snippet;
    if(m_configuration.isPositionWithinTheBitmap(center))
    {
        BitmapXY topLeftCorner;
        BitmapXY bottomRightCorner;
        saveCornersForCenterAndNumberOfBytes(topLeftCorner, bottomRightCorner, center, numberOfBytesToRead);
        snippet = getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
    }
    return snippet;
}

void AprgBitmap::setSnippetWriteToFile(AprgBitmapSnippet const& snippet) const
{
    if(m_configuration.isPositionWithinTheBitmap(snippet.getTopLeftCorner()) && m_configuration.isPositionWithinTheBitmap(snippet.getBottomRightCorner()))
    {
        fstream streamFile(m_configuration.getPath(), fstream::in | fstream::out | fstream::binary);

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
            char * pixelDataPointer = (char *)snippet.getPixelDataConstReference().getConstantBufferPointer()+snippetIndex;
            streamFile.seekg(fileOffsetForStart, streamFile.beg);
            streamFile.write(pixelDataPointer, numberOfBytesToBeCopiedForX);
            snippetIndex += numberOfBytesToBeCopiedForX;
        }
    }
}

void AprgBitmap::saveCornersForCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const
{
    int side(m_configuration.estimateSquareSideInPixels(numberOfBytes));
    int halfSide(side/2);
    int left(center.getX()-halfSide);
    int right(center.getX()+halfSide);
    m_configuration.adjustToCorrectCoordinate(left, m_configuration.getBitmapWidth());
    m_configuration.adjustToCorrectCoordinate(right, m_configuration.getBitmapWidth());
    m_configuration.adjustToCorrectLength(left, right, side, m_configuration.getBitmapWidth());

    int xSizeInBytes(m_configuration.getOneRowSizeInBytesFromPixels(left, right));
    xSizeInBytes = (xSizeInBytes > 0) ? xSizeInBytes : 1;
    int ySizeInBytes(numberOfBytes/xSizeInBytes);
    int halfYSizeInBytes(ySizeInBytes/2);
    int top(center.getY()-halfYSizeInBytes);
    int bottom(center.getY()+halfYSizeInBytes);
    m_configuration.adjustToCorrectCoordinate(top, m_configuration.getBitmapHeight());
    m_configuration.adjustToCorrectCoordinate(bottom, m_configuration.getBitmapHeight());
    m_configuration.adjustToCorrectLength(top, bottom, ySizeInBytes, m_configuration.getBitmapHeight());

    topLeftCorner.setX(left);
    topLeftCorner.setY(top);
    bottomRightCorner.setX(right);
    bottomRightCorner.setY(bottom);
}


}
