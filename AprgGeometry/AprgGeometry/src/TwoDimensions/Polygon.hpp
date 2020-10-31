#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <algorithm>
#include <array>

#include <iostream>

namespace alba
{
template<unsigned int numberOfVertices>
class Polygon
{public:
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
        for(unsigned int i=0; i<size; i++)
        {
            if(i==size-1)
            {
                std::cout<<" i:"<<i<<" i:0"<<std::endl;
                getPointsFromVertices(points, interval, i, 0);
            }
            else
            {
                std::cout<<" i:"<<i<<" i+1:"<<i+1<<std::endl;
                getPointsFromVertices(points, interval, i, i+1);
            }
        }
        return points; //RVO
    }

    void getPointsFromVertices(Points & points, double const interval, unsigned int vertexIndex1, unsigned int vertexIndex2) const
    {
        Point const & firstPoint(m_vertices[vertexIndex1]);
        Point const & secondPoint(m_vertices[vertexIndex2]);
        std::cout<<firstPoint.getDisplayableString()<<std::endl;
        std::cout<<secondPoint.getDisplayableString()<<std::endl;
        Line line(firstPoint, secondPoint);
        Points pointsFromCurrentLine(line.getPoints(firstPoint, secondPoint, interval));
        std::cout<<"pointsFromCurrentLine"<<pointsFromCurrentLine.size()<<std::endl;

        copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), std::back_inserter(points));
    }

private:
    std::array<Point, numberOfVertices> m_vertices;
};
}