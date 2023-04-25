#include "Quadrilateral.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba {

namespace TwoDimensions {

Quadrilateral::Quadrilateral() : QuadrilateralPolygonParent() {}

Quadrilateral::Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth)
    : QuadrilateralPolygonParent{first, second, third, fourth} {}

Quadrilateral::StartEndOfXAndY::StartEndOfXAndY(
    double const xStartParameter, double const xEndParameter, double const yParameter)
    : xStart(xStartParameter), xEnd(xEndParameter), y(yParameter) {}

void Quadrilateral::traverseArea(double const interval, TraverseOperation const& traverseOperation) const {
    GroupOfPoints groupOfPointsBasedOnYValue(getGroupOfPointsBasedOnYValue());
    ListOfStartEndOfXAndY listOfStartEndOfXAndY(getStartEndForXs(groupOfPointsBasedOnYValue, interval));
    for (StartEndOfXAndY const& startEndOfXAndY : listOfStartEndOfXAndY) {
        AlbaValueRange<double> rangeForX(startEndOfXAndY.xStart, startEndOfXAndY.xEnd, interval);
        rangeForX.traverse([&](double const x) { traverseOperation(Point(x, startEndOfXAndY.y)); });
    }
}

Quadrilateral::GroupOfPoints Quadrilateral::getGroupOfPointsBasedOnYValue() const {
    GroupOfPoints result;
    Points vertices(m_vertices.begin(), m_vertices.end());
    if (!vertices.empty()) {
        sortPointsInYAndThenX(vertices);
        unsigned int groupOfPointsIndex(0);
        Point previousPoint(vertices.front());
        result.emplace_back();
        result[groupOfPointsIndex].emplace_back(vertices.front());
        for (auto it = vertices.cbegin() + 1; it != vertices.cend(); it++) {
            Point const& currentPoint(*it);
            if (isAlmostEqual(currentPoint.getY(), previousPoint.getY())) {
                result[groupOfPointsIndex].emplace_back(currentPoint);
            } else {
                result.emplace_back();
                groupOfPointsIndex++;
                result[groupOfPointsIndex].emplace_back(currentPoint);
            }
            previousPoint = currentPoint;
        }
        for (Points& pointsInResult : result) {
            sort(pointsInResult.begin(), pointsInResult.end());
        }
    }
    return result;
}

Quadrilateral::ListOfStartEndOfXAndY Quadrilateral::getStartEndForXs(
    Quadrilateral::GroupOfPoints const& groupOfPointsBasedOnYValue, double const interval) const {
    ListOfStartEndOfXAndY result;
    unsigned int groupSize = groupOfPointsBasedOnYValue.size();
    if (groupSize == 1) {
        Points points(groupOfPointsBasedOnYValue.at(0));
        result = getStartEndForXsFor1Points(points);
    } else if (groupSize == 2) {
        Points points1(groupOfPointsBasedOnYValue.at(0));
        Points points2(groupOfPointsBasedOnYValue.at(1));
        result = getStartEndForXsFor2Points(points1, points2, interval);
    } else if (groupSize == 3) {
        Points points1(groupOfPointsBasedOnYValue.at(0));
        Points points2(groupOfPointsBasedOnYValue.at(1));
        Points points3(groupOfPointsBasedOnYValue.at(2));
        result = getStartEndForXsFor3Points(points1, points2, points3, interval);
    } else if (groupSize == 4) {
        Points points1(groupOfPointsBasedOnYValue.at(0));
        Points points2(groupOfPointsBasedOnYValue.at(1));
        Points points3(groupOfPointsBasedOnYValue.at(2));
        Points points4(groupOfPointsBasedOnYValue.at(3));
        result = getStartEndForXsFor4Points(points1, points2, points3, points4, interval);
    }
    return result;
}

Quadrilateral::ListOfStartEndOfXAndY Quadrilateral::getStartEndForXsFor1Points(Points const& points) const {
    ListOfStartEndOfXAndY result;
    if (points.size() == 4) {
        result.emplace_back(points.at(0).getX(), points.at(3).getX(), points.at(0).getY());
    }
    return result;
}

Quadrilateral::ListOfStartEndOfXAndY Quadrilateral::getStartEndForXsFor2Points(
    Points const& points1, Points const& points2, double const interval) const {
    ListOfStartEndOfXAndY result;
    unsigned int points1Size = points1.size();
    unsigned int points2Size = points2.size();
    if (points1Size == 1 && points2Size == 3) {
        Point point1(points1.at(0));
        Point point21(points2.at(0));
        Point point23(points2.at(2));
        Line line1To21(point1, point21);
        Line line1To23(point1, point23);
        AlbaValueRange<double> rangeForY(point1.getY(), point21.getY(), interval);
        rangeForY.traverse([&](double const y) {
            result.emplace_back(line1To21.calculateXFromY(y), line1To23.calculateXFromY(y), y);
        });
    } else if (points1Size == 2 && points2Size == 2) {
        Point point11(points1.at(0));
        Point point12(points1.at(1));
        Point point21(points2.at(0));
        Point point22(points2.at(1));
        Line line11To21(point11, point21);
        Line line12To22(point12, point22);
        AlbaValueRange<double> rangeForY(point11.getY(), point21.getY(), interval);
        rangeForY.traverse([&](double const y) {
            result.emplace_back(line11To21.calculateXFromY(y), line12To22.calculateXFromY(y), y);
        });
    } else if (points1Size == 3 && points2Size == 1) {
        Point point11(points1.at(0));
        Point point13(points1.at(2));
        Point point2(points2.at(0));
        Line line11To2(point11, point2);
        Line line13To2(point13, point2);
        AlbaValueRange<double> rangeForY(point11.getY(), point2.getY(), interval);
        rangeForY.traverse([&](double const y) {
            result.emplace_back(line11To2.calculateXFromY(y), line13To2.calculateXFromY(y), y);
        });
    }
    return result;
}

