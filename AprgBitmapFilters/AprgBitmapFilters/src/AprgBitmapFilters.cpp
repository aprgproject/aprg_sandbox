#include "AprgBitmapFilters.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

AprgBitmapFilters::AprgBitmapFilters(string const& path)
    : m_backgroundColor(0x00FFFFFF)
    , m_bitmap(path)
    , m_originalCanvas(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_canvas(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor))
{}

bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const //RGB algo
{
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getRed(color1)-(int)getRed(color2))>(int)similarityColorLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getGreen(color1)-(int)getGreen(color2))>(int)similarityColorLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getBlue(color1)-(int)getBlue(color2))>(int)similarityColorLimit);
    return  !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

/*
bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < m_similarityColorLimit;
}
*/

void AprgBitmapFilters::findPenPixel(double const penSearchRadius, unsigned int const similarityColorLimit)
{
    m_originalCanvas.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(m_originalCanvas.isPositionInside(pointInCircle))
            {
                unsigned int const currentColor(m_originalCanvas.getColorAt(pointInCircle));
                if(isSimilar(centerColor, currentColor, similarityColorLimit))
                {
                    bitmapPointsWithSimilarColors.emplace_back(pointInCircle);
                }
                else
                {
                    bitmapPointsWithDisimilarColors.emplace_back(pointInCircle);
                }
            }
        });        if(bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size())
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithDisimilarColors);
        }        else
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void AprgBitmapFilters::saveBlurredNonPenPixelsToCanvas(double const blurRadius, unsigned int const similarityColorLimit)
{
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {
            m_canvas.setPixelAt(bitmapPoint, getBlurredColor(m_originalCanvas, bitmapPoint, blurRadius,[&](unsigned int centerColor, unsigned int currentColor, BitmapXY pointInCircle)
            {
                PixelInformation pointInCirclePixelInformation(m_pixelInformationDatabase.getPixelInformation(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit) && currentColor!=m_backgroundColor && pointInCirclePixelInformation.type != PixelType::Pen;
            }));
        }
    });
}

void AprgBitmapFilters::saveFilledGapsUsingBlurToCanvas(double const blurRadius)
{
    AprgBitmapSnippet canvas1(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor));
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        canvas1.setPixelAt(bitmapPoint, color);
    });

    unsigned int numberOfPixelsWithChangedColor(1);
    while(numberOfPixelsWithChangedColor!=0)
    {
        numberOfPixelsWithChangedColor=0;
        AprgBitmapSnippet canvas2(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor));
        canvas1.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
        {
            unsigned int newColor(color);
            if(m_backgroundColor == color)
            {
                newColor = getBlurredColor(canvas1, bitmapPoint, blurRadius,[&](unsigned int , unsigned int currentColor, BitmapXY )
                {
                    return m_backgroundColor!=currentColor;
                });
                if(m_backgroundColor != newColor)
                {
                    numberOfPixelsWithChangedColor++;
                }
            }
            canvas2.setPixelAt(bitmapPoint, newColor);
        });
        canvas1=canvas2;
    }
    m_canvas=canvas1;
}

void AprgBitmapFilters::saveNonPenPixelsToCanvas()
{
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {            m_canvas.setPixelAt(bitmapPoint, color);
        }
    });
}
void AprgBitmapFilters::setPenPixelsToCanvas()
{
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type == PixelType::Pen)
        {
            m_canvas.setPixelAt(bitmapPoint, color);
        }
    });
}

void AprgBitmapFilters::clearCanvas()
{
    m_canvas = m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor);
}

void AprgBitmapFilters::saveCanvasToBitmapFile(){
    m_bitmap.setSnippetWriteToFile(m_canvas);
}

void AprgBitmapFilters::setBackgroundColor(unsigned int const backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

unsigned int AprgBitmapFilters::getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const
{
    unsigned int const centerColor(canvas.getColorAt(centerXY));
    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    circle.traverseArea(1, [&](Point const& point)
    {
        BitmapXY pointInCircle(convertPointToBitmapXY(point));
        if(canvas.isPositionInside(pointInCircle))
        {
            unsigned int const currentColor(canvas.getColorAt(pointInCircle));
            if(isIncludedInBlur(centerColor, currentColor, pointInCircle))
            {
                isChanged=true;
                double distanceFromCenter(twoDimensionsHelper::getDistance(convertBitmapXYToPoint(centerXY), convertBitmapXYToPoint(pointInCircle)));
                double blurWeight(getBlurWeight(distanceFromCenter, blurRadius));
                totalBlurredColorRed+=blurWeight*getRed(currentColor);
                totalBlurredColorGreen+=blurWeight*getGreen(currentColor);
                totalBlurredColorBlue+=blurWeight*getBlue(currentColor);
                totalBlurWeight+=blurWeight;
            }
        }
    });
    unsigned int blurredColor(m_backgroundColor);
    if(isChanged)
    {
        blurredColor = AlbaBitManipulation<unsigned int>::concatenateBytes((unsigned char)(totalBlurredColorRed/totalBlurWeight), (unsigned char)(totalBlurredColorGreen/totalBlurWeight), (unsigned char)(totalBlurredColorBlue/totalBlurWeight));
    }
    return blurredColor;
}
double AprgBitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);}

unsigned char AprgBitmapFilters::getRed(unsigned int const color) const
{
    return (AlbaBitManipulation<unsigned int>::getByteAt<2>(color));
}

unsigned char AprgBitmapFilters::getGreen(unsigned int const color) const
{
    return (AlbaBitManipulation<unsigned int>::getByteAt<1>(color));
}

unsigned char AprgBitmapFilters::getBlue(unsigned int const color) const
{
    return (AlbaBitManipulation<unsigned int>::getByteAt<0>(color));
}

Point AprgBitmapFilters::convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const
{
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY AprgBitmapFilters::convertPointToBitmapXY(Point const& pointPosition) const
{
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

}
