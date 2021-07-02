#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <Bitmap/CommonTypes.hpp>
#include <BitmapTraversal/OutwardCircleTraversal.hpp>
#include <TwoDimensions/Circle.hpp>

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

    void traverse(
            TwoDimensions::Circle const& circle,
            TraverseOperation const& traverseOperation) const;
    void traverse(
            BitmapXY const& centerPoint,
            OutwardCircleTraversal::RadiusCoordinatesPair const& radiusCoordinatesPair,
            TraverseOperation const& traverseOperation) const;

private:
    void checkPointBeforeDoingTraverseOperation(
            BitmapXY const& point,
            TraverseOperation const& traverseOperation) const;
    BitmapSnippet const& m_bitmapSnippet;
};

}

}
