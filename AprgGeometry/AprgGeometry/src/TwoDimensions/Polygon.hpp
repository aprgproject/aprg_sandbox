#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <array>

namespace alba
{

template<unsigned int numberOfVertices>
class Polygon
{
public:
    Polygon()
    {}

    Polygon(std::initializer_list<Point> vertices)
    {
        static_assert(numberOfVertices>2, "The numberOfVertices is less than 2. Its not a polygon by definition.");
        unsigned int limit = std::min(numberOfVertices, vertices.size());
        std::copy(vertices.begin(), vertices.begin()+limit, m_vertices.begin());
    }

    Lines getLines() const
    {
        Lines line;
        unsigned int size = m_vertices.size();
        for(int i=0; i<size; i++)
        {
            if(i==size-1)
            {
                line.emplace_back(m_vertices[i], m_vertices[0]);
            }
            else
            {
                line.emplace_back(m_vertices[i], m_vertices[i+1]);
            }
        }
        return line; //RVO
    }

    Points getPoints(double const interval) const
    {
        Points points;
        unsigned int size = m_vertices.size();
        for(unsigned int i=0; i<size-1; i++)
        {
            getPointsFromVerticesWithoutLastPoint(points, interval, i, i+1);
        }
        getPointsFromVerticesWithoutLastPoint(points, interval, size-1, 0);
        return points; //RVO
    }

    void getPointsFromVerticesWithoutLastPoint(Points & points, double const interval, unsigned int vertexIndex1, unsigned int vertexIndex2) const
    {
        Point const & firstPoint(m_vertices[vertexIndex1]);
        Point const & secondPoint(m_vertices[vertexIndex2]);
        Line line(firstPoint, secondPoint);
        Points pointsFromCurrentLine(line.getPointsWithoutLastPoint(firstPoint, secondPoint, interval));
        copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), std::back_inserter(points));
    }

private:
    std::array<Point, numberOfVertices> m_vertices;
};
}