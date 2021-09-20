#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(RationalizeTermOverTermTest, ConstructionWorks)
{
    RationalizeTermOverTerm rationalizeTermOverTerm1;
    RationalizeTermOverTerm rationalizeTermOverTerm2(Term("x"), Term("y"));

    EXPECT_TRUE(rationalizeTermOverTerm1.getNumerator().isEmpty());
    EXPECT_TRUE(rationalizeTermOverTerm1.getDenominator().isEmpty());
    EXPECT_EQ(Term("x"), rationalizeTermOverTerm2.getNumerator());
    EXPECT_EQ(Term("y"), rationalizeTermOverTerm2.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWithSquareRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForPolynomialOverPolynomialWithSquareRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-9, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWithCubeRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-8, {})});
    Term expectedDenominator(Polynomial
    {Monomial(1, {{"x", 1}}),
     Monomial(-1, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(-2, {{"x", AlbaNumber::createFraction(1, 3)}}),
     Monomial(-12, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForPolynomialOverPolynomialWithCubeRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term expectedNumerator(Polynomial
    {Monomial(1, {{"x", 1}}),
     Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(3, {{"x", AlbaNumber::createFraction(1, 3)}}),
     Monomial(-18, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-27, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWith6thRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-64, {})});
    Term expectedDenominator(Polynomial
    {Monomial(1, {{"x", 1}}),
     Monomial(-1, {{"x", AlbaNumber::createFraction(5, 6)}}),
     Monomial(-2, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(-4, {{"x", AlbaNumber::createFraction(1, 2)}}),
     Monomial(-8, {{"x", AlbaNumber::createFraction(1, 3)}}),
     Monomial(-16, {{"x", AlbaNumber::createFraction(1, 6)}}),
     Monomial(-96, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForPolynomialOverPolynomialWith6thRoot)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term expectedNumerator(Polynomial
    {Monomial(1, {{"x", 1}}),
     Monomial(1, {{"x", AlbaNumber::createFraction(5, 6)}}),
     Monomial(3, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(9, {{"x", AlbaNumber::createFraction(1, 2)}}),
     Monomial(27, {{"x", AlbaNumber::createFraction(1, 3)}}),
     Monomial(81, {{"x", AlbaNumber::createFraction(1, 6)}}),
     Monomial(-486, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-729, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForExpressionOverExpressionWithSquareRoot)
{
    Term numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term numeratorPart1Radical(createExpressionIfPossible({numeratorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term numeratorPart2Radical(createExpressionIfPossible({numeratorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term numerator(createExpressionIfPossible({numeratorPart1Radical, Term("+"), numeratorPart2Radical}));
    Term denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term denominatorPart1Radical(createExpressionIfPossible({denominatorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term denominatorPart2Radical(createExpressionIfPossible({denominatorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term denominator(createExpressionIfPossible({denominatorPart1Radical, Term("+"), denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term expectedNumerator(1);
    string expectedDenominatorString("(((1[x^2] + -6[x] + 8)^(1/2))-((1[x^2] + -7[x] + 12)^(1/2))"
                                     "+((1[x^2] + -7[x] + 10)^(1/2))-((1[x^2] + -8[x] + 15)^(1/2)))");
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominatorString, rationalizeTermOverTerm.getDenominator().getDisplayableString());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForExpressionOverExpressionWithSquareRoot)
{
    Term numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term numeratorPart1Radical(createExpressionIfPossible({numeratorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term numeratorPart2Radical(createExpressionIfPossible({numeratorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term numerator(createExpressionIfPossible({numeratorPart1Radical, Term("+"), numeratorPart2Radical}));
    Term denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term denominatorPart1Radical(createExpressionIfPossible({denominatorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term denominatorPart2Radical(createExpressionIfPossible({denominatorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term denominator(createExpressionIfPossible({denominatorPart1Radical, Term("+"), denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    string expectedNumeratorString("(((1[x^2] + -6[x] + 8)^(1/2))-((1[x^2] + -7[x] + 10)^(1/2))"
                                   "+((1[x^2] + -7[x] + 12)^(1/2))-((1[x^2] + -8[x] + 15)^(1/2)))");
    Term expectedDenominator(1);
    EXPECT_EQ(expectedNumeratorString, rationalizeTermOverTerm.getNumerator().getDisplayableString());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForExpressionOverExpressionWithCubeRoot)
{
    Term numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term numeratorPart1Radical(createExpressionIfPossible({numeratorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term numeratorPart2Radical(createExpressionIfPossible({numeratorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term numerator(createExpressionIfPossible({numeratorPart1Radical, Term("+"), numeratorPart2Radical}));
    Term denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term denominatorPart1Radical(createExpressionIfPossible({denominatorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term denominatorPart2Radical(createExpressionIfPossible({denominatorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term denominator(createExpressionIfPossible({denominatorPart1Radical, Term("+"), denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term expectedNumerator(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})});
    string expectedDenominatorString("(((1[x^3] + -8[x^2] + 20[x] + -16)^(1/3))-((1[x^3] + -9[x^2] + 26[x] + -24)^(1/3))+((1[x^3] + -10[x^2] + 33[x] + -36)^(1/3))"
                                     "+((1[x^3] + -9[x^2] + 24[x] + -20)^(1/3))-((1[x^3] + -10[x^2] + 31[x] + -30)^(1/3))+((1[x^3] + -11[x^2] + 39[x] + -45)^(1/3)))");
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominatorString, rationalizeTermOverTerm.getDenominator().getDisplayableString());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForExpressionOverExpressionWithCubeRoot)
{
    Term numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term numeratorPart1Radical(createExpressionIfPossible({numeratorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term numeratorPart2Radical(createExpressionIfPossible({numeratorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term numerator(createExpressionIfPossible({numeratorPart1Radical, Term("+"), numeratorPart2Radical}));
    Term denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term denominatorPart1Radical(createExpressionIfPossible({denominatorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term denominatorPart2Radical(createExpressionIfPossible({denominatorPart2, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term denominator(createExpressionIfPossible({denominatorPart1Radical, Term("+"), denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    string expectedNumeratorString("(((1[x^3] + -10[x^2] + 32[x] + -32)^(1/3))-((1[x^3] + -11[x^2] + 38[x] + -40)^(1/3))+((1[x^3] + -12[x^2] + 45[x] + -50)^(1/3))"
                                   "+((1[x^3] + -11[x^2] + 40[x] + -48)^(1/3))-((1[x^3] + -12[x^2] + 47[x] + -60)^(1/3))+((1[x^3] + -13[x^2] + 55[x] + -75)^(1/3)))");
    Term expectedDenominator(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-9, {})});
    EXPECT_EQ(expectedNumeratorString, rationalizeTermOverTerm.getNumerator().getDisplayableString());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorForExample1)
{
    Term numeratorPart1(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(-2, {})});
    Term numeratorPart1Radical(createExpressionIfPossible({numeratorPart1, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term numerator(createExpressionIfPossible({numeratorPart1Radical, Term("-"), Term(1.259921049894873)}));
    Term denominator("deltaX");
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    string expectedNumeratorString("((1[deltaX] + -4)+(((0 + -1.41421i)[deltaX] + (0 + 2.82843i))^(2/3))+((1.414213562373095[deltaX] + -2.82842712474619)^(2/3)))");
    string expectedDenominatorString("(deltaX*(1.587401051968199+((1[deltaX] + -2)^(2/3))+((2[deltaX] + -4)^(1/3))))");
    EXPECT_EQ(expectedNumeratorString, rationalizeTermOverTerm.getNumerator().getDisplayableString());
    EXPECT_EQ(expectedDenominatorString, rationalizeTermOverTerm.getDenominator().getDisplayableString());
}

}

}