#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

namespace alba
{

namespace AprgBitmap
{

TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition);
BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition);
void animeColorsInPenCircles(PenCircles & penCircles, AnimizeColor const& animizeColor);

}

}
