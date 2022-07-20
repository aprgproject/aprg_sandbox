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

TEST(ConstantTest, GetDisplayableStringWorks)
{
    Constant constant1;
    Constant constant2(true);
    Constant constant3(false);

    EXPECT_EQ("[false]", constant1.getDisplayableString());
    EXPECT_EQ("[true]", constant2.getDisplayableString());
    EXPECT_EQ("[false]", constant3.getDisplayableString());
}

TEST(ConstantTest, SettingANewNumberWorks)
{
    Constant constant(true);
    EXPECT_TRUE(constant.getBooleanValue());

    constant.setValue(false);
    EXPECT_FALSE(constant.getBooleanValue());
}

}

}
