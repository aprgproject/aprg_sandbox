#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{
namespace algebra
{

TEST(LimitTest, IsRejectedLimitValueForDirectSubstitutionAndIterativeMethodsWorks)
{
    EXPECT_TRUE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(0)));
    EXPECT_FALSE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(1)));
    EXPECT_TRUE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    EXPECT_TRUE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(AlbaNumber::Value::NegativeInfinity)));
    EXPECT_TRUE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(AlbaNumber::Value::NotANumber)));
    EXPECT_TRUE(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber(AlbaNumber::createComplexNumber(2, 3))));
}

TEST(LimitTest, GetLimitValueByApproachTypeWorksForPolynomialOverPolynomial){
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));
    EXPECT_EQ(AlbaNumber(10), getLimitValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::BothSides));
    EXPECT_EQ(AlbaNumber(10), getLimitValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::PositiveSide));
    EXPECT_EQ(AlbaNumber(10), getLimitValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitInBothSidesWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitInBothSides(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitInPositiveSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitInPositiveSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitInNegativeSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitInNegativeSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitByIterationAndLinearInterpolationWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 6, 10));
    EXPECT_EQ(AlbaNumber(10), getLimitByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 4, 10));
}

TEST(LimitTest, GetValueUsingLinearInterpolationWorks)
{
    EXPECT_EQ(AlbaNumber(6), getValueUsingLinearInterpolation(1, 2, 3, 2, 4));
    EXPECT_EQ(AlbaNumber(2), getValueUsingLinearInterpolation(1, 2, 3, 2, 2));
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 1, 2).isNotANumber());
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 2, 2).isNotANumber());
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksWhichDoesNotResultToConstant)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}, {"y", 2}}), Monomial(-7, {})});

    Term expectedTermWithY(Polynomial{Monomial(12, {{"y", 2}}), Monomial(-7, {})});
    EXPECT_EQ(expectedTermWithY, getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::BothSides));
    EXPECT_EQ(expectedTermWithY, getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::PositiveSide));
    EXPECT_EQ(expectedTermWithY, getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});

    EXPECT_EQ(Term(5), getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::BothSides));
    EXPECT_EQ(Term(5), getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(5), getLimitAsItApproachesAValue(polynomialTerm, "x", 3, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForConstantOverPolynomial)
{
    Term numerator(3);
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_TRUE(isNotANumber(getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::BothSides)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForConstantOverPolynomialSquared)
{
    Term numerator(3);
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term denominator(createExpressionIfPossible({polynomialTerm, Term("^"), Term(2)}));
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::BothSides));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), getLimitAsItApproachesAValue(constantOverPolynomialTerm, "x", 2, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(10), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::BothSides));
    EXPECT_EQ(Term(10), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(10), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 5, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForPolynomialOverPolynomialWithFractionalValues)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(0.25), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 4, LimitApproachType::BothSides));
    EXPECT_EQ(Term(0.25), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 4, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(0.25), getLimitAsItApproachesAValue(polynomialOverPolynomialTerm, "x", 4, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForSignumFunction)
{
    Term signumFunctionTerm(sgn(Term("x")));

    EXPECT_TRUE(isNotANumber(getLimitAsItApproachesAValue(signumFunctionTerm, "x", 0, LimitApproachType::BothSides)));
    EXPECT_EQ(Term(1), getLimitAsItApproachesAValue(signumFunctionTerm, "x", 0, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(-1), getLimitAsItApproachesAValue(signumFunctionTerm, "x", 0, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForAbsoluteValueFunction)
{
    Term absoluteValueFunction(Functions::abs(Term("x")));

    EXPECT_EQ(Term(Constant(0)), getLimitAsItApproachesAValue(absoluteValueFunction, "x", 0, LimitApproachType::BothSides));
    EXPECT_EQ(Term(Constant(0)), getLimitAsItApproachesAValue(absoluteValueFunction, "x", 0, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(Constant(0)), getLimitAsItApproachesAValue(absoluteValueFunction, "x", 0, LimitApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAsItApproachesAValueWorksForASpecifiedFunction)
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

    EXPECT_EQ(Term(3), getLimitAsItApproachesAValue(functionTermToTest, "x", 1, LimitApproachType::BothSides));
    EXPECT_EQ(Term(3), getLimitAsItApproachesAValue(functionTermToTest, "x", 1, LimitApproachType::PositiveSide));
    EXPECT_EQ(Term(3), getLimitAsItApproachesAValue(functionTermToTest, "x", 1, LimitApproachType::NegativeSide));
}

}

}