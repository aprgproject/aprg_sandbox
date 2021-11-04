#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

TEST(TermRaiseToTermsTest, ConstructionWithNoArgumentWorks)
{
    TermRaiseToTerms termRaiseToTerms;

    EXPECT_TRUE(termRaiseToTerms.getBase().isEmpty());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
}

TEST(TermRaiseToTermsTest, ConstructionWithTermsWithDetailsWorks)
{
    TermsWithDetails termsInRaiseToPowerExpression;
    termsInRaiseToPowerExpression.emplace_back(Term("x"), TermAssociationType::Positive);
    termsInRaiseToPowerExpression.emplace_back(Term("y"), TermAssociationType::Positive);
    TermRaiseToTerms termRaiseToTerms(termsInRaiseToPowerExpression);

    TermsWithDetails expectedExponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentsWithDetailsWorks)
{
    Term base("x");
    TermsWithDetails exponentsWithDetails{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    TermRaiseToTerms termRaiseToTerms(base, exponentsWithDetails);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    EXPECT_EQ(exponentsWithDetails, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentsWorks)
{
    Term base("x");
    Terms exponents{Term("y")};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentWorks)
{
    Term base("x");
    Term exponent("y");
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(exponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, DoesEvenExponentCancellationHappenWorks)
{
    TermRaiseToTerms termRaiseToTerms1(Term("base"), {Term(3), Term(5)});
    TermRaiseToTerms termRaiseToTerms2(Term("base"), {Term(3), Term(AlbaNumber::createFraction(1, 3))});
    TermRaiseToTerms termRaiseToTerms3(Term("base"), {Term(AlbaNumber::createFraction(4, 3)), Term(AlbaNumber::createFraction(1, 3))});
    TermRaiseToTerms termRaiseToTerms4(Term("base"), {Term(AlbaNumber::createFraction(1, 3)), Term(AlbaNumber::createFraction(1, 6))});
    TermRaiseToTerms termRaiseToTerms5(Term("base"), {Term(AlbaNumber::createFraction(4, 3)), Term(AlbaNumber::createFraction(1, 6))});

    EXPECT_FALSE(termRaiseToTerms1.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms2.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms3.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms4.doesEvenExponentCancellationHappen());
    EXPECT_TRUE(termRaiseToTerms5.doesEvenExponentCancellationHappen());
}

TEST(TermRaiseToTermsTest, GetCombinedTermWorks)
{
    TermRaiseToTerms termRaiseToTerms(Term("base"), {Term("exponent1"), Term("exponent2")});

    Term expectedTerm(createExpressionIfPossible(
    {Term("base"), Term("^"), Term(Monomial(1, {{"exponent1", 1}, {"exponent2", 1}}))}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, GetCombinedExponentsWorks)
{
    TermRaiseToTerms termRaiseToTerms(Term("base"), {Term("exponent1"), Term("exponent2")});

    Term expectedTerm(Monomial(1, {{"exponent1", 1}, {"exponent2", 1}}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedExponents());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsZero)
{
    Term base(Constant(0));
    TermRaiseToTerms termRaiseToTerms(base, {Term("a"), Term("b")});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Constant(0)), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(Constant(0)), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsOne)
{
    Term base(1);
    TermRaiseToTerms termRaiseToTerms(base, {Term("a"), Term("b")});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(1), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenThereAreNoExponents)
{
    Term base("base");
    TermRaiseToTerms termRaiseToTerms(base, Terms{});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("base"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentIsZero)
{
    Term base("base");
    TermRaiseToTerms termRaiseToTerms(base, {Term(Constant(0)), Term("anotherExponent")});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(1), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentIsOne)
{
    Term base("base");
    TermRaiseToTerms termRaiseToTerms(base, {Term(1), Term(1)});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("base"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsMonomialAndExponentIsNumber)
{
    Term base(Monomial(1, {{"x", 2}}));
    TermRaiseToTerms termRaiseToTerms(base, {Term(AlbaNumber::createFraction(1, 2))});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("x"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsPolynomialAndExponentIsNumber)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, Term(2));

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnMultiplicationExpression)
{
    Term base("base");
    Term absoluteValueOfA(Functions::abs(Term("a")));
    Term absoluteValueOfB(Functions::abs(Term("b")));
    Terms exponents{absoluteValueOfA, absoluteValueOfB};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    Term expectedExponent(createExpressionIfPossible({absoluteValueOfA, Term("*"), absoluteValueOfB}));
    TermsWithDetails expectedExponents{TermWithDetails(expectedExponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({base, Term("^"), expectedExponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnAdditionExpression)
{
    Term base("base");
    Term exponent(createExpressionIfPossible({Term(Functions::abs(Term("a"))), Term("+"), Term(Functions::abs(Term("b")))}));
    TermRaiseToTerms termRaiseToTerms(base, {exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(exponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({base, Term("^"), exponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorks)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Terms exponents{Term(4), Term(AlbaNumber::createFraction(1, 2))};
    TermRaiseToTerms termRaiseToTerms(base, exponents);
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Functions::abs(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}))), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorks)
{
    Term base(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, Term("x"));
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(Monomial(2, {{"x", 1}})), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithSimplifyingToFactors)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, Term(5));
    termRaiseToTerms.setAsShouldSimplifyToFactors(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(5), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), Term("^"), Term(5)}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithReducingExponentialToLogarithmic)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term base(getEAsTerm());
    Term exponent(ln(polynomialTerm));
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    Term expectedCombinedTerm(polynomialTerm);
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithReducingExponentialToLogarithmicWithMultipleExponents)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term base(getEAsTerm());
    Term exponent(ln(polynomialTerm));
    TermRaiseToTerms termRaiseToTerms(base, {Term(2), exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), Term("^"), Term(2)}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithNegativeNumberRaiseToInfinity)
{
    Term base(-1);
    Term exponent(AlbaNumber(AlbaNumber::Value::PositiveInfinity));
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    termRaiseToTerms.simplify();

    EXPECT_TRUE(isNotANumber(termRaiseToTerms.getBase()));
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_TRUE(isNotANumber(termRaiseToTerms.getCombinedTerm()));
}

}

}
