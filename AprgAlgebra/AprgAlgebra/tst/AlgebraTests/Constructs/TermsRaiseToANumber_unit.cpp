#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(TermRaiseToANumberTest, ConstructionWorks) {
    TermRaiseToANumber termRaiseToANumber("x", 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(TermRaiseToANumberTest, IsEmptyWorks) {
    TermRaiseToANumber empty;
    TermRaiseToANumber nonEmpty("x", 5);

    EXPECT_TRUE(empty.isEmpty());
    EXPECT_FALSE(nonEmpty.isEmpty());
}

TEST(TermRaiseToANumberTest, IsRadicalWorks) {
    TermRaiseToANumber termWithIntegerExponent("x", 5);
    TermRaiseToANumber termWithFractionalExponent("x", AlbaNumber::createFraction(3, 4));
    TermRaiseToANumber termWithDoubleExponent("x", 1.693);

    EXPECT_FALSE(termWithIntegerExponent.isRadical());
    EXPECT_TRUE(termWithFractionalExponent.isRadical());
    EXPECT_TRUE(termWithDoubleExponent.isRadical());
}

TEST(TermRaiseToANumberTest, GetCombinedTermWorks) {
    TermRaiseToANumber baseAndExponent1("x", 1);
    TermRaiseToANumber baseAndExponent2(Monomial(5, {{"x", 6}}), 7);
    TermRaiseToANumber baseAndExponent3(sin("x"), 7);

    string stringToExpect1("x");
    string stringToExpect2("78125[x^42]");
    string stringToExpect3("(sin(x)^7)");
    EXPECT_EQ(stringToExpect1, convertToString(baseAndExponent1.getCombinedTerm()));
    EXPECT_EQ(stringToExpect2, convertToString(baseAndExponent2.getCombinedTerm()));
    EXPECT_EQ(stringToExpect3, convertToString(baseAndExponent3.getCombinedTerm()));
}

TEST(TermRaiseToANumberTest, GetBaseWorks) {
    TermRaiseToANumber termRaiseToANumber("x", 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
}

TEST(TermRaiseToANumberTest, GetExponentWorks) {
    TermRaiseToANumber termRaiseToANumber("x", 5);

    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(TermRaiseToANumberTest, GetBaseReferenceWorks) {
    TermRaiseToANumber termRaiseToANumber("x", 5);

    termRaiseToANumber.getBaseReference() = "y";

    EXPECT_EQ(Term("y"), termRaiseToANumber.getBase());
}

}  // namespace algebra

}  // namespace alba
