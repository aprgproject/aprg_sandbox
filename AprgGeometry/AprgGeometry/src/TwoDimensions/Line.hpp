#pragma once

#include <TwoDimensions/Point.hpp>

#include <vector>

namespace alba{

enum class LineType
{    Horizontal,
    Vertical,
    WithPositiveSlope,
    WithNegativeSlope,
    Invalid
};

class Line
{
public:
    Line(Point const& first, Point const& second);
    Line(double const aCoefficient, double const bCoefficient, double const cCoefficient);
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    LineType getType() const;
    double getXIntercept() const;
    double getYIntercept() const;    double getSlope() const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    Points getPoints(Point const& first, Point const& second, double const interval) const;
    Points getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const;
    double calculateYFromX(double const x) const;
    double calculateXFromY(double const y) const;
private:
    void getPointsForVerticalLine(Points & points, Point const& first, Point const& second, double const interval) const;
    void getPointsForHorizontalLine(Points & points, Point const& first, Point const& second, double const interval) const;
    void getPointsForLineWithSlope(Points & points, Point const& first, Point const& second, double const interval) const;
    void mergePointsFromPointsFromXAndY(Points & points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate, bool const isDirectionAscendingForX) const;
    LineType determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const;
    LineType determineLineTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const;
    LineType m_type;    double m_yIntercept;
    double m_xIntercept;
    double m_aCoefficient; //form: a*x + b*y + c
    double m_bCoefficient; //form: a*x + b*y + c    double m_cCoefficient; //form: a*x + b*y + c
    double m_slope;
};

using Lines = std::vector<Line>;

}
