#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Utilities.hpp>

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
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(5)}));
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

TEST(ExpressionTest, GetTermsWithAssociationWorks)
{
    Expression expression(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

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
    Expression expression(createExpressionIfPossible(Terms{Term("x"), Term("+"), Term("y"), Term("-"), Term("z")}));

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
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression3;
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(96)));
    Expression expression4(createExpressionIfPossible(Terms{Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("()", expression1.getDisplayableString());
    EXPECT_EQ("(695-interest+debt)", expression2.getDisplayableString());
    EXPECT_EQ("(1/96)", expression3.getDisplayableString());
    EXPECT_EQ("((695-interest+debt)^cash)", expression4.getDisplayableString());
}

TEST(ExpressionTest, GetDebugStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));
    Expression expression3;
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(96)));
    Expression expression4(createExpressionIfPossible(Terms{Term(expression2), Term("^"), Term("cash")}));

    EXPECT_EQ("( [?]|| )", expression1.getDebugString());
    EXPECT_EQ("( [+-]||695[Constant][POS]-interest[Variable][NEG]+debt[Variable][POS] )", expression2.getDebugString());
    EXPECT_EQ("( [*/]||1/96[Constant][NEG] )", expression3.getDebugString());
    EXPECT_EQ("( [^]||( [+-]||695[Constant][POS]-interest[Variable][NEG]+debt[Variable][POS] )[Expression][POS]^cash[Variable][POS] )", expression4.getDebugString());
}

TEST(ExpressionTest, ClearWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest"), Term("+"), Term("debt")}));

    expression1.clear();
    expression2.clear();

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_TRUE(expression2.isEmpty());
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

TEST(ExpressionTest, PutTermWithAdditionUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression2.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression3.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("+"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("+"), Term("x"), Term("-"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("+"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(subExpression2), Term("+"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term noEffectTerm(Constant(0));
    expression1.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression2.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression3.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(constant));

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

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest"), Term("-"), Term("x"), Term("+"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("-"), Term("x"), Term("+"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

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

TEST(ExpressionTest, PutTermWithMultiplicationUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression2.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression3.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("*"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term("x"), Term("/"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("*"), Term("x"), Term("/"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest"), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("*"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutPolynomialFirstWithMultiplicationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialFirstWithMultiplication(polynomial);
    expression2.putPolynomialFirstWithMultiplication(polynomial);
    expression3.putPolynomialFirstWithMultiplication(polynomial);
    expression4.putPolynomialFirstWithMultiplication(polynomial);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term(100)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term("a")})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term("b")})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}})), Term("*"), Term(100)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}})), Term("*"), Term("a")})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}})), Term("*"), Term("b")}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term(200), Term("*"), Term("a"), Term("/"), Term("b")})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}})), Term("*"), Term(200), Term("*"), Term("a"), Term("/"), Term("b")}))
                    }));
    Expression subExpression(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}})), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutPolynomialSecondWithMultiplicationWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialSecondWithMultiplication(polynomial);
    expression2.putPolynomialSecondWithMultiplication(polynomial);
    expression3.putPolynomialSecondWithMultiplication(polynomial);
    expression4.putPolynomialSecondWithMultiplication(polynomial);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(100), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term("a"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term("b"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(100), Term("*"), Term(Monomial(1, {{"y", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term("a"), Term("*"), Term(Monomial(1, {{"y", 1}}))})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term("b"), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b"), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b"), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    Expression subExpression(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression), Term("*"), Term(Monomial(1, {{"x", 1}}))})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(subExpression), Term("*"), Term(Monomial(1, {{"y", 1}}))}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorks)
{
    Expression subExpression1(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term("c"), Term("^"), Term("d")}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
    Expression subExpression4(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression subExpression5(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b"), Term("^"), Term("c"), Term("^"), Term("d")}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(subExpression1), Term("/"), Term(subExpression2)}));
    Expression expression4(createExpressionIfPossible(Terms{Term(subExpression1), Term("^"), Term(subExpression2)}));
    Expression expression5(createExpressionIfPossible(Terms{Term(subExpression1), Term("-"), Term(subExpression2)}));

    Expression expressionToApply1(createExpressionIfPossible(Terms{Term(subExpression3), Term("-"), Term(subExpression4)}));
    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(subExpression3);

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    Terms{
                        Term(subExpression3), Term("-"), Term(subExpression4)
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression4)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("/"), Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("/"), Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression5), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression5), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect5(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression3)}))
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
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression2.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(constant));

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

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expression1.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("/"), Term("y")}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest"), Term("/"), Term("x"), Term("*"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("/"), Term("x"), Term("*"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("/"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("-"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

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