Quadrilateral::ListOfStartEndOfXAndY Quadrilateral::getStartEndForXsFor3Points(
    Points const& points1, Points const& points2, Points const& points3, double const interval) const {
    ListOfStartEndOfXAndY result;
    unsigned int points1Size = points1.size();
    unsigned int points2Size = points2.size();
    unsigned int points3Size = points3.size();
    if (points1Size == 1 && points2Size == 1 && points3Size == 2) {
        Point point1(points1.at(0));
        Point point2(points2.at(0));
        Point point31(points3.at(0));
        Point point32(points3.at(1));
        if (point1.getX() < point2.getX()) {
            Line line1To31(point1, point31);
            Line line1To2(point1, point2);
            Line line2To32(point2, point32);
            AlbaValueRange<double> rangeForY(point1.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To31.calculateXFromY(y), line1To2.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point31.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To31.calculateXFromY(y), line2To32.calculateXFromY(y), y);
            });
        } else {
            Line line1To2(point1, point2);
            Line line1To32(point1, point32);
            Line line2To31(point2, point31);
            AlbaValueRange<double> rangeForY(point1.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To2.calculateXFromY(y), line1To32.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point31.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line2To31.calculateXFromY(y), line1To32.calculateXFromY(y), y);
            });
        }
    } else if (points1Size == 1 && points2Size == 2 && points3Size == 1) {
        Point point1(points1.at(0));
        Point point21(points2.at(0));
        Point point22(points2.at(1));
        Point point3(points3.at(0));
        Line line1To21(point1, point21);
        Line line1To22(point1, point22);
        Line line21To3(point21, point3);
        Line line22To3(point22, point3);
        AlbaValueRange<double> rangeForY(point1.getY(), point21.getY(), interval);
        rangeForY.traverse([&](double const y) {
            result.emplace_back(line1To21.calculateXFromY(y), line1To22.calculateXFromY(y), y);
        });
        rangeForY = AlbaValueRange<double>(point21.getY() + interval, point3.getY(), interval);
        rangeForY.traverse([&](double const y) {
            result.emplace_back(line21To3.calculateXFromY(y), line22To3.calculateXFromY(y), y);
        });
    } else if (points1Size == 2 && points2Size == 1 && points3Size == 1) {
        Point point11(points1.at(0));
        Point point12(points1.at(1));
        Point point2(points2.at(0));
        Point point3(points3.at(0));
        if (point2.getX() < point3.getX()) {
            Line line11To2(point11, point2);
            Line line12To3(point12, point3);
            Line line2To3(point2, point3);
            AlbaValueRange<double> rangeForY(point11.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line11To2.calculateXFromY(y), line12To3.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point3.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line2To3.calculateXFromY(y), line12To3.calculateXFromY(y), y);
            });
        } else {
            Line line11To3(point11, point3);
            Line line12To2(point12, point2);
            Line line2To3(point2, point3);
            AlbaValueRange<double> rangeForY(point11.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line11To3.calculateXFromY(y), line12To2.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point3.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line11To3.calculateXFromY(y), line2To3.calculateXFromY(y), y);
            });
        }
    }
    return result;
}

Quadrilateral::ListOfStartEndOfXAndY Quadrilateral::getStartEndForXsFor4Points(
    Points const& points1, Points const& points2, Points const& points3, Points const& points4,
    double const interval) const {
    ListOfStartEndOfXAndY result;
    if (points1.size() == 1 && points2.size() == 1 && points3.size() == 1 && points4.size() == 1) {
        Point point1(points1.at(0));
        Point point2(points2.at(0));
        Point point3(points3.at(0));
        Point point4(points4.at(0));
        Line line1To2(point1, point2);
        Line line1To3(point1, point3);
        Line line2To4(point2, point4);
        Line line3To4(point3, point4);
        if (point2.getX() < point3.getX()) {
            AlbaValueRange<double> rangeForY(point1.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To2.calculateXFromY(y), line1To3.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point3.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line2To4.calculateXFromY(y), line1To3.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point3.getY() + interval, point4.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line2To4.calculateXFromY(y), line3To4.calculateXFromY(y), y);
            });
        } else {
            AlbaValueRange<double> rangeForY(point1.getY(), point2.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To3.calculateXFromY(y), line1To2.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point2.getY() + interval, point3.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line1To3.calculateXFromY(y), line2To4.calculateXFromY(y), y);
            });
            rangeForY = AlbaValueRange<double>(point3.getY() + interval, point4.getY(), interval);
            rangeForY.traverse([&](double const y) {
                result.emplace_back(line3To4.calculateXFromY(y), line2To4.calculateXFromY(y), y);
            });
        }
    }
    return result;
}

ostream& operator<<(ostream& out, Quadrilateral const& quadrilateral) {
    out << "[" << quadrilateral.m_vertices.at(0) << "][" << quadrilateral.m_vertices.at(1) << "]["
        << quadrilateral.m_vertices.at(2) << "][" << quadrilateral.m_vertices.at(3) << "]";
    return out;
}

}  // namespace TwoDimensions
}  // namespace alba
