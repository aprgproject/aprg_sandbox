#include <Monomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(MonomialTest, MonomialsAreConstructedCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial::VariablesToExponentsMap variablesToExponents{{"i", -7}};
    Monomial monomial3(23, variablesToExponents);

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    ASSERT_TRUE(monomial1.getVariablesToExponentsMapConstReference().empty());

    EXPECT_DOUBLE_EQ(-54, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap1.size());
    EXPECT_DOUBLE_EQ(6, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1.25, variableMap1.at("y").getDouble());

    EXPECT_DOUBLE_EQ(23, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(-7, variableMap2.at("i").getDouble());
}

TEST(MonomialTest, IsConstantOnlyFunctionWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(23, {});

    EXPECT_TRUE(monomial1.isConstantOnly());
    EXPECT_FALSE(monomial2.isConstantOnly());
    EXPECT_TRUE(monomial3.isConstantOnly());
}

TEST(MonomialTest, SettingANewConstantWorks)
{
    Monomial monomial;
    EXPECT_DOUBLE_EQ(0, monomial.getConstantConstReference().getDouble());

    monomial.setConstant(512);
    EXPECT_DOUBLE_EQ(512, monomial.getConstantConstReference().getDouble());
}

TEST(MonomialTest, SettingANewVariableWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.setVariableWtihExponent("i", 62);
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(62, variableMap.at("i").getDouble());
}

TEST(MonomialTest, SettingASetOfNewVariablesWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.setVariablesWithExponents({{"j", -4}, {"k", -0.75}});
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(-4, variableMap.at("j").getDouble());
    EXPECT_DOUBLE_EQ(-0.75, variableMap.at("k").getDouble());
}

}

}
