#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>

#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(LimitsAtInfinityTest, XWorksAndSimplifiesToZero)
{
    LimitsAtInfinity limits(Term("x"), "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, OneOverXWorksAndSimplifiesToZero)
{
    Term term(createExpressionIfPossible({Term(1), Term("/"), Term("x")}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(AlbaNumber(0));
    Term expectedValueTerm(AlbaNumber(0));
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithEqualDegreeWorks)
{
    Term numerator(Polynomial{Monomial(2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(AlbaNumber(2));
    Term expectedValueTerm(AlbaNumber(2));
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndPositiveWorks)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    LimitsAtInfinity limits(term, "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndNegativeWorks)
{
    Term numerator(Polynomial{Monomial(-6, {{"x", 2}}), Monomial(2, {{"x", 1}})});
    Term denominator(Polynomial{Monomial(3, {{"x", 1}}), Monomial(5, {})});
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    LimitsAtInfinity limits(term, "x");

    EXPECT_EQ(Term(Monomial(-2, {{"x", 1}})), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithDenominatorDegreeIsGreaterWorks)
{
    Term numerator(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(5, {})});
    Term denominator(Polynomial{Monomial(4, {{"x", 3}}), Monomial(-1, {})});
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(AlbaNumber(0));
    Term expectedValueTerm(AlbaNumber(0));
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitsAtInfinityTest, PolynomialOverSquareRootOfPolynomialWithEqualDegreeWorks)
{
    Term numerator("x");
    Term denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorInSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term term(createExpressionIfPossible({numerator, Term("/"), denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(AlbaNumber(1));
    Term expectedValueTerm(AlbaNumber(1));
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity));
}

}

}
