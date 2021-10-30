#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationUtilitiesTest, SimplifyTermToACommonDenominatorWorks)
{
    Term denominator1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term denominator2(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term firstTerm(createExpressionIfPossible({Term(1), Term("/"), denominator1}));
    Term secondTerm(createExpressionIfPossible({Term(1), Term("/"), denominator2}));

    Term termToTest(createExpressionIfPossible({firstTerm, Term("+"), secondTerm}));
    simplifyTermToACommonDenominator(termToTest);

    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})});
    Term expectedTerm(createExpressionIfPossible({Term(-5), Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, termToTest);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})}),
                        Term("/"),
                        Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}),
                    }));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks_OnExponentPlusPolynomialDenominator)
{\
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^x+((1)/(x+2))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Polynomial polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression subExpression1(createExpressionIfPossible({Term(2), Term("^"), Term("x")}));
    Expression subExpression2(createExpressionIfPossible({Term("x"), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression4(createExpressionIfPossible({Term(1), Term("+"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4), Term("/"), Term(polynomialToExpect)}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks_OnExponentWithFractionExpressions)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^(((1)/(x+2))+((1)/(x-2)))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Polynomial polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression subExpression(createExpressionIfPossible({Term(Monomial(2, {{"x", 1}})), Term("/"), Term(polynomialToExpect)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(2), Term("^"), Term(subExpression)}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_FALSE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTerm)
{
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(Term(Monomial(5, {{}})), TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTermWithManyExpressions)
{
    Term oneTerm(createExpressionInAnExpression(createExpressionInAnExpression(createAndWrapExpressionFromATerm(Term(Monomial(5, {{}}))))));
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(oneTerm, TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}



}

}

}
