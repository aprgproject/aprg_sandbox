#include "ColorUtilities.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>

using namespace alba::mathHelper;
using namespace std;

// https://en.wikipedia.org/wiki/HSL_and_HSV

namespace alba {

namespace AprgBitmap {

namespace ColorUtilities {

constexpr uint8_t MAX_COLOR_VALUE = 0xFF;

bool isSimilar(uint32_t const color1, uint32_t const color2, uint32_t const similarityColorLimit)  // RGB algo
{
    bool isRedDifferenceBeyondLimit =
        getPositiveDelta<uint32_t>(extractRed(color1), extractRed(color2)) > similarityColorLimit;
    bool isGreenDifferenceBeyondLimit =
        getPositiveDelta<uint32_t>(extractGreen(color1), extractGreen(color2)) > similarityColorLimit;
    bool isBlueDifferenceBeyondLimit =
        getPositiveDelta<uint32_t>(extractBlue(color1), extractBlue(color2)) > similarityColorLimit;
    return !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

uint32_t getColorValueOnly(uint32_t const value) { return 0xFFFFFF & value; }

/*
bool isSimilar(uint32_t const color1, uint32_t const color2)//Pythagorean algo
{
    double
colorDifferenceAcrossDifferentColors(getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2),
(double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2))); return
colorDifferenceAcrossDifferentColors < m_similarityColorLimit;
}
*/

ColorPercentagesData calculateColorPercentagesData(uint32_t const color) {
    ColorPercentagesData result{};
    double red = extractRed(color);
    double green = extractGreen(color);
    double blue = extractBlue(color);
    result.redPercentage = red / MAX_COLOR_VALUE;
    result.greenPercentage = green / MAX_COLOR_VALUE;
    result.bluePercentage = blue / MAX_COLOR_VALUE;
    result.colorPercentageMax = max(max(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.colorPercentageMin = min(min(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.deltaMaxMinPercentage = result.colorPercentageMax - result.colorPercentageMin;
    return result;
}

double calculateHueDegrees(ColorPercentagesData const& colorPercentagesData) {
    double hueDegrees;
    if (colorPercentagesData.deltaMaxMinPercentage == 0) {
        hueDegrees = 0;
    } else {
        double hueBy60Degrees(0);
        if (colorPercentagesData.colorPercentageMax == colorPercentagesData.redPercentage) {
            hueBy60Degrees = (colorPercentagesData.greenPercentage - colorPercentagesData.bluePercentage) /
                             colorPercentagesData.deltaMaxMinPercentage;
        } else if (colorPercentagesData.colorPercentageMax == colorPercentagesData.greenPercentage) {
            hueBy60Degrees = ((colorPercentagesData.bluePercentage - colorPercentagesData.redPercentage) /
                              colorPercentagesData.deltaMaxMinPercentage) +
                             2;
        } else if (colorPercentagesData.colorPercentageMax == colorPercentagesData.bluePercentage) {
            hueBy60Degrees = ((colorPercentagesData.redPercentage - colorPercentagesData.greenPercentage) /
                              colorPercentagesData.deltaMaxMinPercentage) +
                             4;
        }
        hueDegrees = hueBy60Degrees * 60;
        if (hueDegrees < 0) {
            hueDegrees += 360;
        }
    }
    return hueDegrees;
}

double calculateColorIntensityDecimal(uint32_t const color) {
    return (((double)extractRed(color) + extractGreen(color) + extractBlue(color)) / MAX_COLOR_VALUE) / 3;
}

double calculateLuma601Decimal(uint32_t const color) {
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    return colorPercentagesData.redPercentage * 0.2990 + colorPercentagesData.greenPercentage * 0.5870 +
           colorPercentagesData.bluePercentage * 0.1140;
}

double calculateLuma709Decimal(uint32_t const color) {
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    return colorPercentagesData.redPercentage * 0.2126 + colorPercentagesData.greenPercentage * 0.7152 +
           colorPercentagesData.bluePercentage * 0.0722;
}

double calculateSaturationColorIntensityDecimal(uint32_t const color) {
    double result;
    double colorIntensityDecimal(calculateColorIntensityDecimal(color));
    if (colorIntensityDecimal == 0) {
        result = 0;
    } else {
        result = 1 - ((double)extractMinForOneColor(color) / MAX_COLOR_VALUE / colorIntensityDecimal);
    }
    return result;
}

HueSaturationLightnessData createHueSaturationLightnessData(
    double const hueDegrees, double const saturationLightnessDecimal, double const lightnessDecimal) {
    HueSaturationLightnessData result{};
    result.hueDegrees = hueDegrees;
    result.saturationLightnessDecimal = saturationLightnessDecimal;
    result.lightnessDecimal = lightnessDecimal;
    return result;
}

HueSaturationValueData createHueSaturationValueData(
    double const hueDegrees, double const saturationValueDecimal, double const valueDecimalOfColorMax) {
    HueSaturationValueData result{};
    result.hueDegrees = hueDegrees;
    result.saturationValueDecimal = saturationValueDecimal;
    result.valueDecimalOfColorMax = valueDecimalOfColorMax;
    return result;
}

uint32_t combineRgbToColor(uint8_t const red, uint8_t const green, uint8_t const blue) {
    return AlbaBitManipulation<uint32_t>::concatenateBytes(red, green, blue);
}

uint32_t combine2Colors(uint32_t const color1, uint32_t const color2) {
    return combineRgbToColor(
        static_cast<uint8_t>(round(static_cast<double>(extractRed(color1) + extractRed(color2)) / 2)),
        static_cast<uint8_t>(round(static_cast<double>(extractGreen(color1) + extractGreen(color2)) / 2)),
        static_cast<uint8_t>(round(static_cast<double>(extractBlue(color1) + extractBlue(color2)) / 2)));
}

uint32_t convertChromaColorDataToColor(ChromaColorData const& chromaColorData) {
    double c = chromaColorData.chroma;
    double x = chromaColorData.xSecondLargestComponent;
    double m = chromaColorData.mOffset;
    double hueDegrees(chromaColorData.hueDegrees);
    double redPrime(0);
    double greenPrime(0);
    double bluePrime(0);
    if (hueDegrees >= 0 && hueDegrees < 60) {
        redPrime = c;
        greenPrime = x;
        bluePrime = 0;
    } else if (hueDegrees >= 60 && hueDegrees < 120) {
        redPrime = x;
        greenPrime = c;
        bluePrime = 0;
    } else if (hueDegrees >= 120 && hueDegrees < 180) {
        redPrime = 0;
        greenPrime = c;
        bluePrime = x;
    } else if (hueDegrees >= 180 && hueDegrees < 240) {
        redPrime = 0;
        greenPrime = x;
        bluePrime = c;
    } else if (hueDegrees >= 240 && hueDegrees < 300) {
        redPrime = x;
        greenPrime = 0;
        bluePrime = c;
    } else if (hueDegrees >= 300 && hueDegrees < 360) {
        redPrime = c;
        greenPrime = 0;
        bluePrime = x;
    }
    return combineRgbToColor(
        static_cast<uint8_t>(round((redPrime + m) * MAX_COLOR_VALUE)),
        static_cast<uint8_t>(round((greenPrime + m) * MAX_COLOR_VALUE)),
        static_cast<uint8_t>(round((bluePrime + m) * MAX_COLOR_VALUE)));
}

HueSaturationLightnessData convertColorToHueSaturationLightnessData(uint32_t const color) {
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    HueSaturationLightnessData result{};
    result.hueDegrees = calculateHueDegrees(colorPercentagesData);
    result.lightnessDecimal = (colorPercentagesData.colorPercentageMax + colorPercentagesData.colorPercentageMin) / 2;
    if (colorPercentagesData.deltaMaxMinPercentage == 0) {
        result.saturationLightnessDecimal = 0;
    } else {
        result.saturationLightnessDecimal =
            colorPercentagesData.deltaMaxMinPercentage / (1 - getAbsoluteValue(result.lightnessDecimal * 2 - 1));
    }
    return result;
}

HueSaturationValueData convertColorToHueSaturationValueData(uint32_t const color) {
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    HueSaturationValueData result{};
    result.hueDegrees = calculateHueDegrees(colorPercentagesData);
    result.valueDecimalOfColorMax = colorPercentagesData.colorPercentageMax;
    if (colorPercentagesData.colorPercentageMax == 0) {
        result.saturationValueDecimal = 0;
    } else {
        result.saturationValueDecimal =
            colorPercentagesData.deltaMaxMinPercentage / colorPercentagesData.colorPercentageMax;
    }
    return result;
}

uint32_t convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hslData) {
    ChromaColorData chromaColorData{};
    chromaColorData.chroma =
        (1 - getAbsoluteValue(hslData.lightnessDecimal * 2 - 1)) * hslData.saturationLightnessDecimal;
    chromaColorData.xSecondLargestComponent =
        chromaColorData.chroma * (1 - getAbsoluteValue(fmod((hslData.hueDegrees / 60), 2) - 1));
    chromaColorData.mOffset = hslData.lightnessDecimal - (chromaColorData.chroma / 2);
    chromaColorData.hueDegrees = hslData.hueDegrees;
    return convertChromaColorDataToColor(chromaColorData);
}

uint32_t convertHueSaturationValueDataToColor(HueSaturationValueData const& hsvData) {
    ChromaColorData chromaColorData{};
    chromaColorData.chroma = hsvData.valueDecimalOfColorMax * hsvData.saturationValueDecimal;
    chromaColorData.xSecondLargestComponent =
        chromaColorData.chroma * (1 - getAbsoluteValue(fmod((hsvData.hueDegrees / 60), 2) - 1));
    chromaColorData.mOffset = hsvData.valueDecimalOfColorMax - chromaColorData.chroma;
    chromaColorData.hueDegrees = hsvData.hueDegrees;
    return convertChromaColorDataToColor(chromaColorData);
}

HueSaturationValueData convertHslDataToHsvData(HueSaturationLightnessData const& hslData) {
    HueSaturationValueData result{};
    result.hueDegrees = hslData.hueDegrees;
    result.valueDecimalOfColorMax =
        hslData.lightnessDecimal +
        hslData.saturationLightnessDecimal * min(hslData.lightnessDecimal, 1 - hslData.lightnessDecimal);
    if (result.valueDecimalOfColorMax == 0) {
        result.saturationValueDecimal = 0;
    } else {
        result.saturationValueDecimal = 2 - (2 * hslData.lightnessDecimal / result.valueDecimalOfColorMax);
    }
    return result;
}

HueSaturationLightnessData convertHsvDataToHslData(HueSaturationValueData const& hsvData) {
    HueSaturationLightnessData result{};
    result.hueDegrees = hsvData.hueDegrees;
    result.lightnessDecimal =
        hsvData.valueDecimalOfColorMax - (hsvData.valueDecimalOfColorMax * hsvData.saturationValueDecimal / 2);
    if (result.lightnessDecimal == 0 || result.lightnessDecimal == 1) {
        result.saturationLightnessDecimal = 0;
    } else {
        result.saturationLightnessDecimal = (hsvData.valueDecimalOfColorMax - result.lightnessDecimal) /
                                            (min(result.lightnessDecimal, 1 - result.lightnessDecimal));
    }
    return result;
}

uint8_t extractRed(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color)); }

uint8_t extractGreen(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color)); }

uint8_t extractBlue(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color)); }

uint8_t extractMaxForOneColor(uint32_t const color) {
    return max(max(extractRed(color), extractGreen(color)), extractBlue(color));
}

uint8_t extractMinForOneColor(uint32_t const color) {
    return min(min(extractRed(color), extractGreen(color)), extractBlue(color));
}

}  // namespace ColorUtilities

}  // namespace AprgBitmap

}  // namespace alba
