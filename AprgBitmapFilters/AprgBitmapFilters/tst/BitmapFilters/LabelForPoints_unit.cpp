#include <BitmapFilters/LabelForPoints.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

TEST(LabelForPointsTest, IsInitialLabelWorks)
{
    EXPECT_TRUE(isInitialLabel(INITIAL_LABEL_VALUE));
    EXPECT_FALSE(isInitialLabel(INVALID_LABEL_VALUE));
}

TEST(LabelForPointsTest, IsInvalidLabelWorks)
{
    EXPECT_FALSE(isInvalidLabel(INITIAL_LABEL_VALUE));
    EXPECT_TRUE(isInvalidLabel(INVALID_LABEL_VALUE));
}

TEST(LabelForPointsTest, IsInitialOrInvalidLabelWorks)
{
    EXPECT_TRUE(isInitialOrInvalidLabel(INITIAL_LABEL_VALUE));
    EXPECT_TRUE(isInitialOrInvalidLabel(INVALID_LABEL_VALUE));
    EXPECT_FALSE(isInitialOrInvalidLabel(1u));
}

TEST(LabelForPointsTest, GetLabelColorWorks)
{
    EXPECT_EQ(0x0u, getLabelColor(INITIAL_LABEL_VALUE));
    EXPECT_EQ(0x1A2BCEu, getLabelColor(INVALID_LABEL_VALUE));
    EXPECT_EQ(0x9ACA3Bu, getLabelColor(1u));
    EXPECT_EQ(0xCD651Du, getLabelColor(2u));
}

TEST(LabelForPointsTest, GetLabelWorks)
{
    LabelForPoints labelForPixels;
    labelForPixels.setLabel(BitmapXY(12, 34), 0x123456u);

    EXPECT_EQ(0x123456u, labelForPixels.getLabel(BitmapXY(12, 34)));
    EXPECT_EQ(INITIAL_LABEL_VALUE, labelForPixels.getLabel(BitmapXY(56, 78)));
}

TEST(LabelForPointsTest, GetPixelsToLabelsWorks)
{
    LabelForPoints labelForPixels;
    labelForPixels.setLabel(BitmapXY(12, 34), 0x123456u);

    LabelForPoints::PixelsToLabelsMap const& pixelsToLabels(labelForPixels.getPixelsToLabels());

    ASSERT_EQ(1u, pixelsToLabels.size());
    LabelForPoints::PixelsToLabelsPair const& pairToVerify(*pixelsToLabels.cbegin());
    EXPECT_EQ(BitmapXY(12, 34), pairToVerify.first);
    EXPECT_EQ(0x123456u, pairToVerify.second);
}

TEST(LabelForPointsTest, SetLabelWorks)
{
    LabelForPoints labelForPixels;

    labelForPixels.setLabel(BitmapXY(12, 34), 0x123456u);

    LabelForPoints::PixelsToLabelsMap const& pixelsToLabels(labelForPixels.getPixelsToLabels());
    ASSERT_EQ(1u, pixelsToLabels.size());
    LabelForPoints::PixelsToLabelsPair const& pairToVerify(*pixelsToLabels.cbegin());
    EXPECT_EQ(BitmapXY(12, 34), pairToVerify.first);
    EXPECT_EQ(0x123456u, pairToVerify.second);
}


}

}
