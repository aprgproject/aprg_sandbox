#pragma once

#include <map>
#include <string>

namespace alba
{

namespace AprgBitmap
{

void gatherAndSaveDataInAnimizeColor(std::string const& bitmapPath);

class AnimizeColor
{
public:
    AnimizeColor();
    struct ColorDetails
    {
        unsigned int count;
        double newValue;
    };
    using ColorDataMap=std::map<double, ColorDetails>;
    using ColorDataPair=std::pair<double, ColorDetails>;

    unsigned int getNewColor(unsigned int const originalColor) const;
    double getNewLightness(double const originalValue) const;
    double getNewSaturation(double const originalValue) const;
    void gatherStatistics(std::string const& bitmapPath);
    void calculateNewValues();
    void saveColorData(std::string const& path);

private:
    bool isValueIncluded(double const value) const;
    void addCountToValue(
            ColorDataMap & colorDataMap,
            double const lightness);
    void calculateNewValues(ColorDataMap & colorDataMap);
    double getNewValue(
            ColorDataMap const& colorDataMap,
            double const originalLightnessValue) const;
    double m_lowestIncludedValue;
    double m_highestIncludedValue;
    ColorDataMap m_lightnessData;
    ColorDataMap m_saturationData;
};

}

}
