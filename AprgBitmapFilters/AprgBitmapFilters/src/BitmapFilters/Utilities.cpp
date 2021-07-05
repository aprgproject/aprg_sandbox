#include "Utilities.hpp"

#include <cmath>

using namespace alba::TwoDimensions;

namespace alba
{

namespace AprgBitmap
{

Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition)
{
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY convertPointToBitmapXY(Point const& pointPosition)
{
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

void animeColorsInPenCircles(PenCircles & penCircles, AnimizeColor const& animizeColor)
{
    PenCircles::PointToPenCircleDetailsMap & map(penCircles.getPenCirclesReference());
    for(PenCircles::PointToPenCircleDetailsMap::iterator it=map.begin(); it!=map.end(); it++)
    {
        it->second.color = animizeColor.getNewColor(it->second.color);
    }
}

}

}
