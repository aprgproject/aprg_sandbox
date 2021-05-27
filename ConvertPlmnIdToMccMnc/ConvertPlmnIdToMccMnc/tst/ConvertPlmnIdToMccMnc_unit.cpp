#include <ConvertPlmnIdToMccMnc.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, ConvertPlmnIdToMccMncFirstNibbleOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x100000));    EXPECT_EQ(10, mccMncPair.mcc);
    EXPECT_EQ(0, mccMncPair.mnc);
}
TEST(SampleTest, ConvertPlmnIdToMccMncFirstTwoNibblesOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x120000));
    EXPECT_EQ(12, mccMncPair.mcc);
    EXPECT_EQ(0, mccMncPair.mnc);
}

TEST(SampleTest, ConvertPlmnIdToMccMncFirstThreeNibblesOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x123000));
    EXPECT_EQ(12, mccMncPair.mcc);
    EXPECT_EQ(3, mccMncPair.mnc);
}

TEST(SampleTest, ConvertPlmnIdToMccMncFirstFourNibblesOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x123400));
    EXPECT_EQ(412, mccMncPair.mcc);
    EXPECT_EQ(3, mccMncPair.mnc);
}

TEST(SampleTest, ConvertPlmnIdToMccMncFirstFiveNibblesOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x123450));
    EXPECT_EQ(412, mccMncPair.mcc);
    EXPECT_EQ(53, mccMncPair.mnc);
}

TEST(SampleTest, ConvertPlmnIdToMccMncFirstSixNibblesOfPlmnId)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x123456));
    EXPECT_EQ(412, mccMncPair.mcc);
    EXPECT_EQ(653, mccMncPair.mnc);
}

TEST(SampleTest, ConvertPlmnIdToMccMncWithFillerDigit)
{
    MccMncPair mccMncPair(convertPlmnIdToMccMnc(0x12F456));
    EXPECT_EQ(412, mccMncPair.mcc);
    EXPECT_EQ(65, mccMncPair.mnc);
}

}