TEST(ExpressionTest, PutTermWithRaiseToPowerWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionInExponent(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{expressionInExponent, Term("^"), Term(42)}));

    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(42)));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(42)));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(42)));

    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression nullExpression;
    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(nullExpression)));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term noEffectTerm(Constant(1));
    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(noEffectTerm));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingConstantWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Term constant(42);
    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(constant));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(constant));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(42)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(42)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("^"), Term(42)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));
    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term("x"), Term("^"), Term("y")}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression, Term("^"), Term("x"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));

    Expression expressionToApply(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    expression1.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(expressionToApply));

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(695), Term("+"), Term("interest")}));
    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("x"), Term("-"), Term("y")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(695), Term("^"), Term("interest"), Term("^"), Term(subExpression1)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{subExpression2, Term("^"), Term(subExpression1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, ReverseTheAssociationOfTheTermsWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(695)}));

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
    TermsWithAssociation::TermWithDetails termWithDetails(
                getBaseTermConstReferenceFromTerm(Term(10)),
                TermAssociationType::Positive);

    terms.putTermWithDetails(termWithDetails);
    terms.putTermWithDetails(termWithDetails);
    expression.set(OperatorLevel::AdditionAndSubtraction, terms);

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(10), Term("+"), Term(10)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SetTermWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression2(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(695), Term("*"), Term("interest")}));

    expression1.setTerm(Term());
    expression2.setTerm(Term(87));
    expression3.setTerm(Term(createExpressionIfPossible(Terms{Term(78), Term("+"), Term("energy")})));

    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term()}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(87)}));
    Expression expressionToExpect3(createExpressionIfPossible(Terms{Term(78), Term("+"), Term("energy")}));
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

