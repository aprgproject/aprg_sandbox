#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <Container/AlbaRange.hpp>
#include <String/AlbaStringHelper.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>
#include <string>

namespace alba
{

class AprgGraph
{
public:
    enum class LabelType
    {
        VerticalLabel,
        HorizontalLabel,
        OriginLabel
    };
    using RangeWithDoubles=AlbaRange<double>;
    using FunctionWithDoubles = std::function<double(double)>;

    AprgGraph(std::string const& bitmapPath, BitmapXY const& originInBitmap, BitmapDoubleXY const& magnification);
    void drawPoint(Point const& point, unsigned int const color);
    void drawDiscontinuousPoints(Points const& points, unsigned int const color);
    void drawContinuousPoints(Points const& points, unsigned int const color);
    void drawLine(Line const& line, unsigned int const color);
    void drawCircle(Circle const& circle, unsigned int const color);
    void drawGrid(BitmapDoubleXY const& gridInterval);
    void drawFunctionUsingX(unsigned int const color, FunctionWithDoubles const& functionFromXToY);
    void drawFunctionUsingY(unsigned int const color, FunctionWithDoubles const& functionFromYToX);
    void drawNumberLabel(LabelType const labelType, BitmapXY const& numberPosition, double const number);
    void drawCharacter(BitmapXY const& upLeftPoint, char const character, unsigned int const colorToWrite);
    void saveChangesToBitmapFile();

private:
    std::string getBitmapFilePathOfCharacter(char const character) const;
    double getLowestInterval();
    BitmapXY convertToBitmapXY(Point const& geometryPosition);
    Point convertToPoint(BitmapXY const& bitmapPosition);
    Point convertToPointInBitmap(Point const& realPosition);
    BitmapXY convertPointInBitmapToBitmapXY(Point const& bitmapPosition);
    AprgBitmap m_bitmap;
    AprgBitmapSnippet m_bitmapSnippet;
    BitmapXY m_originInBitmap;
    BitmapDoubleXY m_magnification;
    double m_lowestInterval;
    Point m_realUpLeftPoint;
    Point m_realDownRightPoint;
    alba::stringHelper::NumberToStringConverter m_numberToStringConverter;
};

}
