#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba::algebra::Functions;
using namespace std;

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

TEST(TermRaiseToANumberTest, IsEmptyWorks)
{
    TermRaiseToANumber empty;
    TermRaiseToANumber nonEmpty(Term("x"), 5);

    EXPECT_TRUE(empty.isEmpty());
    EXPECT_FALSE(nonEmpty.isEmpty());
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

TEST(TermRaiseToANumberTest, GetCombinedTermWorks)
{
    TermRaiseToANumber baseAndExponent1(Term("x"), 1);
    TermRaiseToANumber baseAndExponent2(Term(Monomial(5, {{"x", 6}})), 7);
    TermRaiseToANumber baseAndExponent3(Term(sin(Term("x"))), 7);

    string stringToExpect1("x");
    string stringToExpect2("78125[x^42]");
    string stringToExpect3("(sin(x)^7)");
    EXPECT_EQ(stringToExpect1, baseAndExponent1.getCombinedTerm().getDisplayableString());
    EXPECT_EQ(stringToExpect2, baseAndExponent2.getCombinedTerm().getDisplayableString());
    EXPECT_EQ(stringToExpect3, baseAndExponent3.getCombinedTerm().getDisplayableString());
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

TEST(TermRaiseToANumberTest, GetBaseReferenceWorks)
{
    TermRaiseToANumber termRaiseToANumber(Term("x"), 5);

    termRaiseToANumber.getBaseReference() = Term("y");

    EXPECT_EQ(Term("y"), termRaiseToANumber.getBase());
}

}

}
