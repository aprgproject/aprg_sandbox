#include <Algebra/Equation/EquationBuilder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(EquationBuilderTest, ConstructionWorks)
{
    EquationBuilder("");
}

TEST(EquationBuilderTest, GetEquationWorksWhenVariableEqualsVariable)
{
    EquationBuilder builder("a=b");

    Equation expectedEquation(Term("a"), "=", Term("b"));
    EXPECT_EQ(expectedEquation, builder.getEquation());
}

TEST(EquationBuilderTest, GetEquationWorksWhenMonomialEqualsMonomial)
{
    EquationBuilder builder("531*x^2*y^3 = 145*a^4*b^5");

    Equation expectedEquation(Term(Monomial(531, {{"x",2},{"y",3}})), "=", Term(Monomial(145, {{"a",4},{"b",5}})));
    EXPECT_EQ(expectedEquation, builder.getEquation());
}

TEST(EquationBuilderTest, GetTermStringsWorks)
{
    EquationBuilder builder("a=b=c=d");

    stringHelper::strings termStrings(builder.getTermStrings());

    ASSERT_EQ(4u, termStrings.size());
    EXPECT_EQ("a", termStrings.at(0));
    EXPECT_EQ("b", termStrings.at(1));
    EXPECT_EQ("c", termStrings.at(2));
    EXPECT_EQ("d", termStrings.at(3));
}

TEST(EquationBuilderTest, GetEquationOperatorStringsWorks)
{
    EquationBuilder builder("a=a==a!=a<a>a<=a>=a");

    stringHelper::strings equationOperatorStrings(builder.getEquationOperatorStrings());

    ASSERT_EQ(7u, equationOperatorStrings.size());
    EXPECT_EQ("=", equationOperatorStrings.at(0));
    EXPECT_EQ("==", equationOperatorStrings.at(1));
    EXPECT_EQ("!=", equationOperatorStrings.at(2));
    EXPECT_EQ("<", equationOperatorStrings.at(3));
    EXPECT_EQ(">", equationOperatorStrings.at(4));
    EXPECT_EQ("<=", equationOperatorStrings.at(5));
    EXPECT_EQ(">=", equationOperatorStrings.at(6));
}

}

}
