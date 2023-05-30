#include "BitmapSnippetTraversal.hpp"

#include <BitmapManipulator/Utilities.hpp>

using namespace alba::TwoDimensions;

namespace alba {

namespace AprgBitmap {

BitmapSnippetTraversal::BitmapSnippetTraversal(BitmapSnippet const& bitmapSnippet) : m_bitmapSnippet(bitmapSnippet) {}

void BitmapSnippetTraversal::traverseCircleArea(
    Circle const& circle, TraverseOperation const& traverseOperation) const {
    circle.traverseArea(1, [&](Point const& point) {
        checkPointBeforeDoingTraverseOperation(convertPointToBitmapXY(point), traverseOperation);
    });
}

void BitmapSnippetTraversal::traverseQuadrilateralArea(
    Quadrilateral const& quadrilateral, TraverseOperation const& traverseOperation) const {
    quadrilateral.traverseArea(1, [&](Point const& point) {
        checkPointBeforeDoingTraverseOperation(convertPointToBitmapXY(point), traverseOperation);
    });
}

void BitmapSnippetTraversal::traverseCoordinatesCombinations(
    BitmapXY const& centerPoint, int const coordinate1, int const coordinate2,
    TraverseOperation const& traverseOperation) const {
    int i = coordinate1;
    int j = coordinate2;
    if (i == 0 && j == 0) {
        checkPointBeforeDoingTraverseOperation(centerPoint, traverseOperation);
    } else if (i == 0) {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + j, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - j, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() + j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() - j), traverseOperation);
    } else if (j == 0) {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + i, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - i, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() + i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() - i), traverseOperation);
    } else if (i == j) {
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + i, centerPoint.getY() + i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - i, centerPoint.getY() + i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + i, centerPoint.getY() - i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - i, centerPoint.getY() - i), traverseOperation);
    } else {
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + i, centerPoint.getY() + j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - i, centerPoint.getY() + j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + i, centerPoint.getY() - j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - i, centerPoint.getY() - j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + j, centerPoint.getY() + i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - j, centerPoint.getY() + i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() + j, centerPoint.getY() - i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(
            BitmapXY(centerPoint.getX() - j, centerPoint.getY() - i), traverseOperation);
    }
}

void BitmapSnippetTraversal::traverse4WayConnectivity(
    BitmapXY const& centerPoint, TraverseOperation const& traverseOperation) const {
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - 1, centerPoint.getY()), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + 1, centerPoint.getY()), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() - 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() + 1), traverseOperation);
}

void BitmapSnippetTraversal::traverse8WayConnectivity(
    BitmapXY const& centerPoint, TraverseOperation const& traverseOperation) const {
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - 1, centerPoint.getY()), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + 1, centerPoint.getY()), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() - 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY() + 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - 1, centerPoint.getY() - 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() - 1, centerPoint.getY() + 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + 1, centerPoint.getY() - 1), traverseOperation);
    checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX() + 1, centerPoint.getY() + 1), traverseOperation);
}

void BitmapSnippetTraversal::checkPointBeforeDoingTraverseOperation(
    BitmapXY const& point, TraverseOperation const& traverseOperation) const {
    if (m_bitmapSnippet.isPositionInsideTheSnippet(point)) {
        traverseOperation(point);
    }
}

}  // namespace AprgBitmap

}  // namespace alba
