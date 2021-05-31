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

TEST(OperatorTest, PerformOperationWorks)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_DOUBLE_EQ(0, nullOperator.performOperation(10, 2).getDouble());
    EXPECT_DOUBLE_EQ(12, addOperator.performOperation(10, 2).getDouble());
    EXPECT_DOUBLE_EQ(8, subtractOperator.performOperation(10, 2).getDouble());
    EXPECT_DOUBLE_EQ(20, multiplyOperator.performOperation(10, 2).getDouble());
    EXPECT_DOUBLE_EQ(5, divideOperator.performOperation(10, 2).getDouble());
    EXPECT_DOUBLE_EQ(100, raiseToPowerOperator.performOperation(10, 2).getDouble());
}

TEST(OperatorTest, IsAdditionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_FALSE(nullOperator.isAddition());
    EXPECT_TRUE(addOperator.isAddition());
    EXPECT_FALSE(subtractOperator.isAddition());
    EXPECT_FALSE(multiplyOperator.isAddition());
    EXPECT_FALSE(divideOperator.isAddition());
    EXPECT_FALSE(raiseToPowerOperator.isAddition());
}

TEST(OperatorTest, IsSubtractionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_FALSE(nullOperator.isSubtraction());
    EXPECT_FALSE(addOperator.isSubtraction());
    EXPECT_TRUE(subtractOperator.isSubtraction());
    EXPECT_FALSE(multiplyOperator.isSubtraction());
    EXPECT_FALSE(divideOperator.isSubtraction());
    EXPECT_FALSE(raiseToPowerOperator.isSubtraction());
}

TEST(OperatorTest, IsMultiplicationWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_FALSE(nullOperator.isMultiplication());
    EXPECT_FALSE(addOperator.isMultiplication());
    EXPECT_FALSE(subtractOperator.isMultiplication());
    EXPECT_TRUE(multiplyOperator.isMultiplication());
    EXPECT_FALSE(divideOperator.isMultiplication());
    EXPECT_FALSE(raiseToPowerOperator.isMultiplication());
}

TEST(OperatorTest, IsDivisionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_FALSE(nullOperator.isDivision());
    EXPECT_FALSE(addOperator.isDivision());
    EXPECT_FALSE(subtractOperator.isDivision());
    EXPECT_FALSE(multiplyOperator.isDivision());
    EXPECT_TRUE(divideOperator.isDivision());
    EXPECT_FALSE(raiseToPowerOperator.isDivision());
}

TEST(OperatorTest, IsRaiseToPowerWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");

    EXPECT_FALSE(nullOperator.isRaiseToPower());
    EXPECT_FALSE(addOperator.isRaiseToPower());
    EXPECT_FALSE(subtractOperator.isRaiseToPower());
    EXPECT_FALSE(multiplyOperator.isRaiseToPower());
    EXPECT_FALSE(divideOperator.isRaiseToPower());
    EXPECT_TRUE(raiseToPowerOperator.isRaiseToPower());
}

}

}