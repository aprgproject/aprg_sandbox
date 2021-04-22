#include <Math/AlbaRatio.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaRatioTest, BothParametersAreZero)
{
    AlbaRatio actualRatio(0,0);

    EXPECT_EQ(AlbaRatio::Type::BothValuesZero, actualRatio.getType());
    EXPECT_EQ(0, actualRatio.getValidRatioIfPossible());
    EXPECT_TRUE(actualRatio.isBothZero());
    EXPECT_FALSE(actualRatio.isOnlyOneValueZero());
    EXPECT_FALSE(actualRatio.hasValidRatio());
}

TEST(AlbaRatioTest, OnlyFirstParametersIsZero)
{
    AlbaRatio actualRatio(0,2983);

    EXPECT_EQ(AlbaRatio::Type::FirstValueIsZero, actualRatio.getType());
    EXPECT_EQ(0, actualRatio.getValidRatioIfPossible());
    EXPECT_FALSE(actualRatio.isBothZero());
    EXPECT_TRUE(actualRatio.isOnlyOneValueZero());
    EXPECT_FALSE(actualRatio.hasValidRatio());
}

TEST(AlbaRatioTest, OnlySecondParametersIsZero)
{
    AlbaRatio actualRatio(98,0);

    EXPECT_EQ(AlbaRatio::Type::SecondValueIsZero, actualRatio.getType());
    EXPECT_EQ(0, actualRatio.getValidRatioIfPossible());
    EXPECT_FALSE(actualRatio.isBothZero());
    EXPECT_TRUE(actualRatio.isOnlyOneValueZero());
    EXPECT_FALSE(actualRatio.hasValidRatio());
}

TEST(AlbaRatioTest, BothParametersAreNonZero)
{
    AlbaRatio actualRatio(16,2);

    EXPECT_EQ(AlbaRatio::Type::WithValidRatio, actualRatio.getType());
    EXPECT_EQ(8, actualRatio.getValidRatioIfPossible());
    EXPECT_FALSE(actualRatio.isBothZero());
    EXPECT_FALSE(actualRatio.isOnlyOneValueZero());
    EXPECT_TRUE(actualRatio.hasValidRatio());
}

}
