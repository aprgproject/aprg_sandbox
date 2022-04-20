#pragma once

#include <cstdint>

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

bool isSimilar(uint32_t const color1, uint32_t const color2, uint32_t const similarityColorLimit);

uint32_t getColorValueOnly(uint32_t const value);

ColorPercentagesData calculateColorPercentagesData(uint32_t const color);
double calculateHueDegrees(ColorPercentagesData const& colorPercentagesData);
double calculateColorIntensityDecimal(uint32_t const color);
double calculateLuma601Decimal(uint32_t const color); //Rec. 601 NTSC
double calculateLuma709Decimal(uint32_t const color); //Rec. 709
double calculateSaturationColorIntensityDecimal(uint32_t const color);

HueSaturationLightnessData createHueSaturationLightnessData(double const hueDegrees, double const saturationLightnessDecimal, double const lightnessDecimal);
HueSaturationValueData createHueSaturationValueData(double const hueDegrees, double const saturationValueDecimal, double const valueDecimalOfColorMax);

uint32_t combineRgbToColor(uint8_t const red, uint8_t const green, uint8_t const blue);
uint32_t combine2Colors(uint32_t const color1, uint32_t const color2);

uint32_t convertChromaColorDataToColor(ChromaColorData const& chromaColorData);
HueSaturationLightnessData convertColorToHueSaturationLightnessData(uint32_t const color);
HueSaturationValueData convertColorToHueSaturationValueData(uint32_t const color);
uint32_t convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hslData);
uint32_t convertHueSaturationValueDataToColor(HueSaturationValueData const& hsvData);
HueSaturationValueData convertHslDataToHsvData(HueSaturationLightnessData const& hslData);
HueSaturationLightnessData convertHsvDataToHslData(HueSaturationValueData const& hsvData);

uint8_t extractRed(uint32_t const color);
uint8_t extractGreen(uint32_t const color);
uint8_t extractBlue(uint32_t const color);
uint8_t extractMaxForOneColor(uint32_t const color);
uint8_t extractMinForOneColor(uint32_t const color);

}

}

}
