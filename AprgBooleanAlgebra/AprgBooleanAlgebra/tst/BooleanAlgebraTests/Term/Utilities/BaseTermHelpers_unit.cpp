#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(BaseTermHelpersTest, CreateBasePointerWorksForLValue) {
    Term originalTerm(true);

    BaseTermUniquePointer uniquePointer(createBasePointer(originalTerm));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, CreateBasePointerWorksForRValue) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, DuplicateUniquePointerWorks) {
    BaseTermUniquePointer originalPointer(createBasePointer(Term(true)));

    BaseTermUniquePointer duplicatedPointer(duplicateUniquePointer(originalPointer));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(duplicatedPointer));
}

TEST(BaseTermHelpersTest, CreateAUniquePointerFromTermWorks) {
    BaseTermUniquePointer uniquePointerToVerify(createBasePointer(Term(true)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointerToVerify));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromBaseTermWorks) {
    Term originalTerm(true);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(static_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromBaseTermWorks) {
    Term originalTerm(true);

    Term& termToVerify(getTermReferenceFromBaseTerm(static_cast<BaseTerm&>(originalTerm)));
    originalTerm = Term(true);

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    Term& termToChange(getTermReferenceFromUniquePointer(uniquePointer));
    termToChange.getConstantReference().setValue(763);

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));
    EXPECT_EQ(Term(763), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromTermWorks) {
    Term originalTerm(true);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));

    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromTermWorks) {
    Term originalTerm(true);

    BaseTerm& baseTerm(getBaseTermReferenceFromTerm(originalTerm));
    Term& termToVerify(static_cast<Term&>(baseTerm));
    originalTerm = Term(true);

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    BaseTerm& baseTerm(getBaseTermReferenceFromUniquePointer(uniquePointer));

    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

}  // namespace booleanAlgebra

}  // namespace alba
