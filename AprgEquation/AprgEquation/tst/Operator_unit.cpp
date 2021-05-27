#include <Operator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(OperatorTest, OperatorsAreConstructedCorrectly)
{
    Operator operator1;
    Operator operator2("test");

    EXPECT_EQ("", operator1.getOperatorString());
    EXPECT_EQ("test", operator2.getOperatorString());
}

TEST(OperatorTest, SettingANewOperatingStringWorks)
{
    Operator operatorForTest;
    EXPECT_EQ("", operatorForTest.getOperatorString());

    operatorForTest.setOperatorString("multiply");
    EXPECT_EQ("multiply", operatorForTest.getOperatorString());
}

}

}
