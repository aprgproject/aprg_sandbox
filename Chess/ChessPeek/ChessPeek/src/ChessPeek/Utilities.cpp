#include "Utilities.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

XY convertToXY(BitmapXY const& bitmapXY) {
    return {static_cast<int>(bitmapXY.getX()), static_cast<int>(bitmapXY.getY())};
}

BitmapXY convertToBitmapXY(XY const& xy) {
    return {static_cast<unsigned int>(xy.getX()), static_cast<unsigned int>(xy.getY())};
}

double calculateColorIntensityDecimal(uint32_t const color) {
    return (((double)extractRed(color) + extractGreen(color) + extractBlue(color)) / 0xFF) / 3;
}

uint8_t extractRed(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color)); }

uint8_t extractGreen(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color)); }

uint8_t extractBlue(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color)); }

}  // namespace chess

}  // namespace alba
