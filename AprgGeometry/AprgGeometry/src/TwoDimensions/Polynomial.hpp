#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <algorithm>
#include <array>

namespace alba
{

template<unsigned int degree>
class Polynomial
{
public:
    Polynomial()
    {}

    Polynomial(std::initializer_list<double> coefficients)
    {
        unsigned int limit = std::min(degree, coefficients.size());
        std::copy(coefficients.begin(), coefficients.begin()+limit, m_coefficients.begin());
    }

    //getTangentLine at point

    Points getPoints(double const interval, double const x1, double const x2) const
    {
        SortedPoints sortedPoints;
        for(double x=x1; x<x2; x+=interval)
        {
            Point firstPoint(x1, calculateYfromX(x1));
            Point secondPoint(x2, calculateYfromX(x2));
            Line line(firstPoint, secondPoint);
            Points pointsInLine(line.getPoints(firstPoint, secondPoint, interval));
            std::copy(pointsInLine.begin(), pointsInLine.end(), std::inserter(sortedPoints, sortedPoints.begin()));
        }
        Points points;
        copy(sortedPoints.begin(), sortedPoints.end(), std::back_inserter(points));
        return points; //RVO
    }

    double calculateYfromX(double const x) const
    {
        double valueOfPowerOfX(1);
        double result(0);
        for(unsigned int i=0; i<size; i++)
        {
            result += m_coefficients[i]*valueOfPowerOfX;
            valueOfPowerOfX *= x;
        }
        return result;
    }


private:
    std::array<double, degree> m_coefficients; //form is c0 + c1*x + c2*x2....
};

}