TEST(ExpressionTest, SimplifyWorksOnSingleTermExpression)
{
    Term expressionTerm(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
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

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingNullExpressions)
{
    Expression nullExpression(createExpressionInAnExpression(Expression()));
    Expression expression(createExpressionIfPossible(Terms{nullExpression, Term("+"), nullExpression, Term("+"), nullExpression}));

    expression.simplify();

    Expression expressionToExpect;
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnZeroForAddingAndSubtracting)
{
    Expression expression(createExpressionIfPossible(Terms{Term(Constant(0)), Term("-"), Term(200), Term("-"), Term(50), Term("-"), Term(Constant(0))}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(-250)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnZeroForMultiplying)
{
    Expression expression(createExpressionIfPossible(Terms{Term(Constant(0)), Term("*"), Term(200), Term("*"), Term(50)}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(Constant(0))}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnZeroForMultiplyingWithRaiseToPowerExpression)
{
    Expression expression(createExpressionIfPossible(Terms{Term(Constant(0)), Term("*"), Term("z"), Term("^"), Term("z")}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(Constant(0))}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants)
{
    Expression expression(createExpressionIfPossible(Terms{Term(100), Term("+"), Term(200), Term("-"), Term(50)}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(250)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsMonomialPolynomial)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(Monomial(43, {{"x", 2}, {"y", 3}})),
                        Term("+"), Term(159),
                        Term("-"), Term(Polynomial{
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
                            Monomial(-56, {{"x", 3}}),
                            Monomial(410, {})
                        })}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsWithExpressionInBetween)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(500),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(150)
                    }));

    expression.simplify();

    Expression subExpression(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(350), Term("+"), Term(subExpression)}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingZerosWithExpressionInBetween)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(Constant(0)),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"),  Term(Constant(0))
                    }));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressions)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(5), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(3), Term("*"), Term("y"), Term("^"), Term("y")
                    }));

    expression.simplify();

    Expression subExpression(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(3), Term("*"), Term(subExpression)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("^"), Term("y"),
                        Term("-"), Term(2), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(3), Term("*"), Term("x"), Term("^"), Term("y"),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term(4), Term("*"), Term("x"), Term("^"), Term("y"),
                        Term("+"), Term(5), Term("*"), Term("y"), Term("^"), Term("y")
                    }));

    expression.simplify();

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression4(createExpressionIfPossible(Terms{Term(4), Term("*"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(subExpression3), Term("+"), Term(subExpression4)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(100), Term("*"), Term("y"), Term("^"), Term("y"), Term("*"), Term("x"), Term("^"), Term("x"),
                        Term("-"), Term(10), Term("*"), Term("x"), Term("^"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")
                    }));

    expression.simplify();

    Expression subExpression1(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(90), Term("*"), Term(subExpression3)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(8), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(6), Term("*"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")
                    }));

    expression.simplify();

    Expression subExpression1(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term(Monomial(-5, {{"x", 1}})), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(subExpression2), Term("+"), Term(subExpression3)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnMultiplyingAndDividingConstants)
{
    Expression expression(createExpressionIfPossible(Terms{Term(100), Term("*"), Term(200), Term("/"), Term(50)}));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(400)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnMultiplyingAndDividingPolynomials)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term(Polynomial{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})}),
                        Term("/"),
                        Term(Polynomial{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})})
                    }));

    expression.simplify();

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(Polynomial{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})}),
                        Term("/"),
                        Term(Polynomial{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})})
                    }));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnMultiplyingAndDividingRaiseToPowerExpressionsCanBeCancelled)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("^"), Term("x"),
                        Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("*"), Term("z"), Term("^"), Term("z"),
                        Term("/"), Term("z"), Term("^"), Term("z"),
                        Term("/"), Term("y"), Term("^"), Term("y"),
                        Term("/"), Term("x"), Term("^"), Term("x")
                    }));

    expression.simplify();

    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(1)}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialFirstWithMultiplication)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialFirstWithMultiplication(polynomial);
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
    Expression subExpression(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Variable("x")), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Variable("y")), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialSecondWithMultiplication)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(100), Term("+"), Term("a"), Term("-"), Term("b")}));
    Expression expression3(createExpressionIfPossible(Terms{Term(200), Term("*"), Term("a"), Term("/"), Term("b")}));
    Expression expression4(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
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
    Expression subExpression(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Variable("x")), Term("*"), Term(subExpression)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(Variable("y")), Term("*"), Term(subExpression)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutExpressionWithMultiplication)
{
    Expression subExpression1(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term("c"), Term("^"), Term("d")}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("x")}));
    Expression subExpression4(createExpressionIfPossible(Terms{Term("y"), Term("^"), Term("y")}));
    Expression subExpression5(
                createExpressionIfPossible(
                    Terms{
                        Term("a"), Term("^"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}}))}))
                    }));
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expression3(createExpressionIfPossible(Terms{Term(subExpression1), Term("/"), Term(subExpression2)}));
    Expression expression4(createExpressionIfPossible(Terms{Term(subExpression1), Term("^"), Term(subExpression2)}));
    Expression expression5(createExpressionIfPossible(Terms{Term(subExpression1), Term("-"), Term(subExpression2)}));
    Expression expressionToApply1(createExpressionIfPossible(Terms{Term(subExpression3), Term("-"), Term(subExpression4)}));
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
                    Terms{
                        Term(subExpression3), Term("-"), Term(subExpression4)
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression4)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression3)})),
                        Term("+"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect3(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression3), Term("/"), Term(subExpression2)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression4), Term("/"), Term(subExpression2)}))
                    }));
    Expression expressionToExpect4(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression5), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression5), Term("*"), Term(subExpression4)}))
                    }));
    Expression expressionToExpect5(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(subExpression1), Term("*"), Term(subExpression3)})),
                        Term("-"), Term(createExpressionIfPossible(Terms{Term(subExpression2), Term("*"), Term(subExpression3)}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, SimplifyWorksOnRaiseToPowerIfBaseIsOneOrZero)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(1), Term("^"), Term("a"), Term("^"), Term("b")}));
    Expression expression2(createExpressionIfPossible(Terms{Term(Constant(0)), Term("^"), Term("c"), Term("^"), Term("d")}));

    expression1.simplify();
    expression2.simplify();

    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(1)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(Constant(0))}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

