#pragma once

#include <TwoDimensions/Polynomial.hpp>

namespace alba
{

namespace TwoDimensions
{

using ParabolaPolynomialParent = Polynomial<3>;

class Parabola : public ParabolaPolynomialParent
{
public:
    //vertex focus directrix?
    Parabola();
    Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient); // ax2 + bx + c = 0

    double getA() const;
    double getB() const;
    double getC() const;
    Point getVertex() const;
    std::string getDisplayableString() const;
};

std::ostream & operator<<(std::ostream & out, Parabola const& parabola);

}
}
