#include "AprgColorUtilities.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>


#include <Debug/AlbaDebug.hpp>

using namespace std;

//https://en.wikipedia.org/wiki/HSL_and_HSV
namespace alba
{
namespace ColorUtilities
{

constexpr unsigned int MAX_COLOR_VALUE = 0xFF;

ColorPercentagesData calculateColorPercentagesData(unsigned int const color)
{
    ColorPercentagesData result;
    double red = extractRed(color);
    double green = extractGreen(color);
    double blue = extractBlue(color);
    result.redPercentage = red/MAX_COLOR_VALUE;
    result.greenPercentage = green/MAX_COLOR_VALUE;
    result.bluePercentage = blue/MAX_COLOR_VALUE;
    result.colorPercentageMax = max(max(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.colorPercentageMin = min(min(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.deltaMaxMinPercentage = result.colorPercentageMax-result.colorPercentageMin;
    return result;
}

double calculateHueDegrees(ColorPercentagesData const& colorPercentagesData)
{
    double hueDegrees;
    if(colorPercentagesData.deltaMaxMinPercentage == 0)
    {
        hueDegrees = 0;
    }    else
    {
        double hueBy60Degrees(0);
        if(colorPercentagesData.colorPercentageMax==colorPercentagesData.redPercentage)
        {
            hueBy60Degrees=fmod(((colorPercentagesData.greenPercentage-colorPercentagesData.bluePercentage)/colorPercentagesData.deltaMaxMinPercentage), 6);
        }
        else if(colorPercentagesData.colorPercentageMax==colorPercentagesData.greenPercentage)
        {
            hueBy60Degrees=(((colorPercentagesData.bluePercentage-colorPercentagesData.redPercentage)/colorPercentagesData.deltaMaxMinPercentage)+2);
        }
        else if(colorPercentagesData.colorPercentageMax==colorPercentagesData.bluePercentage)
        {
            hueBy60Degrees=(((colorPercentagesData.redPercentage-colorPercentagesData.greenPercentage)/colorPercentagesData.deltaMaxMinPercentage)+4);
        }
        hueDegrees = hueBy60Degrees*60;
    }    return hueDegrees;
}

double calculateColorIntensityDecimal(unsigned int const color)
{
    return (((double)extractRed(color)+extractGreen(color)+extractBlue(color))/MAX_COLOR_VALUE)/3;
}

double calculateLuma601Decimal(unsigned int const color)
{
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    return colorPercentagesData.redPercentage*0.2990 +
            colorPercentagesData.greenPercentage*0.5870 +
            colorPercentagesData.bluePercentage*0.1140;
}

double calculateLuma709Decimal(unsigned int const color)
{
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    return colorPercentagesData.redPercentage*0.2126 +
            colorPercentagesData.greenPercentage*0.7152 +
            colorPercentagesData.bluePercentage*0.0722;
}

double calculateSaturationColorIntensityDecimal(unsigned int const color)
{
    double result;
    double colorIntensityDecimal(calculateColorIntensityDecimal(color));
    if(colorIntensityDecimal == 0)
    {
        result = 0;
    }
    else
    {
        result = 1-((double)extractMinForOneColor(color)/MAX_COLOR_VALUE/colorIntensityDecimal);
    }
    return result;
}

HueSaturationLightnessData createHueSaturationLightnessData(
        double const hueDegrees,
        double const saturationLightnessDecimal,        double const lightnessDecimal)
{
    HueSaturationLightnessData result;
    result.hueDegrees = hueDegrees;    result.saturationLightnessDecimal = saturationLightnessDecimal;
    result.lightnessDecimal = lightnessDecimal;
    return result;
}

HueSaturationValueData createHueSaturationValueData(
        double const hueDegrees,
        double const saturationValueDecimal,
        double const valueDecimalOfColorMax)
{
    HueSaturationValueData result;
    result.hueDegrees = hueDegrees;
    result.saturationValueDecimal = saturationValueDecimal;
    result.valueDecimalOfColorMax = valueDecimalOfColorMax;
    return result;
}

unsigned int combineRgbToColor(unsigned char const red, unsigned char const green, unsigned char const blue)
{
    return AlbaBitManipulation<unsigned int>::concatenateBytes(red, green, blue);
}

unsigned int convertChromaColorDataToColor(ChromaColorData const& chromaColorData)
{
    double c = chromaColorData.chroma;
    double x = chromaColorData.xSecondLargestComponent;
    double m = chromaColorData.mOffset;
    double hueDegrees(chromaColorData.hueDegrees);
    double redPrime(0);
    double greenPrime(0);
    double bluePrime(0);
    if(hueDegrees>=0 && hueDegrees<60)
    {
        redPrime = c; greenPrime = x; bluePrime=0;
    }
    else if(hueDegrees>=60 && hueDegrees<120)
    {
        redPrime = x; greenPrime = c; bluePrime=0;
    }
    else if(hueDegrees>=120 && hueDegrees<180)
    {
        redPrime = 0; greenPrime = c; bluePrime=x;
    }
    else if(hueDegrees>=180 && hueDegrees<240)
    {
        redPrime = 0; greenPrime = x; bluePrime=c;
    }
    else if(hueDegrees>=240 && hueDegrees<300)
    {
        redPrime = x; greenPrime = 0; bluePrime=c;
    }
    else if(hueDegrees>=300 && hueDegrees<360)
    {
        redPrime = c; greenPrime = 0; bluePrime=x;
    }
    ALBA_PRECISION(20);
    ALBA_PRINT4(c,x,m,hueDegrees);
    ALBA_PRINT3(redPrime,greenPrime,bluePrime);
    ALBA_PRINT3(round((redPrime+m)*MAX_COLOR_VALUE),round((greenPrime+m)*MAX_COLOR_VALUE),round((bluePrime+m)*MAX_COLOR_VALUE));
    return combineRgbToColor(
                static_cast<unsigned char>(round((redPrime+m)*MAX_COLOR_VALUE)),
                static_cast<unsigned char>(round((greenPrime+m)*MAX_COLOR_VALUE)),
                static_cast<unsigned char>(round((bluePrime+m)*MAX_COLOR_VALUE)));
}

HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color)
{
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    HueSaturationLightnessData result;
    result.hueDegrees = calculateHueDegrees(colorPercentagesData);
    result.lightnessDecimal = (colorPercentagesData.colorPercentageMax+colorPercentagesData.colorPercentageMin)/2;
    if(colorPercentagesData.deltaMaxMinPercentage == 0)
    {
        result.saturationLightnessDecimal = 0;
    }
    else
    {
        result.saturationLightnessDecimal = colorPercentagesData.deltaMaxMinPercentage/(1-mathHelper::getAbsoluteValue(result.lightnessDecimal*2-1));
    }
    return result;
}
HueSaturationValueData convertColorToHueSaturationValueData(unsigned int const color)
{
    ColorPercentagesData colorPercentagesData(calculateColorPercentagesData(color));
    HueSaturationValueData result;
    result.hueDegrees = calculateHueDegrees(colorPercentagesData);
    result.valueDecimalOfColorMax = colorPercentagesData.colorPercentageMax;
    if(colorPercentagesData.colorPercentageMax == 0)
    {
        result.saturationValueDecimal = 0;
    }
    else
    {
        result.saturationValueDecimal = colorPercentagesData.deltaMaxMinPercentage/colorPercentagesData.colorPercentageMax;
    }
    return result;
}
unsigned int convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hslData)
{
    ChromaColorData chromaColorData;    chromaColorData.chroma = (1-mathHelper::getAbsoluteValue(hslData.lightnessDecimal*2-1))*hslData.saturationLightnessDecimal;
    chromaColorData.xSecondLargestComponent = chromaColorData.chroma*(1-mathHelper::getAbsoluteValue(fmod((hslData.hueDegrees/60), 2)-1));
    chromaColorData.mOffset = hslData.lightnessDecimal-(chromaColorData.chroma/2);
    chromaColorData.hueDegrees = hslData.hueDegrees;
    return convertChromaColorDataToColor(chromaColorData);
}

unsigned int convertHueSaturationValueDataToColor(HueSaturationValueData const& hsvData)
{
    ChromaColorData chromaColorData;
    chromaColorData.chroma = hsvData.valueDecimalOfColorMax*hsvData.saturationValueDecimal;
    chromaColorData.xSecondLargestComponent = chromaColorData.chroma*(1-mathHelper::getAbsoluteValue(fmod((hsvData.hueDegrees/60), 2)-1));
    chromaColorData.mOffset = hsvData.valueDecimalOfColorMax-chromaColorData.chroma;
    chromaColorData.hueDegrees = hsvData.hueDegrees;
    return convertChromaColorDataToColor(chromaColorData);
}

HueSaturationValueData convertHslDataToHsvData(HueSaturationLightnessData const& hslData)
{
    HueSaturationValueData result;
    result.hueDegrees = hslData.hueDegrees;
    result.valueDecimalOfColorMax = hslData.lightnessDecimal + hslData.saturationLightnessDecimal*min(hslData.lightnessDecimal, 1-hslData.lightnessDecimal);
    if(result.valueDecimalOfColorMax==0)
    {
        result.saturationValueDecimal=0;
    }
    else
    {
        result.saturationValueDecimal=2-(2*hslData.lightnessDecimal/result.valueDecimalOfColorMax);
    }
    return result;
}

HueSaturationLightnessData convertHsvDataToHslData(HueSaturationValueData const& hsvData)
{
    HueSaturationLightnessData result;
    result.hueDegrees = hsvData.hueDegrees;
    result.lightnessDecimal = hsvData.valueDecimalOfColorMax-(hsvData.valueDecimalOfColorMax*hsvData.saturationValueDecimal/2);
    if(result.lightnessDecimal==0 || result.lightnessDecimal==1)
    {
        result.saturationLightnessDecimal=0;
    }
    else
    {
        result.saturationLightnessDecimal = (hsvData.valueDecimalOfColorMax-result.lightnessDecimal) /
                (min(result.lightnessDecimal, 1-result.lightnessDecimal));
    }
    return result;
}

unsigned char extractRed(unsigned int const color){
    return (AlbaBitManipulation<unsigned int>::getByteAt<2>(color));
}
unsigned char extractGreen(unsigned int const color)
{
    return (AlbaBitManipulation<unsigned int>::getByteAt<1>(color));
}

unsigned char extractBlue(unsigned int const color)
{
    return (AlbaBitManipulation<unsigned int>::getByteAt<0>(color));
}

unsigned char extractMaxForOneColor(unsigned int const color)
{
    return max(max(extractRed(color), extractGreen(color)), extractBlue(color));
}

unsigned char extractMinForOneColor(unsigned int const color)
{
    return min(min(extractRed(color), extractGreen(color)), extractBlue(color));
}

}

}