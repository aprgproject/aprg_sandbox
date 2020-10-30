#pragma once

#include <TwoDimensions/Point.hpp>

#include <vector>

namespace alba
{

enum class LineType
{
    Horizontal,
    Vertical,
    WithPositiveSlope,
    WithNegativeSlope,
    Unknown
};

class Line
{
public:
    Line(Point const& first, Point const& second);
    LineType getType() const;
    double getXIntercept() const;
    double getYIntercept() const;
    double getSlope() const;
    Points getPoints(Point const& first, Point const& second, double const interval) const;
    double calculateYFromX(double const x) const;
    double calculateXFromY(double const y) const;

private:
    LineType determineLineType(double const deltaY, double const deltaX) const;
    LineType m_type;
    double m_yIntercept;
    double m_xIntercept;
    double m_slope;
};

using Lines = std::vector<Line>;

}