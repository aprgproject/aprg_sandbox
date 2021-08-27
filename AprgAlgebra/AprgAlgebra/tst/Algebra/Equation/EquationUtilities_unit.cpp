#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
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

TEST(EquationUtilitiesTest, DoesNegativeVariableSubstitutionYieldsToTheSameEquationWorks)
{
    EXPECT_TRUE(doesNegativeVariableSubstitutionYieldsToTheSameEquation(Equation(Term("a"), "=", Term("b")), {"x"}));
    EXPECT_FALSE(doesNegativeVariableSubstitutionYieldsToTheSameEquation(Equation(Term("a"), "=", Term("b")), {"a"}));
    EXPECT_FALSE(doesNegativeVariableSubstitutionYieldsToTheSameEquation(Equation(Term("a"), "=", Term("b")), {"b"}));
    EXPECT_TRUE(doesNegativeVariableSubstitutionYieldsToTheSameEquation(Equation(Term("a"), "=", Term("b")), {"a", "b"}));
}

TEST(EquationUtilitiesTest, IsSymmetricAlongXAxisWorks)
{
    EXPECT_FALSE(isSymmetricAlongXAxis(Equation(Term("x"), "=", Term("y"))));
    EXPECT_TRUE(isSymmetricAlongXAxis(Equation(Term("x"), "=", Term(Monomial(1, {{"y", 2}})))));
    EXPECT_TRUE(isSymmetricAlongXAxis(Equation(Term("x"), "=", Term(abs(Term("y"))))));
}

TEST(EquationUtilitiesTest, IsSymmetricAlongYAxisWorks)
{
    EXPECT_FALSE(isSymmetricAlongYAxis(Equation(Term("y"), "=", Term("x"))));
    EXPECT_TRUE(isSymmetricAlongYAxis(Equation(Term("y"), "=", Term(Monomial(1, {{"x", 2}})))));
    EXPECT_TRUE(isSymmetricAlongYAxis(Equation(Term("y"), "=", Term(abs(Term("x"))))));
}

TEST(EquationUtilitiesTest, IsSymmetricOnOriginWorks)
{
    EXPECT_TRUE(isSymmetricOnOrigin(Equation(Term("y"), "=", Term("x"))));
    EXPECT_FALSE(isSymmetricOnOrigin(Equation(Term("y"), "=", Term(Monomial(1, {{"x", 2}})))));
    EXPECT_TRUE(isSymmetricOnOrigin(Equation(Term("y"), "=", Term(Monomial(1, {{"x", 3}})))));
    EXPECT_FALSE(isSymmetricOnOrigin(Equation(Term("y"), "=", Term(abs(Term("x"))))));
    EXPECT_TRUE(isSymmetricOnOrigin(Equation(Term(Monomial(1, {{"x", 1}, {"y", 1}})), "=", Term(1))));
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

TEST(EquationUtilitiesTest, GetReverseEquationOperatorStringWorks)
{
    EXPECT_EQ("", getReverseEquationOperatorString(""));
    EXPECT_EQ("=", getReverseEquationOperatorString("="));
    EXPECT_EQ("==", getReverseEquationOperatorString("=="));
    EXPECT_EQ("!=", getReverseEquationOperatorString("!="));
    EXPECT_EQ(">", getReverseEquationOperatorString("<"));
    EXPECT_EQ("<", getReverseEquationOperatorString(">"));;
    EXPECT_EQ(">=", getReverseEquationOperatorString("<="));
    EXPECT_EQ("<=", getReverseEquationOperatorString(">="));
    EXPECT_EQ("!!", getReverseEquationOperatorString("!!"));
}

TEST(EquationUtilitiesTest, BuildEquationIfPossibleWorks)
{
    Equation expectedEquation(Term("a"), "=", Term("b"));

    EXPECT_EQ(expectedEquation, buildEquationIfPossible("a=b"));
}

}

}
