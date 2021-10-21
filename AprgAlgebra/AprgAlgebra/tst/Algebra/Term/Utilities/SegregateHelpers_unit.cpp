#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(MonomialHelpersTest, SegregateMonomialsWithAndWithoutVariable)
{
    Monomials monomialsToSegregate(
    {Monomial(1, {{"x", 2}, {"y", 3}}),
     Monomial(4, {{"y", 5}, {"z", 6}}),
     Monomial(7, {{"x", 8}, {"z", 9}})});

    Monomials monomialWithVariable;
    Monomials monomialWithoutVariable;
    segregateMonomialsWithAndWithoutVariable(monomialsToSegregate, "x", monomialWithVariable, monomialWithoutVariable);

    ASSERT_EQ(2U, monomialWithVariable.size());
    EXPECT_EQ(Monomial(1, {{"x", 2}, {"y", 3}}), monomialWithVariable.at(0));
    EXPECT_EQ(Monomial(7, {{"x", 8}, {"z", 9}}), monomialWithVariable.at(1));
    ASSERT_EQ(1U, monomialWithoutVariable.size());
    EXPECT_EQ(Monomial(4, {{"y", 5}, {"z", 6}}), monomialWithoutVariable.at(0));
}

TEST(SegregateHelpersTest, SegregateMonomialsAndNonMonomialsWorksForTerms)
{
    Terms monomialTerms;    Terms nonMonomialTerms;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));

    segregateMonomialsAndNonMonomials({Term(234), termExpression}, monomialTerms, nonMonomialTerms);

    ASSERT_EQ(1U, monomialTerms.size());
    EXPECT_EQ(Term(234), monomialTerms.at(0));
    ASSERT_EQ(1U, nonMonomialTerms.size());
    EXPECT_EQ(termExpression, nonMonomialTerms.at(0));
}

TEST(SegregateHelpersTest, SegregateMonomialsAndNonMonomialsWorksForTermsWithDetails)
{
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails monomialTerms;
    TermsWithDetails nonMonomialTerms;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(termExpression);

    segregateMonomialsAndNonMonomials(termsWithAssociation.getTermsWithDetails(), monomialTerms, nonMonomialTerms);

    ASSERT_EQ(1U, monomialTerms.size());
    TermWithDetails const& termWithDetails1(monomialTerms.at(0));
    EXPECT_EQ(Term(753), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    ASSERT_EQ(1U, nonMonomialTerms.size());
    TermWithDetails const& termWithDetails2(nonMonomialTerms.at(0));
    EXPECT_EQ(termExpression, getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails2.association);
}

TEST(SegregateHelpersTest, SegregatePolynomialAndNonPolynomialsWorks)
{
    Terms polynomialTerms;
    Terms nonPolynomialTerms;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));

    segregatePolynomialAndNonPolynomials({Term(234), termExpression}, polynomialTerms, nonPolynomialTerms);

    ASSERT_EQ(1U, polynomialTerms.size());
    EXPECT_EQ(Term(234), polynomialTerms.at(0));
    ASSERT_EQ(1U, nonPolynomialTerms.size());
    EXPECT_EQ(termExpression, nonPolynomialTerms.at(0));
}

TEST(SegregateHelpersTest, SegregateNonExpressionsAndExpressionsWorks)
{
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(termExpression);

    segregateNonExpressionsAndExpressions(termsWithAssociation.getTermsWithDetails(), termsWithNonExpressions, termsWithExpressions);

    ASSERT_EQ(1U, termsWithNonExpressions.size());
    TermWithDetails const& termWithDetails1(termsWithNonExpressions.at(0));
    EXPECT_EQ(Term(753), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    ASSERT_EQ(1U, termsWithExpressions.size());
    TermWithDetails const& termWithDetails2(termsWithExpressions.at(0));
    EXPECT_EQ(termExpression, getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails2.association);
}

TEST(SegregateHelpersTest, SegregateTermsWithPositiveAndNegativeAssociationsWorks)
{
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsInPositive;
    TermsWithDetails termsInNegative;
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(Term(159));

    segregateTermsWithPositiveAndNegativeAssociations(termsWithAssociation.getTermsWithDetails(), termsInPositive, termsInNegative);

    ASSERT_EQ(1U, termsInPositive.size());
    TermWithDetails const& termWithDetails1(termsInPositive.at(0));
    EXPECT_EQ(Term(159), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails1.association);
    ASSERT_EQ(1U, termsInNegative.size());
    TermWithDetails const& termWithDetails2(termsInNegative.at(0));
    EXPECT_EQ(Term(753), getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

}

}
