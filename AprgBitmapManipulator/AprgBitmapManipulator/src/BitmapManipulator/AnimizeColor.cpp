#include "AnimizeColor.hpp"

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace alba::AprgBitmap;
using namespace alba::AprgBitmap::ColorUtilities;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

void gatherAndSaveDataInAnimizeColor(string const& bitmapPath)
{
    AlbaLocalPathHandler bitmapPathHandler(bitmapPath);
    AlbaLocalPathHandler colorDataPathHandler(bitmapPathHandler.getDirectory() + R"(\)" + bitmapPathHandler.getFilenameOnly() + R"(_AnimizeColorData.csv)");

    AnimizeColor statistics;
    statistics.gatherStatistics(bitmapPathHandler.getFullPath());
    statistics.calculateNewValues();
    statistics.saveColorData(colorDataPathHandler.getFullPath());
}

AnimizeColor::AnimizeColor()
    : m_lowestIncludedValue(0.1)
    , m_highestIncludedValue(0.9)
{}

uint32_t AnimizeColor::getNewColor(uint32_t const originalColor) const
{
    HueSaturationLightnessData newHslData(convertColorToHueSaturationLightnessData(originalColor));
    newHslData.lightnessDecimal = getNewLightness(newHslData.lightnessDecimal);
    newHslData.saturationLightnessDecimal = getNewSaturation(newHslData.saturationLightnessDecimal);
    return convertHueSaturationLightnessDataToColor(newHslData);
}

double AnimizeColor::getNewLightness(double const originalValue) const
{
    return getNewValue(m_lightnessData, originalValue);
}

double AnimizeColor::getNewSaturation(double const originalValue) const
{
    return getNewValue(m_saturationData, originalValue);
}

void AnimizeColor::gatherStatistics(string const& bitmapPath)
{
    Bitmap bitmap(bitmapPath);
    BitmapSnippet canvas(bitmap.getSnippetReadFromFileWholeBitmap());
    canvas.traverse([&](BitmapXY const&, unsigned int const color)
    {
        HueSaturationLightnessData hslData(convertColorToHueSaturationLightnessData(color));
        addCountToValue(m_lightnessData, hslData.lightnessDecimal);
        addCountToValue(m_saturationData, hslData.saturationLightnessDecimal);
    });
}

void AnimizeColor::calculateNewValues()
{
    calculateNewValues(m_lightnessData);
    calculateNewValues(m_saturationData);
}

void AnimizeColor::saveColorData(string const& path)
{
    ofstream colorDataFileStream(path);

    colorDataFileStream << "lightness, newLightness\n";
    for(ValueAndColorDataPair const lightnessCountPair : m_lightnessData)
    {
        colorDataFileStream << lightnessCountPair.first
                            << ", " << lightnessCountPair.second.newValue
                            << "\n";
        /*for(unsigned int i=0; i<lightnessCountPair.second.count; i++)
        {
            colorDataFileStream << lightnessCountPair.first
                                << ", " << lightnessCountPair.second.newLightness
                                << "\n";
        }*/
    }
}
bool AnimizeColor::isValueIncluded(double const value) const
{
    return value >= m_lowestIncludedValue && value <= m_highestIncludedValue;}

void AnimizeColor::addCountToValue(
        ColorDataMap & colorDataMap,
        double const value)
{
    if(isValueIncluded(value))
    {
        if(colorDataMap.find(value) == colorDataMap.cend())
        {
            ColorDetails details{};
            details.count=1;
            colorDataMap.emplace(value, details);
        }
        else
        {
            colorDataMap.at(value).count++;
        }
    }
}

void AnimizeColor::calculateNewValues(ColorDataMap & colorDataMap)
{
    unsigned int totalCount=0;
    for(auto const& colorDataPair : colorDataMap)
    {
        totalCount += colorDataPair.second.count;
    }
    unsigned int partialCount=0;
    double diffOfHighestAndLowestValue=m_highestIncludedValue-m_lowestIncludedValue;
    for(auto & colorDataPair : colorDataMap)
    {
        unsigned int currentCount=colorDataPair.second.count;
        colorDataPair.second.newValue = (((static_cast<double>(currentCount)/2)+partialCount)/totalCount*diffOfHighestAndLowestValue)
                + m_lowestIncludedValue;
        partialCount+=currentCount;
    }
}

double AnimizeColor::getNewValue(
        ColorDataMap const& colorDataMap,
        double const originalValue) const
{
    double newValue=originalValue;
    if(isValueIncluded(originalValue))
    {
        if(colorDataMap.find(originalValue) != colorDataMap.cend())
        {
            newValue = colorDataMap.at(originalValue).newValue;
        }
        else
        {
            pair<ColorDataMap::const_iterator, ColorDataMap::const_iterator> iterators
                    = containerHelper::getLowerAndUpperConstIteratorsInMap(colorDataMap, originalValue);
            ColorDataMap::const_iterator itLower(iterators.first);
            ColorDataMap::const_iterator itUpper(iterators.second);
            double deltaX = itUpper->first - itLower->first;
            double deltaY = itUpper->second.newValue - itLower->second.newValue;
            double deltaXToInterpolate = originalValue-itLower->first;
            double deltaYInterpolated = deltaXToInterpolate/deltaX*deltaY;
            newValue = itLower->second.newValue+deltaYInterpolated;
        }
    }
    return newValue;
}

}

}
