#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationTest, DifferentiateWorksForConstant)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(1), differentiationForX.differentiate(Variable("x")));
    EXPECT_EQ(Term("a"), differentiationForX.differentiate(Variable("a")));
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Monomial(13, {})));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Term(Monomial(8, {{"x", 7}})), differentiationForX.differentiate(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Term(Monomial(42, {{"x", 6}, {"y", 8}, {"z", 9}})), differentiationForX.differentiate(Monomial(6, {{"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Constant(0));
    Term expectedTerm3(Polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})});
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiate(polynomial1));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiate(polynomial2));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiate(polynomial3));
}

TEST(DifferentiationTest, DifferentiateMonomialWorks)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Monomial(0, {}), differentiationForX.differentiateMonomial(Monomial(13, {})));
    EXPECT_EQ(Monomial(0, {}), differentiationForX.differentiateMonomial(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Monomial(8, {{"x", 7}}), differentiationForX.differentiateMonomial(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Monomial(-15, {{"x", -6}}), differentiationForX.differentiateMonomial(Monomial(3, {{"x", -5}})));
    EXPECT_EQ(Monomial(42, {{"x", 6}, {"y", 8}, {"z", 9}}), differentiationForX.differentiateMonomial(Monomial(6, {{"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks)
{
    Differentiation differentiationForX("x");
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};

    Polynomial expectedPolynomial1;
    Polynomial expectedPolynomial2;
    Polynomial expectedPolynomial3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    EXPECT_EQ(expectedPolynomial1, differentiationForX.differentiatePolynomial(polynomial1));
    EXPECT_EQ(expectedPolynomial2, differentiationForX.differentiatePolynomial(polynomial2));
    EXPECT_EQ(expectedPolynomial3, differentiationForX.differentiatePolynomial(polynomial3));
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term term1(Polynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 2}})});
    Term term2(Polynomial{Monomial(3, {{"x", 5}}), Monomial(1, {{"x", 2}})});

    Term expectedTerm(Polynomial{Monomial(48, {{"x", 7}}), Monomial(-84, {{"x", 6}}), Monomial(10, {{"x", 4}}), Monomial(-16, {{"x", 3}})});
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoMultipliedTerms(term1, term2));
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term expectedNumerator(Polynomial{Monomial(2, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(6, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(16, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(18, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(1, {})});
    Term expectedTerm(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoDividedTerms(numerator, denominator));
}

}

}
