#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(LimitTest, IsAlmostEqualForLimitIterationWorks)
{
    AlbaNumberToleranceToZeroScopeObject scopeObject;
    scopeObject.doSomethingToAvoidWarning();

    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(1E-15), AlbaNumber(3E-15)));
    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(1E-16), AlbaNumber(3E-16)));
}

TEST(LimitTest, IsAlmostEqualForLimitCheckingWorks)
{
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(1E-5), AlbaNumber(3E-5)));
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(1E-6), AlbaNumber(3E-6)));
}

TEST(LimitTest, HasVerticalAsymptoteAtValueWorks)
{
    Term numerator(3);
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_FALSE(hasVerticalAsymptoteAtValue(Term("x"), "x", 2));
    EXPECT_TRUE(hasVerticalAsymptoteAtValue(constantOverPolynomialTerm, "x", 2));
}

TEST(LimitTest, HasHorizontalAsymptoteAtValueWorks)
{
    Term numerator("x");
    Term denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorInSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_FALSE(hasHorizontalAsymptoteAtValue(term, "x", 3));
    EXPECT_TRUE(hasHorizontalAsymptoteAtValue(term, "x", 1));
}

TEST(LimitTest, IsSqueezeTheoremSatisfiedWorks)
{
    Term f(buildTermIfPossible("-4*(x-2)^2 + 3"));
    Term g(buildTermIfPossible("(x-2)*(x^2 - 4*x + 7)/(x-2)"));
    Term h(buildTermIfPossible("4*(x-2)^2 + 3"));

    EXPECT_FALSE(isSqueezeTheoremSatisfied(h, g, f, "x", 1));
    EXPECT_TRUE(isSqueezeTheoremSatisfied(h, g, f, "x", 2));
}

TEST(LimitTest, GetLimitAtAValueByApproachTypeWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueInBothSidesWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInBothSides(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInThePositiveSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInThePositiveSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInTheNegativeSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInTheNegativeSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueByIterationAndLinearInterpolationWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 6, 10));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 4, 10));
}

TEST(LimitTest, GetLimitAtAValueUsingTrendOfValuesWorks)
{
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({Term(3), Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(AlbaNumber::Value::PositiveInfinity), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 3, 4));
    EXPECT_EQ(AlbaNumber(AlbaNumber::Value::NegativeInfinity), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 1, 0));
    EXPECT_EQ(AlbaNumber(AlbaNumber::createFraction(9, 10)), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 5, 6, 7));
}

TEST(LimitTest, GetValueUsingLinearInterpolationWorks)
{
    EXPECT_EQ(AlbaNumber(6), getValueUsingLinearInterpolation(1, 2, 3, 2, 4));
    EXPECT_EQ(AlbaNumber(2), getValueUsingLinearInterpolation(1, 2, 3, 2, 2));
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 1, 2).isNotANumber());
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 2, 2).isNotANumber());
}

TEST(LimitTest, GetLimitAtAValueWorksWhichDoesNotResultToConstant)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}, {"y", 2}}), Monomial(-7, {})});

    Term expectedTermWithY(Polynomial{Monomial(12, {{"y", 2}}), Monomial(-7, {})});
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});

    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomial)
{
    Term numerator(3);
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_TRUE(isNotANumber(getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomialSquared)
{
    Term numerator(3);
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term denominator(createExpressionIfPossible({polynomialTerm, Term("^"), Term(2)}));
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThree_ThisHitsDiscontinuityInLimitIteration)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_TRUE(isNotANumber(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_TRUE(isNotANumber(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide)));
    EXPECT_TRUE(isNotANumber(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide)));
}

TEST(LimitTest, SimplifyAndGetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThree_ThisCancelsProblematicFactors)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithFractionalValues)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForSignumFunction)
{
    Term signumFunctionTerm(sgn(Term("x")));

    EXPECT_TRUE(isNotANumber(getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(Term(1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForAbsoluteValueFunction)
{
    Term absoluteValueFunction(Functions::abs(Term("x")));

    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForASpecifiedFunction)
{
    Function functionToTest(
                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
        AlbaNumber numberSquared(number^2);
        if(number > 1)
        {
            result = numberSquared + 2;
        }
        else if(number < 1)
        {
            result = AlbaNumber(4) - numberSquared;
        }
        else
        {
            result = AlbaNumber(AlbaNumber::Value::NotANumber);
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtInfinityWorks)
{
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAtInfinity(Term("x"), "x", AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAtInfinity(Term("x"), "x", AlbaNumber::Value::PositiveInfinity));
}

}

}
