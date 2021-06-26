#include <Equation/Term/Expression.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{
namespace equation
{
TEST(ExpressionTest, ConstructionWorks)
{
    Expression expression1;
    Expression expression2(Term(12));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithAssociation::TermsWithDetails const& termsToVerify1(expression1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithAssociation::TermsWithDetails const& termsToVerify2(expression2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(12), termToVerify);
}

TEST(ExpressionTest, EqualityOperatorWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+"), Term("interest")}))}));
    Expression expression3(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible({Term(5)}));
    Expression expression5(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+")}))}));
    Expression expression6(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+"), Term("interest")}))}));

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
    Expression expression2(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+"), Term("interest")}))}));
    Expression expression3(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible({Term(5)}));
    Expression expression5(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+")}))}));
    Expression expression6(createExpressionIfPossible({Term(5), Term("+"), Term(createExpressionIfPossible({Term(5), Term("+"), Term("interest")}))}));

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
    Expression expression2(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(6)}));
    Expression expression4(createExpressionIfPossible({Term(6), Term("+"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression5(createExpressionIfPossible({Term(5), Term("+"), Term("interest")}));
    Expression expression6(createExpressionIfPossible({Term(7), Term("+"), Term("interest")}));

    EXPECT_FALSE(expression1<expression1);
    EXPECT_FALSE(expression2<expression2);
    EXPECT_FALSE(expression2<expression3);
    EXPECT_TRUE(expression2<expression4);
    EXPECT_FALSE(expression2<expression5);
    EXPECT_TRUE(expression2<expression6);
}

TEST(ExpressionTest, IsEmptyWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(5)}));
    Expression expression3(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_FALSE(expression2.isEmpty());
    EXPECT_FALSE(expression3.isEmpty());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(5)}));
    Expression expression3(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));

    EXPECT_FALSE(expression1.containsOnlyOneTerm());
    EXPECT_TRUE(expression2.containsOnlyOneTerm());
    EXPECT_FALSE(expression3.containsOnlyOneTerm());
}

TEST(ExpressionTest, GetCommonOperatorLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(5)}));
    Expression expression3(createExpressionIfPossible({Term(6), Term("+"), Term("interest")}));
    Expression expression4(createExpressionIfPossible({Term(6), Term("-"), Term("interest")}));
    Expression expression5(createExpressionIfPossible({Term(6), Term("*"), Term("interest")}));
    Expression expression6(createExpressionIfPossible({Term(6), Term("/"), Term("interest")}));
    Expression expression7(createExpressionIfPossible({Term(6), Term("^"), Term("interest")}));

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
    Expression expression1(createExpressionIfPossible({Term(5412)}));
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    EXPECT_EQ(Term(5412), getTermConstReferenceFromBaseTerm(expression1.getFirstTermConstReference()));
    EXPECT_EQ(Term(695), getTermConstReferenceFromBaseTerm(expression2.getFirstTermConstReference()));
}

