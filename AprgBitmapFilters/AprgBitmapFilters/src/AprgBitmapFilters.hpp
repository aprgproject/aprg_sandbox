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
    void saveBlurredNotPenPixelsToCanvas(double const blurRadius);
    void saveNotPenPixelsToCanvas();
    void setPenPixelsToCanvas();
    void clearCanvas();
    void saveCanvasToBitmapFile();
    void setSimilarityLimit(unsigned int const limit);
    bool isSimilar(unsigned int const color1, unsigned int const color2) const;

private:
    unsigned int getBlurredColor(BitmapXY const& centerXY, double const blurRadius) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;
    unsigned char getRed(unsigned int const color) const;
    unsigned char getGreen(unsigned int const color) const;
    unsigned char getBlue(unsigned int const color) const;
    Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const;
    BitmapXY convertPointToBitmapXY(Point const& pointPosition) const;
    unsigned int m_similarityLimit;
    AprgBitmap m_bitmap;
    AprgBitmapSnippet const m_originalCanvas;
    AprgBitmapSnippet m_canvas;
    PixelInformationDatabase m_pixelInformationDatabase;
};

}
