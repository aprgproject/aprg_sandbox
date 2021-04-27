#include <AprgColorUtilities.hpp>

#include <gtest/gtest.h>


#include <Debug/AlbaDebug.hpp>

using namespace alba;
using namespace alba::ColorUtilities;
using namespace std;

TEST(ColorUtilitiesTest, CalculateColorAnalysisDataWorks)
{
    ColorAnalysisData data1(calculateColorAnalysisData(0x0));
    ColorAnalysisData data2(calculateColorAnalysisData(0xFFFFFF));
    ColorAnalysisData data3(calculateColorAnalysisData(0xB2C368));

    EXPECT_DOUBLE_EQ(0, data1.redPercentage);
    EXPECT_DOUBLE_EQ(0, data1.greenPercentage);
    EXPECT_DOUBLE_EQ(0, data1.bluePercentage);
    EXPECT_DOUBLE_EQ(0, data1.colorMax);
    EXPECT_DOUBLE_EQ(0, data1.colorMin);
    EXPECT_DOUBLE_EQ(0, data1.deltaMaxMin);
    EXPECT_DOUBLE_EQ(1, data2.redPercentage);
    EXPECT_DOUBLE_EQ(1, data2.greenPercentage);
    EXPECT_DOUBLE_EQ(1, data2.bluePercentage);
    EXPECT_DOUBLE_EQ(1, data2.colorMax);
    EXPECT_DOUBLE_EQ(1, data2.colorMin);
    EXPECT_DOUBLE_EQ(0, data2.deltaMaxMin);
    EXPECT_DOUBLE_EQ(0.69803921568627447236, data3.redPercentage);
    EXPECT_DOUBLE_EQ(0.76470588235294112422, data3.greenPercentage);
    EXPECT_DOUBLE_EQ(0.40784313725490195512, data3.bluePercentage);
    EXPECT_DOUBLE_EQ(0.76470588235294112422, data3.colorMax);
    EXPECT_DOUBLE_EQ(0.40784313725490195512, data3.colorMin);
    EXPECT_DOUBLE_EQ(0.3568627450980391691, data3.deltaMaxMin);
}

TEST(ColorUtilitiesTest, CalculateHueDegreesWorks)
{
    double hueDegrees1(calculateHueDegrees(calculateColorAnalysisData(0x0)));
    double hueDegrees2(calculateHueDegrees(calculateColorAnalysisData(0xFFFFFF)));
    double hueDegrees3(calculateHueDegrees(calculateColorAnalysisData(0x83A96E)));

    EXPECT_DOUBLE_EQ(0, hueDegrees1);
    EXPECT_DOUBLE_EQ(0, hueDegrees2);
    EXPECT_DOUBLE_EQ(98.644067796610187315, hueDegrees3);
}

TEST(ColorUtilitiesTest, CreateHueSaturationLightnessDataWorks)
{
    HueSaturationLightnessData hslData(createHueSaturationLightnessData(1.1, 2.2, 3.3));

    EXPECT_DOUBLE_EQ(1.1, hslData.hueDegrees);
    EXPECT_DOUBLE_EQ(2.2, hslData.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(3.3, hslData.lightnessDecimal);
}

TEST(ColorUtilitiesTest, CreateHueSaturationValueDataWorks)
{
    HueSaturationValueData hsvData(createHueSaturationValueData(1.1, 2.2, 3));

    EXPECT_DOUBLE_EQ(1.1, hsvData.hueDegrees);
    EXPECT_DOUBLE_EQ(2.2, hsvData.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(3, hsvData.valueDecimalOfColorMax);
}

TEST(ColorUtilitiesTest, CombineRgbColorWorks)
{
    EXPECT_EQ(0x0u, combineRgbToColor(0x0, 0x0, 0x0));
    EXPECT_EQ(0x6A0000u, combineRgbToColor(0x6A, 0x0, 0x0));
    EXPECT_EQ(0x005A00u, combineRgbToColor(0x0, 0x5A, 0x0));
    EXPECT_EQ(0x0000CDu, combineRgbToColor(0x0, 0x0, 0xCD));
    EXPECT_EQ(0x6A5ACDu, combineRgbToColor(0x6A, 0x5A, 0xCD));
}

TEST(ColorUtilitiesTest, ConvertColorToHueSaturationLightnessDataWorks)
{
    HueSaturationLightnessData hslData1(convertColorToHueSaturationLightnessData(0x0));
    HueSaturationLightnessData hslData2(convertColorToHueSaturationLightnessData(0xFFFFFF));
    HueSaturationLightnessData hslData3(convertColorToHueSaturationLightnessData(0xF4A460));

    EXPECT_DOUBLE_EQ(0, hslData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData1.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(0, hslData1.lightnessDecimal);
    EXPECT_DOUBLE_EQ(0, hslData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData2.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(1, hslData2.lightnessDecimal);
    EXPECT_DOUBLE_EQ(27.567567567567568432, hslData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.87058823529411788478, hslData3.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(0.66666666666666674068, hslData3.lightnessDecimal);
}

TEST(ColorUtilitiesTest, ConvertColorToHueSaturationValueDataWorks)
{
    HueSaturationValueData hsvData1(convertColorToHueSaturationValueData(0x0));
    HueSaturationValueData hsvData2(convertColorToHueSaturationValueData(0xFFFFFF));
    HueSaturationValueData hsvData3(convertColorToHueSaturationValueData(0xF4A460));

    EXPECT_DOUBLE_EQ(0, hsvData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hsvData1.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(0, hsvData1.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(0, hsvData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hsvData2.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(1, hsvData2.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(27.567567567567568432, hsvData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.60655737704918033515, hsvData3.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(0.95686274509803925792, hsvData3.valueDecimalOfColorMax);

    ALBA_PRECISION(20);
    ALBA_PRINT1(hsvData3.hueDegrees);
    ALBA_PRINT1(hsvData3.saturationValueDecimal);
    ALBA_PRINT1(hsvData3.valueDecimalOfColorMax);
}

TEST(ColorUtilitiesTest, ConvertHueSaturationLightnessDataToColorWorks)
{
    HueSaturationLightnessData hslData1(createHueSaturationLightnessData(0, 0, 0));
    HueSaturationLightnessData hslData2(createHueSaturationLightnessData(360, 1, 1));
    HueSaturationLightnessData hslData3(createHueSaturationLightnessData(123, 0.56, 0.78));

    EXPECT_EQ(0x0u, convertHueSaturationLightnessDataToColor(hslData1));
    EXPECT_EQ(0xFFFFFFu, convertHueSaturationLightnessDataToColor(hslData2));
    EXPECT_EQ(0xA7E6ABu, convertHueSaturationLightnessDataToColor(hslData3));
}

TEST(ColorUtilitiesTest, ExtractRedWorks)
{
    EXPECT_EQ(0xFFu, extractRed(0xFFFFFF));
    EXPECT_EQ(0x0u, extractRed(0x0));
    EXPECT_EQ(0x32u, extractRed(0x32CD32));
}

TEST(ColorUtilitiesTest, ExtractGreenWorks)
{
    EXPECT_EQ(0xFFu, extractGreen(0xFFFFFF));
    EXPECT_EQ(0x0u, extractGreen(0x0));
    EXPECT_EQ(0xB3u, extractGreen(0x3CB371));
}

TEST(ColorUtilitiesTest, ExtractBlueWorks)
{
    EXPECT_EQ(0xFFu, extractBlue(0xFFFFFF));
    EXPECT_EQ(0x0u, extractBlue(0x0));
    EXPECT_EQ(0x57u, extractBlue(0x2E8B57));
}

