#include <Algebra/Equation/Equation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(EquationTest, EquationsAreConstructedCorrectly)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));

    EXPECT_EQ(Operator("="), equation1.getEquationOperator());
    EXPECT_TRUE(equation1.getLeftHandTerm().isEmpty());
    EXPECT_TRUE(equation1.getRightHandTerm().isEmpty());
    EXPECT_EQ(Operator(">"), equation2.getEquationOperator());
    EXPECT_EQ(Term(7), equation2.getLeftHandTerm());
    EXPECT_EQ(Term(8), equation2.getRightHandTerm());
}

TEST(EquationTest, EqualityOperatorWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));
    Equation equation3(">", Term(7), Term(8));
    Equation equation4(">", Term(7), Term(Monomial(1, {{"x", 1}})));
    Equation equation5(">", Term(Monomial(1, {{"x", 1}})), Term(8));
    Equation equation6(">=", Term(Monomial(1, {{"x", 1}})), Term(8));

    EXPECT_TRUE(equation1==equation1);
    EXPECT_FALSE(equation1==equation2);
    EXPECT_TRUE(equation2==equation2);
    EXPECT_TRUE(equation2==equation3);
    EXPECT_FALSE(equation2==equation4);
    EXPECT_FALSE(equation2==equation5);
    EXPECT_FALSE(equation2==equation6);
}

TEST(EquationTest, InequalityOperatorWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));
    Equation equation3(">", Term(7), Term(8));
    Equation equation4(">", Term(7), Term(Monomial(1, {{"x", 1}})));
    Equation equation5(">", Term(Monomial(1, {{"x", 1}})), Term(8));
    Equation equation6(">=", Term(Monomial(1, {{"x", 1}})), Term(8));

    EXPECT_FALSE(equation1!=equation1);
    EXPECT_TRUE(equation1!=equation2);
    EXPECT_FALSE(equation2!=equation2);
    EXPECT_FALSE(equation2!=equation3);
    EXPECT_TRUE(equation2!=equation4);
    EXPECT_TRUE(equation2!=equation5);
    EXPECT_TRUE(equation2!=equation6);
}

TEST(EquationTest, LessThanOperatorWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2("<", Term(7), Term(17));
    Equation equation3("<", Term(7), Term(17));
    Equation equation4("<", Term(7), Term(16));
    Equation equation5("<", Term(7), Term(18));
    Equation equation6("<", Term(6), Term(17));
    Equation equation7("<", Term(8), Term(17));
    Equation equation8("==", Term(7), Term(17));
    Equation equation9(">", Term(7), Term(17));

    EXPECT_FALSE(equation1<equation1);
    EXPECT_FALSE(equation2<equation3);
    EXPECT_FALSE(equation2<equation4);
    EXPECT_TRUE(equation2<equation5);
    EXPECT_FALSE(equation2<equation6);
    EXPECT_TRUE(equation2<equation7);
    EXPECT_FALSE(equation2<equation8);
    EXPECT_TRUE(equation2<equation9);
}

TEST(EquationTest, GetEquationOperatorWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));

    EXPECT_EQ(Operator("="), equation1.getEquationOperator());
    EXPECT_EQ(Operator(">"), equation2.getEquationOperator());
}

TEST(EquationTest, GetLeftHandTermWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));

    EXPECT_TRUE(equation1.getLeftHandTerm().isEmpty());
    EXPECT_EQ(Term(7), equation2.getLeftHandTerm());
}

TEST(EquationTest, GetRightHandTermWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));

    EXPECT_TRUE(equation1.getRightHandTerm().isEmpty());
    EXPECT_EQ(Term(8), equation2.getRightHandTerm());
}

TEST(EquationTest, GetDisplayableStringWorks)
{
    Equation equation1("=", Term(), Term());
    Equation equation2(">", Term(7), Term(8));

    EXPECT_EQ("{EmptyTerm} = {EmptyTerm}", equation1.getDisplayableString());
    EXPECT_EQ("7 > 8", equation2.getDisplayableString());
}

}

}
