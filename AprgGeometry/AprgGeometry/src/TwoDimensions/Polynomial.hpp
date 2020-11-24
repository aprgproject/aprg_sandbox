#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <array>

namespace alba
{

template<unsigned int numberOfCoefficients>
class Polynomial
{
public:
    Polynomial()
    {}

    Polynomial(std::initializer_list<double> coefficients)
    {
        static_assert(numberOfCoefficients>0, "The numberOfCoefficients is not more than 0. Its not a polynomial");
        unsigned int limit = std::min(numberOfCoefficients, coefficients.size());
        std::copy(coefficients.begin(), coefficients.begin()+limit, m_coefficients.begin());
        saveFirstDerivativeCoefficients();
    }

    Line getTangentLineAt(double const x) const
    {
        double slope = getSlopeAt(x);
        double y = calculateYfromX(x);
        return Line(Point(x, y), Point(x+1, y+slope));
    }

    Points getPoints(double const startValueOfX, double const endValueOfX, double const interval) const
    {
        Points points;
        Point previousPoint(startValueOfX, calculateYfromX(startValueOfX));
        twoDimensionsHelper::traverseValues(startValueOfX, endValueOfX, interval, [&](double traverseValueOfX)
        {
            Point currentPoint(traverseValueOfX, calculateYfromX(traverseValueOfX));
            if(currentPoint != previousPoint)
            {
                getPointsFromTwoPointsWithoutLastPoint(points, previousPoint, currentPoint, interval);
            }
            previousPoint = currentPoint;
        });
        points.push_back(Point(endValueOfX, calculateYfromX(endValueOfX)));
        return points; //RVO
    }

    double calculateYfromX(double const x) const
    {
        double valueOfPowerOfX(1);
        double result(0);
        for(double const coefficient : m_coefficients)
        {
            result += coefficient*valueOfPowerOfX;
            valueOfPowerOfX *= x;
        }
        return result;
    }

    double getSlopeAt(double const x) const
    {
        double valueOfPowerOfX(1);
        double result(0);
        for(double const coefficient : m_coefficientsOfFirstDerivative)
        {
            result += coefficient*valueOfPowerOfX;
            valueOfPowerOfX *= x;
        }
        return result;
    }

private:
    void saveFirstDerivativeCoefficients()
    {
        for(unsigned int i=1; i<numberOfCoefficients; i++)
        {
            m_coefficientsOfFirstDerivative[i-1] = i*m_coefficients[i];
        }
    }

    void getPointsFromTwoPointsWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval) const
    {
        Line line(previousPoint, currentPoint);
        Points pointsInLine(line.getPointsWithoutLastPoint(previousPoint, currentPoint, interval));
        std::copy(pointsInLine.begin(), pointsInLine.end(), std::back_inserter(points));
    }

    std::array<double, numberOfCoefficients> m_coefficients; //form is c0 + c1*x + c2*x2....
    std::array<double, numberOfCoefficients-1> m_coefficientsOfFirstDerivative; //form is c0 + c1*x + c2*x2....
};

}
