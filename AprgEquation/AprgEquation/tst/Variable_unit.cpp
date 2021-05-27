#include <Variable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(VariableTest, VariablesAreConstructedCorrectly)
{
    Variable operator1;
    Variable operator2("time");

    EXPECT_EQ("", operator1.getVariableName());
    EXPECT_EQ("time", operator2.getVariableName());
}

TEST(VariableTest, SettingANewVariableNameWorks)
{
    Variable operatorForTest;
    EXPECT_EQ("", operatorForTest.getVariableName());

    operatorForTest.setVariableName("omega");
    EXPECT_EQ("omega", operatorForTest.getVariableName());
}

}

}
