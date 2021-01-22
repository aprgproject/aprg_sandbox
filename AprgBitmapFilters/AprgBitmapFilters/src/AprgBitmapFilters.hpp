#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <PixelInformationDatabase.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

class AprgBitmapFilters
{
public:
    using BlurCondition = std::function<bool(unsigned int,unsigned int,BitmapXY)>;

    AprgBitmapFilters(std::string const& path);
    bool isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const;
    void findPenPixel(double const penSearchRadius, unsigned int const similarityColorLimit);
    void setBlurredNonPenPixelsToOutputCanvas(double const blurRadius, unsigned int const similarityColorLimit);
    void setBlankGapsUsingBlurToOutputCanvas(double const blurRadius);
    void setNonPenPixelsToOutputCanvas();
    void setPenPixelsToOutputCanvas();
    void clearOutputCanvas();
    void copyOutputCanvasToInputCanvas();
    void saveOutputCanvasToBitmapFile();
    void setBackgroundColor(unsigned int const backgroundColor);

private:
    unsigned int getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;
    unsigned char getRed(unsigned int const color) const;
    unsigned char getGreen(unsigned int const color) const;
    unsigned char getBlue(unsigned int const color) const;
    Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const;
    BitmapXY convertPointToBitmapXY(Point const& pointPosition) const;
    unsigned int m_backgroundColor;
    AprgBitmap m_bitmap;
    AprgBitmapSnippet m_inputCanvas;
    AprgBitmapSnippet m_outputCanvas;
    PixelInformationDatabase m_pixelInformationDatabase;
};

}
