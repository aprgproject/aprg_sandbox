#include <AprgColorUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace alba::ColorUtilities;
using namespace std;

TEST(ColorUtilitiesTest, ConvertColorToHueSaturationLightnessDataWorks)
{
    HueSaturationLightnessData hslData1(convertColorToHueSaturationLightnessData(0x0));
    HueSaturationLightnessData hslData2(convertColorToHueSaturationLightnessData(0xFFFFFF));
    HueSaturationLightnessData hslData3(convertColorToHueSaturationLightnessData(0xF4A460));

    EXPECT_DOUBLE_EQ(0, hslData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData1.saturationDecimal);
    EXPECT_DOUBLE_EQ(0, hslData1.lightnessDecimal);
    EXPECT_DOUBLE_EQ(0, hslData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData2.saturationDecimal);
    EXPECT_DOUBLE_EQ(1, hslData2.lightnessDecimal);
    EXPECT_DOUBLE_EQ(27.567567567567568432, hslData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.87058823529411788478, hslData3.saturationDecimal);
    EXPECT_DOUBLE_EQ(0.66666666666666674068, hslData3.lightnessDecimal);
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

TEST(ColorUtilitiesTest, CombineRgbColorWorks)
{
    EXPECT_EQ(0x0u, combineRgbColor(0x0, 0x0, 0x0));
    EXPECT_EQ(0x6A0000u, combineRgbColor(0x6A, 0x0, 0x0));
    EXPECT_EQ(0x005A00u, combineRgbColor(0x0, 0x5A, 0x0));
    EXPECT_EQ(0x0000CDu, combineRgbColor(0x0, 0x0, 0xCD));
    EXPECT_EQ(0x6A5ACDu, combineRgbColor(0x6A, 0x5A, 0xCD));
}

