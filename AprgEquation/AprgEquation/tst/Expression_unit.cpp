#include <Expression.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

namespace equation
{

TEST(ExpressionTest, ConstructionWorks)
{
    Expression expression1;
    Expression expression2(getBaseTermConstReferenceFromTerm(Term(12)));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify1(expression1.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify2(expression2.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify(getTermConstReferenceFromBaseTerm(getBaseTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer)));
    EXPECT_EQ(Term(12), termToVerify);
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
    EXPECT_FALSE(expression1==expression2);
    EXPECT_TRUE(expression2==expression2);
    EXPECT_FALSE(expression2==expression3);
    EXPECT_FALSE(expression2==expression4);
    EXPECT_FALSE(expression2==expression5);
    EXPECT_TRUE(expression2==expression6);
}

TEST(ExpressionTest, ContainsNoTermsWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));

    EXPECT_TRUE(expression1.containsNoTerms());
    EXPECT_FALSE(expression2.containsNoTerms());
    EXPECT_FALSE(expression3.containsNoTerms());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks)
{
    Expression expression1;    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));

    EXPECT_FALSE(expression1.containsOnlyOneTerm());
    EXPECT_TRUE(expression2.containsOnlyOneTerm());
    EXPECT_FALSE(expression3.containsOnlyOneTerm());
}

TEST(ExpressionTest, GetCommonOperatorLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible(Terms{Term(6), Term("-"), Term("interest")}));
    Expression expression5(createExpressionIfPossible(Terms{Term(6), Term("*"), Term("interest")}));
    Expression expression6(createExpressionIfPossible(Terms{Term(6), Term("/"), Term("interest")}));
    Expression expression7(createExpressionIfPossible(Terms{Term(6), Term("^"), Term("interest")}));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression3.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression4.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression5.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression6.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::RaiseToPower, expression7.getCommonOperatorLevel());
}

TEST(ExpressionTest, GetFirstTermConstReferenceWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(5412)}));
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    EXPECT_EQ(Term(5412), getTermConstReferenceFromBaseTerm(expression1.getFirstTermConstReference()));
    EXPECT_EQ(Term(695), getTermConstReferenceFromBaseTerm(expression2.getFirstTermConstReference()));
}

TEST(ExpressionTest, GetTermsWorks)
{
    Expression expression(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    TermsWithPriorityAndAssociation terms(expression.getTerms());
    TermsWithPriorityAndAssociation::TermsWithDetails termsWithDetailsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(3u, termsWithDetailsToVerify.size());
    EXPECT_EQ(Term(695), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsWithDetailsToVerify.at(0).association);    EXPECT_EQ(Term("interest"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Negative, termsWithDetailsToVerify.at(1).association);
    EXPECT_EQ(Term("debt"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsWithDetailsToVerify.at(2).association);
}

TEST(ExpressionTest, GetDisplayableStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression3;
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(Term(96)));
    Expression expression4(createExpressionIfPossible(Terms{Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("()", expression1.getDisplayableString());
    EXPECT_EQ("(695-interest+debt)", expression2.getDisplayableString());
    EXPECT_EQ("(1/96)", expression3.getDisplayableString());
    EXPECT_EQ("((695-interest+debt)^cash)", expression4.getDisplayableString());
}

TEST(ExpressionTest, SimplifyWorksOnSingleTermExpression)
{
    Term expressionTerm(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
    Term expressionInExpressionTerm(Expression(getBaseTermConstReferenceFromTerm(expressionTerm)));
    Term expressionInExpressionInExpressionTerm(Expression(getBaseTermConstReferenceFromTerm(expressionInExpressionTerm)));
    Expression expression(createExpressionIfPossible(Terms{expressionInExpressionInExpressionTerm}));

    expression.simplify();

    EXPECT_EQ(expressionTerm, expression);
}

TEST(ExpressionTest, SimplifyWorksOnContinuousSingleTermExpression)
{
    Term expressionTerm(Expression(getBaseTermConstReferenceFromTerm(Term(967))));
    Term expressionInExpressionTerm(Expression(getBaseTermConstReferenceFromTerm(expressionTerm)));
    Term expressionInExpressionInExpressionTerm(Expression(getBaseTermConstReferenceFromTerm(expressionInExpressionTerm)));
    Expression expression(createExpressionIfPossible(Terms{expressionInExpressionInExpressionTerm}));

    expression.simplify();

    EXPECT_EQ(createExpressionIfPossible(Terms{Term(967)}), expression);
}

TEST(ExpressionTest, ClearAndSetTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    expression1.clearAndSetTerm(Term(24));
    expression2.clearAndSetTerm(Term(65));

    EXPECT_EQ(createExpressionIfPossible(Terms{Term(24)}), expression1);
    EXPECT_EQ(createExpressionIfPossible(Terms{Term(65)}), expression2);
}

TEST(ExpressionTest, AddTermWorks)
{
    Expression expression1;    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionInMultiplication(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInMultiplication, Term("+"), Term(42)}));

    expression1.addTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionInMultiplication(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("-"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInMultiplication, Term("-"), Term(42)}));

    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInExponent, Term("*"), Term(42)}));

    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("/"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInExponent, Term("/"), Term(42)}));

    expression1.divideTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInExponent, Term("^"), Term(42)}));

    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SetCommonOperatorLevelWorks)
{
    Expression expression1;
    Expression expression2;
    Expression expression3;
    Expression expression4;

    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expression3.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expression4.setCommonOperatorLevel(OperatorLevel::RaiseToPower);

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression3.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::RaiseToPower, expression4.getCommonOperatorLevel());
}

TEST(ExpressionTest, ReverseTheAssociationOfTheTermsWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695)}));
    Expression expressionToExpect1;
    Expression expressionToExpect2;
    expressionToExpect2.subtractTerm(getBaseTermConstReferenceFromTerm(Term(695)));
    expressionToExpect2.setCommonOperatorLevel(OperatorLevel::Unknown);

    expression1.reverseTheAssociationOfTheTerms();
    expression2.reverseTheAssociationOfTheTerms();

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

}

}
