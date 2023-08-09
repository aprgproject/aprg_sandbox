#pragma once

#include <Bitmap/BitmapConfiguration.hpp>
#include <Bitmap/CommonTypes.hpp>

#include <functional>

namespace alba
{

namespace AprgBitmap
{

class BitmapSnippet
{
public:
    using TraverseFunction = std::function<void(BitmapXY const&, unsigned int const)>;
    using TraverseAndUpdateFunction = std::function<void(BitmapXY const&, unsigned int &)>;

    BitmapSnippet();
    BitmapSnippet(BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition, BitmapConfiguration const& configuration);

    bool isPositionInsideTheSnippet(BitmapXY const position) const;
    BitmapConfiguration getConfiguration() const;
    BitmapXY getTopLeftCorner() const;
    BitmapXY getBottomRightCorner() const;
    unsigned int getDeltaX() const;
    unsigned int getDeltaY() const;
    unsigned int getNumberOfPixelsInSnippet() const;
    unsigned int getPixelDataSize() const;

    void loadPixelDataFromFileInConfiguration();
    void clear();
    void clearAndPutOneColorOnWholeSnippet(unsigned char const colorByte);

    PixelData& getPixelDataReference();
    PixelData const& getPixelDataConstReference() const;
    unsigned int getPixelAt(BitmapXY const position) const;
    unsigned int getColorAt(BitmapXY const position) const;
    bool isBlackAt(BitmapXY const position) const;
    void setPixelAt(BitmapXY const position, unsigned int const value);

    void traverse(TraverseFunction const& traverseFunction) const;
    void traverseAndUpdate(TraverseAndUpdateFunction const& traverseFunction);

private:
    unsigned int calculateShiftValue(BitmapXY const position) const;
    unsigned int calculateIndexInPixelData(BitmapXY const position) const;
    unsigned int getPixelAtForPixelInAByte(unsigned char const* reader, unsigned int const index, BitmapXY const position) const;
    unsigned int getPixelAtForMultipleBytePixels(unsigned char const* reader, unsigned int const index) const;
    void setPixelAtForPixelInAByte(unsigned char * writer, unsigned int const index, BitmapXY const position, unsigned int const value);
    void setPixelAtForMultipleBytePixels(unsigned char * writer, unsigned int const index, unsigned int const value);
    BitmapXY m_topLeftCorner;
    BitmapXY m_bottomRightCorner;
    BitmapConfiguration m_configuration;
    PixelData m_pixelData;
};

}

}
