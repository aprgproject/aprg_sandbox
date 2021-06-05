#include <Constant.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(ConstantTest, ConstantsAreConstructedCorrectly)
{
    Constant constant1;
    Constant constant2(3484);
    Constant constant3(-1561);
    Constant constant4(-415, 41745);
    Constant constant5(-85.45631);

    EXPECT_DOUBLE_EQ(0, constant1.getNumberConstReference().getDouble());
    EXPECT_DOUBLE_EQ(3484, constant2.getNumberConstReference().getDouble());
    EXPECT_DOUBLE_EQ(-1561, constant3.getNumberConstReference().getDouble());
    EXPECT_DOUBLE_EQ(-0.0099413103365672533, constant4.getNumberConstReference().getDouble());
    EXPECT_DOUBLE_EQ(-85.45631, constant5.getNumberConstReference().getDouble());
}

TEST(ConstantTest, EqualityOperatorWorks)
{
    Constant constant1;
    Constant constant2(3484);
    Constant constant3(-1561);
    Constant constant4(3484);

    EXPECT_TRUE(constant1==constant1);
    EXPECT_FALSE(constant1==constant2);
    EXPECT_TRUE(constant2==constant2);
    EXPECT_FALSE(constant2==constant3);
    EXPECT_TRUE(constant2==constant4);
}

TEST(ConstantTest, SettingANewNumberWorks)
{
    Constant constant(3484);
    EXPECT_DOUBLE_EQ(3484, constant.getNumberConstReference().getDouble());

    constant.setNumber(4521);
    EXPECT_DOUBLE_EQ(4521, constant.getNumberConstReference().getDouble());
}

}

}
