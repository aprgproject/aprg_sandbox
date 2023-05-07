#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <ChessPeek/CommonTypes.hpp>

#include <cstdint>

namespace alba {

namespace chess {

XY convertToXY(AprgBitmap::BitmapXY const& bitmapXY);
AprgBitmap::BitmapXY convertToBitmapXY(XY const& xy);
double calculateColorIntensityDecimal(uint32_t const color);
uint8_t extractRed(uint32_t const color);
uint8_t extractGreen(uint32_t const color);
uint8_t extractBlue(uint32_t const color);

}  // namespace chess

}  // namespace alba