TEST(ExpressionTest, SimplifyWorksOnRaiseToPowerIfExponentIsOne)
{
    Expression expression1(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term(1)}));
    Expression expression2(createExpressionIfPossible(Terms{Term("b"), Term("^"), Term(1), Term("^"), Term(1), Term("^"), Term(1)}));

    expression1.simplify();
    expression2.simplify();

    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term("a")}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term("b")}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

TEST(ExpressionTest, SimplifyWorksOnRaiseToPowerIfExponentIsZero)
{
    Expression expression1(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term(Constant(0))}));
    Expression expression2(createExpressionIfPossible(Terms{Term("b"), Term("^"), Term("a"), Term("^"), Term(Constant(0)), Term("^"), Term("b")}));

    expression1.simplify();
    expression2.simplify();

    Expression expressionToExpect1(createExpressionIfPossible(Terms{Term(1)}));
    Expression expressionToExpect2(createExpressionIfPossible(Terms{Term(1)}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

TEST(ExpressionTest, SimplifyWorksOnRaiseToPowerWithMultipleTerms)
{
    Expression expression1(createExpressionIfPossible(Terms{Term("a"), Term("^"), Term("b"), Term("^"), Term("c"), Term("^"), Term("d")}));
    Expression expression2(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term(2), Term("^"), Term(3), Term("^"), Term("y")}));

    expression1.simplify();
    expression2.simplify();

    Expression expressionToExpect1(
                createExpressionIfPossible(
                    Terms{
                        Term("a"), Term("^"), Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}}))}))
                    }));
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("^"), Term(createExpressionIfPossible(Terms{Term(Monomial(6, {{"y", 1}}))}))
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

TEST(ExpressionTest, SimplifyToACommonDenominatorWorks)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));

    expression.simplifyToACommonDenominator();

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})}),
                        Term("/"),
                        Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}),
                    }));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SortWorks)
{
    Expression expression(
                createExpressionIfPossible(
                    Terms{
                        Term("-"), Term(2),
                        Term("-"), Term(3),
                        Term("+"), Term(4),
                        Term("+"), Term(5),
                        Term("-"), Term(Polynomial{Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})})
                    }));

    expression.sort();

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("+"), Term(4),
                        Term("+"), Term(5),
                        Term("-"), Term(2),
                        Term("-"), Term(3),
                        Term("-"), Term(Polynomial{Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(100, {}), Monomial(10, {})})
                    }));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SubstituteVariablesToValuesWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible(Terms{Term("x"), Term("^"), Term("y")}));

    expression1.substituteVariablesToValues({{"x", 2}, {"y", 5}});
    expression2.substituteVariablesToValues({{"x", 2}, {"y", 5}});

    Expression expressionToExpect1;
    Expression expressionToExpect2(
                createExpressionIfPossible(
                    Terms{
                        Term(2), Term("^"), Term(5)
                    }));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

}

}
