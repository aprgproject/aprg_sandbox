#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationUtilitiesTest, IsDifferentiableAtWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAt(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAt(termToTest, "x", 2));
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
    Term expectedTerm(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("/"), expectedRadicalTerm}));
    EXPECT_EQ(expectedTerm, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialOverPolynomialAndWhenXIsAVariable)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term derivative(getDerivativeAtUsingLimit(polynomialOverPolynomialTerm, "x", Term("a"), LimitAtAValueApproachType::BothSides));

    Term expectedDenominator(Polynomial{Monomial(1, {{"a", 2}}), Monomial(-6, {{"a", 1}}), Monomial(9, {})});
    Term expectedTerm(createExpressionIfPossible({Term(5), Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, derivative);
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

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorks)
{
    Term term(Polynomial{Monomial(1, {{"a", 2}}), Monomial(1, {})});

    Term derivative(getDerivativeDefinition(term, "a"));

    Term expectedTerm(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(2, {{"x", 1}})});
    EXPECT_EQ(expectedTerm, derivative);
}


}

}
