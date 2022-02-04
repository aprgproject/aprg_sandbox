#include <Algebra/Equation/EquationOperator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(EquationOperatorTest, EquationOperatorsAreConstructedCorrectly)
{
    EquationOperator operator1;
    EquationOperator operator2("test");

    EXPECT_EQ("", operator1.getOperatorString());
    EXPECT_EQ("test", operator2.getOperatorString());
}

TEST(EquationOperatorTest, EqualityEquationOperatorWorks)
{
    EquationOperator operator1;
    EquationOperator operator2("=");
    EquationOperator operator3("<");
    EquationOperator operator4("=");

    EXPECT_TRUE(operator1==operator1);
    EXPECT_FALSE(operator1==operator2);
    EXPECT_TRUE(operator2==operator2);
    EXPECT_FALSE(operator2==operator3);
    EXPECT_TRUE(operator2==operator4);
}

TEST(EquationOperatorTest, InequalityEquationOperatorWorks)
{
    EquationOperator operator1;
    EquationOperator operator2("=");
    EquationOperator operator3("<");
    EquationOperator operator4("=");

    EXPECT_FALSE(operator1!=operator1);
    EXPECT_TRUE(operator1!=operator2);
    EXPECT_FALSE(operator2!=operator2);
    EXPECT_TRUE(operator2!=operator3);
    EXPECT_FALSE(operator2!=operator4);
}

TEST(EquationOperatorTest, LessThanEquationOperatorWorks)
{
    EXPECT_FALSE(EquationOperator() < EquationOperator());
    EXPECT_FALSE(EquationOperator("=") < EquationOperator("="));
    EXPECT_TRUE(EquationOperator("=") < EquationOperator("=="));
    EXPECT_TRUE(EquationOperator("=") < EquationOperator(">"));
}

TEST(EquationOperatorTest, IsEqualWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isEqual());
    EXPECT_TRUE(singleEqualityOperator.isEqual());
    EXPECT_TRUE(doubleEqualityOperator.isEqual());
    EXPECT_FALSE(inequalityOperator.isEqual());
    EXPECT_FALSE(lessThanOperator.isEqual());
    EXPECT_FALSE(greaterThanOperator.isEqual());
    EXPECT_FALSE(lessThanOperatorOrEqual.isEqual());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isEqual());
    EXPECT_FALSE(invalidEquationOperator.isEqual());
}

TEST(EquationOperatorTest, IsNotEqualWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isNotEqual());
    EXPECT_FALSE(singleEqualityOperator.isNotEqual());
    EXPECT_FALSE(doubleEqualityOperator.isNotEqual());
    EXPECT_TRUE(inequalityOperator.isNotEqual());
    EXPECT_FALSE(lessThanOperator.isNotEqual());
    EXPECT_FALSE(greaterThanOperator.isNotEqual());
    EXPECT_FALSE(lessThanOperatorOrEqual.isNotEqual());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isNotEqual());
    EXPECT_FALSE(invalidEquationOperator.isNotEqual());
}

TEST(EquationOperatorTest, IsLessThanWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isLessThan());
    EXPECT_FALSE(singleEqualityOperator.isLessThan());
    EXPECT_FALSE(doubleEqualityOperator.isLessThan());
    EXPECT_FALSE(inequalityOperator.isLessThan());
    EXPECT_TRUE(lessThanOperator.isLessThan());
    EXPECT_FALSE(greaterThanOperator.isLessThan());
    EXPECT_FALSE(lessThanOperatorOrEqual.isLessThan());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isLessThan());
    EXPECT_FALSE(invalidEquationOperator.isLessThan());
}

TEST(EquationOperatorTest, IsGreaterThanWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isGreaterThan());
    EXPECT_FALSE(singleEqualityOperator.isGreaterThan());
    EXPECT_FALSE(doubleEqualityOperator.isGreaterThan());
    EXPECT_FALSE(inequalityOperator.isGreaterThan());
    EXPECT_FALSE(lessThanOperator.isGreaterThan());
    EXPECT_TRUE(greaterThanOperator.isGreaterThan());
    EXPECT_FALSE(lessThanOperatorOrEqual.isGreaterThan());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isGreaterThan());
    EXPECT_FALSE(invalidEquationOperator.isGreaterThan());
}

TEST(EquationOperatorTest, IsLessThanOrEqualWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isLessThanOrEqual());
    EXPECT_FALSE(singleEqualityOperator.isLessThanOrEqual());
    EXPECT_FALSE(doubleEqualityOperator.isLessThanOrEqual());
    EXPECT_FALSE(inequalityOperator.isLessThanOrEqual());
    EXPECT_FALSE(lessThanOperator.isLessThanOrEqual());
    EXPECT_FALSE(greaterThanOperator.isLessThanOrEqual());
    EXPECT_TRUE(lessThanOperatorOrEqual.isLessThanOrEqual());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isLessThanOrEqual());
    EXPECT_FALSE(invalidEquationOperator.isLessThanOrEqual());
}

