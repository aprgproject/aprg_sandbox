#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Geometry/TwoDimensions/Constructs/Circle.hpp>
#include <Geometry/TwoDimensions/Constructs/Ellipse.hpp>
#include <Geometry/TwoDimensions/Constructs/Hyperbola.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

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
    using RangeWithDoubles=AlbaValueRange<double>;
    using FunctionWithDoubles = std::function<double(double)>;

    AprgGraph(std::string const& bitmapPath, AprgBitmap::BitmapXY const& originInBitmap, AprgBitmap::BitmapDoubleXY const& magnification);

    void drawPoint(TwoDimensions::Point const& point, unsigned int const color);
    void drawDiscontinuousPoints(TwoDimensions::Points const& points, unsigned int const color);
    void drawContinuousPoints(TwoDimensions::Points const& points, unsigned int const color);
    void drawLine(TwoDimensions::Line const& line, unsigned int const color);
    void drawCircle(TwoDimensions::Circle const& circle, unsigned int const color);
    void drawEllipse(TwoDimensions::Ellipse const& ellipse, unsigned int const color);
    void drawHyperbola(TwoDimensions::Hyperbola const& hyperbola, unsigned int const color);

    void drawTermWithXYSubstitution(algebra::Term const& term, unsigned int const color);
    void drawEquationWithXYSubstitution(algebra::Equation const& equation, unsigned int const color);

    void drawGrid(AprgBitmap::BitmapDoubleXY const& gridInterval);
    void drawFunctionUsingX(unsigned int const color, FunctionWithDoubles const& functionFromXToY);
    void drawFunctionUsingY(unsigned int const color, FunctionWithDoubles const& functionFromYToX);
    void drawNumberLabel(LabelType const labelType, TwoDimensions::Point const& bitmapPointNumberPosition, double const number);
    void drawCharacter(AprgBitmap::BitmapXY const& upLeftPoint, char const character, unsigned int const colorToWrite);
    void saveChangesToBitmapFile();

private:
    bool isBitmapPointInTheBitmap(TwoDimensions::Point const& bitmapPoint);
    std::string getBitmapFilePathOfCharacter(char const character) const;
    double getLowestInterval() const;
    TwoDimensions::Point convertBitmapXYToRealPoint(AprgBitmap::BitmapXY const& bitmapPosition) const;
    TwoDimensions::Point convertRealPointToBitmapPoint(TwoDimensions::Point const& realPosition) const;
    int convertRealXCoordinateToBitmapXCoordinate(double const xCoordinate) const;
    int convertRealYCoordinateToBitmapYCoordinate(double const yCoordinate) const;
    double convertBitmapXCoordinateToRealXCoordinate(double const xCoordinate) const;
    double convertBitmapYCoordinateToRealYCoordinate(double const yCoordinate) const;
    void drawBitmapPointIfPossible(TwoDimensions::Point const& bitmapPoint, unsigned int const color);
    void drawConnectedBitmapPointsIfPossible(TwoDimensions::Points const& bitmapPoints, unsigned int const color);
    void drawTermWithXSubstitution(algebra::Term const& term, unsigned int const color);
    void drawTermWithYSubstitution(algebra::Term const& term, unsigned int const color);
    void drawEquationWithXSubstitution(algebra::Equation const& equation, unsigned int const color);
    void drawEquationWithYSubstitution(algebra::Equation const& equation, unsigned int const color);
    AprgBitmap::Bitmap m_bitmap;
    AprgBitmap::BitmapSnippet m_bitmapSnippet;
    AprgBitmap::BitmapXY m_originInBitmap;
    AprgBitmap::BitmapDoubleXY m_magnification;
    double m_lowestInterval;
    TwoDimensions::Point m_realUpLeftPoint;
    TwoDimensions::Point m_realDownRightPoint;
    alba::stringHelper::StringConverterWithFormatting m_numberToStringConverter;
};

}
