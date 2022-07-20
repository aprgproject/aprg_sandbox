#include <BooleanAlgebra/Term/TermTypes/Operator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
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
    Operator operator2("&");
    Operator operator3("|");
    Operator operator4("&");

    EXPECT_TRUE(operator1==operator1);
    EXPECT_FALSE(operator1==operator2);
    EXPECT_TRUE(operator2==operator2);
    EXPECT_FALSE(operator2==operator3);
    EXPECT_TRUE(operator2==operator4);
}

TEST(OperatorTest, InequalityOperatorWorks)
{
    Operator operator1;
    Operator operator2("&");
    Operator operator3("|");
    Operator operator4("&");

    EXPECT_FALSE(operator1!=operator1);
    EXPECT_TRUE(operator1!=operator2);
    EXPECT_FALSE(operator2!=operator2);
    EXPECT_TRUE(operator2!=operator3);
    EXPECT_FALSE(operator2!=operator4);
}

TEST(OperatorTest, LessThanOperatorWorks)
{
    EXPECT_FALSE(Operator() < Operator());
    EXPECT_FALSE(Operator("&") < Operator("&"));
    EXPECT_FALSE(Operator("|") < Operator("&"));
    EXPECT_TRUE(Operator("&") < Operator("|"));
}

TEST(OperatorTest, IsNotWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isNot());
    EXPECT_TRUE(notOperator.isNot());
    EXPECT_FALSE(andOperator.isNot());
    EXPECT_FALSE(orOperator.isNot());
    EXPECT_FALSE(openingGroupOperator.isNot());
    EXPECT_FALSE(closingGroupOperator.isNot());
    EXPECT_FALSE(invalidOperator.isNot());
}

TEST(OperatorTest, IsAndWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isAnd());
    EXPECT_FALSE(notOperator.isAnd());
    EXPECT_TRUE(andOperator.isAnd());
    EXPECT_FALSE(orOperator.isAnd());
    EXPECT_FALSE(openingGroupOperator.isAnd());
    EXPECT_FALSE(closingGroupOperator.isAnd());
    EXPECT_FALSE(invalidOperator.isAnd());
}

TEST(OperatorTest, IsOrWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isOr());
    EXPECT_FALSE(notOperator.isOr());
    EXPECT_FALSE(andOperator.isOr());
    EXPECT_TRUE(orOperator.isOr());
    EXPECT_FALSE(openingGroupOperator.isOr());
    EXPECT_FALSE(closingGroupOperator.isOr());
    EXPECT_FALSE(invalidOperator.isOr());
}

TEST(OperatorTest, IsAnOperatorThatCanPerformedWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(notOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(andOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(orOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(openingGroupOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(closingGroupOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(invalidOperator.isAnOperatorThatCanPerformed());
}

TEST(OperatorTest, IsOpeningGroupOperatorWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isOpeningGroupOperator());
    EXPECT_FALSE(notOperator.isOpeningGroupOperator());
    EXPECT_FALSE(andOperator.isOpeningGroupOperator());
    EXPECT_FALSE(orOperator.isOpeningGroupOperator());
    EXPECT_TRUE(openingGroupOperator.isOpeningGroupOperator());
    EXPECT_FALSE(closingGroupOperator.isOpeningGroupOperator());
    EXPECT_FALSE(invalidOperator.isOpeningGroupOperator());
}

TEST(OperatorTest, IsClosingGroupOperatorWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isClosingGroupOperator());
    EXPECT_FALSE(notOperator.isClosingGroupOperator());
    EXPECT_FALSE(andOperator.isClosingGroupOperator());
    EXPECT_FALSE(orOperator.isClosingGroupOperator());
    EXPECT_FALSE(openingGroupOperator.isClosingGroupOperator());
    EXPECT_TRUE(closingGroupOperator.isClosingGroupOperator());
    EXPECT_FALSE(invalidOperator.isClosingGroupOperator());
}

TEST(OperatorTest, GetOperatorTypeWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_EQ(OperatorType::Unknown, nullOperator.getOperatorType());
    EXPECT_EQ(OperatorType::Not, notOperator.getOperatorType());
    EXPECT_EQ(OperatorType::And, andOperator.getOperatorType());
    EXPECT_EQ(OperatorType::Or, orOperator.getOperatorType());
    EXPECT_EQ(OperatorType::Unknown, openingGroupOperator.getOperatorType());
    EXPECT_EQ(OperatorType::Unknown, closingGroupOperator.getOperatorType());
    EXPECT_EQ(OperatorType::Unknown, invalidOperator.getOperatorType());
}

TEST(OperatorTest, GetOperatorStringValueWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_TRUE(nullOperator.getOperatorString().empty());
    EXPECT_EQ("~", notOperator.getOperatorString());
    EXPECT_EQ("&", andOperator.getOperatorString());
    EXPECT_EQ("|", orOperator.getOperatorString());
    EXPECT_EQ("(", openingGroupOperator.getOperatorString());
    EXPECT_EQ(")", closingGroupOperator.getOperatorString());
    EXPECT_EQ("invalid", invalidOperator.getOperatorString());
}

TEST(OperatorTest, GetDisplayableStringWorks)
{
    Operator nullOperator;
    Operator notOperator("~");
    Operator andOperator("&");
    Operator orOperator("|");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_TRUE(nullOperator.getDisplayableString().empty());
    EXPECT_EQ("~", notOperator.getDisplayableString());
    EXPECT_EQ("&", andOperator.getDisplayableString());
    EXPECT_EQ("|", orOperator.getDisplayableString());
    EXPECT_EQ("(", openingGroupOperator.getDisplayableString());
    EXPECT_EQ(")", closingGroupOperator.getDisplayableString());
    EXPECT_EQ("invalid", invalidOperator.getDisplayableString());
}

TEST(OperatorTest, SettingANewOperatingStringWorks)
{
    Operator operatorForTest1;
    Operator operatorForTest2;

    operatorForTest2.setOperatorString("multiply");

    EXPECT_EQ("", operatorForTest1.getOperatorString());
    EXPECT_EQ("multiply", operatorForTest2.getOperatorString());
}

}

}
