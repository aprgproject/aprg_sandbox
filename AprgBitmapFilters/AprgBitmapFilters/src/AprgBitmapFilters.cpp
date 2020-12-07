#include "AprgBitmapFilters.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

unsigned int const whiteColor = 0x00FFFFFF;

AprgBitmapFilters::AprgBitmapFilters(string const& path)
    : m_similarityLimit(0x80)
    , m_bitmap(path)
    , m_originalCanvas(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_canvas(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(whiteColor))
{}

void AprgBitmapFilters::findPenPixel(double const penSearchRadius)
{
    m_originalCanvas.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY bitmapPointInCircle(convertPointToBitmapXY(point));
            if(m_originalCanvas.isPositionInside(bitmapPointInCircle))
            {
                unsigned int const currentColor(m_originalCanvas.getColorAt(bitmapPointInCircle));
                if(isSimilar(centerColor, currentColor))
                {
                    bitmapPointsWithSimilarColors.emplace_back(bitmapPointInCircle);
                }
                else
                {
                    bitmapPointsWithDisimilarColors.emplace_back(bitmapPointInCircle);
                }
            }
        });
        if(bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size())
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithDisimilarColors);
        }
        else
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void AprgBitmapFilters::saveBlurredNotPenPixelsToCanvas(double const blurRadius)
{
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {
            m_canvas.setPixelAt(bitmapPoint, getBlurredColor(bitmapPoint, blurRadius));
        }
    });
}

void AprgBitmapFilters::saveNotPenPixelsToCanvas()
{
    m_originalCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {
            m_canvas.setPixelAt(bitmapPoint, color);
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
    m_canvas = m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(whiteColor);
}

void AprgBitmapFilters::saveCanvasToBitmapFile()
{
    m_bitmap.setSnippetWriteToFile(m_canvas);
}

void AprgBitmapFilters::setSimilarityLimit(unsigned int const limit)
{
    m_similarityLimit = limit;
}

bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const //RGB algo
{
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getRed(color1)-(int)getRed(color2))>m_similarityLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getGreen(color1)-(int)getGreen(color2))>m_similarityLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getBlue(color1)-(int)getBlue(color2))>m_similarityLimit);
    return  !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

/*
bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < m_similarityLimit;
}
*/

unsigned int AprgBitmapFilters::getBlurredColor(BitmapXY const& centerXY, double const blurRadius) const
{
    unsigned int const centerColor(m_originalCanvas.getColorAt(centerXY));
    double totalBlurredColorRed(getRed(centerColor));
    double totalBlurredColorGreen(getGreen(centerColor));
    double totalBlurredColorBlue(getBlue(centerColor));
    double totalBlurWeight(getBlurWeight(0, blurRadius));
    bool isChanged(false);
    //ALBA_PRINT5(centerColor, totalBlurredColorRed, totalBlurredColorGreen, totalBlurredColorBlue, totalBlurWeight);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    circle.traverseArea(1, [&](Point const& point)
    {
        BitmapXY bitmapPointInCircle(convertPointToBitmapXY(point));
        if(m_originalCanvas.isPositionInside(bitmapPointInCircle))
        {
            PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPointInCircle));
            unsigned int const currentColor(m_originalCanvas.getColorAt(bitmapPointInCircle));
            if(isSimilar(centerColor, currentColor) && pixelInformation.type != PixelType::Pen)
            {
                isChanged=true;
                double distanceFromCenter(twoDimensionsHelper::getDistance(convertBitmapXYToPoint(centerXY), convertBitmapXYToPoint(bitmapPointInCircle)));
                double blurWeight(getBlurWeight(distanceFromCenter, blurRadius));
                totalBlurredColorRed+=blurWeight*getRed(currentColor);
                totalBlurredColorGreen+=blurWeight*getGreen(currentColor);
                totalBlurredColorBlue+=blurWeight*getBlue(currentColor);
                totalBlurWeight+=blurWeight;
                //ALBA_PRINT2(distanceFromCenter, blurWeight);
                //ALBA_PRINT4(totalBlurredColorRed, totalBlurredColorGreen, totalBlurredColorBlue, totalBlurWeight);
            }
        }
    });
    unsigned int blurredColor(0x00FFFFFF);
    if(isChanged)
    {
        blurredColor = AlbaBitManipulation<unsigned int>::concatenateBytes((unsigned char)(totalBlurredColorRed/totalBlurWeight), (unsigned char)(totalBlurredColorGreen/totalBlurWeight), (unsigned char)(totalBlurredColorBlue/totalBlurWeight));
    }
    //ALBA_PRINT1(blurredColor);
    return blurredColor;
}

double AprgBitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);
}

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
