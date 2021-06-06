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

TEST(OperatorTest, EqualityOperatorWorks)
{
    Operator operator1;
    Operator operator2("+");
    Operator operator3("-");
    Operator operator4("+");

    EXPECT_TRUE(operator1==operator1);
    EXPECT_FALSE(operator1==operator2);
    EXPECT_TRUE(operator2==operator2);
    EXPECT_FALSE(operator2==operator3);
    EXPECT_TRUE(operator2==operator4);
}

TEST(OperatorTest, IsAdditionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isAddition());
    EXPECT_TRUE(addOperator.isAddition());
    EXPECT_FALSE(subtractOperator.isAddition());
    EXPECT_FALSE(multiplyOperator.isAddition());
    EXPECT_FALSE(divideOperator.isAddition());
    EXPECT_FALSE(raiseToPowerOperator.isAddition());
    EXPECT_FALSE(invalidOperator.isAddition());
}

TEST(OperatorTest, IsSubtractionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isSubtraction());
    EXPECT_FALSE(addOperator.isSubtraction());
    EXPECT_TRUE(subtractOperator.isSubtraction());
    EXPECT_FALSE(multiplyOperator.isSubtraction());
    EXPECT_FALSE(divideOperator.isSubtraction());
    EXPECT_FALSE(raiseToPowerOperator.isSubtraction());
    EXPECT_FALSE(invalidOperator.isSubtraction());
}

TEST(OperatorTest, IsMultiplicationWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isMultiplication());
    EXPECT_FALSE(addOperator.isMultiplication());
    EXPECT_FALSE(subtractOperator.isMultiplication());
    EXPECT_TRUE(multiplyOperator.isMultiplication());
    EXPECT_FALSE(divideOperator.isMultiplication());
    EXPECT_FALSE(raiseToPowerOperator.isMultiplication());
    EXPECT_FALSE(invalidOperator.isMultiplication());
}

TEST(OperatorTest, IsDivisionWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isDivision());
    EXPECT_FALSE(addOperator.isDivision());
    EXPECT_FALSE(subtractOperator.isDivision());
    EXPECT_FALSE(multiplyOperator.isDivision());
    EXPECT_TRUE(divideOperator.isDivision());
    EXPECT_FALSE(raiseToPowerOperator.isDivision());
    EXPECT_FALSE(invalidOperator.isDivision());
}

TEST(OperatorTest, IsRaiseToPowerWorksAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isRaiseToPower());
    EXPECT_FALSE(addOperator.isRaiseToPower());
    EXPECT_FALSE(subtractOperator.isRaiseToPower());
    EXPECT_FALSE(multiplyOperator.isRaiseToPower());
    EXPECT_FALSE(divideOperator.isRaiseToPower());
    EXPECT_TRUE(raiseToPowerOperator.isRaiseToPower());
    EXPECT_FALSE(invalidOperator.isRaiseToPower());
}

TEST(OperatorTest, GetOperatorLevelAsExpected)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_EQ(OperatorLevel::Unknown, nullOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, addOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, subtractOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, multiplyOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, divideOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::RaiseToPower, raiseToPowerOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, invalidOperator.getOperatorLevel());
}

TEST(OperatorTest, GetOperatorStringValueAsExpected)
{
    Operator nullOperator;    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_TRUE(nullOperator.getOperatorString().empty());
    EXPECT_EQ("+", addOperator.getOperatorString());
    EXPECT_EQ("-", subtractOperator.getOperatorString());
    EXPECT_EQ("*", multiplyOperator.getOperatorString());
    EXPECT_EQ("/", divideOperator.getOperatorString());
    EXPECT_EQ("^", raiseToPowerOperator.getOperatorString());
    EXPECT_EQ("invalid", invalidOperator.getOperatorString());
}

TEST(OperatorTest, GetDisplayableStringWorks)
{
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator invalidOperator("invalid");

    EXPECT_TRUE(nullOperator.getDisplayableString().empty());
    EXPECT_EQ("+", addOperator.getDisplayableString());
    EXPECT_EQ("-", subtractOperator.getDisplayableString());
    EXPECT_EQ("*", multiplyOperator.getDisplayableString());
    EXPECT_EQ("/", divideOperator.getDisplayableString());
    EXPECT_EQ("^", raiseToPowerOperator.getDisplayableString());
    EXPECT_EQ("invalid", invalidOperator.getDisplayableString());
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
