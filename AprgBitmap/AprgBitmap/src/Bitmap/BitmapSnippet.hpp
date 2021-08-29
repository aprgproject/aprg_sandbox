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
    using TraverseFunction = std::function<void(BitmapXY const&, uint32_t const)>;
    using TraverseAndUpdateFunction = std::function<void(BitmapXY const&, uint32_t &)>;

    BitmapSnippet();
    BitmapSnippet(BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition, BitmapConfiguration const& configuration);
    bool isPositionInsideTheSnippet(BitmapXY const position) const;
    BitmapConfiguration getConfiguration() const;
    BitmapXY getTopLeftCorner() const;    BitmapXY getBottomRightCorner() const;
    unsigned int getDeltaX() const;
    unsigned int getDeltaY() const;
    unsigned int getNumberOfPixelsInSnippet() const;
    unsigned int getPixelDataSize() const;

    void loadPixelDataFromFileInConfiguration();
    void clear();
    void clearAndPutOneColorOnWholeSnippet(unsigned char const colorByte);

    PixelData& getPixelDataReference();
    PixelData const& getPixelDataConstReference() const;
    uint32_t getPixelAt(BitmapXY const position) const;
    uint32_t getColorAt(BitmapXY const position) const;
    bool isBlackAt(BitmapXY const position) const;
    void setPixelAt(BitmapXY const position, uint32_t const value);

    void traverse(TraverseFunction const& traverseFunction) const;
    void traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction);

private:
    unsigned int calculateShiftValue(BitmapXY const position) const;
    unsigned int calculateIndexInPixelData(BitmapXY const position) const;
    uint32_t getPixelAtForPixelInAByte(uint8_t const* reader, unsigned int const index, BitmapXY const position) const;
    uint32_t getPixelAtForMultipleBytePixels(uint8_t const* reader, unsigned int const index) const;
    void setPixelAtForPixelInAByte(uint8_t * writer, unsigned int const index, BitmapXY const position, uint32_t const value);
    void setPixelAtForMultipleBytePixels(uint8_t * writer, unsigned int const index, uint32_t const value);
    BitmapXY m_topLeftCorner;
    BitmapXY m_bottomRightCorner;
    BitmapConfiguration m_configuration;    PixelData m_pixelData;
};

}
}
