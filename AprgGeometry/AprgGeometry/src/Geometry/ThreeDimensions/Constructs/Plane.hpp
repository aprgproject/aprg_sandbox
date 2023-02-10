#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <optional>
#include <vector>

namespace alba{

namespace ThreeDimensions
{
class Plane
{
public:
    Plane();
    Plane(Point const& first, Point const& second, Point const& third);
    Plane(
            double const aCoefficient,
            double const bCoefficient,
            double const cCoefficient,
            Point const& pointInPlane);
    Plane(
            double const aCoefficient,
            double const bCoefficient,
            double const cCoefficient,
            double const dCoefficient);
    bool operator==(Plane const& plane) const;
    bool operator!=(Plane const& plane) const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    double getDCoefficient() const;
    std::optional<double> getXIntercept() const; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    std::optional<double> getYIntercept() const; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    std::optional<double> getZIntercept() const; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    std::optional<double> calculateXFromYAndZ(double const y, double const z) const;
    std::optional<double> calculateYFromXAndZ(double const x, double const z) const;
    std::optional<double> calculateZFromXAndY(double const x, double const y) const;

private:
    friend std::ostream & operator<<(std::ostream & out, Plane const& plane);
    void calculateDCoefficientUsingCoefficientsABCAndAPoint(Point const& first);
    double m_aCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_bCoefficient; //form: a*x + b*y + c*z + d = 0    double m_cCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_dCoefficient; //form: a*x + b*y + c*z + d = 0
};

using Planes = std::vector<Plane>;

}
}
