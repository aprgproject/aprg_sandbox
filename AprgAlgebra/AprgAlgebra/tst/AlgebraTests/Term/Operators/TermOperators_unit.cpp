#include <Algebra/Term/Operators/TermOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermOperatorsTest, UnaryPlusOperatorWorks)
{
    Term term(+Term(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, UnaryMinusOperatorWorks)
{
    Term term(-Term(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermOperatorsTest, BinaryPlusOperatorWorks)
{
    Term term(Term(6)+Term(3));

    EXPECT_EQ(Term(9), term);
}

TEST(TermOperatorsTest, BinaryPlusAssignmentOperatorWorks)
{
    Term term(6);
    term += 3;

    EXPECT_EQ(Term(9), term);
}

TEST(TermOperatorsTest, BinaryMinusOperatorWorks)
{
    Term term(Term(6)-Term(3));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryMinusAssignmentOperatorWorks)
{
    Term term(6);
    term -= 3;

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperatorWorks)
{
    Term term(Term(6)*Term(3));

    EXPECT_EQ(Term(18), term);
}

TEST(TermOperatorsTest, BinaryMultiplyAssignmentOperatorWorks)
{
    Term term(6);
    term *= 3;

    EXPECT_EQ(Term(18), term);
}

TEST(TermOperatorsTest, BinaryDivideOperatorWorks)
{
    Term term(Term(6)/Term(3));

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryDivideAssignmentOperatorWorks)
{
    Term term(6);
    term /= 3;

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperatorWorks)
{
    Term term(Term(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerAssignmentOperatorWorks)
{
    Term term(6);
    term ^= 2;

    EXPECT_EQ(Term(36), term);
}

}

}