TEST(ExpressionTest, GetTermsWithAssociationWorks)
{
    Expression expression(createExpressionIfPossible({Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    TermsWithAssociation terms(expression.getTermsWithAssociation());
    TermsWithAssociation::TermsWithDetails termsWithDetailsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(3u, termsWithDetailsToVerify.size());
    EXPECT_EQ(Term(695), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetailsToVerify.at(0).association);
    EXPECT_EQ(Term("interest"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetailsToVerify.at(1).association);
    EXPECT_EQ(Term("debt"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetailsToVerify.at(2).association);
}

TEST(ExpressionTest, GetTermsWithDetailsThatSatisfiesConditionWhenConditionIsNegativeAssocationWorks)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("+"), Term("y"), Term("-"), Term("z")}));

    TermsWithAssociation terms(
                expression.getTermsWithDetailsThatSatisfiesCondition(
                    [](TermsWithAssociation::TermWithDetails const& termWithDetails) {
                    return termWithDetails.hasNegativeAssociation();
                }));

    TermsWithAssociation::TermsWithDetails termsWithDetailsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1u, termsWithDetailsToVerify.size());
    EXPECT_EQ(Term("z"), getTermConstReferenceFromSharedPointer(termsWithDetailsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetailsToVerify.at(0).association);
}

TEST(ExpressionTest, GetDisplayableStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression3;
    expression3.putTermWithDivisionIfNeeded(Term(96));
    Expression expression4(createExpressionIfPossible({Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("()", expression1.getDisplayableString());
    EXPECT_EQ("(695-interest+debt)", expression2.getDisplayableString());
    EXPECT_EQ("(1/96)", expression3.getDisplayableString());
    EXPECT_EQ("((695-interest+debt)^cash)", expression4.getDisplayableString());
}

TEST(ExpressionTest, GetDebugStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression3;
    expression3.putTermWithDivisionIfNeeded(Term(96));
    Expression expression4(createExpressionIfPossible({Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("( [?]|| )", expression1.getDebugString());
    EXPECT_EQ("( [+-]||695[Constant][POS]-interest[Variable][NEG]+debt[Variable][POS] )", expression2.getDebugString());
    EXPECT_EQ("( [*/]||1/96[Constant][NEG] )", expression3.getDebugString());
    EXPECT_EQ("( [^]||( [+-]||695[Constant][POS]-interest[Variable][NEG]+debt[Variable][POS] )[Expression][POS]^cash[Variable][POS] )", expression4.getDebugString());
}

TEST(ExpressionTest, ClearWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    expression1.clear();
    expression2.clear();

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_TRUE(expression2.isEmpty());
}

TEST(ExpressionTest, ClearAndPutTermInTermsWithAssociationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    expression1.clearAndPutTermInTermsWithAssociation(Term(24));
    expression2.clearAndPutTermInTermsWithAssociation(Term(65));

    EXPECT_EQ(createExpressionIfPossible({Term(24)}), expression1);
    EXPECT_EQ(createExpressionIfPossible({Term(65)}), expression2);
}

TEST(ExpressionTest, PutTermWithAdditionUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression2.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression3.putTermWithAdditionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.putTermWithAdditionIfNeeded(noEffectTerm);
    expression2.putTermWithAdditionIfNeeded(noEffectTerm);
    expression3.putTermWithAdditionIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithAdditionIfNeeded(constant);
    expression2.putTermWithAdditionIfNeeded(constant);
    expression3.putTermWithAdditionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("+"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("+"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("+"), Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("+"), Term("x"), Term("-"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("+"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(subExpression2), Term("+"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression2.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression3.putTermWithSubtractionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression2.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression3.putTermWithSubtractionIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithSubtractionIfNeeded(constant);
    expression2.putTermWithSubtractionIfNeeded(constant);
    expression3.putTermWithSubtractionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("-"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("-"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("-"), Term("x"), Term("+"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("-"), Term("x"), Term("+"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("+"), Term("interest"), Term("-"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression2, Term("-"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression2.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression3.putTermWithMultiplicationIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression2.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression3.putTermWithMultiplicationIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithMultiplicationIfNeeded(constant);
    expression2.putTermWithMultiplicationIfNeeded(constant);
    expression3.putTermWithMultiplicationIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("*"), Term("interest"), Term("*"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("*"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("*"), Term("interest"), Term("*"), Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("*"), Term("x"), Term("/"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("*"), Term("interest"), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression2, Term("*"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutPolynomialFirstWithMultiplicationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialFirstWithMultiplication(polynomial);
    expression2.putPolynomialFirstWithMultiplication(polynomial);
    expression3.putPolynomialFirstWithMultiplication(polynomial);
    expression4.putPolynomialFirstWithMultiplication(polynomial);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term(100)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term("a")})),
                        Term("-"), Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term("b")})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term(100)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term("a")})),
                        Term("-"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term("b")}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term(200), Term("*"), Term("a"), Term("/"), Term("b")})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term(200), Term("*"), Term("a"), Term("/"), Term("b")}))
                    }));
    Expression subExpression(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutPolynomialSecondWithMultiplicationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialSecondWithMultiplication(polynomial);
    expression2.putPolynomialSecondWithMultiplication(polynomial);
    expression3.putPolynomialSecondWithMultiplication(polynomial);
    expression4.putPolynomialSecondWithMultiplication(polynomial);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(100), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term("a"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("-"), Term(createExpressionIfPossible({Term("b"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term(100), Term("*"), Term(Monomial(1, {{"y", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term("a"), Term("*"), Term(Monomial(1, {{"y", 1}}))})),
                        Term("-"), Term(createExpressionIfPossible({Term("b"), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b"), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression subExpression(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible({Term(subExpression), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorks)
{
    Expression subExpression1(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible({Term("c"), Term("^"), Term("d")}));
    Expression subExpression3(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression subExpression4(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression5(createExpressionIfPossible({Term("a"), Term("^"), Term("b"), Term("^"), Term("c"), Term("^"), Term("d")}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expression3(createExpressionIfPossible({Term(subExpression1), Term("/"), Term(subExpression2)}));
    Expression expression4(createExpressionIfPossible({Term(subExpression1), Term("^"), Term(subExpression2)}));
    Expression expression5(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2)}));

    Expression expressionToApply1(createExpressionIfPossible({Term(subExpression3), Term("-"), Term(subExpression4)}));
    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(subExpression3);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    {
                        Term(subExpression3), Term("-"), Term(subExpression4)
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression4)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("+"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("/"), Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression1), Term("/"), Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression5), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression5), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect5(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression3)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression2.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression3.putTermWithDivisionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithDivisionIfNeeded(noEffectTerm);
    expression2.putTermWithDivisionIfNeeded(noEffectTerm);
    expression3.putTermWithDivisionIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithDivisionIfNeeded(constant);
    expression2.putTermWithDivisionIfNeeded(constant);
    expression3.putTermWithDivisionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("/"), Term("interest"), Term("/"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("/"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("/"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("/"), Term("interest"), Term("/"), Term("x"), Term("*"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("/"), Term("x"), Term("*"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("/"), Term("interest"), Term("/"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression2, Term("/"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({expressionInExponent, Term("^"), Term(42)}));

    expression1.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(42));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression2.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression3.putTermWithRaiseToPowerIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithRaiseToPowerIfNeeded(constant);
    expression2.putTermWithRaiseToPowerIfNeeded(constant);
    expression3.putTermWithRaiseToPowerIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("^"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    expression1.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest"), Term("^"), Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression, Term("^"), Term("x"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(695), Term("^"), Term("interest"), Term("^"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible({subExpression2, Term("^"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermsWithDetailsWorks)
{
    Expression expressionToTest;
    TermsWithDetails termsWithDetails;
    termsWithDetails.emplace_back(Term(10), TermAssociationType::Negative);
    termsWithDetails.emplace_back(Term(20), TermAssociationType::Positive);
    termsWithDetails.emplace_back(Term(30), TermAssociationType::Positive);

    expressionToTest.putTermsWithDetails(termsWithDetails);

    TermsWithDetails termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(3u, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(0).association);
    EXPECT_EQ(Term(20), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(1).association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(2).association);
}

TEST(ExpressionTest, ReverseTheAssociationOfTheTermsWorks)
{
    Expression expression1;    Expression expression2(createExpressionIfPossible({Term(695)}));

    expression1.reverseTheAssociationOfTheTerms();
    expression2.reverseTheAssociationOfTheTerms();
    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithAssociation::TermsWithDetails const& termsToVerify1(expression1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithAssociation::TermsWithDetails const& termsToVerify2(expression2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify2.at(0).association);
    Term const& termToVerify(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(695), termToVerify);
}

TEST(ExpressionTest, SetWorks)
{
    Expression expression;
    TermsWithAssociation terms;
    TermsWithAssociation::TermWithDetails termWithDetails(Term(10), TermAssociationType::Positive);

    terms.putTermWithDetails(termWithDetails);
    terms.putTermWithDetails(termWithDetails);
    expression.set(OperatorLevel::AdditionAndSubtraction, terms);

    Expression expressionToExpect(createExpressionIfPossible({Term(10), Term("+"), Term(10)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SetTermWorks)
{
    Expression expression1(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression2(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible({Term(695), Term("*"), Term("interest")}));

    expression1.setTerm(Term());
    expression2.setTerm(Term(87));
    expression3.setTerm(Term(createExpressionIfPossible({Term(78), Term("+"), Term("energy")})));

    Expression expressionToExpect1(createExpressionIfPossible({Term()}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(87)}));
    Expression expressionToExpect3(createExpressionIfPossible({Term(78), Term("+"), Term("energy")}));
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

TEST(ExpressionTest, SetCommonOperatorLevelIfStillUnknownWorks)
{
    Expression expression1;
    Expression expression2;
    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);

    expression1.setCommonOperatorLevelIfStillUnknown(OperatorLevel::MultiplicationAndDivision);
    expression2.setCommonOperatorLevelIfStillUnknown(OperatorLevel::MultiplicationAndDivision);

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression2.getCommonOperatorLevel());
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants)
{
    Expression expressionToTest(createExpressionIfPossible({Term(100), Term("+"), Term(200), Term("-"), Term(50)}));

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(250)));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialFirstWithMultiplication)
{
    Expression expression1;    Expression expression2(createExpressionIfPossible({Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};    expression1.putPolynomialFirstWithMultiplication(polynomial);
    expression2.putPolynomialFirstWithMultiplication(polynomial);
    expression3.putPolynomialFirstWithMultiplication(polynomial);
    expression4.putPolynomialFirstWithMultiplication(polynomial);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})})));
    Expression expressionToExpect2(
                createOrCopyExpressionFromATerm(
                    Term(Polynomial{
                             Monomial(1, {{"a", 1}, {"x", 1}}),
                             Monomial(1, {{"a", 1}, {"y", 1}}),
                             Monomial(-1, {{"b", 1}, {"x", 1}}),
                             Monomial(-1, {{"b", 1}, {"y", 1}}),
                             Monomial(100, {{"x", 1}}),
                             Monomial(100, {{"y", 1}})
                         })));
    Expression expressionToExpect3(
                createOrCopyExpressionFromATerm(
                    Term(Polynomial{
                             Monomial(200, {{"a", 1}, {"b", -1}, {"x", 1}}),
                             Monomial(200, {{"a", 1}, {"b", -1}, {"y", 1}})
                         })));
    Expression subExpression(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Variable("x")), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Variable("y")), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialSecondWithMultiplication)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible({Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialSecondWithMultiplication(polynomial);
    expression2.putPolynomialSecondWithMultiplication(polynomial);
    expression3.putPolynomialSecondWithMultiplication(polynomial);
    expression4.putPolynomialSecondWithMultiplication(polynomial);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})})));
    Expression expressionToExpect2(
                createOrCopyExpressionFromATerm(
                    Term(Polynomial{
                             Monomial(1, {{"a", 1}, {"x", 1}}),
                             Monomial(1, {{"a", 1}, {"y", 1}}),
                             Monomial(-1, {{"b", 1}, {"x", 1}}),
                             Monomial(-1, {{"b", 1}, {"y", 1}}),
                             Monomial(100, {{"x", 1}}),
                             Monomial(100, {{"y", 1}})
                         })));
    Expression expressionToExpect3(
                createOrCopyExpressionFromATerm(
                    Term(Polynomial{
                             Monomial(200, {{"a", 1}, {"b", -1}, {"x", 1}}),
                             Monomial(200, {{"a", 1}, {"b", -1}, {"y", 1}})
                         })));
    Expression subExpression(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(Variable("x")), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Variable("y")), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutExpressionWithMultiplication)
{
    Expression subExpression1(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible({Term("c"), Term("^"), Term("d")}));
    Expression subExpression3(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression subExpression4(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression5(
                createExpressionIfPossible(
                    {
                        Term("a"), Term("^"), Term(createExpressionIfPossible({Term(Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}}))}))
                    }));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expression3(createExpressionIfPossible({Term(subExpression1), Term("/"), Term(subExpression2)}));
    Expression expression4(createExpressionIfPossible({Term(subExpression1), Term("^"), Term(subExpression2)}));
    Expression expression5(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expressionToApply1(createExpressionIfPossible({Term(subExpression3), Term("-"), Term(subExpression4)}));
    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(subExpression3);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    {
                        Term(subExpression3), Term("-"), Term(subExpression4)
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression4)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("+"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression3), Term("/"), Term(subExpression2)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression4), Term("/"), Term(subExpression2)}))
                    }));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression5), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression5), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect5(
                createExpressionIfPossible(
                    {
                        Term(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible({Term(subExpression2), Term("*"), Term(subExpression3)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, SortWorks)
{
    Expression expression(                createExpressionIfPossible(
                    {
                        Term("-"), Term(2),
                        Term("-"), Term(3),                        Term("+"), Term(4),
                        Term("+"), Term(5),
                        Term("-"),
                        Term(Polynomial{
                            Monomial(100, {}),
                            Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}),
                            Monomial(9, {{"x", 8}}),
                            Monomial(10, {})})
                    }));

    expression.sort();

    Expression expressionToExpect(
                createExpressionIfPossible(
                    {
                        Term("+"), Term(4),
                        Term("+"), Term(5),
                        Term("-"), Term(2),
                        Term("-"), Term(3),
                        Term("-"),
                        Term(Polynomial{
                            Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}),
                            Monomial(9, {{"x", 8}}),
                            Monomial(100, {}),
                            Monomial(10, {})})
                    }));
    EXPECT_EQ(expressionToExpect, expression);
}

}

}