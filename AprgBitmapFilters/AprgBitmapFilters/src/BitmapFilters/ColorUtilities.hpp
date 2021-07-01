#pragma once

namespace alba
{

namespace AprgBitmap
{

namespace ColorUtilities
{
struct ColorPercentagesData
{
    double redPercentage;
    double greenPercentage;
    double bluePercentage;
    double colorPercentageMax;
    double colorPercentageMin;
    double deltaMaxMinPercentage;
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

ColorPercentagesData calculateColorPercentagesData(unsigned int const color);
double calculateHueDegrees(ColorPercentagesData const& colorPercentagesData);
double calculateColorIntensityDecimal(unsigned int const color);
double calculateLuma601Decimal(unsigned int const color); //Rec. 601 NTSC
double calculateLuma709Decimal(unsigned int const color); //Rec. 709
double calculateSaturationColorIntensityDecimal(unsigned int const color);

HueSaturationLightnessData createHueSaturationLightnessData(double const hueDegrees, double const saturationLightnessDecimal, double const lightnessDecimal);
HueSaturationValueData createHueSaturationValueData(double const hueDegrees, double const saturationValueDecimal, double const valueDecimalOfColorMax);

unsigned int combineRgbToColor(unsigned char const red, unsigned char const green, unsigned char const blue);

unsigned int convertChromaColorDataToColor(ChromaColorData const& chromaColorData);
HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color);
HueSaturationValueData convertColorToHueSaturationValueData(unsigned int const color);
unsigned int convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hueSaturationLightnessData);
unsigned int convertHueSaturationValueDataToColor(HueSaturationValueData const& hsvData);
HueSaturationValueData convertHslDataToHsvData(HueSaturationLightnessData const& hslData);
HueSaturationLightnessData convertHsvDataToHslData(HueSaturationValueData const& hsvData);

unsigned char extractRed(unsigned int const color);
unsigned char extractGreen(unsigned int const color);
unsigned char extractBlue(unsigned int const color);
unsigned char extractMaxForOneColor(unsigned int const color);
unsigned char extractMinForOneColor(unsigned int const color);

}

}

}