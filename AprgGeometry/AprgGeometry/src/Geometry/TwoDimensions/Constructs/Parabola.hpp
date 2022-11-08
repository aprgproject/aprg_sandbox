#pragma once

#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>
#include <Geometry/TwoDimensions/Constructs/PolynomialInXEqualsY.hpp>
#include <Geometry/TwoDimensions/Constructs/PolynomialInYEqualsX.hpp>

namespace alba
{

namespace TwoDimensions
{

enum class ParabolaOrientation
{
    PolynomialX,
    PolynomialY,
};

template <ParabolaOrientation orientation>
struct ParabolaOrientationTraits
{
    static_assert(sizeof(orientation) == -1, "Parabola orientation traits are not defined");
};

template<>
struct ParabolaOrientationTraits<ParabolaOrientation::PolynomialX>
{
    using ParabolaOrientationPolynomialType = PolynomialInXEqualsY<3>;
};

template<>
struct ParabolaOrientationTraits<ParabolaOrientation::PolynomialY>
{
    using ParabolaOrientationPolynomialType = PolynomialInYEqualsX<3>;
};

template<ParabolaOrientation parabolaOrientation>
using ParabolaPolynomialType = typename ParabolaOrientationTraits<parabolaOrientation>::ParabolaOrientationPolynomialType;

template<ParabolaOrientation parabolaOrientation>
class Parabola : public ParabolaPolynomialType<parabolaOrientation>
{
public:
    using ParabolaParent = ParabolaPolynomialType<parabolaOrientation>;
    //vertex focus directrix?
    Parabola()
        : ParabolaParent()
    {}

     // ax2 + bx + c = y or ay2 + by + c = x
    Parabola(
            double const aCoefficient,
            double const bCoefficient,
            double const cCoefficient)
        : ParabolaParent{aCoefficient, bCoefficient, cCoefficient}
    {}

    double getA() const
    {
        return ParabolaParent::m_coefficients.at(2);
    }

    double getB() const
    {
        return ParabolaParent::m_coefficients.at(1);
    }

    double getC() const
    {
        return ParabolaParent::m_coefficients.at(0);
    }

    double getP() const
    {
        //(x-xt)^2 = 4p*(y-yt)
        return 1/(getA()*4);
    }

    double getTranslationInX() const
    {
        //(x-xt)^2 = 4p*(y-yt)
        return -2*getB()*getP();
    }

    double getTranslationInY() const
    {
        //(x-xt)^2 = 4p*(y-yt)
        return getC() - (pow(getTranslationInX(), 2)/(4*getP()));
    }

    double getEccentricity() const
    {
        return 1;
    }

    double getLengthOfLatusRectum() const
    {
        // The horizontal chord through the focus is called the latus rectum; one half of it is the semi-latus rectum.
        return mathHelper::getAbsoluteValue<double>(4*getP());
    }

    Point getVertex() const
    {
        double a(getA());
        double b(getB());
        double c(getC());
        double vertexCoordinate1 = -b/(2*a);
        double vertexCoordinate2 = ((4*a*c)-(b*b))/(4*a);
        Point vertex;
        if(ParabolaOrientation::PolynomialX == parabolaOrientation)
        {
            vertex = Point(vertexCoordinate1, vertexCoordinate2);
        }
        else
        {
            vertex = Point(vertexCoordinate2, vertexCoordinate1);
        }
        return vertex;
    }

    Point getFocus() const
    {
        double p(getP());
        double xt(getTranslationInX());
        double yt(getTranslationInY());
        Point focus;
        if(ParabolaOrientation::PolynomialX == parabolaOrientation)
        {
            focus = Point(xt, yt+p);
        }
        else
        {
            focus = Point(xt+p, yt);
        }
        return focus;
    }

    Line getDirectrix() const
    {
        double p(getP());
        double xt(getTranslationInX());
        double yt(getTranslationInY());
        Line directrix;
        if(ParabolaOrientation::PolynomialX == parabolaOrientation)
        {
            directrix = Line(Point(0, yt-p), Point(1, yt-p));
        }
        else
        {
            directrix = Line(Point(xt-p, 0), Point(xt-p, 1));
        }
        return directrix;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        if(ParabolaOrientation::PolynomialX == parabolaOrientation)
        {
            ss << getA() << "*[x^2] + " << getB() << "*x + " << getC() << " = 0";
        }
        else if(ParabolaOrientation::PolynomialY == parabolaOrientation)
        {
            ss << getA() << "*[y^2] + " << getB() << "*y + " << getC() << " = 0";
        }
        return ss.str();
    }

private:
};

template<ParabolaOrientation parabolaOrientation>
std::ostream & operator<<(std::ostream & out, Parabola<parabolaOrientation> const& parabola)
{
    out << parabola.getDisplayableString();
    return out;
}

}
}
