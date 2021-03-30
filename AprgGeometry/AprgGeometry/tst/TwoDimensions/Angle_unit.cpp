#include <TwoDimensions/Angle.hpp>

#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions;
using namespace alba::mathHelper;
using namespace std;


TEST(TwoDimensionsLineTest, EmptyAngle)
{
    Angle angle;
    EXPECT_EQ(0, angle.getDegrees());
    EXPECT_EQ(0, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingDegreesWorks)
{
    Angle angle(AngleInputType::Degrees, 45);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingRadiansWorks)
{
    Angle angle(AngleInputType::Radians, getPi()/4);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionWithMoreThanOneRevolutionWorks)
{
    Angle angle(AngleInputType::Radians, getPi()*11.75);
    EXPECT_DOUBLE_EQ(-45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(-getPi()/4, angle.getRadians());
}
