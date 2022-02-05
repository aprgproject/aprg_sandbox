#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/Math/Angle/AlbaAngle.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(TwoDimensionsLineTest, EmptyAngle)
{
    AlbaAngle angle;
    EXPECT_EQ(0, angle.getDegrees());
    EXPECT_EQ(0, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingDegreesWorks)
{
    AlbaAngle angle(AngleUnitType::Degrees, 45);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ConstructionUsingRadiansWorks)
{
    AlbaAngle angle(AngleUnitType::Radians, getPi()/4);
    EXPECT_DOUBLE_EQ(45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, SettingNearZeroWithMoreThanOneRevolutionWorks)
{
    AlbaAngle angle(AngleUnitType::Radians, getPi()*11.75);
    angle.setAngleValueInDegreesNearestToZero();

    EXPECT_DOUBLE_EQ(-45, angle.getDegrees());
    EXPECT_DOUBLE_EQ(-getPi()/4, angle.getRadians());
}

TEST(TwoDimensionsLineTest, ArithmeticOperationsWorks)
{
    EXPECT_DOUBLE_EQ(105, (AlbaAngle(AngleUnitType::Degrees, 90)+AlbaAngle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(75, (AlbaAngle(AngleUnitType::Degrees, 90)-AlbaAngle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(15, (+AlbaAngle(AngleUnitType::Degrees, 15)).getDegrees());
    EXPECT_DOUBLE_EQ(-15, (-AlbaAngle(AngleUnitType::Degrees, 15)).getDegrees());
}

}
