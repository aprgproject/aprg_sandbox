#include <Algebra/Equation/EquationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(EquationUtilitiesTest, IsEqualWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_TRUE(isEqual(term1, term1));
    EXPECT_TRUE(isEqual(term1, term2));
    EXPECT_FALSE(isEqual(term1, term3));
    EXPECT_FALSE(isEqual(term1, term4));
    EXPECT_FALSE(isEqual(term1, term5));
}

TEST(EquationUtilitiesTest, IsNotEqualWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_FALSE(isNotEqual(term1, term1));
    EXPECT_FALSE(isNotEqual(term1, term2));
    EXPECT_TRUE(isNotEqual(term1, term3));
    EXPECT_TRUE(isNotEqual(term1, term4));
    EXPECT_TRUE(isNotEqual(term1, term5));
}

TEST(EquationUtilitiesTest, IsLessThanWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_FALSE(isLessThan(term1, term1));
    EXPECT_FALSE(isLessThan(term1, term2));
    EXPECT_FALSE(isLessThan(term1, term3));
    EXPECT_TRUE(isLessThan(term1, term4));
    EXPECT_FALSE(isLessThan(term1, term5));
}

TEST(EquationUtilitiesTest, IsGreaterThanWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_FALSE(isGreaterThan(term1, term1));
    EXPECT_FALSE(isGreaterThan(term1, term2));
    EXPECT_TRUE(isGreaterThan(term1, term3));
    EXPECT_FALSE(isGreaterThan(term1, term4));
    EXPECT_FALSE(isGreaterThan(term1, term5));
}

TEST(EquationUtilitiesTest, IsLessThanOrEqualWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_TRUE(isLessThanOrEqual(term1, term1));
    EXPECT_TRUE(isLessThanOrEqual(term1, term2));
    EXPECT_FALSE(isLessThanOrEqual(term1, term3));
    EXPECT_TRUE(isLessThanOrEqual(term1, term4));
    EXPECT_FALSE(isLessThanOrEqual(term1, term5));
}

TEST(EquationUtilitiesTest, IsGreaterThanOrEqualWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_TRUE(isGreaterThanOrEqual(term1, term1));
    EXPECT_TRUE(isGreaterThanOrEqual(term1, term2));
    EXPECT_TRUE(isGreaterThanOrEqual(term1, term3));
    EXPECT_FALSE(isGreaterThanOrEqual(term1, term4));
    EXPECT_FALSE(isGreaterThanOrEqual(term1, term5));
}

TEST(EquationUtilitiesTest, IsEquationOperationSatisfiedWorks)
{
    Term term1(1234);
    Term term2(1234);
    Term term3(1111);
    Term term4(5678);
    Term term5("x");

    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("="), term1, term1));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("="), term1, term2));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("="), term1, term3));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("="), term1, term4));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("="), term1, term5));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("!="), term1, term1));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("!="), term1, term2));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("!="), term1, term3));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("!="), term1, term4));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("!="), term1, term5));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<"), term1, term1));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<"), term1, term2));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<"), term1, term3));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("<"), term1, term4));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<"), term1, term5));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">"), term1, term1));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">"), term1, term2));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator(">"), term1, term3));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">"), term1, term4));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">"), term1, term5));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("<="), term1, term1));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("<="), term1, term2));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<="), term1, term3));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator("<="), term1, term4));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator("<="), term1, term5));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator(">="), term1, term1));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator(">="), term1, term2));
    EXPECT_TRUE(isEquationOperationSatisfied(EquationOperator(">="), term1, term3));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">="), term1, term4));
    EXPECT_FALSE(isEquationOperationSatisfied(EquationOperator(">="), term1, term5));
}

}

}
