#pragma once

#include <Optional/AlbaOptional.hpp>
#include <ThreeDimensions/Point.hpp>

#include <vector>

namespace alba
{

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
    bool operator==(Plane const& plane) const;
    bool operator!=(Plane const& plane) const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    double getDCoefficient() const;
    AlbaOptional<double> getXIntercept() const;
    AlbaOptional<double> getYIntercept() const;
    AlbaOptional<double> getZIntercept() const;
    AlbaOptional<double> calculateXFromYAndZ(double const y, double const z) const;
    AlbaOptional<double> calculateYFromXAndZ(double const x, double const z) const;
    AlbaOptional<double> calculateZFromXAndY(double const x, double const y) const;

    std::string getDisplayableString() const;

private:
    void calculateDCoefficientUsingCoefficientsABCAndAPoint(Point const& first);
    void setXYZIntercepts();
    double m_aCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_bCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_cCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_dCoefficient; //form: a*x + b*y + c*z + d = 0
    AlbaOptional<double> m_xIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    AlbaOptional<double> m_yIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    AlbaOptional<double> m_zIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
};

using Planes = std::vector<Plane>;

}
}
