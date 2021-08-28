#include <Algebra/Constructs/TermRaiseToANumber.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(TermRaiseToANumberTest, ConstructionWorks)
{
    TermRaiseToANumber termRaiseToANumber(Term("x"), 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(TermRaiseToANumberTest, IsRadicalWorks)
{
    TermRaiseToANumber termWithIntegerExponent(Term("x"), 5);
    TermRaiseToANumber termWithFractionalExponent(Term("x"), AlbaNumber::createFraction(3, 4));
    TermRaiseToANumber termWithDoubleExponent(Term("x"), 1.693);

    EXPECT_FALSE(termWithIntegerExponent.isRadical());
    EXPECT_TRUE(termWithFractionalExponent.isRadical());
    EXPECT_TRUE(termWithDoubleExponent.isRadical());
}

TEST(TermRaiseToANumberTest, GetBaseWorks)
{
    TermRaiseToANumber termRaiseToANumber(Term("x"), 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
}

TEST(TermRaiseToANumberTest, GetExponentWorks)
{
    TermRaiseToANumber termRaiseToANumber(Term("x"), 5);

    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

}

}
