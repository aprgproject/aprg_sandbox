#include <Variable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(VariableTest, VariablesAreConstructedCorrectly)
{
    Variable variable1;
    Variable variable2("time");

    EXPECT_EQ("", variable1.getVariableName());
    EXPECT_EQ("time", variable2.getVariableName());
}

TEST(VariableTest, EqualityVariableWorks)
{
    Variable variable1;
    Variable variable2("x");
    Variable variable3("power");
    Variable variable4("x");

    EXPECT_TRUE(variable1==variable1);
    EXPECT_FALSE(variable1==variable2);
    EXPECT_TRUE(variable2==variable2);
    EXPECT_FALSE(variable2==variable3);
    EXPECT_TRUE(variable2==variable4);
}

TEST(VariableTest, InequalityVariableWorks)
{
    Variable variable1;
    Variable variable2("x");
    Variable variable3("power");
    Variable variable4("x");

    EXPECT_FALSE(variable1!=variable1);
    EXPECT_TRUE(variable1!=variable2);
    EXPECT_FALSE(variable2!=variable2);
    EXPECT_TRUE(variable2!=variable3);
    EXPECT_FALSE(variable2!=variable4);
}

TEST(VariableTest, LessThanOperatorWorks)
{
    EXPECT_FALSE(Variable() < Variable());
    EXPECT_FALSE(Variable("x") < Variable("x"));
    EXPECT_FALSE(Variable("x") < Variable("w"));
    EXPECT_TRUE(Variable("x") < Variable("y"));
}

TEST(VariableTest, GetDisplayableStringWorks)
{
    Variable variable1;
    Variable variable2("time");

    EXPECT_EQ("", variable1.getDisplayableString());
    EXPECT_EQ("time", variable2.getDisplayableString());
}

TEST(VariableTest, SettingANewVariableNameWorks)
{
    Variable variableForTest;
    EXPECT_EQ("", variableForTest.getVariableName());

    variableForTest.setVariableName("omega");
    EXPECT_EQ("omega", variableForTest.getVariableName());
}

}

}
