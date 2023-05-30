#include "Utilities.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

XY convertToXY(BitmapXY const& bitmapXY) { return bitmapXY; }

BitmapXY convertToBitmapXY(XY const& xy) { return xy; }

double calculateColorIntensityDecimal(uint32_t const color) {
    return (((double)extractRed(color) + extractGreen(color) + extractBlue(color)) / 0xFF) / 3;
}

uint8_t extractRed(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color)); }

uint8_t extractGreen(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color)); }

uint8_t extractBlue(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color)); }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
