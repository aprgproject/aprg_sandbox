#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace booleanAlgebra
{

TEST(BaseTermHelpersTest, CreateAUniquePointerFromTermWorks)
{
    BaseTermUniquePointer uniquePointerToVerify(createAUniquePointerFromTerm(Term(9652)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointerToVerify));
    EXPECT_EQ(Term(9652), termToVerify);
}

TEST(BaseTermHelpersTest, CreateASharedPointerFromTermWorks)
{
    BaseTermSharedPointer sharedPointerToVerify(createASharedPointerFromTerm(Term(6415)));

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointerToVerify));
    EXPECT_EQ(Term(6415), termToVerify);    EXPECT_EQ(1, sharedPointerToVerify.use_count());
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromBaseTermWorks){
    Term originalTerm(7896);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(dynamic_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(createAUniquePointerFromTerm(Term(9541)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));

    EXPECT_EQ(Term(9541), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(createASharedPointerFromTerm(Term(9541)));

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointer));

    EXPECT_EQ(Term(9541), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(BaseTermHelpersTest, GetTermReferenceFromBaseTermWorks){
    Term originalTerm(7896);

    Term & termToVerify(getTermReferenceFromBaseTerm(dynamic_cast<BaseTerm &>(originalTerm)));    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(createAUniquePointerFromTerm(Term(9652)));

    Term & termToChange(getTermReferenceFromUniquePointer(uniquePointer));
    termToChange.getConstantReference().setValue(763);

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));
    EXPECT_EQ(Term(763), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(createASharedPointerFromTerm(Term(9652)));

    Term & termToChange(getTermReferenceFromSharedPointer(sharedPointer));
    termToChange.getConstantReference().setValue(763);

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointer));
    EXPECT_EQ(Term(763), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromTermWorks){
    Term originalTerm(7896);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));
    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(new Term(6415));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(createASharedPointerFromTerm(Term(6415)));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromSharedPointer(sharedPointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromTermWorks){
    Term originalTerm(7896);

    BaseTerm & baseTerm(getBaseTermReferenceFromTerm(originalTerm));    Term & termToVerify(dynamic_cast<Term &>(baseTerm));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(new Term(6415));

    BaseTerm & baseTerm(getBaseTermReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(createASharedPointerFromTerm(Term(6415)));

    BaseTerm & baseTerm(getBaseTermReferenceFromSharedPointer(sharedPointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

}
}