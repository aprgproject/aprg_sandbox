#include <Algebra/Term/TermTypes/TermWithDetails.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermWithDetailsTest, ConstructionWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(termWithDetails1);

    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

TEST(TermWithDetailsTest, EqualityOperatorWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const& termWithDetails2(termWithDetails1);
    TermWithDetails termWithDetails3(Term(20), TermAssociationType::Negative);
    TermWithDetails termWithDetails4(Term(10), TermAssociationType::Positive);

    EXPECT_TRUE(termWithDetails1==termWithDetails1);
    EXPECT_TRUE(termWithDetails1==termWithDetails2);
    EXPECT_FALSE(termWithDetails1==termWithDetails3);
    EXPECT_FALSE(termWithDetails1==termWithDetails4);
}

TEST(TermWithDetailsTest, InequalityOperatorWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const& termWithDetails2(termWithDetails1);
    TermWithDetails termWithDetails3(Term(20), TermAssociationType::Negative);
    TermWithDetails termWithDetails4(Term(10), TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1!=termWithDetails1);
    EXPECT_FALSE(termWithDetails1!=termWithDetails2);
    EXPECT_TRUE(termWithDetails1!=termWithDetails3);
    EXPECT_TRUE(termWithDetails1!=termWithDetails4);
}

TEST(TermWithDetailsTest, LessThanOperatorWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails3(Term(9), TermAssociationType::Positive);
    TermWithDetails termWithDetails4(Term(11), TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1 < termWithDetails1);
    EXPECT_TRUE(termWithDetails1 < termWithDetails2);
    EXPECT_FALSE(termWithDetails2 < termWithDetails1);
    EXPECT_FALSE(termWithDetails1 < termWithDetails3);
    EXPECT_TRUE(termWithDetails1 < termWithDetails4);
}

TEST(TermWithDetailsTest, HasPositiveAssociationWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_TRUE(termWithDetails1.hasPositiveAssociation());
    EXPECT_FALSE(termWithDetails2.hasPositiveAssociation());
}

TEST(TermWithDetailsTest, HasNegativeAssociationWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_FALSE(termWithDetails1.hasNegativeAssociation());
    EXPECT_TRUE(termWithDetails2.hasNegativeAssociation());
}

TEST(TermWithDetailsTest, GetAssociationPriorityWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_EQ(1U, termWithDetails1.getAssociationPriority());
    EXPECT_EQ(2U, termWithDetails2.getAssociationPriority());
}

TEST(TermWithDetailsTest, GetDisplayableStringWorks)
{
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_EQ("[{POS}{10}]", termWithDetails1.getDisplayableString());
    EXPECT_EQ("[{NEG}{10}]", termWithDetails2.getDisplayableString());
}

TEST(TermWithDetailsTest, ClearWorks)
{
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);

    termWithDetails.clear();

    EXPECT_EQ(nullptr, termWithDetails.baseTermSharedPointer.get());
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails.association);
}

}

}
