#pragma once

namespace alba
{

namespace ColorUtilities
{

struct HueSaturationLightnessData
{
    double hueDegrees;
    double saturationDecimal;
    double lightnessDecimal;
};

HueSaturationLightnessData createHueSaturationLightnessData(double const hueDegrees, double const saturationDecimal, double const lightnessDecimal);
HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color);
unsigned int  convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hueSaturationLightnessData);

unsigned char extractRed(unsigned int const color);
unsigned char extractGreen(unsigned int const color);
unsigned char extractBlue(unsigned int const color);
unsigned int combineRgbColor(unsigned char const red, unsigned char const green, unsigned char const blue);

}

}
