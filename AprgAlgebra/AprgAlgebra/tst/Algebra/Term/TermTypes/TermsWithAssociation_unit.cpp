#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermsWithAssociationTest, TermsWithAssociationEqualityOperatorWorks)
{
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
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
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
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
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermsWithAssociation terms4;
    TermsWithAssociation terms5;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(9), TermAssociationType::Positive);
    TermWithDetails termWithDetails3(Term(11), TermAssociationType::Positive);
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
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_TRUE(terms1.isEmpty());
    EXPECT_FALSE(terms2.isEmpty());
    EXPECT_FALSE(terms3.isEmpty());
}

TEST(TermsWithAssociationTest, GetSizeWorks)
{
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermsWithAssociation terms3;
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);
    terms2.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);
    terms3.putTermWithDetails(termWithDetails);

    EXPECT_EQ(0U, terms1.getSize());
    EXPECT_EQ(1U, terms2.getSize());
    EXPECT_EQ(2U, terms3.getSize());
}

TEST(TermsWithAssociationTest, GetFirstTermConstReferenceWorks)
{
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails2);

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(terms1.getFirstTermConstReference()));
    EXPECT_EQ(Term(20), getTermConstReferenceFromBaseTerm(terms2.getFirstTermConstReference()));
}

TEST(TermsWithAssociationTest, GetFirstAssociationTypeWorks)
{
    TermsWithAssociation terms1;
    TermsWithAssociation terms2;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    terms1.putTermWithDetails(termWithDetails1);
    terms2.putTermWithDetails(termWithDetails2);

    EXPECT_EQ(TermAssociationType::Negative, terms1.getFirstAssociationType());
    EXPECT_EQ(TermAssociationType::Positive, terms2.getFirstAssociationType());
}


TEST(TermsWithAssociationTest, GetTermsWithDetailsWorks)
{
    TermsWithAssociation terms;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_TRUE(termWithDetails1==termsToVerify.at(0));
    EXPECT_TRUE(termWithDetails2==termsToVerify.at(1));
}

TEST(TermsWithAssociationTest, ClearWorks)
{
    TermsWithAssociation terms;
    TermWithDetails termWithDetails1(Term(30), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails termWithDetails3(Term(10), TermAssociationType::Positive);
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);
    terms.putTermWithDetails(termWithDetails3);

    terms.clear();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    EXPECT_TRUE(termsToVerify.empty());
}

TEST(TermsWithAssociationTest, SortWorks)
{
    TermsWithAssociation terms;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails termWithDetails3(Term(30), TermAssociationType::Positive);
    terms.putTermWithDetails(termWithDetails1);
    terms.putTermWithDetails(termWithDetails2);
    terms.putTermWithDetails(termWithDetails3);

    terms.sort();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(20), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(1).association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(2).association);
}

TEST(TermsWithAssociationTest, PutTermWithDetailsWorks)
{
    TermsWithAssociation terms;
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);

    terms.putTermWithDetails(termWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, PutTermsWithDetailsWorks)
{
    TermsWithAssociation terms;
    TermsWithDetails termsWithDetails
    {TermWithDetails(Term(100), TermAssociationType::Positive),
                TermWithDetails(Term(2), TermAssociationType::Negative)};

    terms.putTermsWithDetails(termsWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term(100), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    EXPECT_EQ(Term(2), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(1).association);
}

TEST(TermsWithAssociationTest, PutTermWithAssociationWorks)
{
    TermsWithAssociation terms;

    terms.putTermWithAssociation(Term(10), TermAssociationType::Negative);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, PutTermWithPositiveAssociationWorks)
{
    TermsWithAssociation terms;

    terms.putTermWithPositiveAssociation(Term(10));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, PutTermWithNegativeAssociationWorks)
{
    TermsWithAssociation terms;

    terms.putTermWithNegativeAssociation(Term(10));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
}

TEST(TermsWithAssociationTest, ReverseTheAssociationOfTheTermsWorks)
{
    TermsWithAssociation terms;
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Positive);
    terms.putTermWithDetails(termWithDetails);
    terms.putTermWithDetails(termWithDetails);

    terms.reverseTheAssociationOfTheTerms();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(1).association);
}

}

}
