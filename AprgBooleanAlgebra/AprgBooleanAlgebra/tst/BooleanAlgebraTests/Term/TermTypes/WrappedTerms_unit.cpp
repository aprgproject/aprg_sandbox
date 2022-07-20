#include <BooleanAlgebra/Term/TermTypes/WrappedTerm.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(WrappedTermTest, ConstructionWorks)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm wrappedTerm2(wrappedTerm1);

    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(wrappedTerm1.baseTermSharedPointer));
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(wrappedTerm2.baseTermSharedPointer));
}

TEST(WrappedTermTest, EqualityOperatorWorks)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm const& wrappedTerm2(wrappedTerm1);
    WrappedTerm wrappedTerm3(Term(false));
    WrappedTerm wrappedTerm4(Term(true));

    EXPECT_TRUE(wrappedTerm1==wrappedTerm1);
    EXPECT_TRUE(wrappedTerm1==wrappedTerm2);
    EXPECT_FALSE(wrappedTerm1==wrappedTerm3);
    EXPECT_TRUE(wrappedTerm1==wrappedTerm4);
}

TEST(WrappedTermTest, InequalityOperatorWorks)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm const& wrappedTerm2(wrappedTerm1);
    WrappedTerm wrappedTerm3(Term(false));
    WrappedTerm wrappedTerm4(Term(true));

    EXPECT_FALSE(wrappedTerm1!=wrappedTerm1);
    EXPECT_FALSE(wrappedTerm1!=wrappedTerm2);
    EXPECT_TRUE(wrappedTerm1!=wrappedTerm3);
    EXPECT_FALSE(wrappedTerm1!=wrappedTerm4);
}

TEST(WrappedTermTest, LessThanOperatorWorks)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm wrappedTerm2(Term(true));
    WrappedTerm wrappedTerm3(Term(false));

    EXPECT_FALSE(wrappedTerm1 < wrappedTerm1);
    EXPECT_FALSE(wrappedTerm1 < wrappedTerm2);
    EXPECT_FALSE(wrappedTerm2 < wrappedTerm1);
    EXPECT_FALSE(wrappedTerm1 < wrappedTerm3);
    EXPECT_TRUE(wrappedTerm3 < wrappedTerm1);
}

TEST(WrappedTermTest, GetDisplayableStringWorks)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm wrappedTerm2(Term(false));

    EXPECT_EQ("{[true]}", wrappedTerm1.getDisplayableString());
    EXPECT_EQ("{[false]}", wrappedTerm2.getDisplayableString());
}

TEST(WrappedTermTest, ClearWorks)
{
    WrappedTerm wrappedTerm(Term(10));

    wrappedTerm.clear();

    EXPECT_EQ(nullptr, wrappedTerm.baseTermSharedPointer.get());
}

}

}
