#pragma once

#include <map>
#include <string>

namespace alba {

namespace AprgBitmap {

void gatherAndSaveDataInAnimizeColor(std::string const& bitmapPath);

class AnimizeColor {
public:
    AnimizeColor();
    struct ColorDetails {
        int count;
        double newValue;
    };
    using ColorDataMap = std::map<double, ColorDetails>;
    using ValueAndColorDataPair = std::pair<double, ColorDetails>;

    uint32_t getNewColor(uint32_t const originalColor) const;
    double getNewLightness(double const originalValue) const;
    double getNewSaturation(double const originalValue) const;
    void gatherStatistics(std::string const& bitmapPath);
    void calculateNewValues();
    void saveColorData(std::string const& path);

private:
    bool isValueIncluded(double const value) const;
    void addCountToValue(ColorDataMap& colorDataMap, double const value);
    void calculateNewValues(ColorDataMap& colorDataMap);
    double getNewValue(ColorDataMap const& colorDataMap, double const originalValue) const;
    double m_lowestIncludedValue;
    double m_highestIncludedValue;
    ColorDataMap m_lightnessData;
    ColorDataMap m_saturationData;
};

}  // namespace AprgBitmap

}  // namespace alba
