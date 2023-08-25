#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba {

namespace TwoDimensions {

template <int numberOfVertices>
Polygon<numberOfVertices>::Polygon() {}

template <int numberOfVertices>
Polygon<numberOfVertices>::Polygon(initializer_list<Point> const& vertices) {
    static_assert(numberOfVertices > 2, "The numberOfVertices is less than 2. Its not a polygon by definition.");
    int limit = min(numberOfVertices, static_cast<int>(vertices.size()));
    copy(vertices.begin(), vertices.begin() + limit, m_vertices.begin());
}

template <int numberOfVertices>
bool Polygon<numberOfVertices>::isEquilateral() const {
    Distances lengthOfSides(getLengthOfSides());
    return adjacent_find(lengthOfSides.cbegin(), lengthOfSides.cend(), [](double const length1, double const length2) {
               return !isAlmostEqual(length1, length2);
           }) == lengthOfSides.cend();
}

template <int numberOfVertices>
bool Polygon<numberOfVertices>::isEquiangular() const {
    AlbaAngles anglesAtVertices(getAnglesAtVertices());
    return adjacent_find(
               anglesAtVertices.cbegin(), anglesAtVertices.cend(),
               [](AlbaAngle const& angle1, AlbaAngle const& angle2) {
                   return !isAlmostEqual(angle1.getDegrees(), angle2.getDegrees());
               }) == anglesAtVertices.cend();
}

template <int numberOfVertices>
bool Polygon<numberOfVertices>::isRegular() const {
    return isEquilateral() && isEquiangular();
}

template <int numberOfVertices>
Lines Polygon<numberOfVertices>::getLines() const {
    Lines lines;
    int sizeMinusOne = static_cast<int>(m_vertices.size()) - 1;
    for (int i = 0; i < sizeMinusOne; i++) {
        lines.emplace_back(m_vertices[i], m_vertices[i + 1]);
    }
    lines.emplace_back(m_vertices[sizeMinusOne], m_vertices[0]);
    return lines;  // RVO
}

template <int numberOfVertices>
LineSegments Polygon<numberOfVertices>::getLineSegments() const {
    LineSegments lineSegments;
    int sizeMinusOne = static_cast<int>(m_vertices.size()) - 1;
    for (int i = 0; i < sizeMinusOne; i++) {
        lineSegments.emplace_back(m_vertices[i], m_vertices[i + 1]);
    }
    lineSegments.emplace_back(m_vertices[sizeMinusOne], m_vertices[0]);
    return lineSegments;  // RVO
}

template <int numberOfVertices>
typename Polygon<numberOfVertices>::Distances Polygon<numberOfVertices>::getLengthOfSides() const {
    Distances lengthOfSides;
    int sizeMinusOne = static_cast<int>(m_vertices.size()) - 1;
    for (int i = 0; i < sizeMinusOne; i++) {
        lengthOfSides[i] = getDistance(m_vertices[i], m_vertices[i + 1]);
    }
    lengthOfSides[sizeMinusOne] = getDistance(m_vertices[sizeMinusOne], m_vertices[0]);
    return lengthOfSides;  // RVO
}

template <int numberOfVertices>
Points Polygon<numberOfVertices>::getVertices() const {
    return Points(cbegin(m_vertices), cend(m_vertices));
}

template <int numberOfVertices>
AlbaAngles Polygon<numberOfVertices>::getAnglesAtVertices() const {
    AlbaAngles anglesAtVertices;
    int sizeMinusOne = static_cast<int>(m_vertices.size()) - 1;
    anglesAtVertices.emplace_back(
        getTheInnerAngleUsingThreePoints(m_vertices[0], m_vertices[sizeMinusOne], m_vertices[1]));
    for (int i = 1; i < sizeMinusOne; i++) {
        anglesAtVertices.emplace_back(
            getTheInnerAngleUsingThreePoints(m_vertices[i], m_vertices[i - 1], m_vertices[i + 1]));
    }
    anglesAtVertices.emplace_back(
        getTheInnerAngleUsingThreePoints(m_vertices[sizeMinusOne], m_vertices[sizeMinusOne - 1], m_vertices[0]));
    return anglesAtVertices;  // RVO
}

template <int numberOfVertices>
AlbaAngle Polygon<numberOfVertices>::getSumOfAngles() const {
    return AlbaAngle(AngleUnitType::Degrees, (numberOfVertices - 2) * 180);
}

template <int numberOfVertices>
Points Polygon<numberOfVertices>::getPoints(double const interval) const {
    Points points;
    int sizeMinusOne = static_cast<int>(m_vertices.size()) - 1;
    for (int i = 0; i < sizeMinusOne; i++) {
        getPointsFromVerticesWithoutLastPoint(points, interval, i, i + 1);
    }
    getPointsFromVerticesWithoutLastPoint(points, interval, sizeMinusOne, 0);
    return points;  // RVO
}

template <int numberOfVertices>
void Polygon<numberOfVertices>::getPointsFromVerticesWithoutLastPoint(
    Points& points, double const interval, int vertexIndex1, int vertexIndex2) const {
    Point const& firstPoint(m_vertices[vertexIndex1]);
    Point const& secondPoint(m_vertices[vertexIndex2]);
    Line line(firstPoint, secondPoint);
    Points pointsFromCurrentLine(line.getPointsWithoutLastPoint(firstPoint, secondPoint, interval));
    points.reserve(pointsFromCurrentLine.size());
    copy(pointsFromCurrentLine.cbegin(), pointsFromCurrentLine.cend(), back_inserter(points));
}

template class Polygon<3>;  // clang needs this on implementation file
template class Polygon<4>;  // clang needs this on implementation file

}  // namespace TwoDimensions
}  // namespace alba
