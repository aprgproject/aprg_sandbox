#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>

using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{
namespace TwoDimensions
{

template<unsigned int numberOfVertices>
Polygon<numberOfVertices>::Polygon()
{}

template<unsigned int numberOfVertices>
Polygon<numberOfVertices>::Polygon(std::initializer_list<Point> vertices)
{
    static_assert(numberOfVertices>2, "The numberOfVertices is less than 2. Its not a polygon by definition.");
    unsigned int limit = std::min(numberOfVertices, static_cast<unsigned int>(vertices.size()));
    std::copy(vertices.begin(), vertices.begin()+limit, m_vertices.begin());
}

template<unsigned int numberOfVertices>
Lines Polygon<numberOfVertices>::getLines() const
{
    Lines lines;
    int sizeMinusOne = static_cast<int>(m_vertices.size())-1;
    for(int i=0; i<sizeMinusOne; i++)
    {
        lines.emplace_back(m_vertices[i], m_vertices[i+1]);
    }
    lines.emplace_back(m_vertices[sizeMinusOne], m_vertices[0]);
    return lines; //RVO
}

template<unsigned int numberOfVertices>
Points Polygon<numberOfVertices>::getVertices() const
{
    return Points(cbegin(m_vertices), cend(m_vertices));
}

template<unsigned int numberOfVertices>
array<double, numberOfVertices> Polygon<numberOfVertices>::getLengthOfSides() const
{
    array<double, numberOfVertices> lengthOfSides;
    int sizeMinusOne = static_cast<int>(m_vertices.size())-1;
    for(int i=0; i<sizeMinusOne; i++)
    {
        lengthOfSides[i]=getDistance(m_vertices[i], m_vertices[i+1]);
    }
    lengthOfSides[sizeMinusOne]=getDistance(m_vertices[sizeMinusOne], m_vertices[0]);
    return lengthOfSides; //RVO
}

template<unsigned int numberOfVertices>Dimensionless::Angles Polygon<numberOfVertices>::getAnglesAtVertices() const
{
    Dimensionless::Angles anglesAtVertices;
    int sizeMinusOne = static_cast<int>(m_vertices.size())-1;
    anglesAtVertices.emplace_back(getTheInnerAngleUsingThreePoints(m_vertices[0], m_vertices[sizeMinusOne], m_vertices[1]));
    for(int i=1; i<sizeMinusOne; i++)
    {
        anglesAtVertices.emplace_back(getTheInnerAngleUsingThreePoints(m_vertices[i], m_vertices[i-1], m_vertices[i+1]));
    }
    anglesAtVertices.emplace_back(getTheInnerAngleUsingThreePoints(m_vertices[sizeMinusOne], m_vertices[sizeMinusOne-1], m_vertices[0]));
    return anglesAtVertices; //RVO
}

template<unsigned int numberOfVertices>
Points Polygon<numberOfVertices>::getPoints(double const interval) const
{
    Points points;
    int sizeMinusOne = static_cast<int>(m_vertices.size())-1;
    for(int i=0; i<sizeMinusOne; i++)
    {
        getPointsFromVerticesWithoutLastPoint(points, interval, i, i+1);
    }
    getPointsFromVerticesWithoutLastPoint(points, interval, sizeMinusOne, 0);
    return points; //RVO
}

template<unsigned int numberOfVertices>
void Polygon<numberOfVertices>::getPointsFromVerticesWithoutLastPoint(Points & points, double const interval, unsigned int vertexIndex1, unsigned int vertexIndex2) const
{    Point const & firstPoint(m_vertices[vertexIndex1]);
    Point const & secondPoint(m_vertices[vertexIndex2]);
    Line line(firstPoint, secondPoint);
    Points pointsFromCurrentLine(line.getPointsWithoutLastPoint(firstPoint, secondPoint, interval));
    copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), std::back_inserter(points));
}

}
}
