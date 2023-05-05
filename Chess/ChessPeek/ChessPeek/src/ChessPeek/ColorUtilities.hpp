#pragma once

#include <cstdint>

namespace alba {

namespace chess {

double calculateColorIntensityDecimal(uint32_t const color);
uint8_t extractRed(uint32_t const color);
uint8_t extractGreen(uint32_t const color);
uint8_t extractBlue(uint32_t const color);

}  // namespace chess

}  // namespace alba
