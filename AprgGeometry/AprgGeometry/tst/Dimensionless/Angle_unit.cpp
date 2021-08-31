#include <Dimensionless/Angle.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace Dimensionless
{

TEST(TwoDimensionsLineTest, EmptyAngle)
{
    Angle angle;
    EXPECT_EQ(0, angle.getDegrees());
    EXPECT_EQ(0, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingDegreesWorks)
{
    Angle angle(AngleUnitType::Degrees, 45);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingRadiansWorks)
{
    Angle angle(AngleUnitType::Radians, getPi()/4);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, SettingNearZeroWithMoreThanOneRevolutionWorks)
{
    Angle angle(AngleUnitType::Radians, getPi()*11.75);
    angle.setAngleValueInDegreesNearestToZero();

    EXPECT_DOUBLE_EQ(-45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(-getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ArithmeticOperationsWorks)
{
    EXPECT_DOUBLE_EQ(105, (Angle(AngleUnitType::Degrees, 90)+Angle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(75, (Angle(AngleUnitType::Degrees, 90)-Angle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(15, (+Angle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(-15, (-Angle(AngleUnitType::Degrees, 15)).getDegrees());
}

}

}
