#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <Bitmap/CommonTypes.hpp>
#include <Geometry/TwoDimensions/Circle.hpp>
#include <Geometry/TwoDimensions/Quadrilateral.hpp>

#include <functional>
namespace alba
{
namespace AprgBitmap
{

class BitmapSnippetTraversal
{
public:
    using TraverseOperation = std::function<void(BitmapXY const&)>;

    BitmapSnippetTraversal(BitmapSnippet const& bitmapSnippet);

    void traverseCircleArea(
            TwoDimensions::Circle const& circle,
            TraverseOperation const& traverseOperation) const;
    void traverseQuadrilateralArea(
            TwoDimensions::Quadrilateral const& quadrilateral,
            TraverseOperation const& traverseOperation) const;
    void traverseCoordinatesCombinations(
            BitmapXY const& centerPoint,
            unsigned int const coordinate1,
            unsigned int const coordinate2,
            TraverseOperation const& traverseOperation) const;
    void traverse4WayConnectivity(
            BitmapXY const& centerPoint,
            TraverseOperation const& traverseOperation) const;
    void traverse8WayConnectivity(
            BitmapXY const& centerPoint,
            TraverseOperation const& traverseOperation) const;

private:
    void checkPointBeforeDoingTraverseOperation(
            BitmapXY const& point,
            TraverseOperation const& traverseOperation) const;
    BitmapSnippet const& m_bitmapSnippet;
};

}

}
