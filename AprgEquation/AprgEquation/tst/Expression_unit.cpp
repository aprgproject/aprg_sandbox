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
    Expression expression1;
    Expression expression2(getBaseTermConstReferenceFromTerm(Term(12)));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify1(expression1.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify2(expression2.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
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

TEST(ExpressionTest, InequalityOperatorWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+"), Term("interest")}))}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression5(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+")}))}));
    Expression expression6(createExpressionIfPossible(Terms{Term(5), Term("+"), Term(createExpressionIfPossible(Terms{Term(5), Term("+"), Term("interest")}))}));

    EXPECT_FALSE(expression1!=expression1);
    EXPECT_TRUE(expression1!=expression2);
    EXPECT_FALSE(expression2!=expression2);
    EXPECT_TRUE(expression2!=expression3);
    EXPECT_TRUE(expression2!=expression4);
    EXPECT_TRUE(expression2!=expression5);
    EXPECT_FALSE(expression2!=expression6);
}

TEST(ExpressionTest, LessThanOperatorWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6)}));
    Expression expression4(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression5(createExpressionIfPossible(Terms{Term(5), Term("+"), Term("interest")}));
    Expression expression6(createExpressionIfPossible(Terms{Term(7), Term("+"), Term("interest")}));

    EXPECT_FALSE(expression1<expression1);
    EXPECT_FALSE(expression2<expression2);
    EXPECT_FALSE(expression2<expression3);
    EXPECT_TRUE(expression2<expression4);
    EXPECT_FALSE(expression2<expression5);
    EXPECT_TRUE(expression2<expression6);
}

TEST(ExpressionTest, IsEmptyWorks)
{
    Expression expression1;    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(6), Term("+"), Term("interest")}));

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_FALSE(expression2.isEmpty());
    EXPECT_FALSE(expression3.isEmpty());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
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
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsWithDetailsToVerify.at(0).association);
    EXPECT_EQ(Term("interest"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(1).baseTermSharedPointer));
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
    //Expression expression4(createExpressionIfPossible(Terms{Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("()", expression1.getDisplayableString());
    EXPECT_EQ("(695-interest+debt)", expression2.getDisplayableString());
    EXPECT_EQ("(1/96)", expression3.getDisplayableString());
    //EXPECT_EQ("((695-interest+debt)^cash)", expression4.getDisplayableString());
}

TEST(ExpressionTest, SimplifyWorksOnSingleTermExpression)
{    Term expressionTerm(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expression(createExpressionIfPossible(Terms{expressionInExpressionInExpressionTerm}));

    expression.simplify();

    EXPECT_EQ(expressionTerm, expression);
}

TEST(ExpressionTest, SimplifyWorksOnContinuousSingleTermExpression)
{
    Term expressionTerm(createAndWrapExpressionFromATerm(Term(967)));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expression(createExpressionIfPossible(Terms{expressionInExpressionInExpressionTerm}));

    expression.simplify();

    EXPECT_EQ(createExpressionIfPossible(Terms{Term(967)}), expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants)
{
    Expression expression(createExpressionIfPossible(Terms{Term(100), Term("+"), Term(200), Term("-"), Term(50)}));
    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(250)}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsMonomialPolynomial)
{
    Expression expression(
                createExpressionIfPossible(                    Terms{
                        Term(Monomial(43, {{"x", 2}, {"y", 3}})),
                        Term("+"),
                        Term(159),
                        Term("-"),
                        Term(Polynomial{
                            Monomial(56, {{"x", 3}}),
                            Monomial(-251, {}),
                            Monomial(13, {{"x", 2}, {"y", 3}})
                        })
                    }));

    expression.simplify();

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(Polynomial{
                            Monomial(30, {{"x", 2}, {"y", 3}}),
                            Monomial(410, {}),
                            Monomial(-56, {{"x", 3}})
                        })}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsWithExpressionInBetween)
{
    Expression expression(
                createExpressionIfPossible(                    Terms{
                        Term(500),
                        Term("+"),
                        Term("y"),
                        Term("^"),
                        Term("y"),
                        Term("-"),
                        Term(150)
                    }));

    expression.simplify();

    Expression subExpression(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(350), Term("+"), Term(subExpression)}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnMultiplyingAndDividingConstants)
{
    Expression expression(createExpressionIfPossible(Terms{Term(100), Term("*"), Term(200), Term("/"), Term(50)}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(400)}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SaveTermWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    expression1.saveTerm(Term());
    expression2.saveTerm(Term(87));
    expression3.saveTerm(Term(createExpressionIfPossible(Terms{Term(78), Term("+"), Term("energy")})));

    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term()}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(87)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(78), Term("+"), Term("energy")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, AddTermUsingNullExpressionWorks){
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.addTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, AddTermUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.addTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, AddTermUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.addTerm(getBaseTermConstReferenceFromTerm(constant));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(constant));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("+"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, AddTermUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("+"), Term("x"), Term("-"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, AddTermUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.addTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(subExpression2), Term("+"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermUsingNullExpressionWorks)
{    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(constant));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(constant));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("-"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("-"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("-"), Term("x"), Term("+"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("-"), Term("x"), Term("+"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SubtractTermUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.subtractTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("-"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("-"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermUsingNullExpressionWorks)
{    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(constant));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(constant));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("*"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("*"), Term("x"), Term("/"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, MultiplyTermUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.multiplyTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("*"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermUsingNullExpressionWorks)
{    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression nullExpression;
    expression1.divideTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.divideTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Term constant(42);
    expression1.divideTerm(getBaseTermConstReferenceFromTerm(constant));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(constant));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest"), Term("/"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("/"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest"), Term("/"), Term("x"), Term("*"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("/"), Term("x"), Term("*"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, DivideTermUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.divideTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest"), Term("/"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("/"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermWorks)
{    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInExponent, Term("^"), Term(42)}));

    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(constant));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(constant));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("^"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));
    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("^"), Term("x"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, RaiseToPowerTermUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("^"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SetCommonOperatorLevelWorks)
{    Expression expression1;
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

    expression1.reverseTheAssociationOfTheTerms();
    expression2.reverseTheAssociationOfTheTerms();

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify1(expression1.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify2(expression2.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Negative, termsToVerify2.at(0).association);
    Term const& termToVerify(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(695), termToVerify);
}

TEST(ExpressionTest, ClearAndPutTermInTermsWithAssociationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    expression1.clearAndPutTermInTermsWithAssociation(Term(24));
    expression2.clearAndPutTermInTermsWithAssociation(Term(65));

    EXPECT_EQ(createExpressionIfPossible(Terms{Term(24)}), expression1);
    EXPECT_EQ(createExpressionIfPossible(Terms{Term(65)}), expression2);
}

}

}