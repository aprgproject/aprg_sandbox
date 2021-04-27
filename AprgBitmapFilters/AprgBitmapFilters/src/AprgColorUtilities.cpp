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

HueSaturationLightnessData createHueSaturationLightnessData(
        double const hueDegrees,
        double const saturationDecimal,
        double const lightnessDecimal)
{
    HueSaturationLightnessData result;
    result.hueDegrees = hueDegrees;
    result.saturationDecimal = saturationDecimal;
    result.lightnessDecimal = lightnessDecimal;
    return result;
}

HueSaturationLightnessData convertColorToHueSaturationLightnessData(unsigned int const color)
{
    double redPercentage = (double)extractRed(color)/MAX_COLOR_VALUE;
    double greenPercentage = (double)extractGreen(color)/MAX_COLOR_VALUE;
    double bluePercentage = (double)extractBlue(color)/MAX_COLOR_VALUE;
    double colorMax = max(max(redPercentage, greenPercentage), bluePercentage);
    double colorMin = min(min(redPercentage, greenPercentage), bluePercentage);
    double deltaMaxMin = colorMax-colorMin;
    HueSaturationLightnessData result;
    result.lightnessDecimal = ((double)colorMax+colorMin)/2;
    if(deltaMaxMin == 0)
    {
        result.hueDegrees = 0;
        result.saturationDecimal = 0;
    }
    else
    {
        result.saturationDecimal = deltaMaxMin/(1-mathHelper::getAbsoluteValue(result.lightnessDecimal*2-1));
        double hueBy60Degrees(0);
        if(colorMax==redPercentage)
        {
            hueBy60Degrees=fmod(((greenPercentage-bluePercentage)/deltaMaxMin), 6);
        }
        else if(colorMax==greenPercentage)
        {
            hueBy60Degrees=(((bluePercentage-redPercentage)/deltaMaxMin)+2);
        }
        else if(colorMax==bluePercentage)
        {
            hueBy60Degrees=(((redPercentage-greenPercentage)/deltaMaxMin)+4);
        }
        result.hueDegrees = hueBy60Degrees*60;
    }
    return result;
}

unsigned int convertHueSaturationLightnessDataToColor(HueSaturationLightnessData const& hslData)
{
    double c = (1-mathHelper::getAbsoluteValue(hslData.lightnessDecimal*2-1))*hslData.saturationDecimal;
    double x = c*(1-mathHelper::getAbsoluteValue(fmod((hslData.hueDegrees/60), 2)-1));
    double m = hslData.lightnessDecimal-(c/2);
    double redPrime(0);
    double greenPrime(0);
    double bluePrime(0);
    if(hslData.hueDegrees>=0 && hslData.hueDegrees<60)
    {
        redPrime = c; greenPrime = x; bluePrime=0;
    }
    else if(hslData.hueDegrees>=60 && hslData.hueDegrees<120)
    {
        redPrime = x; greenPrime = c; bluePrime=0;
    }
    else if(hslData.hueDegrees>=120 && hslData.hueDegrees<180)
    {
        redPrime = 0; greenPrime = c; bluePrime=x;
    }
    else if(hslData.hueDegrees>=180 && hslData.hueDegrees<240)
    {
        redPrime = 0; greenPrime = x; bluePrime=c;
    }
    else if(hslData.hueDegrees>=240 && hslData.hueDegrees<300)
    {
        redPrime = x; greenPrime = 0; bluePrime=c;
    }
    else if(hslData.hueDegrees>=300 && hslData.hueDegrees<360)
    {
        redPrime = c; greenPrime = 0; bluePrime=x;
    }
    return combineRgbColor(
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

unsigned int combineRgbColor(unsigned char const red, unsigned char const green, unsigned char const blue)
{
    return AlbaBitManipulation<unsigned int>::concatenateBytes(red, green, blue);
}

}

}
