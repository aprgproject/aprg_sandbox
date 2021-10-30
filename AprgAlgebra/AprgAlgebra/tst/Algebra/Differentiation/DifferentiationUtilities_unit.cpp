#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
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

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorks)
{
    Term term(Polynomial{Monomial(1, {{"a", 2}}), Monomial(1, {})});

    Term derivative(getDerivativeDefinition(term, "a"));

    Term termToExpect(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(2, {{"x", 1}})});
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenInputIsAConstant)
{
    Term termToTest(5);

    Term derivative(getDerivativeAtUsingLimit(termToTest, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Constant(0)), derivative);
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
    Equation equationToTest(leftHandSide, "=", Term(Constant(0)));

    Equation equationToVerify(getIntegralEquationForFirstOrderDifferentialEquation(equationToTest, "x", "y"));

    string stringToExpect("y = (((e)^1[x^2][y])*((-3/2[y^2]/((e)^1[x^2][y]))+((e)*((e)^1[x^2][y]))))");
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

    Term termToVerify(getSlopeOfTermInPolarCoordinates(radiusOfLimacon, thetaName, AlbaNumber(AlbaNumber::Value::pi)));

    EXPECT_EQ(Term(-1), termToVerify);
}

TEST(DifferentiationUtilitiesTest, GetDifferentiabilityDomainWorks)
{
    Polynomial numerator{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
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

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Term termToExpect(createExpressionIfPossible({insideSquareRootTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, termToTest);
}

}

}
