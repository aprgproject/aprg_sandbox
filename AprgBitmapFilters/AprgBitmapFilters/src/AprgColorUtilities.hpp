#pragma once

namespace alba
{

namespace ColorUtilities
{

struct ColorAnalysisData
{
    double redPercentage;
    double greenPercentage;
    double bluePercentage;
    double colorMax;
    double colorMin;
    double deltaMaxMin;
};

struct HueSaturationLightnessData
{
    double hueDegrees;
    double saturationLightnessDecimal;
    double lightnessDecimal;
};

struct HueSaturationValueData
{
    double hueDegrees;
    double saturationValueDecimal;
    double valueDecimalOfColorMax;
};

struct ChromaColorData
{
    double chroma;
    double xSecondLargestComponent;
    double mOffset;
    double hueDegrees;
};

ColorAnalysisData calculateColorAnalysisData(unsigned int const color);
double calculateHueDegrees(ColorAnalysisData const& colorAnalysisData);

HueSaturationLightnessData createHueSaturationLightnessData(double const hueDegrees, double const saturationLightnessDecimal, double const lightnessDecimal);
HueSaturationValueData createHueSaturationValueData(double const hueDegrees, double const saturationValueDecimal, double const valueDecimalOfColorMax);

unsigned int combineRgbToColor(unsigned char const red, unsigned char const green, unsigned char const blue);

HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color);
HueSaturationValueData convertColorToHueSaturationValueData(unsigned int const color);
unsigned int convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hueSaturationLightnessData);
unsigned int convertHueSaturationValueDataToColor(HueSaturationValueData const& hsvData);
unsigned int convertChromaColorDataToColor(ChromaColorData const& chromaColorData);

unsigned char extractRed(unsigned int const color);
unsigned char extractGreen(unsigned int const color);
unsigned char extractBlue(unsigned int const color);

}

}
