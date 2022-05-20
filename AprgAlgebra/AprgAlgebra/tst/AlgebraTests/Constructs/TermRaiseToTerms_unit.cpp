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

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentsWorks)
{
    Term base("x");
    Terms exponents{"y"};
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
    TermRaiseToTerms termRaiseToTerms1("base", {3, 5});
    TermRaiseToTerms termRaiseToTerms2("base", {3, AlbaNumber::createFraction(1, 3)});
    TermRaiseToTerms termRaiseToTerms3("base", {AlbaNumber::createFraction(4, 3), AlbaNumber::createFraction(1, 3)});
    TermRaiseToTerms termRaiseToTerms4("base", {AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(1, 6)});
    TermRaiseToTerms termRaiseToTerms5("base", {AlbaNumber::createFraction(4, 3), AlbaNumber::createFraction(1, 6)});

    EXPECT_FALSE(termRaiseToTerms1.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms2.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms3.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms4.doesEvenExponentCancellationHappen());
    EXPECT_TRUE(termRaiseToTerms5.doesEvenExponentCancellationHappen());
}

TEST(TermRaiseToTermsTest, GetCombinedTermWorks)
{
    TermRaiseToTerms termRaiseToTerms("base", {"exponent1", "exponent2"});

    Term expectedTerm(createExpressionIfPossible(
    {"base", "^", Monomial(1, {{"exponent1", 1}, {"exponent2", 1}})}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, GetCombinedExponentsWorks)
{
    TermRaiseToTerms termRaiseToTerms("base", {"exponent1", "exponent2"});

    Term expectedTerm(Monomial(1, {{"exponent1", 1}, {"exponent2", 1}}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedExponents());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsZero)
{
    Term base(0);
    TermRaiseToTerms termRaiseToTerms(base, {"a", "b"});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(0), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(0), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsOne)
{
    Term base(1);
    TermRaiseToTerms termRaiseToTerms(base, {"a", "b"});

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
    TermRaiseToTerms termRaiseToTerms(base, {0, "anotherExponent"});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(1), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentIsOne)
{
    Term base("base");
    TermRaiseToTerms termRaiseToTerms(base, {1, 1});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("base"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsMonomialAndExponentIsNumber)
{
    Term base(Monomial(1, {{"x", 2}}));
    TermRaiseToTerms termRaiseToTerms(base, AlbaNumber::createFraction(1, 2));

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("x"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsPolynomialAndExponentIsNumber)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, 2);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnMultiplicationExpression)
{
    Term base("base");
    Term absoluteValueOfA(abs("a"));
    Term absoluteValueOfB(abs("b"));
    Terms exponents{absoluteValueOfA, absoluteValueOfB};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    Term expectedExponent(createExpressionIfPossible({absoluteValueOfA, "*", absoluteValueOfB}));
    TermsWithDetails expectedExponents{TermWithDetails(expectedExponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({base, "^", expectedExponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnAdditionExpression)
{
    Term base("base");
    Term exponent(createExpressionIfPossible({abs("a"), "+", abs("b")}));
    TermRaiseToTerms termRaiseToTerms(base, {exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(exponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({base, "^", exponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorks)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Terms exponents{4, AlbaNumber::createFraction(1, 2)};
    TermRaiseToTerms termRaiseToTerms(base, exponents);
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})})), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorks)
{
    Term base(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, "x");
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(Monomial(2, {{"x", 1}})), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithSimplifyingToFactors)
{
    Term base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, 5);
    termRaiseToTerms.setAsShouldSimplifyToFactors(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(5), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 5}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithReducingExponentialToLogarithmic)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term base(getEAsATerm());
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
    Term base(getEAsATerm());
    Term exponent(ln(polynomialTerm));
    TermRaiseToTerms termRaiseToTerms(base, {2, exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term expectedCombinedTerm(createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 2}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithNegativeNumberRaiseToInfinity)
{
    Term base(-1);
    Term exponent(AlbaNumber(AlbaNumber::Value::PositiveInfinity));
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    termRaiseToTerms.simplify();

    EXPECT_TRUE(isNan(termRaiseToTerms.getBase()));
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_TRUE(isNan(termRaiseToTerms.getCombinedTerm()));
}

}

}
