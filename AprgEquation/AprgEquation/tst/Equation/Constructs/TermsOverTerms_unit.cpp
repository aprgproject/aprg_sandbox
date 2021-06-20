#include <Equation/Constructs/TermsOverTerms.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{
namespace equation
{

TEST(TermsOverTermsTest, ConstructionWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermsOverTerms termsOverTerms1(Terms{}, Terms{});
    TermsOverTerms termsOverTerms2(Terms{Term(5)}, Terms{Term("x")});
    TermsOverTerms termsOverTerms3({termWithDetails}, {termWithDetails});

    EXPECT_TRUE(termsOverTerms1.getNumerators().empty());
    EXPECT_TRUE(termsOverTerms1.getDenominators().empty());
    Terms numeratorsToVerify1(termsOverTerms2.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify1.size());
    EXPECT_EQ(Term(5), numeratorsToVerify1.at(0));
    Terms denominatorsToVerify1(termsOverTerms2.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify1.size());
    EXPECT_EQ(Term("x"), denominatorsToVerify1.at(0));
    Terms numeratorsToVerify2(termsOverTerms3.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify2.size());
    EXPECT_EQ(Term(10), numeratorsToVerify2.at(0));
    Terms denominatorsToVerify3(termsOverTerms3.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify3.size());
    EXPECT_EQ(Term(10), denominatorsToVerify3.at(0));
}

TEST(TermsOverTermsTest, GetNumeratorsAndGetDenominatorsWorks)
{
    TermsOverTerms termsOverTerms(Terms{Term(5)}, Terms{Term("x")});

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(5), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term("x"), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorks)
{
    TermsOverTerms termsOverTerms(Terms{Term(5)}, Terms{Term("x")});

    TermsWithDetails termsWithDetails(termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
    ASSERT_EQ(2u, termsWithDetails.size());
    EXPECT_EQ(Term(5), getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetails.at(0).association);
    EXPECT_EQ(Term("x"), getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetails.at(1).association);
}

TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorksWhenBothNumeratorsAndDenominatorsAreEmpty)
{
    TermsOverTerms termsOverTerms(Terms{}, Terms{});

    TermsWithDetails termsWithDetails(termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
    EXPECT_TRUE(termsWithDetails.empty());
}

TEST(TermsOverTermsTest, SimplifyRemovesOnSamePolynomialInNumeratorAndDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    TermsOverTerms termsOverTerms(Terms{Term(polynomial2), Term(polynomial1)}, Terms{Term(polynomial1), Term(polynomial3)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomial2), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomial3), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyRemovesOnSameFactorsInNumeratorAndDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 2}}), Monomial(-1, {})};
    TermsOverTerms termsOverTerms(Terms{Term(polynomial1)}, Terms{Term(polynomial2)});

    termsOverTerms.simplify();

    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect1), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyRemovesOnSameFactorsFirstBeforeCombining)
{
    Polynomial polynomial1{Monomial(12, {{"x", 1}}), Monomial(-15, {})};
    Polynomial polynomial2{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomial3{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomial4{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    Polynomial polynomial5{Monomial(8, {{"x", 1}}), Monomial(-10, {})};
    Terms numerators{Term(polynomial1), Term(polynomial2), Term(polynomial3), Term(polynomial4)};
    Terms denominators{Term(polynomial2), Term(polynomial5)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplify();

    Polynomial polynomialToExpect{Monomial(264, {{"x", 2}}), Monomial(-15, {{"x", 1}}), Monomial(-351, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term(2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAsCombiningPolynomialsOnNumeratorAndDenominatorSeparately)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{Term(polynomial1), Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial2)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplify();

    Polynomial polynomialToExpect1{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(4, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect1), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyToFactorsWorksAsDoesNotCombinePolynomials)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{Term(polynomial1), Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial2)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplifyToFactors();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(2u, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomial1), numeratorsToVerify.at(0));
    EXPECT_EQ(Term(polynomial1), numeratorsToVerify.at(1));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(2u, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomial2), denominatorsToVerify.at(0));
    EXPECT_EQ(Term(polynomial2), denominatorsToVerify.at(1));
}

TEST(TermsOverTermsTest, SimplifyRemovesOnSameExpressionInNumeratorAndDenominator)
{
    Expression expression1(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expression3(createExpressionIfPossible({Term("z"), Term("^"), Term("z")}));
    TermsOverTerms termsOverTerms(Terms{Term(expression2), Term(expression1)}, Terms{Term(expression1), Term(expression3)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1u, numeratorsToVerify.size());
    EXPECT_EQ(Term(expression2), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1u, denominatorsToVerify.size());
    EXPECT_EQ(Term(expression3), denominatorsToVerify.at(0));
}

/*
TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorksOnTermsEmptyAndOne)
{
    TermsOverTerms item(Terms{Term(), Term(1)}, Terms{Term(), Term(1)});

    TermsWithDetails termsWithDetails(item.getNumeratorAndDenominatorAsTermWithDetails());
    EXPECT_TRUE(termsWithDetails.empty());
}
*/
}

}