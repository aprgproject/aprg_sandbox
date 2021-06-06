#include <Expression.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(ExpressionTest, ConstructionWorks)
{
    Expression();
}

TEST(ExpressionTest, EqualityOperatorWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+"), Term("interest")}))}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression5(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+")}))}));
    Expression expression6(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+"), Term("interest")}))}));

    EXPECT_TRUE(expression1==expression1);
    EXPECT_FALSE(expression1==expression2);    EXPECT_TRUE(expression2==expression2);
    EXPECT_FALSE(expression2==expression3);
    EXPECT_FALSE(expression2==expression4);
    EXPECT_FALSE(expression2==expression5);
    EXPECT_TRUE(expression2==expression6);
}

}

}
