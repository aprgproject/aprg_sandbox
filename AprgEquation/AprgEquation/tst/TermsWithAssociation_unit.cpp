#include <TermsWithAssociation.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TEST(TermsWithAssociationTest, TermWithDetailsConstructionWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);

    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

TEST(TermsWithAssociationTest, TermWithDetailsEqualityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails4(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);

    EXPECT_TRUE(termWithDetails1==termWithDetails1);
    EXPECT_TRUE(termWithDetails1==termWithDetails2);
    EXPECT_FALSE(termWithDetails1==termWithDetails3);
    EXPECT_FALSE(termWithDetails1==termWithDetails4);
}

TEST(TermsWithAssociationTest, TermWithDetailsInequalityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails4(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1!=termWithDetails1);
    EXPECT_FALSE(termWithDetails1!=termWithDetails2);
    EXPECT_TRUE(termWithDetails1!=termWithDetails3);
    EXPECT_TRUE(termWithDetails1!=termWithDetails4);
}

TEST(TermsWithAssociationTest, LessThanOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(9)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails4(
                getBaseTermConstReferenceFromTerm(Term(11)),
                TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1 < termWithDetails1);
    EXPECT_TRUE(termWithDetails1 < termWithDetails2);
    EXPECT_FALSE(termWithDetails2 < termWithDetails1);
    EXPECT_FALSE(termWithDetails1 < termWithDetails3);
    EXPECT_TRUE(termWithDetails1 < termWithDetails4);
}

TEST(TermsWithAssociationTest, HasPositiveAssociationWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);

    EXPECT_TRUE(termWithDetails1.hasPositiveAssociation());
    EXPECT_FALSE(termWithDetails2.hasPositiveAssociation());
}

TEST(TermsWithAssociationTest, HasNegativeAssociationWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);

    EXPECT_FALSE(termWithDetails1.hasNegativeAssociation());
    EXPECT_TRUE(termWithDetails2.hasNegativeAssociation());
}

TEST(TermsWithAssociationTest, GetAssociationPriorityWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);

    EXPECT_EQ(1u, termWithDetails1.getAssociationPriority());
    EXPECT_EQ(2u, termWithDetails2.getAssociationPriority());
}

TEST(TermsWithAssociationTest, TermsWithAssociationEqualityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
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

TEST(TermsWithAssociationTest, TermsWithAssociationInequalityOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails1);
    terms3.putTermWithDetails(termWithDetails2);
    terms4.putTermWithDetails(termWithDetails1);
    terms4.putTermWithDetails(termWithDetails1);

    EXPECT_FALSE(terms1!=terms1);
    EXPECT_FALSE(terms1!=terms2);
    EXPECT_TRUE(terms1!=terms3);
    EXPECT_TRUE(terms1!=terms4);
}

TEST(TermsWithAssociationTest, TermsWithAssociationLessThanOperatorWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(9)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(11)),
                TermAssociationType::Positive);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
    TermsWithAssociation terms5;
    terms1.putTermWithDetails(termWithDetails1);
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails1);
    terms3.putTermWithDetails(termWithDetails1);
    terms3.putTermWithDetails(termWithDetails1);
    terms3.putTermWithDetails(termWithDetails1);
    terms4.putTermWithDetails(termWithDetails2);
    terms5.putTermWithDetails(termWithDetails3);

    EXPECT_FALSE(terms1<terms1);
    EXPECT_FALSE(terms1<terms2);
    EXPECT_TRUE(terms1<terms3);
    EXPECT_FALSE(terms2<terms4);
    EXPECT_TRUE(terms2<terms5);
}

TEST(TermsWithAssociationTest, IsEmptyWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_TRUE(terms1.isEmpty());
    EXPECT_FALSE(terms2.isEmpty());
    EXPECT_FALSE(terms3.isEmpty());
}

TEST(TermsWithAssociationTest, GetSizeWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_EQ(0u, terms1.getSize());
    EXPECT_EQ(1u, terms2.getSize());
    EXPECT_EQ(2u, terms3.getSize());
}

TEST(TermsWithAssociationTest, GetFirstTermConstReferenceWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails2);

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(terms1.getFirstTermConstReference()));
    EXPECT_EQ(Term(20), getTermConstReferenceFromBaseTerm(terms2.getFirstTermConstReference()));
}

TEST(TermsWithAssociationTest, GetTermsWithDetailsWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermsWithAssociation terms;
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_TRUE(termWithDetails1==termsToVerify.at(0));
    EXPECT_TRUE(termWithDetails2==termsToVerify.at(1));
}

TEST(TermsWithAssociationTest, ClearWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(30)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermsWithAssociation terms;
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);
    terms.putTermWithDetails(termWithDetails3);

    terms.clear();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    EXPECT_TRUE(termsToVerify.empty());
}

TEST(TermsWithAssociationTest, SortWorks)
{
    TermWithDetails termWithDetails1(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermWithDetails termWithDetails2(
                getBaseTermConstReferenceFromTerm(Term(20)),
                TermAssociationType::Positive);
    TermWithDetails termWithDetails3(
                getBaseTermConstReferenceFromTerm(Term(30)),
                TermAssociationType::Positive);
    TermsWithAssociation terms;
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);
    terms.putTermWithDetails(termWithDetails3);

    terms.sort();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(3u, termsToVerify.size());
    EXPECT_EQ(Term(20), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(1).association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(2).association);
}

TEST(TermsWithAssociationTest, PutTermWithDetailsWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Negative);
    TermsWithAssociation terms;

    terms.putTermWithDetails(termWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, PutTermWithPositiveAssociationWorks)
{
    TermsWithAssociation terms;

    terms.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(Term(10)));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, PutTermWithNegativeAssociationWorks)
{
    TermsWithAssociation terms;

    terms.putTermWithNegativeAssociation(getBaseTermConstReferenceFromTerm(Term(10)));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, ReverseTheAssociationOfTheTermsWorks)
{
    TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);
    TermsWithAssociation terms;
    terms.putTermWithDetails(termWithDetails);
    terms.putTermWithDetails(termWithDetails);

    terms.reverseTheAssociationOfTheTerms();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(1).association);
}

}

}

