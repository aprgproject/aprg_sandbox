#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace booleanAlgebra
{

TEST(BaseTermHelpersTest, DuplicateUniquePointerWorks)
{
    Term originalTerm(7896);

    BaseTermUniquePointer uniquePointer(duplicateUniquePointer(originalTerm.createBasePointerByCopy()));

    EXPECT_EQ(Term(7896), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, CreateAUniquePointerFromTermWorks)
{
    BaseTermUniquePointer uniquePointerToVerify(Term(9652).createBasePointerByMove());

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointerToVerify));
    EXPECT_EQ(Term(9652), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromBaseTermWorks)
{
    Term originalTerm(7896);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(dynamic_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(Term(9541).createBasePointerByMove());

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));

    EXPECT_EQ(Term(9541), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromBaseTermWorks)
{
    Term originalTerm(7896);

    Term & termToVerify(getTermReferenceFromBaseTerm(dynamic_cast<BaseTerm &>(originalTerm)));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(Term(9652).createBasePointerByMove());

    Term & termToChange(getTermReferenceFromUniquePointer(uniquePointer));
    termToChange.getConstantReference().setValue(763);

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));
    EXPECT_EQ(Term(763), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromTermWorks)
{
    Term originalTerm(7896);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(Term(6415).createBasePointerByMove());

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromTermWorks)
{
    Term originalTerm(7896);

    BaseTerm & baseTerm(getBaseTermReferenceFromTerm(originalTerm));
    Term & termToVerify(dynamic_cast<Term &>(baseTerm));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromUniquePointerWorks)
{
    BaseTermUniquePointer uniquePointer(Term(6415).createBasePointerByMove());

    BaseTerm & baseTerm(getBaseTermReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

}

}
