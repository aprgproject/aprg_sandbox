#include <TermsWithPriorityAndAssociation.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using AssociationType=alba::equation::TermsWithPriorityAndAssociation::AssociationType;
using TermWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TEST(TermsWithPriorityAndAssociationTest, TermWithDetailsConstructionWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);

    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termWithDetails1.association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termWithDetails2.association);
}

TEST(TermsWithPriorityAndAssociationTest, TermWithDetailsEqualityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(20)),
                AssociationType::Negative);
    TermWithDetails termWithDetails4(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Positive);

    EXPECT_TRUE(termWithDetails1==termWithDetails1);
    EXPECT_TRUE(termWithDetails1==termWithDetails2);
    EXPECT_FALSE(termWithDetails1==termWithDetails3);
    EXPECT_FALSE(termWithDetails1==termWithDetails4);
}

TEST(TermsWithPriorityAndAssociationTest, HasPositiveAssociationWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);

    EXPECT_TRUE(termWithDetails1.hasPositiveAssociation());
    EXPECT_FALSE(termWithDetails2.hasPositiveAssociation());
}

TEST(TermsWithPriorityAndAssociationTest, HasNegativeAssociationWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);

    EXPECT_FALSE(termWithDetails1.hasNegativeAssociation());
    EXPECT_TRUE(termWithDetails2.hasNegativeAssociation());
}

TEST(TermsWithPriorityAndAssociationTest, GetAssociationPriorityWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);

    EXPECT_EQ(1u, termWithDetails1.getAssociationPriority());
    EXPECT_EQ(0u, termWithDetails2.getAssociationPriority());
}

TEST(TermsWithPriorityAndAssociationTest, TermsWithPriorityAndAssociationEqualityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                AssociationType::Positive);
    TermsWithPriorityAndAssociation terms1;
    TermsWithPriorityAndAssociation terms2;
    TermsWithPriorityAndAssociation terms3;
    TermsWithPriorityAndAssociation terms4;
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails1);
    terms3.putTermWithDetails(termWithDetails2);
    terms4.putTermWithDetails(termWithDetails1);
    terms4.putTermWithDetails(termWithDetails1);

    EXPECT_TRUE(terms1==terms1);
    EXPECT_TRUE(terms1==terms2);
    EXPECT_FALSE(terms1==terms3);
    EXPECT_FALSE(terms1==terms4);
}

TEST(TermsWithPriorityAndAssociationTest, IsEmptyWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermsWithPriorityAndAssociation terms1;
    TermsWithPriorityAndAssociation terms2;
    TermsWithPriorityAndAssociation terms3;
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_TRUE(terms1.isEmpty());
    EXPECT_FALSE(terms2.isEmpty());
    EXPECT_FALSE(terms3.isEmpty());
}

TEST(TermsWithPriorityAndAssociationTest, GetSizeWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermsWithPriorityAndAssociation terms1;
    TermsWithPriorityAndAssociation terms2;    TermsWithPriorityAndAssociation terms3;
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_EQ(0u, terms1.getSize());
    EXPECT_EQ(1u, terms2.getSize());
    EXPECT_EQ(2u, terms3.getSize());
}

TEST(TermsWithPriorityAndAssociationTest, GetFirstTermConstReferenceWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                AssociationType::Positive);
    TermsWithPriorityAndAssociation terms1;
    TermsWithPriorityAndAssociation terms2;
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails2);

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(terms1.getFirstTermConstReference()));
    EXPECT_EQ(Term(20), getTermConstReferenceFromBaseTerm(terms2.getFirstTermConstReference()));
}

TEST(TermsWithPriorityAndAssociationTest, GetTermsWithDetailsWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                AssociationType::Positive);
    TermsWithPriorityAndAssociation terms;
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_TRUE(termWithDetails1==termsToVerify.at(0));
    EXPECT_TRUE(termWithDetails2==termsToVerify.at(1));
}

TEST(TermsWithPriorityAndAssociationTest, ClearWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                AssociationType::Positive);
    TermsWithPriorityAndAssociation terms;
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);

    terms.clear();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    EXPECT_TRUE(termsToVerify.empty());
}

TEST(TermsWithPriorityAndAssociationTest, PutTermWithDetailsWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Negative);
    TermsWithPriorityAndAssociation terms;

    terms.putTermWithDetails(termWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithPriorityAndAssociationTest, PutTermWithPositiveAssociationWorks)
{
    TermsWithPriorityAndAssociation terms;

    terms.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(Term(10)));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Positive, termsToVerify.at(0).association);
}

TEST(TermsWithPriorityAndAssociationTest, PutTermWithNegativeAssociationWorks)
{
    TermsWithPriorityAndAssociation terms;

    terms.putTermWithNegativeAssociation(getBaseTermConstReferenceFromTerm(Term(10)));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithPriorityAndAssociationTest, ReverseTheAssociationOfTheTermsWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                AssociationType::Positive);
    TermsWithPriorityAndAssociation terms;
    terms.putTermWithDetails(termWithDetails);
    terms.putTermWithDetails(termWithDetails);

    terms.reverseTheAssociationOfTheTerms();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termsToVerify.at(0).association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(AssociationType::Negative, termsToVerify.at(1).association);
}

}

}

