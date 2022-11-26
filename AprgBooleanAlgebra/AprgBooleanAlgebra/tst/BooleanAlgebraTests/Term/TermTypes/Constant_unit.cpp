#include <BooleanAlgebra/Term/TermTypes/Constant.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(ConstantTest, ConstantsAreConstructedCorrectly)
{
    Constant constant1;
    Constant constant2(true);
    Constant constant3(false);

    EXPECT_FALSE(constant1.getBooleanValue());
    EXPECT_TRUE(constant2.getBooleanValue());
    EXPECT_FALSE(constant3.getBooleanValue());
}

TEST(ConstantTest, EqualityOperatorWorks)
{
    Constant constant1;
    Constant constant2(true);
    Constant constant3(false);
    Constant constant4(true);

    EXPECT_TRUE(constant1==constant1);
    EXPECT_FALSE(constant1==constant2);
    EXPECT_TRUE(constant2==constant2);
    EXPECT_FALSE(constant2==constant3);
    EXPECT_TRUE(constant2==constant4);
}

TEST(ConstantTest, InequalityOperatorWorks)
{
    Constant constant1;
    Constant constant2(true);
    Constant constant3(false);
    Constant constant4(true);

    EXPECT_FALSE(constant1!=constant1);
    EXPECT_TRUE(constant1!=constant2);
    EXPECT_FALSE(constant2!=constant2);
    EXPECT_TRUE(constant2!=constant3);
    EXPECT_FALSE(constant2!=constant4);
}

TEST(ConstantTest, LessThanOperatorWorks)
{
    EXPECT_FALSE(Constant() < Constant());
    EXPECT_FALSE(Constant(true) < Constant(true));
    EXPECT_FALSE(Constant(true) < Constant(false));
    EXPECT_TRUE(Constant(false) < Constant(true));
}

TEST(ConstantTest, NotOperationWorks)
{
    EXPECT_EQ(Constant(true), ~Constant(false));
    EXPECT_EQ(Constant(false), ~Constant(true));
}

TEST(ConstantTest, SettingANewNumberWorks)
{
    Constant constant(true);    EXPECT_TRUE(constant.getBooleanValue());

    constant.setValue(false);
    EXPECT_FALSE(constant.getBooleanValue());
}

TEST(ConstantTest, NegateWorks)
{
    Constant constant1(false);
    Constant constant2(true);

    constant1.negate();
    constant2.negate();

    EXPECT_TRUE(constant1.getBooleanValue());
    EXPECT_FALSE(constant2.getBooleanValue());
}

TEST(ConstantTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    Constant constant1;
    Constant constant2(true);
    Constant constant3(false);

    ss << constant1 << "," << constant2 << "," << constant3;

    EXPECT_EQ("[false],[true],[false]", ss.str());
}

}

}