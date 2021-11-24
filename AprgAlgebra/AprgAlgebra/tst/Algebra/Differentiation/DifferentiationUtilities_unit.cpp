#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationUtilitiesTest, IsTheFirstFundamentalTheoremOfCalculusTrueWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest1, "x"));
    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest2, "x"));
    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest3, "x"));
}

TEST(DifferentiationUtilitiesTest, IsDifferentiableAtWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAt(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAt(termToTest, "x", 2));
}

TEST(DifferentiationUtilitiesTest, IsDifferentiableAtUsingDerivativeDefinitionWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAtUsingDerivativeDefinition(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAtUsingDerivativeDefinition(termToTest, "x", 2));
}

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorks)
{
    Term termToTest(Polynomial{Monomial(1, {{"a", 2}}), Monomial(1, {})});

    Term derivative(getDerivativeDefinition(termToTest, "a"));

    Term termToExpect(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(2, {{"x", 1}})});
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorksWithRadical)
{
    Term termToTest(Monomial(1, {{"a", AlbaNumber::createFraction(1, 3)}}));

    Term derivative(getDerivativeDefinition(termToTest, "a"));

    string stringToExpect("(1/(1[x^(2/3)]+(1[x^(1/3)]*((1[deltaX] + 1[x])^(1/3)))+((1[deltaX] + 1[x])^(2/3))))");
    EXPECT_EQ(stringToExpect, derivative.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenInputIsAConstant)
{
    Term termToTest(5);

    Term derivative(getDerivativeAtUsingLimit(termToTest, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(0), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAValue)
{
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term derivative(getDerivativeAtUsingLimit(termToTest, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(4), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAVariable)
{
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term derivative(getDerivativeAtUsingLimit(termToTest, "x", Term("y"), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Monomial(2, {{"y", 1}})), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAVariableAndMonomialIsRadical)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    Term derivative(getDerivativeAtUsingLimit(termToTest, "x", Term("y"), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Monomial(AlbaNumber::createFraction(1, 3), {{"y", AlbaNumber::createFraction(-2, 3)}})), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialAndWhenXIsAValue)
{
    Term polynomialTerm(Polynomial{Monomial(3, {{"x", 2}}), Monomial(12, {})});

    Term derivative(getDerivativeAtUsingLimit(polynomialTerm, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(12), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialAndWhenXIsAVariable)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-3, {{"x", 1}}), Monomial(4, {})});

    Term derivative(getDerivativeAtUsingLimit(polynomialTerm, "x", Term("z"), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"z", 2}}), Monomial(-3, {})}), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForRadicalAndWhenXIsAVariable)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term radicalTerm(createExpressionIfPossible({polynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term derivative(getDerivativeAtUsingLimit(radicalTerm, "x", Term("a"), LimitAtAValueApproachType::BothSides));

    Term expectedSubPolynomial(Polynomial{Monomial(1, {{"a", 1}}), Monomial(-3, {})});
    Term expectedRadicalTerm(createExpressionIfPossible({expectedSubPolynomial, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToExpect(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("/"), expectedRadicalTerm}));
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialOverPolynomialAndWhenXIsAVariable)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term derivative(getDerivativeAtUsingLimit(polynomialOverPolynomialTerm, "x", Term("a"), LimitAtAValueApproachType::BothSides));

    Term expectedDenominator(Polynomial{Monomial(1, {{"a", 2}}), Monomial(-6, {{"a", 1}}), Monomial(9, {})});
    Term termToExpect(createExpressionIfPossible({Term(5), Term("/"), expectedDenominator}));
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetRelationshipOfDerivativeOfTheInverseAndTheDerivativeWorks)
{
    Term termToTest1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term termToTest2(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {})});
    Term termToTest3(Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {})});

    Equation equation1(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest1, "x", "c", "d"));
    Equation equation2(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest2, "x", "c", "d"));
    Equation equation3(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest3, "x", "c", "d"));

    string stringToExpect1("1 = 1");
    string stringToExpect2("((1/2)/((1[d] + -2)^(1/2))) = (1/2)[c^-1]");
    string stringToExpect3("((1/3)/((1[d] + -3)^(2/3))) = (1/3)[c^-2]");
    EXPECT_EQ(stringToExpect1, equation1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, equation2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, equation3.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetIntegralEquationForFirstOrderDifferentialEquationWorks)
{
    Term leftHandSide(Polynomial{Monomial(1, {{"d[y]/d[x]", 1}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(-3, {{"x", 1}})});
    Equation equationToTest(leftHandSide, "=", Term(0));

    Equation equationToVerify(getIntegralEquationForFirstOrderDifferentialEquation(equationToTest, "x", "y"));

    string stringToExpect("y = ((((e)^1[x^2][y])*-3/2[y^2]/((e)^1[x^2][y]))+(((e)^1[x^2][y])*(e)*((e)^1[x^2][y])))");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetLogarithmicDifferentiationToYieldDyOverDxWorks)
{
    Polynomial xMinusOne{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Term termToTest(createExpressionIfPossible({Term(xMinusOne), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term dyOverDx(getLogarithmicDifferentiationToYieldDyOverDx(termToTest, "x", "y"));

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term squareRootTerm(createExpressionIfPossible({insideSquareRootTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToExpect(createExpressionIfPossible({Term(1), Term("/"), Term(2), Term("/"), squareRootTerm}));
    EXPECT_EQ(termToExpect, dyOverDx);
}

TEST(DifferentiationUtilitiesTest, GetCartesianDerivativeOfTermInPolarCoordinatesWorks)
{
    string thetaName("theta");
    Term theta(thetaName);
    Term radiusOfLimacon(createExpressionIfPossible({Term(3), Term("+"), Term(2), Term("*"), Term(sin(theta))}));

    Term dyOverDx(getCartesianDerivativeOfTermInPolarCoordinates(radiusOfLimacon, thetaName));

    string stringToExpect("(((4*cos(theta)*sin(theta))+(3*cos(theta)))/((2*cos(theta)*cos(theta))-(3*sin(theta))-(2*sin(theta)*sin(theta))))");
    EXPECT_EQ(stringToExpect, dyOverDx.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetSlopeOfTermInPolarCoordinatesWorks)
{
    string thetaName("theta");
    Term theta(thetaName);
    Term radiusOfLimacon(createExpressionIfPossible({Term(3), Term("+"), Term(2), Term("*"), Term(cos(theta))}));

    Term termToVerify(getSlopeOfTermInPolarCoordinates(radiusOfLimacon, thetaName, AlbaNumber(AlbaNumber::Value::pi)/2));

    EXPECT_EQ(Term(AlbaNumber::createFraction(2, 3)), termToVerify);
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsFormulaWorksForEToTheX)
{
    Term x("x");
    Term termToTest(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));

    Term termToVerify(getApproximationUsingTaylorsFormula(termToTest, "x", Term(0), Term("q"), 3));

    string stringToExpect("((1/6)[q^3] + (1/2)[q^2] + 1[q] + 1)");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsFormulaWorksForSin)
{
    Term x("x");
    Term termToTest(sin(x));

    Term termToVerify(getApproximationUsingTaylorsFormula(termToTest, "x", Term(0), Term("q"), 8));

    string stringToExpect("((-1/5040)[q^7] + (1/120)[q^5] + (-1/6)[q^3] + 1[q])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsRemainderWorks)
{
    Term x("x");
    Term termToTest(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));

    Term termToVerify(getApproximationUsingTaylorsRemainder(termToTest, "x", Term(0), Term(AlbaNumber::createFraction(1, 2)), Term(0), 5));

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 46080)), termToVerify);
    // this means the when n=5 the square root of e is accurate up to 4 decimal places.
}

TEST(DifferentiationUtilitiesTest, GetTotalDerivativeWithInnerTermsUsingChainRuleWorks)
{
    Term t("t");
    Term termToTest(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(1, {{"y", 2}})});
    Term x(createExpressionIfPossible({t, Term("*"), Term(cos(t))}));
    Term y(createExpressionIfPossible({t, Term("*"), Term(sin(t))}));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm("x", x);
    substitution.putVariableWithTerm("y", y);

    Term termToVerify(getTotalDerivativeWithInnerTermsUsingChainRule(termToTest, substitution, "t"));

    string stringToExpect1("((2[t]*(cos(t)^2))+(4[t]*cos(t)*sin(t))-(2[t^2]*(sin(t)^2))+(2[t^2]*(cos(t)^2))+(2[t]*(sin(t)^2)))");
    EXPECT_EQ(stringToExpect1, termToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetTotalDerivativeWorks)
{
    Term termToTest(Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-5, {{"y", 3}})});

    Term termToVerify(getTotalDerivative(termToTest, {"x", "y"}));

    string stringToExpect1("(3[x^2] + -15[y^2] + 3[x] + 3[y])");
    EXPECT_EQ(stringToExpect1, termToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetPartialDerivativeWorks)
{
    Term termToTest(Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-5, {{"y", 3}})});

    Term termToVerify1(getPartialDerivative(termToTest, "x"));
    Term termToVerify2(getPartialDerivative(termToTest, "y"));

    string stringToExpect1("(3[x^2] + 3[y])");
    string stringToExpect2("(-15[y^2] + 3[x])");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetPartialDerivativeContinuouslyWorks)
{
    Term x("x");
    Term y("y");
    Term part1(createExpressionIfPossible({getEAsTerm(), Term("^"), x, Term("*"), Term(sin(y))}));
    Term part2(ln(Monomial(1, {{"x", 1}, {"y", 1}})));
    Term termToTest(createExpressionIfPossible({part1, Term("+"), part2}));

    Term termToVerify(getPartialDerivative(getPartialDerivative(getPartialDerivative(termToTest, "y"), "y"), "x"));

    string stringToExpect("(-1*((e)^x)*sin(y))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationUtilitiesTest, GetDifferentiabilityDomainWorks)
{
    Polynomial numerator{Monomial(1, {{"x", 1}}), Monomial(3, {})};    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Term termToTest(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    SolutionSet differentiabilityDomain(getDifferentiabilityDomain(termToTest, "x"));
    AlbaNumberIntervals const& intervalToVerify(differentiabilityDomain.getAcceptedIntervals());
    ASSERT_EQ(2U, intervalToVerify.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(0.9999979999999644)),
              intervalToVerify.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1.000001999999898), createPositiveInfinityOpenEndpoint()),
              intervalToVerify.at(1));
}

TEST(DifferentiationUtilitiesTest, SimplifyDerivativeByDefinitionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToTest(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));

    simplifyDerivativeByDefinition(termToTest);

    string stringToExpect("(x*((1[x] + 1)^(1/2)))");
    EXPECT_EQ(stringToExpect, termToTest.getDisplayableString());
}

}

}
