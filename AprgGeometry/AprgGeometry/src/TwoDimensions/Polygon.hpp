#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

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
        for(int i=0; i<size; i++)
        {
            if(i==size-1)
            {
                Line line(m_vertices[i], m_vertices[0]);
                Points pointsFromCurrentLine(line.getPoints(m_vertices[i], m_vertices[0], interval));
                copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), std::back_inserter(points));
            }
            else
            {
                Line line(m_vertices[i], m_vertices[i+1]);
                Points pointsFromCurrentLine(line.getPoints(m_vertices[i], m_vertices[i+1], interval));
                copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), std::back_inserter(points));
            }
        }
        return points; //RVO
    }


private:
    std::array<Point, numberOfVertices> m_vertices;
};

}
