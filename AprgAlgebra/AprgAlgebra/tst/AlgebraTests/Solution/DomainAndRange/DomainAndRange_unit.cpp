#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

namespace DomainAndRange {

TEST(DomainAndRangeTest, CalculateDomainUsingTransitionValuesWorksWithFunction) {
    AlbaNumbers values{5, 9.25};

    SolutionSet actualDomain =
        calculateDomainUsingTransitionValues(values, [](AlbaNumber const& number) { return (number - 6) ^ 0.5; });

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createCloseEndpoint(6), createPositiveInfinityOpenEndpoint()), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainUsingTransitionValuesWorksWithFunctionWithNanValues) {
    AlbaNumbers values{3};

    SolutionSet actualDomain = calculateDomainUsingTransitionValues(
        values, [](AlbaNumber const& number) { return (number == 3) ? ALBA_NUMBER_NOT_A_NUMBER : number; });

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(3)), acceptedIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(3), createPositiveInfinityOpenEndpoint()), acceptedIntervals[1]);
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTermWithValues) {
    AlbaNumbers values{1.3, 9.25};
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(values, expression);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(2)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithConstant) {
    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(5);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTerm) {
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(expression);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-2), createCloseEndpoint(2)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTermWithExample1) {
    Polynomial polynomial{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}})};
    Expression expression(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(expression);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(0)), acceptedIntervals[0]);
    EXPECT_EQ(
        AlbaNumberInterval(createCloseEndpoint(2), createPositiveInfinityOpenEndpoint()), acceptedIntervals[1]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithEquationWithValues) {
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(polynomialLeft, "=", 36);
    AlbaNumbers numbers{3.3, 9.9};

    SolutionSet actualDomain = calculateDomainForEquation("x", numbers, equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(6)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithEquation) {
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(polynomialLeft, "=", 36);

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-6), createCloseEndpoint(6)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithEquationUsingExample1) {
    Equation equation("y", "=", Monomial(1, {{"x", 2}}));

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithSquareRootOfQuadratic) {
    Polynomial quadratic{Monomial(9, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({quadratic, "^", AlbaNumber::createFraction(1, 2)}));
    Equation equation(expression, "=", "y");

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-3), createCloseEndpoint(3)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWith2AbsoluteValues) {
    Function absoluteValueOfX(Functions::abs(createExpressionIfPossible({"x"})));
    Function absoluteValueOfY(Functions::abs(createExpressionIfPossible({"y"})));
    Expression leftHandExpression(createExpressionIfPossible({absoluteValueOfX, "+", absoluteValueOfY}));
    Equation equation(leftHandExpression, "=", 1);

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-1), createCloseEndpoint(1)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithXToTheXIsWrong) {
    Expression leftHandExpression(createExpressionIfPossible({"x", "^", "x", "-", 823543}));
    Equation equation(leftHandExpression, "=", "y");

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(143.016087935746)),
        acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWithEquationWithValues) {
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(polynomialLeft, "=", 36);
    AlbaNumbers numbers{3.3, 9.9};

    SolutionSet actualRange = calculateRangeForEquation("x", numbers, equation);

    AlbaNumberIntervals acceptedIntervals(actualRange.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(6)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWithEquation) {
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(polynomialLeft, "=", 36);

    SolutionSet actualRange = calculateRangeForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualRange.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-6), createCloseEndpoint(6)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWithEquationUsingExample1) {
    Equation equation("y", "=", Monomial(1, {{"x", 2}}));

    SolutionSet actualRange = calculateRangeForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualRange.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(0), createPositiveInfinityOpenEndpoint()), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWith2AbsoluteValues) {
    Function absoluteValueOfX(Functions::abs(createExpressionIfPossible({"x"})));
    Function absoluteValueOfY(Functions::abs(createExpressionIfPossible({"y"})));
    Expression leftHandExpression(createExpressionIfPossible({absoluteValueOfX, "+", absoluteValueOfY}));
    Equation equation(leftHandExpression, "=", 1);

    SolutionSet actualRange = calculateRangeForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualRange.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-1), createCloseEndpoint(1)), acceptedIntervals[0]);
}

TEST(DomainAndRangeTest, AppendTransitionValuesWorks) {
    AlbaNumbersSet collectedValues;
    AlbaNumbersSet sortedValues{5, 9.25};

    appendTransitionValues(collectedValues, sortedValues, [](AlbaNumber const& number) { return (number - 6) ^ 0.5; });

    ASSERT_EQ(1U, collectedValues.size());
    AlbaNumbersSet::const_iterator it = collectedValues.cbegin();
    EXPECT_EQ(AlbaNumber(6), *(it++));
}

TEST(DomainAndRangeTest, GetTransitionValueWorks) {
    AlbaNumber actualTransitionValue = getTransitionValue(
        AlbaNumber(9.25), AlbaNumber(5), [](AlbaNumber const& number) { return (number - 6) ^ 0.5; });

    EXPECT_EQ(AlbaNumber(6), actualTransitionValue);
}

TEST(DomainAndRangeTest, IsOneToOneWorks) {
    Equation equation1("y", "=", Monomial(1, {{"x", 2}}));
    Equation equation2("y", "=", Monomial(1, {{"x", 3}}));

    EXPECT_FALSE(isOneToOne("x", equation1));
    EXPECT_TRUE(isOneToOne("x", equation2));
}

}  // namespace DomainAndRange

}  // namespace algebra

}  // namespace alba
