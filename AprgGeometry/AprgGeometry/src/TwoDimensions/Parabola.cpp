#include "Parabola.hpp"

using namespace std;

namespace alba{

namespace TwoDimensions
{
Parabola::Parabola()
    : ParabolaPolynomialParent()
{}

Parabola::Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient) // ax2 + bx + c = 0
    : ParabolaPolynomialParent{cCoefficient, bCoefficient, aCoefficient}
{}

double Parabola::getA() const
{
    return m_coefficients.at(2);
}

double Parabola::getB() const
{
    return m_coefficients.at(1);
}

double Parabola::getC() const
{
    return m_coefficients.at(0);
}

Point Parabola::getVertex() const
{
    double a(getA());
    double b(getB());
    double c(getC());

    return Point(-b/(2*a), ((4*a*c)-(b*b))/(4*a));
}
string Parabola::getDisplayableString() const
{
    std::stringstream ss;    ss << m_coefficients[0] << "*[x^2] + "<< m_coefficients[1] << "*x + " << m_coefficients[2] << " = 0";
    return ss.str();
}

ostream & operator<<(ostream & out, Parabola const& parabola)
{
    out << parabola.getDisplayableString();
    return out;
}

}

}
