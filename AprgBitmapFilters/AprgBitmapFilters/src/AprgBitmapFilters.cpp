#include "AprgBitmapFilters.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/Circle.hpp>

using namespace std;

namespace alba
{

unsigned int const whiteColor = 0x00FFFFFF;

AprgBitmapFilters::AprgBitmapFilters(string const& path)
    : m_bitmap(path)
    , m_originalCanvas(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_canvas(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(whiteColor))
{}

void AprgBitmapFilters::findPenPixel(double const penSearchRadius)
{
    m_originalCanvas.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertPointToBitmapXY(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY bitmapPoint(convertBitmapXYToPoint(point));
            if(m_originalCanvas.isPositionInside(bitmapPoint))
            {
                unsigned int const currentColor(m_originalCanvas.getColorAt(bitmapPoint));
                if(isSimilar(centerColor, currentColor))
                {
                    bitmapPointsWithSimilarColors.emplace_back(bitmapPoint);
                }
                else
                {
                    bitmapPointsWithDisimilarColors.emplace_back(bitmapPoint);
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

bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const //RGB algo
{
    unsigned const char colorDifferenceLimit = 0x10;
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getRed(color1)-(int)getRed(color2))>colorDifferenceLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getGreen(color1)-(int)getGreen(color2))>colorDifferenceLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)getBlue(color1)-(int)getBlue(color2))>colorDifferenceLimit);
    return  isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit;
}

/*
bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    unsigned const char colorDifferenceLimit = 0x20;
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < colorDifferenceLimit;
}
*/

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

Point AprgBitmapFilters::convertPointToBitmapXY(BitmapXY const& bitmapPosition) const
{
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY AprgBitmapFilters::convertBitmapXYToPoint(Point const& pointPosition) const
{
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

}
