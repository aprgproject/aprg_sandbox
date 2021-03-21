#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <Container/AlbaRange.hpp>
#include <String/AlbaStringHelper.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Ellipse.hpp>
#include <TwoDimensions/Hyperbola.hpp>
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
    void drawPoint(TwoDimensions::Point const& point, unsigned int const color);
    void drawDiscontinuousPoints(TwoDimensions::Points const& points, unsigned int const color);
    void drawContinuousPoints(TwoDimensions::Points const& points, unsigned int const color);
    void drawLine(TwoDimensions::Line const& line, unsigned int const color);
    void drawCircle(TwoDimensions::Circle const& circle, unsigned int const color);
    void drawEllipse(TwoDimensions::Ellipse const& ellipse, unsigned int const color);
    void drawHyperbola(TwoDimensions::Hyperbola const& hyperbola, unsigned int const color);
    void drawGrid(BitmapDoubleXY const& gridInterval);
    void drawFunctionUsingX(unsigned int const color, FunctionWithDoubles const& functionFromXToY);
    void drawFunctionUsingY(unsigned int const color, FunctionWithDoubles const& functionFromYToX);
    void drawNumberLabel(LabelType const labelType, BitmapXY const& numberPosition, double const number);
    void drawCharacter(BitmapXY const& upLeftPoint, char const character, unsigned int const colorToWrite);
    void saveChangesToBitmapFile();

private:
    std::string getBitmapFilePathOfCharacter(char const character) const;
    double getLowestInterval() const;
    BitmapXY convertRealPointToBitmapXY(TwoDimensions::Point const& geometryPosition) const;
    TwoDimensions::Point convertBitmapXYToRealPoint(BitmapXY const& bitmapPosition) const;
    TwoDimensions::Point convertRealPointToBitmapPoint(TwoDimensions::Point const& realPosition) const;
    BitmapXY convertBitmapPointToBitmapXY(TwoDimensions::Point const& bitmapPosition) const;
    unsigned int convertRealXCoordinateToBitmapXCoordinate(double const xCoordinate) const;
    unsigned int convertRealYCoordinateToBitmapYCoordinate(double const yCoordinate) const;
    double convertBitmapXCoordinateToRealXCoordinate(double const xCoordinate) const;    double convertBitmapYCoordinateToRealYCoordinate(double const yCoordinate) const;
    AprgBitmap m_bitmap;
    AprgBitmapSnippet m_bitmapSnippet;
    BitmapXY m_originInBitmap;
    BitmapDoubleXY m_magnification;
    double m_lowestInterval;
    TwoDimensions::Point m_realUpLeftPoint;
    TwoDimensions::Point m_realDownRightPoint;
    alba::stringHelper::NumberToStringConverter m_numberToStringConverter;
};
}
