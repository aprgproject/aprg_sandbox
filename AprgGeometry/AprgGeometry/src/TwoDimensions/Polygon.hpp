#pragma once

#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <array>

namespace alba
{

namespace TwoDimensions
{

template<unsigned int numberOfVertices>
class Polygon
{
public:
    Polygon();

    Polygon(std::initializer_list<Point> vertices);

    Lines getLines() const;
    Points getVertices() const;
    Points getPoints(double const interval) const;

    Dimensionless::Angles getAnglesAtVertices() const;

    void getPointsFromVerticesWithoutLastPoint(Points & points, double const interval, unsigned int vertexIndex1, unsigned int vertexIndex2) const;

private:
    std::array<Point, numberOfVertices> m_vertices;
};

template class Polygon<3>;
template class Polygon<4>;

}
}
