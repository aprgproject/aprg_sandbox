#include "AprgColorUtilities.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>

using namespace std;

//https://en.wikipedia.org/wiki/HSL_and_HSV

namespace alba
{

namespace ColorUtilities
{

constexpr unsigned int MAX_COLOR_VALUE = 0xFF;

ColorAnalysisData calculateColorAnalysisData(unsigned int const color)
{
    ColorAnalysisData result;
    result.redPercentage = (double)extractRed(color)/MAX_COLOR_VALUE;
    result.greenPercentage = (double)extractGreen(color)/MAX_COLOR_VALUE;
    result.bluePercentage = (double)extractBlue(color)/MAX_COLOR_VALUE;
    result.colorMax = max(max(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.colorMin = min(min(result.redPercentage, result.greenPercentage), result.bluePercentage);
    result.deltaMaxMin = result.colorMax-result.colorMin;
    return result;
}

double calculateHueDegrees(ColorAnalysisData const& colorAnalysisData)
{
    double hueDegrees;
    if(colorAnalysisData.deltaMaxMin == 0)
    {
        hueDegrees = 0;
    }
    else
    {
        double hueBy60Degrees(0);
        if(colorAnalysisData.colorMax==colorAnalysisData.redPercentage)
        {
            hueBy60Degrees=fmod(((colorAnalysisData.greenPercentage-colorAnalysisData.bluePercentage)/colorAnalysisData.deltaMaxMin), 6);
        }
        else if(colorAnalysisData.colorMax==colorAnalysisData.greenPercentage)
        {
            hueBy60Degrees=(((colorAnalysisData.bluePercentage-colorAnalysisData.redPercentage)/colorAnalysisData.deltaMaxMin)+2);
        }
        else if(colorAnalysisData.colorMax==colorAnalysisData.bluePercentage)
        {
            hueBy60Degrees=(((colorAnalysisData.redPercentage-colorAnalysisData.greenPercentage)/colorAnalysisData.deltaMaxMin)+4);
        }
        hueDegrees = hueBy60Degrees*60;
    }
    return hueDegrees;
}

HueSaturationLightnessData createHueSaturationLightnessData(
        double const hueDegrees,
        double const saturationLightnessDecimal,
        double const lightnessDecimal)
{
    HueSaturationLightnessData result;
    result.hueDegrees = hueDegrees;
    result.saturationLightnessDecimal = saturationLightnessDecimal;
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

HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color)
{
    ColorAnalysisData colorAnalysisData(calculateColorAnalysisData(color));
    HueSaturationLightnessData result;
    result.hueDegrees = calculateHueDegrees(colorAnalysisData);
    result.lightnessDecimal = (colorAnalysisData.colorMax+colorAnalysisData.colorMin)/2;
    if(colorAnalysisData.deltaMaxMin == 0)
    {
        result.saturationLightnessDecimal = 0;
    }
    else
    {
        result.saturationLightnessDecimal = colorAnalysisData.deltaMaxMin/(1-mathHelper::getAbsoluteValue(result.lightnessDecimal*2-1));
    }
    return result;
}

HueSaturationValueData convertColorToHueSaturationValueData(unsigned int const color)
{
    ColorAnalysisData colorAnalysisData(calculateColorAnalysisData(color));
    HueSaturationValueData result;
    result.hueDegrees = calculateHueDegrees(colorAnalysisData);
    result.valueDecimalOfColorMax = colorAnalysisData.colorMax;
    if(colorAnalysisData.deltaMaxMin == 0)
    {
        result.saturationValueDecimal = 0;
    }
    else
    {
        result.saturationValueDecimal = colorAnalysisData.deltaMaxMin/colorAnalysisData.colorMax;
    }
    return result;
}

unsigned int convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hslData)
{
    ChromaColorData chromaColorData;
    chromaColorData.chroma = (1-mathHelper::getAbsoluteValue(hslData.lightnessDecimal*2-1))*hslData.saturationLightnessDecimal;
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
    return combineRgbToColor(
                static_cast<unsigned char>(round((redPrime+m)*MAX_COLOR_VALUE)),
                static_cast<unsigned char>(round((greenPrime+m)*MAX_COLOR_VALUE)),
                static_cast<unsigned char>(round((bluePrime+m)*MAX_COLOR_VALUE)));
}

unsigned char extractRed(unsigned int const color)
{
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

}

}
