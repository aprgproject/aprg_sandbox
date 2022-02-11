#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/PenCircles.hpp>
#include <Geometry/TwoDimensions/Point.hpp>

namespace alba
{
namespace AprgBitmap
{
TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition);
BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition);
void animeColorsInPenCircles(PenCircles & penCircles, AnimizeColor const& animizeColor);

}

}
