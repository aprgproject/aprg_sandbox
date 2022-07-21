#include <BooleanAlgebra/Term/TermTypes/VariableTerm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(VariableTermTest, VariableTermsAreConstructedCorrectly)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");
    VariableTerm variableTerm3("time", true);

    EXPECT_EQ("", variableTerm1.getVariableTermName());
    EXPECT_FALSE(variableTerm1.isNegated());
    EXPECT_EQ("time", variableTerm2.getVariableTermName());
    EXPECT_FALSE(variableTerm2.isNegated());
    EXPECT_EQ("time", variableTerm3.getVariableTermName());
    EXPECT_TRUE(variableTerm3.isNegated());
}

TEST(VariableTermTest, EqualityOperatorWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variable3("power");
    VariableTerm variable4("x", true);

    EXPECT_TRUE(variableTerm1==variableTerm1);
    EXPECT_FALSE(variableTerm1==variableTerm2);
    EXPECT_TRUE(variableTerm2==variableTerm2);
    EXPECT_FALSE(variableTerm2==variable3);
    EXPECT_FALSE(variableTerm2==variable4);
}

TEST(VariableTermTest, InequalityOperatorWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variable3("power");
    VariableTerm variable4("x", true);

    EXPECT_FALSE(variableTerm1!=variableTerm1);
    EXPECT_TRUE(variableTerm1!=variableTerm2);
    EXPECT_FALSE(variableTerm2!=variableTerm2);
    EXPECT_TRUE(variableTerm2!=variable3);
    EXPECT_TRUE(variableTerm2!=variable4);
}

TEST(VariableTermTest, LessThanOperatorWorks)
{
    EXPECT_FALSE(VariableTerm() < VariableTerm());
    EXPECT_FALSE(VariableTerm("x") < VariableTerm("x"));
    EXPECT_FALSE(VariableTerm("x") < VariableTerm("w"));
    EXPECT_TRUE(VariableTerm("x") < VariableTerm("y"));
    EXPECT_FALSE(VariableTerm("x", false) < VariableTerm("x", false));
    EXPECT_FALSE(VariableTerm("x", true) < VariableTerm("x", false));
    EXPECT_TRUE(VariableTerm("x", false) < VariableTerm("x", true));
}

TEST(VariableTermTest, IsNegatedWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time", true);

    EXPECT_FALSE(variableTerm1.isNegated());
    EXPECT_TRUE(variableTerm2.isNegated());
}

TEST(VariableTermTest, GetDisplayableStringWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");

    EXPECT_EQ("", variableTerm1.getDisplayableString());
    EXPECT_EQ("time", variableTerm2.getDisplayableString());
}

TEST(VariableTermTest, SettingANewVariableTermNameWorks)
{
    VariableTerm variableForTest;
    EXPECT_EQ("", variableForTest.getVariableTermName());

    variableForTest.setVariableTermName("omega");
    EXPECT_EQ("omega", variableForTest.getVariableTermName());
}

TEST(VariableTermTest, NegateWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");
    VariableTerm variableTerm3("time", true);

    variableTerm1.negate();
    variableTerm2.negate();
    variableTerm3.negate();

    EXPECT_EQ(VariableTerm("", true), variableTerm1);
    EXPECT_EQ(VariableTerm("time", true), variableTerm2);
    EXPECT_EQ(VariableTerm("time", false), variableTerm3);
}

}

}
