#pragma once

#include <TwoDimensions/Polynomial.hpp>

namespace alba
{

namespace TwoDimensions
{

using ParabolaPolynomialParent = Polynomial<3>;

class Parabola : public ParabolaPolynomialParent
{
    friend std::ostream & operator<<(std::ostream & out, Parabola const& parabola);
public:
    //vertex focus directrix?
    Parabola();
    Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient); // ax2 + bx + c = 0

    std::string getDisplayableString() const;
};

std::ostream & operator<<(std::ostream & out, Parabola const& parabola);

}
}