TEST(EquationOperatorTest, IsGreaterThanOrEqualWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(singleEqualityOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(doubleEqualityOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(inequalityOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(lessThanOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(greaterThanOperator.isGreaterThanOrEqual());
    EXPECT_FALSE(lessThanOperatorOrEqual.isGreaterThanOrEqual());
    EXPECT_TRUE(greaterThanOperatorOrEqual.isGreaterThanOrEqual());
    EXPECT_FALSE(invalidEquationOperator.isGreaterThanOrEqual());
}

TEST(EquationOperatorTest, IsAnEqualityVariantWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isAnEqualityVariant());
    EXPECT_TRUE(singleEqualityOperator.isAnEqualityVariant());
    EXPECT_TRUE(doubleEqualityOperator.isAnEqualityVariant());
    EXPECT_TRUE(inequalityOperator.isAnEqualityVariant());
    EXPECT_FALSE(lessThanOperator.isAnEqualityVariant());
    EXPECT_FALSE(greaterThanOperator.isAnEqualityVariant());
    EXPECT_FALSE(lessThanOperatorOrEqual.isAnEqualityVariant());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isAnEqualityVariant());
    EXPECT_FALSE(invalidEquationOperator.isAnEqualityVariant());
}

TEST(EquationOperatorTest, IsALessThanVariantWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isALessThanVariant());
    EXPECT_FALSE(singleEqualityOperator.isALessThanVariant());
    EXPECT_FALSE(doubleEqualityOperator.isALessThanVariant());
    EXPECT_FALSE(inequalityOperator.isALessThanVariant());
    EXPECT_TRUE(lessThanOperator.isALessThanVariant());
    EXPECT_FALSE(greaterThanOperator.isALessThanVariant());
    EXPECT_TRUE(lessThanOperatorOrEqual.isALessThanVariant());
    EXPECT_FALSE(greaterThanOperatorOrEqual.isALessThanVariant());
    EXPECT_FALSE(invalidEquationOperator.isALessThanVariant());
}

TEST(EquationOperatorTest, IsAGreaterThanVariantWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_FALSE(nullOperator.isAGreaterThanVariant());
    EXPECT_FALSE(singleEqualityOperator.isAGreaterThanVariant());
    EXPECT_FALSE(doubleEqualityOperator.isAGreaterThanVariant());
    EXPECT_FALSE(inequalityOperator.isAGreaterThanVariant());
    EXPECT_FALSE(lessThanOperator.isAGreaterThanVariant());
    EXPECT_TRUE(greaterThanOperator.isAGreaterThanVariant());
    EXPECT_FALSE(lessThanOperatorOrEqual.isAGreaterThanVariant());
    EXPECT_TRUE(greaterThanOperatorOrEqual.isAGreaterThanVariant());
    EXPECT_FALSE(invalidEquationOperator.isAGreaterThanVariant());
}

TEST(EquationOperatorTest, GetEquationOperatorStringValueWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_TRUE(nullOperator.getOperatorString().empty());
    EXPECT_EQ("=", singleEqualityOperator.getOperatorString());
    EXPECT_EQ("==", doubleEqualityOperator.getOperatorString());
    EXPECT_EQ("!=", inequalityOperator.getOperatorString());
    EXPECT_EQ("<", lessThanOperator.getOperatorString());
    EXPECT_EQ(">", greaterThanOperator.getOperatorString());
    EXPECT_EQ("<=", lessThanOperatorOrEqual.getOperatorString());
    EXPECT_EQ(">=", greaterThanOperatorOrEqual.getOperatorString());
    EXPECT_EQ("invalid", invalidEquationOperator.getOperatorString());
}

TEST(EquationOperatorTest, GetDisplayableStringWorks)
{
    EquationOperator nullOperator;
    EquationOperator singleEqualityOperator("=");
    EquationOperator doubleEqualityOperator("==");
    EquationOperator inequalityOperator("!=");
    EquationOperator lessThanOperator("<");
    EquationOperator greaterThanOperator(">");
    EquationOperator lessThanOperatorOrEqual("<=");
    EquationOperator greaterThanOperatorOrEqual(">=");
    EquationOperator invalidEquationOperator("invalid");

    EXPECT_TRUE(nullOperator.getDisplayableString().empty());
    EXPECT_EQ("=", singleEqualityOperator.getDisplayableString());
    EXPECT_EQ("==", doubleEqualityOperator.getDisplayableString());
    EXPECT_EQ("!=", inequalityOperator.getDisplayableString());
    EXPECT_EQ("<", lessThanOperator.getDisplayableString());
    EXPECT_EQ(">", greaterThanOperator.getDisplayableString());
    EXPECT_EQ("<=", lessThanOperatorOrEqual.getDisplayableString());
    EXPECT_EQ(">=", greaterThanOperatorOrEqual.getDisplayableString());
    EXPECT_EQ("invalid", invalidEquationOperator.getDisplayableString());
}

}

}
