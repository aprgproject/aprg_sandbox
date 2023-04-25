#include "Utilities.hpp"

#include <cmath>

using namespace alba::TwoDimensions;

namespace alba {

namespace AprgBitmap {

Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) {
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY convertPointToBitmapXY(Point const& pointPosition) {
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

void animeColorsInPenCircles(PenCircles& penCircles, AnimizeColor const& animizeColor) {
    PenCircles::PointToPenCircleDetailsMap& map(penCircles.getPenCirclesReference());
    for (auto& pointAndPenCircleDetails : map) {
        pointAndPenCircleDetails.second.color = animizeColor.getNewColor(pointAndPenCircleDetails.second.color);
    }
}

}  // namespace AprgBitmap

}  // namespace alba
