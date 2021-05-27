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

    EXPECT_EQ(0, monomial1.getConstantConstReference().getDouble());
    ASSERT_TRUE(monomial1.getVariablesToExponentsMapConstReference().empty());

    EXPECT_EQ(-54, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());    EXPECT_EQ(6, variableMap.at("x").getDouble());
    EXPECT_EQ(-1.25, variableMap.at("y").getDouble());
}
TEST(MonomialTest, SettingANewConstantWorks)
{
    Monomial monomial;
    EXPECT_EQ(0, monomial.getConstantConstReference().getDouble());

    monomial.setConstant(512);
    EXPECT_EQ(512, monomial.getConstantConstReference().getDouble());
}

TEST(MonomialTest, SettingANewVariableWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.setVariableWtihExponent("i", 62);
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_EQ(62, variableMap.at("i").getDouble());
}

TEST(MonomialTest, SettingASetOfNewVariablesWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.setVariablesWithExponents({{"j", -4}, {"k", -0.75}});
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_EQ(-4, variableMap.at("j").getDouble());
    EXPECT_EQ(-0.75, variableMap.at("k").getDouble());
}

}

}
