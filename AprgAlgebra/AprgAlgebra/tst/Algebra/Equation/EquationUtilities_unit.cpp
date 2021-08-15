#include <Algebra/Equation/EquationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(EquationUtilitiesTest, IsEquationOperatorStringWorks)
{
    EXPECT_FALSE(isEquationOperatorString(""));
    EXPECT_TRUE(isEquationOperatorString("="));
    EXPECT_TRUE(isEquationOperatorString("=="));
    EXPECT_TRUE(isEquationOperatorString("!="));
    EXPECT_TRUE(isEquationOperatorString("<"));
    EXPECT_TRUE(isEquationOperatorString(">"));;
    EXPECT_TRUE(isEquationOperatorString("<="));
    EXPECT_TRUE(isEquationOperatorString(">="));
    EXPECT_FALSE(isEquationOperatorString("!!"));
}

TEST(EquationUtilitiesTest, IsEquationOperatorCharacterStringWorks)
{
    EXPECT_FALSE(isEquationOperatorCharacterString(""));
    EXPECT_TRUE(isEquationOperatorCharacterString("="));
    EXPECT_TRUE(isEquationOperatorCharacterString("!"));
    EXPECT_TRUE(isEquationOperatorCharacterString("<"));
    EXPECT_TRUE(isEquationOperatorCharacterString(">"));;
    EXPECT_FALSE(isEquationOperatorCharacterString("?"));
}

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

TEST(EquationUtilitiesTest, DoesAllEquationsHaveEqualityOperatorWorks)
{
    Equation equation1(Term("a"), "=", Term("b"));
    Equation equation2(Term("x"), "=", Term("y"));
    Equation equation3(Term("r"), "!=", Term("p"));

    EXPECT_TRUE(doesAllEquationsHaveEqualityOperator(Equations{}));
    EXPECT_FALSE(doesAllEquationsHaveEqualityOperator(Equations{equation1, equation2, equation3}));
    EXPECT_TRUE(doesAllEquationsHaveEqualityOperator(Equations{equation1, equation2}));
    EXPECT_TRUE(doesAllEquationsHaveEqualityOperator(Equations{equation1, equation1, equation1, equation1}));
    EXPECT_FALSE(doesAllEquationsHaveEqualityOperator(Equations{equation1, equation1, equation1, equation3}));
}

TEST(EquationUtilitiesTest, GetEquationOperatorCharactersWorks)
{
    EXPECT_EQ("!=<>", getEquationOperatorCharacters());
}

TEST(EquationUtilitiesTest, BuildEquationIfPossibleWorks)
{
    Equation expectedEquation(Term("a"), "=", Term("b"));

    EXPECT_EQ(expectedEquation, buildEquationIfPossible("a=b"));
}

TEST(EquationUtilitiesTest, RetrieveAndReturnVariableNamesWorks)
{
    VariableNamesSet variableNamesSet(retrieveAndReturnVariableNames(Equation(Term("a"), "=", Term("b"))));

    ASSERT_EQ(2u, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
}

TEST(EquationUtilitiesTest, RetrieveVariableNamesWorksForEquation)
{
    VariableNamesSet variableNamesSet;
    Equation equation(Term("a"), "=", Term("b"));

    retrieveVariableNames(variableNamesSet, equation);

    ASSERT_EQ(2u, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
}

TEST(EquationUtilitiesTest, RetrieveVariableNamesWorksForEquations)
{
    VariableNamesSet variableNamesSet;
    Equation equation1(Term("a"), "=", Term("b"));
    Equation equation2(Term("x"), "=", Term("y"));
    Equation equation3(Term("r"), "!=", Term("p"));

    retrieveVariableNames(variableNamesSet, Equations{equation1, equation2, equation3});

    ASSERT_EQ(6u, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("p", *(it++));
    EXPECT_EQ("r", *(it++));
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

}

}
