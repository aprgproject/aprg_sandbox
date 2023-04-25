#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <string>
#include <vector>

namespace alba {

namespace TwoDimensions {

enum class LineType { Horizontal, Vertical, WithPositiveSlope, WithNegativeSlope, Invalid };

class Line {
public:
    Line();
    Line(Point const& first, Point const& second);
    Line(double const aCoefficient, double const bCoefficient, double const cCoefficient);  // ax+by+c=0
    Line(double const aCoefficient, double const bCoefficient, Point const& point);         // ax+by+c=0
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    LineType getType() const;
    double getXIntercept() const;  // form: a*(x-x0) + b*(y-y0) = 0
    double getYIntercept() const;  // form: a*(x-x0) + b*(y-y0) = 0
    double getSlope() const;
    double getPerpendicularSlope() const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    double getAUnitIncreaseInX() const;
    double getAUnitIncreaseInY() const;
    Point getAPoint() const;
    Points getPoints(Point const& first, Point const& second, double const interval) const;
    Points getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const;
    double calculateYFromX(double const x) const;
    double calculateXFromY(double const y) const;

private:
    void setLineParametersBasedOnDeltas(double const deltaX, double const deltaY, Point const& point);
    void setLineParametersBasedOnCoefficients(
        double const aCoefficient, double const bCoefficient, double const cCoefficient);
    void setCoefficientsUsingLineTypeAndDeltaXandDeltaYAndAPoint(
        double const deltaY, double const deltaX, Point const& point);
    void getPointsForVerticalLine(Points& points, Point const& first, Point const& second, double const interval) const;
    void getPointsForHorizontalLine(
        Points& points, Point const& first, Point const& second, double const interval) const;
    void getPointsForLineWithSlope(
        Points& points, Point const& first, Point const& second, double const interval) const;
    void mergePointsFromPointsFromXAndY(
        Points& points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate,
        bool const isDirectionAscendingForX) const;
    LineType determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const;
    LineType determineLineTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const;

    friend std::ostream& operator<<(std::ostream& out, Line const& line);

    LineType m_type;
    double m_aCoefficient;  // form: a*x + b*y + c = 0
    double m_bCoefficient;  // form: a*x + b*y + c = 0
    double m_cCoefficient;  // form: a*x + b*y + c = 0
};

using Lines = std::vector<Line>;

}  // namespace TwoDimensions
}  // namespace alba
