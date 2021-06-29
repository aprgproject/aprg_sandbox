#include "Parabola.hpp"

using namespace std;

namespace alba
{

namespace TwoDimensions
{

Parabola::Parabola()
    : ParabolaPolynomialParent()
{}

Parabola::Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient) // ax2 + bx + c = 0
    : ParabolaPolynomialParent{cCoefficient, bCoefficient, aCoefficient}
{}

string Parabola::getDisplayableString() const
{
    std::stringstream ss;
    ss << m_coefficients[0] << "*[x^2] + "<< m_coefficients[1] << "*x + " << m_coefficients[2] << " = 0";
    return ss.str();
}

ostream & operator<<(ostream & out, Parabola const& parabola)
{
    out << parabola.getDisplayableString();
    return out;
}

}
}
