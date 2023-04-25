#include <BooleanAlgebra/Term/Operators/TermOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(TermOperatorsTest, UnaryNotOperatorWorks) {
    EXPECT_EQ(Term(), ~Term());
    EXPECT_EQ(Term(true), ~Term(false));
    EXPECT_EQ(Term(false), ~Term(true));
}

TEST(TermOperatorsTest, BinaryAndOperatorWorks) {
    Term term1 = Term(false) & Term(false);
    Term term2 = Term(false) & Term(true);
    Term term3 = Term(true) & Term(false);
    Term term4 = Term(true) & Term(true);

    EXPECT_EQ(Term(false), term1);
    EXPECT_EQ(Term(false), term2);
    EXPECT_EQ(Term(false), term3);
    EXPECT_EQ(Term(true), term4);
}

TEST(TermOperatorsTest, BinaryAndAssignmentOperatorWorks) {
    Term term1(false);
    term1 &= Term(false);
    Term term2(false);
    term2 &= Term(true);
    Term term3(true);
    term3 &= Term(false);
    Term term4(true);
    term4 &= Term(true);

    EXPECT_EQ(Term(false), term1);
    EXPECT_EQ(Term(false), term2);
    EXPECT_EQ(Term(false), term3);
    EXPECT_EQ(Term(true), term4);
}

TEST(TermOperatorsTest, BinaryOrOperatorWorks) {
    Term term1 = Term(false) | Term(false);
    Term term2 = Term(false) | Term(true);
    Term term3 = Term(true) | Term(false);
    Term term4 = Term(true) | Term(true);

    EXPECT_EQ(Term(false), term1);
    EXPECT_EQ(Term(true), term2);
    EXPECT_EQ(Term(true), term3);
    EXPECT_EQ(Term(true), term4);
}

TEST(TermOperatorsTest, BinaryOrAssignmentOperatorWorks) {
    Term term1(false);
    term1 |= Term(false);
    Term term2(false);
    term2 |= Term(true);
    Term term3(true);
    term3 |= Term(false);
    Term term4(true);
    term4 |= Term(true);

    EXPECT_EQ(Term(false), term1);
    EXPECT_EQ(Term(true), term2);
    EXPECT_EQ(Term(true), term3);
    EXPECT_EQ(Term(true), term4);
}

}  // namespace booleanAlgebra

}  // namespace alba
