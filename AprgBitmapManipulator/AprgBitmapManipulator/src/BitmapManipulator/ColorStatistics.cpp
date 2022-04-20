#include "ColorStatistics.hpp"

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

void gatherAndSaveColorStatistics(string const& bitmapPath)
{
    AlbaLocalPathHandler bitmapPathHandler(bitmapPath);
    AlbaLocalPathHandler colorDataPathHandler(bitmapPathHandler.getDirectory() + R"(\)" + bitmapPathHandler.getFilenameOnly() + R"(_SortedColorData.csv)");
    AlbaLocalPathHandler colorStatisticsPathHandler(bitmapPathHandler.getDirectory() + R"(\)" + bitmapPathHandler.getFilenameOnly() + R"(_Statistics.txt)");

    AprgColorStatistics statistics;
    statistics.gatherStatistics(bitmapPathHandler.getFullPath());
    statistics.saveColorData(colorDataPathHandler.getFullPath());
    statistics.saveColorStatistics(colorStatisticsPathHandler.getFullPath());
}

void AprgColorStatistics::gatherStatistics(string const& bitmapPath)
{
    Bitmap bitmap(bitmapPath);
    BitmapSnippet canvas(bitmap.getSnippetReadFromFileWholeBitmap());
    canvas.traverse([&](BitmapXY const&, uint32_t const color)
    {
        double colorIntensity(calculateColorIntensityDecimal(color));
        double luma601(calculateLuma601Decimal(color));
        double luma709(calculateLuma709Decimal(color));
        colorIntensitySet.emplace(colorIntensity);
        luma601Set.emplace(luma601);
        luma709Set.emplace(luma709);
        HueSaturationLightnessData hslData(convertColorToHueSaturationLightnessData(color));
        HueSaturationValueData hsvData(convertColorToHueSaturationValueData(color));
        hueDegreesSet.emplace(hslData.hueDegrees);
        saturationLightnessSet.emplace(hslData.saturationLightnessDecimal);
        lightnessSet.emplace(hslData.lightnessDecimal);
        saturationValueSet.emplace(hsvData.saturationValueDecimal);
        valueSet.emplace(hsvData.valueDecimalOfColorMax);

        colorIntensitySamples.emplace_back(OneDimensionStatistics::Sample{colorIntensity});
        saturationLightnessSamples.emplace_back(OneDimensionStatistics::Sample{hslData.saturationLightnessDecimal});
        lightnessSamples.emplace_back(OneDimensionStatistics::Sample{hslData.lightnessDecimal});
        saturationValueSamples.emplace_back(OneDimensionStatistics::Sample{hsvData.saturationValueDecimal});
        valueSamples.emplace_back(OneDimensionStatistics::Sample{hsvData.valueDecimalOfColorMax});
        luma601Samples.emplace_back(OneDimensionStatistics::Sample{luma601});
        luma709Samples.emplace_back(OneDimensionStatistics::Sample{luma709});
    });
}

void AprgColorStatistics::saveColorData(string const& path)
{
    ofstream colorDataFileStream(path);
    multiset<double>::const_iterator colorIntensityIterator(colorIntensitySet.cbegin());
    multiset<double>::const_iterator hueDegreesIterator(hueDegreesSet.cbegin());
    multiset<double>::const_iterator saturationLightnessIterator(saturationLightnessSet.cbegin());
    multiset<double>::const_iterator lightnessIterator(lightnessSet.cbegin());
    multiset<double>::const_iterator saturationValueIterator(saturationValueSet.cbegin());
    multiset<double>::const_iterator valueIterator(valueSet.cbegin());
    multiset<double>::const_iterator luma601Iterator(luma601Set.cbegin());
    multiset<double>::const_iterator luma709Iterator(luma709Set.cbegin());

    colorDataFileStream
            << "colorIntensity, "
            << "hueDegreesDividedBy360, "
            << "saturationLightness, "
            << "lightness, "
            << "saturationValueI, "
            << "value, "
            << "luma601, "
            << "luma709" << endl;
    unsigned int count=0;
    unsigned int size = min(colorIntensitySet.size(),
                            min(hueDegreesSet.size(),
                                min(saturationLightnessSet.size(),
                                    min(lightnessSet.size(),
                                        min(saturationValueSet.size(),
                                            min(valueSet.size(),
                                                min(luma601Set.size(), luma601Set.size())))))));
    while(count<size)
    {
        colorDataFileStream
                << *colorIntensityIterator++ << ", "
                << *hueDegreesIterator++/360 << ", "
                << *saturationLightnessIterator++ << ", "
                << *lightnessIterator++ << ", "
                << *saturationValueIterator++ << ", "
                << *valueIterator++ << ", "
                << *luma601Iterator++ << ", "
                << *luma709Iterator++ << endl;
        count++;
    }
}

void AprgColorStatistics::saveColorStatistics(string const& path)
{
    ofstream statisticsFileStream(path);
    OneDimensionStatistics colorIntensityStatistics(colorIntensitySamples);
    OneDimensionStatistics saturationLightnessStatistics(saturationLightnessSamples);
    OneDimensionStatistics lightnessStatistics(lightnessSamples);
    OneDimensionStatistics saturationValueStatistics(saturationValueSamples);
    OneDimensionStatistics valueStatistics(valueSamples);
    OneDimensionStatistics luma601Statistics(luma601Samples);
    OneDimensionStatistics luma709Statistics(luma709Samples);

    statisticsFileStream << "Color Intensity Mean: " << colorIntensityStatistics.getMean().getDisplayableString()
                         << " StdDev: " << colorIntensityStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Saturation Lightness Mean: " << saturationLightnessStatistics.getMean().getDisplayableString()
                         << " StdDev: " << saturationLightnessStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Lightness Mean: " << lightnessStatistics.getMean().getDisplayableString()
                         << " StdDev: " << lightnessStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Saturation Value Mean: " << saturationValueStatistics.getMean().getDisplayableString()
                         << " StdDev: " << saturationValueStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Value Mean: " << valueStatistics.getMean().getDisplayableString()
                         << " StdDev: " << valueStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Luma 601 Mean: " << luma601Statistics.getMean().getDisplayableString()
                         << " StdDev: " << luma601Statistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Luma 709 Mean: " << luma709Statistics.getMean().getDisplayableString()
                         << " StdDev: " << luma709Statistics.getSampleStandardDeviation().getDisplayableString() << endl;
}

}

}
