#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace DomainAndRange
{

TEST(DomainAndRangeTest, CalculateDomainUsingTransitionValuesWorksWithFunction)
{
    AlbaNumbers values{5, 9.25};

    SolutionSet actualDomain = calculateDomainUsingTransitionValues(values, [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(6), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainUsingTransitionValuesWorksWithFunctionWithNanValues)
{
    AlbaNumbers values{3};

    SolutionSet actualDomain = calculateDomainUsingTransitionValues(values, [](AlbaNumber const& number)
    {
        return (number == 3) ? AlbaNumber(AlbaNumber::Value::NotANumber) : number;
    });

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(2u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(3)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(1));
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTermWithValues)
{
    AlbaNumbers values{1.3, 9.25};
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(values, Term(expression));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(2)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithConstant)
{
    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(Term(5));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTerm)
{
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(Term(expression));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-2), createCloseEndpoint(2)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForTermWithOneVariableWorksWithTermWithExample1)
{
    Polynomial polynomial{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(Term(expression));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(2u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(0)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(2), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(1));
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithEquationWithValues)
{
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(Term(polynomialLeft), "=", Term(Constant(36)));
    AlbaNumbers numbers{3.3, 9.9};

    SolutionSet actualDomain = calculateDomainForEquation("x", numbers, equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(6)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithEquation)
{
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(Term(polynomialLeft), "=", Term(Constant(36)));

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-6), createCloseEndpoint(6)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithSquareRootOfQuadratic)
{
    Polynomial quadratic{Monomial(9, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({Term(quadratic), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Equation equation(Term(expression), "=", Term("y"));

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-3), createCloseEndpoint(3)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWith2AbsoluteValues)
{
    Function absoluteValueOfX(Functions::abs(createExpressionIfPossible({Term("x")})));
    Function absoluteValueOfY(Functions::abs(createExpressionIfPossible({Term("y")})));
    Expression leftHandExpression(createExpressionIfPossible({Term(absoluteValueOfX), Term("+"), Term(absoluteValueOfY)}));
    Equation equation(Term(leftHandExpression), "=", Term(Constant(1)));

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-1), createCloseEndpoint(1)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateDomainForEquationWorksWithXToTheXIsWrong)
{
    Expression leftHandExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x"), Term("-"), Term(823543)}));
    Equation equation(Term(leftHandExpression), "=", Term("y"));

    SolutionSet actualDomain = calculateDomainForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(143.016087935746)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWithEquationWithValues)
{
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(Term(polynomialLeft), "=", Term(Constant(36)));
    AlbaNumbers numbers{3.3, 9.9};

    SolutionSet actualDomain = calculateRangeForEquation("x", numbers, equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(6)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWithEquation)
{
    Polynomial polynomialLeft{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})};
    Equation equation(Term(polynomialLeft), "=", Term(Constant(36)));

    SolutionSet actualDomain = calculateRangeForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-6), createCloseEndpoint(6)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, CalculateRangeForEquationWorksWith2AbsoluteValues)
{
    Function absoluteValueOfX(Functions::abs(createExpressionIfPossible({Term("x")})));
    Function absoluteValueOfY(Functions::abs(createExpressionIfPossible({Term("y")})));
    Expression leftHandExpression(createExpressionIfPossible({Term(absoluteValueOfX), Term("+"), Term(absoluteValueOfY)}));
    Equation equation(Term(leftHandExpression), "=", Term(Constant(1)));

    SolutionSet actualDomain = calculateRangeForEquation("x", equation);

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-1), createCloseEndpoint(1)), acceptedIntervals.at(0));
}

TEST(DomainAndRangeTest, AppendTransitionValuesWorks)
{
    AlbaNumbersSet collectedValues;
    AlbaNumbersSet sortedValues{5, 9.25};

    appendTransitionValues(
                collectedValues,
                sortedValues,
                [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    ASSERT_EQ(1u, collectedValues.size());
    AlbaNumbersSet::const_iterator it = collectedValues.cbegin();
    EXPECT_EQ(AlbaNumber(6), *(it++));
}

TEST(DomainAndRangeTest, GetTransitionValueWorks)
{
    AlbaNumber actualTransitionValue = getTransitionValue(
                AlbaNumber(9.25),
                AlbaNumber(5),
                [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    EXPECT_EQ(AlbaNumber(6), actualTransitionValue);
}

}

}

}
