#include <Algebra/Equation/EquationBuilder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(EquationBuilderTest, ConstructionWorks) { EquationBuilder(""); }

TEST(EquationBuilderTest, GetEquationWorksWhenVariableEqualsVariable) {
    EquationBuilder builder("a=b");

    Equation expectedEquation("a", "=", "b");
    EXPECT_EQ(expectedEquation, builder.getEquation());
}

TEST(EquationBuilderTest, GetEquationWorksWhenMonomialEqualsMonomial) {
    EquationBuilder builder("531*x^2*y^3 = 145*a^4*b^5");

    Equation expectedEquation(Monomial(531, {{"x", 2}, {"y", 3}}), "=", Monomial(145, {{"a", 4}, {"b", 5}}));
    EXPECT_EQ(expectedEquation, builder.getEquation());
}

TEST(EquationBuilderTest, GetTermStringsWorks) {
    EquationBuilder builder("a=b=c=d");

    stringHelper::strings termStrings(builder.getTermStrings());

    ASSERT_EQ(4U, termStrings.size());
    EXPECT_EQ("a", termStrings[0]);
    EXPECT_EQ("b", termStrings[1]);
    EXPECT_EQ("c", termStrings[2]);
    EXPECT_EQ("d", termStrings[3]);
}

TEST(EquationBuilderTest, GetEquationOperatorStringsWorks) {    EquationBuilder builder("a=a==a!=a<a>a<=a>=a");

    stringHelper::strings equationOperatorStrings(builder.getEquationOperatorStrings());

    ASSERT_EQ(7U, equationOperatorStrings.size());
    EXPECT_EQ("=", equationOperatorStrings[0]);
    EXPECT_EQ("==", equationOperatorStrings[1]);
    EXPECT_EQ("!=", equationOperatorStrings[2]);
    EXPECT_EQ("<", equationOperatorStrings[3]);
    EXPECT_EQ(">", equationOperatorStrings[4]);
    EXPECT_EQ("<=", equationOperatorStrings[5]);
    EXPECT_EQ(">=", equationOperatorStrings[6]);
}

}  // namespace algebra
}  // namespace alba