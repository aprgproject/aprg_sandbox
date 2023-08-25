#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/LineSegment.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <array>

namespace alba {

namespace TwoDimensions {

template <int numberOfVertices>
class Polygon {
public:
    using Distances = std::array<double, numberOfVertices>;
    Polygon();

    Polygon(std::initializer_list<Point> const& vertices);

    bool isEquilateral() const;
    bool isEquiangular() const;
    bool isRegular() const;

    Lines getLines() const;
    LineSegments getLineSegments() const;
    Points getVertices() const;
    Distances getLengthOfSides() const;
    AlbaAngles getAnglesAtVertices() const;
    AlbaAngle getSumOfAngles() const;

    Points getPoints(double const interval) const;
    void getPointsFromVerticesWithoutLastPoint(
        Points& points, double const interval, int vertexIndex1, int vertexIndex2) const;

protected:
    std::array<Point, numberOfVertices> m_vertices;
};

}  // namespace TwoDimensions
}  // namespace alba
