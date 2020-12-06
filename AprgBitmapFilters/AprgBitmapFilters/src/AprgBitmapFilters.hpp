#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <PixelInformationDatabase.hpp>
#include <TwoDimensions/Point.hpp>

namespace alba
{

class AprgBitmapFilters
{
public:

    AprgBitmapFilters(std::string const& path);
    void findPenPixel(double const penSearchRadius);
    void saveNotPenPixelsToCanvas();
    void setPenPixelsToCanvas();
    void clearCanvas();
    void saveCanvasToBitmapFile();
    bool isSimilar(unsigned int const color1, unsigned int const color2) const;

private:
    unsigned char getRed(unsigned int const color) const;
    unsigned char getGreen(unsigned int const color) const;
    unsigned char getBlue(unsigned int const color) const;
    Point convertPointToBitmapXY(BitmapXY const& bitmapPosition) const;
    BitmapXY convertBitmapXYToPoint(Point const& pointPosition) const;
    AprgBitmap m_bitmap;
    AprgBitmapSnippet const m_originalCanvas;
    AprgBitmapSnippet m_canvas;
    PixelInformationDatabase m_pixelInformationDatabase;
};

}
