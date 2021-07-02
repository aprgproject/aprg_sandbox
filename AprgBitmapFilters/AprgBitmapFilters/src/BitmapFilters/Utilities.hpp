#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <TwoDimensions/Point.hpp>

namespace alba
{

namespace AprgBitmap
{

TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition);
BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition);

}

}
