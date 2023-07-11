#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(ExpressionTest, ConstructionWorks) {
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Negative);
    Expression expression1;
    Expression expression2(Term(12));
    Expression expression3(OperatorLevel::AdditionAndSubtraction, {});
    Expression expression4(OperatorLevel::AdditionAndSubtraction, {termWithDetails1, termWithDetails2});

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expression1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expression2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2[0].association);
    Term const& termToVerify(getTermConstReferenceFromUniquePointer(termsToVerify2[0].baseTermPointer));
    EXPECT_EQ(Term(12), termToVerify);
    EXPECT_EQ(OperatorLevel::Unknown, expression3.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify3(expression3.getTermsWithAssociation().getTermsWithDetails());
    EXPECT_TRUE(termsToVerify3.empty());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression4.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify4(expression4.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify4.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify4[0].association);
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify4[0].baseTermPointer));
    EXPECT_EQ(Term(10), termToVerify2);
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify4[1].association);
    Term const& termToVerify3(getTermConstReferenceFromUniquePointer(termsToVerify4[1].baseTermPointer));
    EXPECT_EQ(Term(20), termToVerify3);
}

TEST(ExpressionTest, ExpressionThatIsDefaultConstructedHasIsSimplifiedFlagNotSet) {
    Expression expression;

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsCopyConstructedHasIsSimplifiedFlagCopied) {
    Expression expressionWithSimplifiedNotSet;
    Expression expressionWithSimplifiedSet;
    expressionWithSimplifiedSet.setAsSimplified();

    Expression const& expression1(expressionWithSimplifiedNotSet);
    Expression expression2(expressionWithSimplifiedSet);

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsConstructedWithTermsWithDetailsHasIsSimplifiedFlagNotSet) {
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Negative);
    Expression expression(OperatorLevel::AdditionAndSubtraction, {termWithDetails1, termWithDetails2});

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, EqualityOperatorWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+", "interest"})}));
    Expression expression3(createExpressionIfPossible({6, "+", "interest"}));
    Expression expression4(createExpressionIfPossible({5}));
    Expression expression5(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+"})}));
    Expression expression6(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+", "interest"})}));

    EXPECT_TRUE(expression1 == expression1);
    EXPECT_FALSE(expression1 == expression2);
    EXPECT_TRUE(expression2 == expression2);
    EXPECT_FALSE(expression2 == expression3);
    EXPECT_FALSE(expression2 == expression4);
    EXPECT_FALSE(expression2 == expression5);
    EXPECT_TRUE(expression2 == expression6);
}

TEST(ExpressionTest, InequalityOperatorWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+", "interest"})}));
    Expression expression3(createExpressionIfPossible({6, "+", "interest"}));
    Expression expression4(createExpressionIfPossible({5}));
    Expression expression5(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+"})}));
    Expression expression6(createExpressionIfPossible({5, "+", createExpressionIfPossible({5, "+", "interest"})}));

    EXPECT_FALSE(expression1 != expression1);
    EXPECT_TRUE(expression1 != expression2);
    EXPECT_FALSE(expression2 != expression2);
    EXPECT_TRUE(expression2 != expression3);
    EXPECT_TRUE(expression2 != expression4);
    EXPECT_TRUE(expression2 != expression5);
    EXPECT_FALSE(expression2 != expression6);
}

TEST(ExpressionTest, LessThanOperatorWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({6, "+", "interest"}));
    Expression expression3(createExpressionIfPossible({6}));
    Expression expression4(createExpressionIfPossible({6, "+", "interest", "+", "debt"}));
    Expression expression5(createExpressionIfPossible({5, "+", "interest"}));
    Expression expression6(createExpressionIfPossible({7, "+", "interest"}));

    EXPECT_FALSE(expression1 < expression1);
    EXPECT_FALSE(expression2 < expression2);
    EXPECT_FALSE(expression2 < expression3);
    EXPECT_TRUE(expression2 < expression4);
    EXPECT_FALSE(expression2 < expression5);
    EXPECT_TRUE(expression2 < expression6);
}

TEST(ExpressionTest, IsEmptyWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({5}));
    Expression expression3(createExpressionIfPossible({6, "+", "interest"}));

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_FALSE(expression2.isEmpty());
    EXPECT_FALSE(expression3.isEmpty());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({5}));
    Expression expression3(createExpressionIfPossible({"-", 5}));
    Expression expression4(createExpressionIfPossible({6, "+", "interest"}));

    EXPECT_FALSE(expression1.containsOnlyOnePositivelyAssociatedTerm());
    EXPECT_TRUE(expression2.containsOnlyOnePositivelyAssociatedTerm());
    EXPECT_FALSE(expression3.containsOnlyOnePositivelyAssociatedTerm());
    EXPECT_FALSE(expression4.containsOnlyOnePositivelyAssociatedTerm());
}

TEST(ExpressionTest, IsSimplifiedWorks) {
    Expression expression1;
    Expression expression2;
    expression2.setAsSimplified();

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, GetCommonOperatorLevelWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({5}));
    Expression expression3(createExpressionIfPossible({6, "+", "interest"}));
    Expression expression4(createExpressionIfPossible({6, "-", "interest"}));
    Expression expression5(createExpressionIfPossible({6, "*", "interest"}));
    Expression expression6(createExpressionIfPossible({6, "/", "interest"}));
    Expression expression7(createExpressionIfPossible({6, "^", "interest"}));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression3.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression4.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression5.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression6.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::RaiseToPower, expression7.getCommonOperatorLevel());
}

TEST(ExpressionTest, GetFirstTermWorks) {
    Expression expression1(createExpressionIfPossible({5412}));
    Expression expression2(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression3(createExpressionIfPossible({"-", 16}));

    EXPECT_EQ(Term(5412), getTermConstReferenceFromBaseTerm(expression1.getFirstTerm()));
    EXPECT_EQ(Term(695), getTermConstReferenceFromBaseTerm(expression2.getFirstTerm()));
    EXPECT_EQ(Term(16), getTermConstReferenceFromBaseTerm(expression3.getFirstTerm()));
}

TEST(ExpressionTest, GetFirstAssociationTypeWorks) {    Expression expression1(createExpressionIfPossible({5412}));
    Expression expression2(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression3(createExpressionIfPossible({"-", 16}));
    EXPECT_EQ(TermAssociationType::Positive, expression1.getFirstAssociationType());
    EXPECT_EQ(TermAssociationType::Positive, expression2.getFirstAssociationType());
    EXPECT_EQ(TermAssociationType::Negative, expression3.getFirstAssociationType());
}

TEST(ExpressionTest, GetTermsWithAssociationWorks) {
    Expression expression(createExpressionIfPossible({695, "-", "interest", "+", "debt"}));

    TermsWithAssociation const& terms(expression.getTermsWithAssociation());
    TermsWithDetails const& termsWithDetailsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(3U, termsWithDetailsToVerify.size());
    EXPECT_EQ(Term(695), getTermConstReferenceFromUniquePointer(termsWithDetailsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetailsToVerify[0].association);
    EXPECT_EQ(Term("interest"), getTermConstReferenceFromUniquePointer(termsWithDetailsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetailsToVerify[1].association);
    EXPECT_EQ(Term("debt"), getTermConstReferenceFromUniquePointer(termsWithDetailsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetailsToVerify[2].association);
}

TEST(ExpressionTest, GetDebugStringWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({695, "-", "interest", "+", "debt"}));
    Expression expression3;
    expression3.putTermWithDivisionIfNeeded(Term(96));
    Expression expression4(createExpressionIfPossible({expression2, "^", "cash"}));

    EXPECT_EQ("( {?}|| )", expression1.getDebugString());
    EXPECT_EQ("( {+-}||695{Constant}{POS}-interest{Variable}{NEG}+debt{Variable}{POS} )", expression2.getDebugString());
    EXPECT_EQ("( {*/}||1/96{Constant}{NEG} )", expression3.getDebugString());
    EXPECT_EQ(
        "( {^}||( {+-}||695{Constant}{POS}-interest{Variable}{NEG}+debt{Variable}{POS} "
        "){Expression}{POS}^cash{Variable}{POS} )",
        expression4.getDebugString());
}

TEST(ExpressionTest, ClearWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({695, "-", "interest", "+", "debt"}));

    expression1.clear();
    expression2.clear();

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_TRUE(expression2.isEmpty());
}

TEST(ExpressionTest, ClearAndPutTermInTermsWithAssociationWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({695, "-", "interest", "+", "debt"}));

    expression1.clearAndPutTermInTermsWithAssociation(Term(24));
    expression2.clearAndPutTermInTermsWithAssociation(Term(65));

    EXPECT_EQ(createExpressionIfPossible({24}), expression1);
    EXPECT_EQ(createExpressionIfPossible({65}), expression2);
}

TEST(ExpressionTest, PutTermWithAdditionUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression nullExpression;
    expression1.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression2.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression3.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression4.putTermWithAdditionIfNeeded(Term(nullExpression));
    expression5.putTermWithAdditionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "*", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAdditionUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Term noEffectTerm(0);
    expression1.putTermWithAdditionIfNeeded(noEffectTerm);
    expression2.putTermWithAdditionIfNeeded(noEffectTerm);
    expression3.putTermWithAdditionIfNeeded(noEffectTerm);
    expression4.putTermWithAdditionIfNeeded(noEffectTerm);
    expression5.putTermWithAdditionIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "*", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression2);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAdditionUsingConstantWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Term constant(42);
    expression1.putTermWithAdditionIfNeeded(constant);
    expression2.putTermWithAdditionIfNeeded(constant);
    expression3.putTermWithAdditionIfNeeded(constant);
    expression4.putTermWithAdditionIfNeeded(constant);
    expression5.putTermWithAdditionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    Expression expressionToExpect2(createExpressionIfPossible({42}));
    Expression expressionToExpect3(createExpressionIfPossible({42}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "+", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "+", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "-", "y"}));
    expression1.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression4.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression5.putTermWithAdditionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "-", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({"x", "-", "y"}));
    Expression expressionToExpect3(createExpressionIfPossible({"x", "-", "y"}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "+", "x", "-", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "+", "x", "-", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAdditionUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "/", "y"}));
    expression1.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression2.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression3.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression4.putTermWithAdditionIfNeeded(Term(expressionToApply));
    expression5.putTermWithAdditionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"x", "/", "y"}));
    Expression subExpression2(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "/", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({"x", "/", "y"}));
    Expression expressionToExpect3(createExpressionIfPossible({"x", "/", "y"}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "+", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "+", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression nullExpression;
    expression1.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression2.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression3.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression4.putTermWithSubtractionIfNeeded(Term(nullExpression));
    expression5.putTermWithSubtractionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "*", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Term noEffectTerm(0);
    expression1.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression2.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression3.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression4.putTermWithSubtractionIfNeeded(noEffectTerm);
    expression5.putTermWithSubtractionIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(0));
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "*", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingConstantWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Term constant(42);
    expression1.putTermWithSubtractionIfNeeded(constant);
    expression2.putTermWithSubtractionIfNeeded(constant);
    expression3.putTermWithSubtractionIfNeeded(constant);
    expression4.putTermWithSubtractionIfNeeded(constant);
    expression5.putTermWithSubtractionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(expressionToExpect1);
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "-", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "-", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "-", "y"}));
    expression1.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression4.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression5.putTermWithSubtractionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "-", "y"}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(expressionToExpect1);
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "-", "x", "+", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "-", "x", "+", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithSubtractionUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(0));
    Expression expression3(createExpressionIfPossible({"-", 0}));
    Expression expression4(createExpressionIfPossible({695, "+", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "*", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "/", "y"}));
    expression1.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression2.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression3.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression4.putTermWithSubtractionIfNeeded(Term(expressionToApply));
    expression5.putTermWithSubtractionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"x", "/", "y"}));
    Expression subExpression2(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(expressionToExpect1);
    Expression expressionToExpect4(createExpressionIfPossible({695, "+", "interest", "-", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "-", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression nullExpression;
    expression1.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression2.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression3.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression4.putTermWithMultiplicationIfNeeded(Term(nullExpression));
    expression5.putTermWithMultiplicationIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "+", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Term noEffectTerm(1);
    expression1.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression2.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression3.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression4.putTermWithMultiplicationIfNeeded(noEffectTerm);
    expression5.putTermWithMultiplicationIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "+", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingConstantWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Term constant(42);
    expression1.putTermWithMultiplicationIfNeeded(constant);
    expression2.putTermWithMultiplicationIfNeeded(constant);
    expression3.putTermWithMultiplicationIfNeeded(constant);
    expression4.putTermWithMultiplicationIfNeeded(constant);
    expression5.putTermWithMultiplicationIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    Expression expressionToExpect2(createExpressionIfPossible({42}));
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "*", 42}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "*", "interest", "*", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "*", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "/", "y"}));
    expression1.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression4.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression5.putTermWithMultiplicationIfNeeded(Term(expressionToApply));

    Expression expressionToExpect1(createExpressionIfPossible({"x", "/", "y"}));
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "*", expressionToExpect1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "*", "interest", "*", "x", "/", "y"}));
    Expression expressionToExpect5(
        createExpressionIfPossible({695, "*", "x", "/", "y", "+", "interest", "*", "x", "/", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithMultiplicationUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "-", "y"}));
    expression1.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression2.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression3.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression4.putTermWithMultiplicationIfNeeded(Term(expressionToApply));
    expression5.putTermWithMultiplicationIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"x", "-", "y"}));
    Expression subExpression2(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "-", "y"}));
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "*", expressionToExpect1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "*", "interest", "*", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "*", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "-", "interest"}));

    Expression nullExpression;
    expression1.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression2.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression3.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression4.putTermWithDivisionIfNeeded(Term(nullExpression));
    expression5.putTermWithDivisionIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "-", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "-", "interest"}));

    Term noEffectTerm(1);
    expression1.putTermWithDivisionIfNeeded(noEffectTerm);
    expression2.putTermWithDivisionIfNeeded(noEffectTerm);
    expression3.putTermWithDivisionIfNeeded(noEffectTerm);
    expression4.putTermWithDivisionIfNeeded(noEffectTerm);
    expression5.putTermWithDivisionIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "-", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingConstantWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "-", "interest"}));

    Term constant(42);
    expression1.putTermWithDivisionIfNeeded(constant);
    expression2.putTermWithDivisionIfNeeded(constant);
    expression3.putTermWithDivisionIfNeeded(constant);
    expression4.putTermWithDivisionIfNeeded(constant);
    expression5.putTermWithDivisionIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({695, "-", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "/", 42}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "/", "interest", "/", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "/", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "-", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "/", "y"}));
    expression1.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression4.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression5.putTermWithDivisionIfNeeded(Term(expressionToApply));

    Expression subExpression(createExpressionIfPossible({695, "-", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "/", "y"}));
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "/", expressionToApply}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "/", "interest", "/", "x", "*", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "/", "x", "*", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithDivisionUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "/", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "-", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "-", "y"}));
    expression1.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression2.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression3.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression4.putTermWithDivisionIfNeeded(Term(expressionToApply));
    expression5.putTermWithDivisionIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"x", "-", "y"}));
    Expression subExpression2(createExpressionIfPossible({695, "-", "interest"}));
    Expression expressionToExpect1(createExpressionInAnExpression(subExpression1));
    expressionToExpect1.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    expressionToExpect1.reverseTheAssociationOfTheTerms();
    Expression expressionToExpect2(expressionToExpect1);
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "/", expressionToApply}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "/", "interest", "/", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "/", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    expression1.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression4.putTermWithRaiseToPowerIfNeeded(Term(42));
    expression5.putTermWithRaiseToPowerIfNeeded(Term(42));

    Expression expressionInExponent(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    Expression expressionToExpect2(createExpressionIfPossible({1, "^", 42}));
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "^", 42}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest", "^", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({expressionInExponent, "^", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression nullExpression;
    expression1.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression4.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));
    expression5.putTermWithRaiseToPowerIfNeeded(Term(nullExpression));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "+", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Term noEffectTerm(1);
    expression1.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression2.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression3.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression4.putTermWithRaiseToPowerIfNeeded(noEffectTerm);
    expression5.putTermWithRaiseToPowerIfNeeded(noEffectTerm);

    Expression expressionToExpect1;
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expressionToExpect5(createExpressionIfPossible({695, "+", "interest"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingConstantWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Term constant(42);
    expression1.putTermWithRaiseToPowerIfNeeded(constant);
    expression2.putTermWithRaiseToPowerIfNeeded(constant);
    expression3.putTermWithRaiseToPowerIfNeeded(constant);
    expression4.putTermWithRaiseToPowerIfNeeded(constant);
    expression5.putTermWithRaiseToPowerIfNeeded(constant);

    Expression subExpression(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({42}));
    Expression expressionToExpect2(createExpressionIfPossible({1, "^", 42}));
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "^", 42}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest", "^", 42}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression, "^", 42}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "^", "y"}));
    expression1.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression4.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression5.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "^", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({1, "^", createExpressionIfPossible({"x", "^", "y"})}));
    Expression expressionToExpect3(
        createExpressionIfPossible({"(", "-", 1, ")", "^", createExpressionIfPossible({"x", "^", "y"})}));
    Expression expressionToExpect4(
        createExpressionIfPossible({695, "^", "interest", "^", createExpressionIfPossible({"x", "^", "y"})}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression1, "^", "x", "^", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(1));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "-", "y"}));
    expression1.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression4.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression5.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"x", "-", "y"}));
    Expression subExpression2(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"x", "-", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({1, "^", subExpression1}));
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "^", subExpression1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest", "^", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "^", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithRaiseToPowerUsingExpressionWithNegativeAssociationExpression) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(2));
    Expression expression3(createExpressionIfPossible({"-", 1}));
    Expression expression4(createExpressionIfPossible({695, "^", "interest"}));
    Expression expression5(createExpressionIfPossible({695, "+", "interest"}));

    Expression expressionToApply(createExpressionIfPossible({"-", "5"}));
    expression1.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression2.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression3.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression4.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));
    expression5.putTermWithRaiseToPowerIfNeeded(Term(expressionToApply));

    Expression subExpression1(createExpressionIfPossible({"-", "5"}));
    Expression subExpression2(createExpressionIfPossible({695, "+", "interest"}));
    Expression expressionToExpect1(createExpressionIfPossible({"-", "5"}));
    Expression expressionToExpect2(createExpressionIfPossible({2, "^", subExpression1}));
    Expression expressionToExpect3(createExpressionIfPossible({"(", "-", 1, ")", "^", subExpression1}));
    Expression expressionToExpect4(createExpressionIfPossible({695, "^", "interest", "^", subExpression1}));
    Expression expressionToExpect5(createExpressionIfPossible({subExpression2, "^", subExpression1}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutPolynomialFirstWithMultiplicationWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({100, "+", "a", "-", "b"}));
    Expression expression3(createExpressionIfPossible({200, "*", "a", "/", "b"}));
    Expression expression4(createExpressionIfPossible({"a", "^", "b"}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialFirstWithMultiplication(polynomial);
    expression2.putPolynomialFirstWithMultiplication(polynomial);
    expression3.putPolynomialFirstWithMultiplication(polynomial);
    expression4.putPolynomialFirstWithMultiplication(polynomial);

    Expression expressionToExpect1(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}})})}));
    Expression expressionToExpect2(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 100}), "+",
         createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", "a"}), "-",
         createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", "b"}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", 100}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", "a"}), "-",
         createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", "b"})}));
    Expression expressionToExpect3(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 200, "*", "a", "/", "b"}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", 200, "*", "a", "/", "b"})}));
    Expression subExpression(createExpressionIfPossible({"a", "^", "b"}));
    Expression expressionToExpect4(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", subExpression}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", subExpression})}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutPolynomialSecondWithMultiplicationWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({100, "+", "a", "-", "b"}));
    Expression expression3(createExpressionIfPossible({200, "*", "a", "/", "b"}));
    Expression expression4(createExpressionIfPossible({"a", "^", "b"}));

    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialSecondWithMultiplication(polynomial);
    expression2.putPolynomialSecondWithMultiplication(polynomial);
    expression3.putPolynomialSecondWithMultiplication(polynomial);
    expression4.putPolynomialSecondWithMultiplication(polynomial);

    Expression expressionToExpect1(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({Monomial(1, {{"y", 1}})})}));
    Expression expressionToExpect2(createExpressionIfPossible(
        {createExpressionIfPossible({100, "*", Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({"a", "*", Monomial(1, {{"x", 1}})}), "-",
         createExpressionIfPossible({"b", "*", Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({100, "*", Monomial(1, {{"y", 1}})}), "+",
         createExpressionIfPossible({"a", "*", Monomial(1, {{"y", 1}})}), "-",
         createExpressionIfPossible({"b", "*", Monomial(1, {{"y", 1}})})}));
    Expression expressionToExpect3(createExpressionIfPossible(
        {createExpressionIfPossible({200, "*", "a", "/", "b", "*", Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({200, "*", "a", "/", "b", "*", Monomial(1, {{"y", 1}})})}));
    Expression subExpression(createExpressionIfPossible({"a", "^", "b"}));
    Expression expressionToExpect4(createExpressionIfPossible(
        {createExpressionIfPossible({subExpression, "*", Monomial(1, {{"x", 1}})}), "+",
         createExpressionIfPossible({subExpression, "*", Monomial(1, {{"y", 1}})})}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorksOnExpressionWithEmptyExpressionAndWillNotHaveImpact) {
    Term term1(createExpressionIfPossible({2, "^", "x"}));
    Term term2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term term3(1);
    Expression expressionToTest;
    Expression expressionToApply(createExpressionIfPossible({term1, "+", term2, "+", term3}));

    expressionToTest.putExpressionWithMultiplication(expressionToApply);

    string stringToExpect1("((2^x)+(1[x] + 1)+1)");
    EXPECT_EQ(stringToExpect1, convertToString(expressionToTest));
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorksOnAdditionAndSubtractionExpression) {
    Expression subExpression1(createExpressionIfPossible({"a", "+", "b"}));
    Expression subExpression2(createExpressionIfPossible({"c", "+", "d"}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expression3(createExpressionIfPossible({subExpression1, "/", subExpression2}));
    Expression expression4(createExpressionIfPossible({subExpression1, "^", subExpression2}));
    Expression expression5(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expressionToApply1(createExpressionIfPossible({"x", "+", "y", "+", 1}));
    Expression expressionToApply2(expression3);

    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(expressionToApply2);

    string stringToExpect1("(x+y+1)");
    string stringToExpect2("((a*x)+(a*y)+a+(b*x)+(b*y)+b-(c*x)-(c*y)-c-(d*x)-(d*y)-d)");
    string stringToExpect3("(((a+b)/(c+d)*x)+((a+b)/(c+d)*y)+((a+b)/(c+d)))");
    string stringToExpect4("((((a+b)^(c+d))*x)+(((a+b)^(c+d))*y)+((a+b)^(c+d)))");
    string stringToExpect5("((a*(a+b)/(c+d))+(b*(a+b)/(c+d))-(c*(a+b)/(c+d))-(d*(a+b)/(c+d)))");
    EXPECT_EQ(stringToExpect1, convertToString(expression1));
    EXPECT_EQ(stringToExpect2, convertToString(expression2));
    EXPECT_EQ(stringToExpect3, convertToString(expression3));
    EXPECT_EQ(stringToExpect4, convertToString(expression4));
    EXPECT_EQ(stringToExpect5, convertToString(expression5));
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorksOnMultiplicationAndDivisionExpression) {
    Expression subExpression1(createExpressionIfPossible({"a", "*", "b"}));
    Expression subExpression2(createExpressionIfPossible({"c", "*", "d"}));
    Expression subExpression3(createExpressionIfPossible({"x", "*", "x"}));
    Expression subExpression4(createExpressionIfPossible({"y", "*", "y"}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expression3(createExpressionIfPossible({subExpression1, "/", subExpression2}));
    Expression expression4(createExpressionIfPossible({subExpression1, "^", subExpression2}));
    Expression expression5(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expressionToApply1(createExpressionIfPossible({subExpression3, "-", subExpression4}));
    Expression const& expressionToApply2(subExpression3);

    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(expressionToApply2);

    string stringToExpect1("((x*x)-(y*y))");
    string stringToExpect2("((a*b*x*x)-(a*b*y*y)-(c*d*x*x)+(c*d*y*y))");
    string stringToExpect3("((a*b/c/d*x*x)-(a*b/c/d*y*y))");
    string stringToExpect4("((((a*b)^(c*d))*x*x)-(((a*b)^(c*d))*y*y))");
    string stringToExpect5("((a*b*x*x)-(c*d*x*x))");
    EXPECT_EQ(stringToExpect1, convertToString(expression1));
    EXPECT_EQ(stringToExpect2, convertToString(expression2));
    EXPECT_EQ(stringToExpect3, convertToString(expression3));
    EXPECT_EQ(stringToExpect4, convertToString(expression4));
    EXPECT_EQ(stringToExpect5, convertToString(expression5));
}

TEST(ExpressionTest, PutExpressionWithMultiplicationWorksOnRaiseToPowerExpression) {
    Expression subExpression1(createExpressionIfPossible({"a", "^", "b"}));
    Expression subExpression2(createExpressionIfPossible({"c", "^", "d"}));
    Expression subExpression3(createExpressionIfPossible({"x", "^", "x"}));
    Expression subExpression4(createExpressionIfPossible({"y", "^", "y"}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expression3(createExpressionIfPossible({subExpression1, "/", subExpression2}));
    Expression expression4(createExpressionIfPossible({subExpression1, "^", subExpression2}));
    Expression expression5(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expressionToApply1(createExpressionIfPossible({subExpression3, "-", subExpression4}));
    Expression const& expressionToApply2(subExpression3);

    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);
    expression5.putExpressionWithMultiplication(expressionToApply2);

    string stringToExpect1("((x^x)-(y^y))");
    string stringToExpect2("(((a^b)*(x^x))-((a^b)*(y^y))-((c^d)*(x^x))+((c^d)*(y^y)))");
    string stringToExpect3("(((a^b)/(c^d)*(x^x))-((a^b)/(c^d)*(y^y)))");
    string stringToExpect4("(((a^b^(c^d))*(x^x))-((a^b^(c^d))*(y^y)))");
    string stringToExpect5("(((a^b)*(x^x))-((c^d)*(x^x)))");
    EXPECT_EQ(stringToExpect1, convertToString(expression1));
    EXPECT_EQ(stringToExpect2, convertToString(expression2));
    EXPECT_EQ(stringToExpect3, convertToString(expression3));
    EXPECT_EQ(stringToExpect4, convertToString(expression4));
    EXPECT_EQ(stringToExpect5, convertToString(expression5));
}

TEST(ExpressionTest, PutTermWithDetailsWorks) {
    Expression expressionToTest;
    TermWithDetails termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails termWithDetails3(Term(30), TermAssociationType::Positive);

    expressionToTest.putTermWithDetails(termWithDetails1);
    expressionToTest.putTermWithDetails(termWithDetails2);
    expressionToTest.putTermWithDetails(termWithDetails3);

    TermsWithDetails termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
    EXPECT_EQ(Term(20), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[1].association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[2].association);
}

TEST(ExpressionTest, PutTermsWithDetailsWorks) {
    Expression expressionToTest;
    TermsWithDetails termsWithDetails;
    termsWithDetails.emplace_back(Term(10), TermAssociationType::Negative);
    termsWithDetails.emplace_back(Term(20), TermAssociationType::Positive);
    termsWithDetails.emplace_back(Term(30), TermAssociationType::Positive);

    expressionToTest.putTermsWithDetails(termsWithDetails);

    TermsWithDetails termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
    EXPECT_EQ(Term(20), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[1].association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[2].association);
}

TEST(ExpressionTest, PutTermWorks) {
    Expression expressionToTest;

    expressionToTest.putTerm(Term(10), TermAssociationType::Negative);
    expressionToTest.putTerm(Term(20), TermAssociationType::Positive);
    expressionToTest.putTerm(Term(30), TermAssociationType::Positive);

    TermsWithDetails termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
    EXPECT_EQ(Term(20), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[1].association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[2].association);
}

TEST(ExpressionTest, ReverseTheAssociationOfTheTermsWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({695}));

    expression1.reverseTheAssociationOfTheTerms();
    expression2.reverseTheAssociationOfTheTerms();

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expression1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expression2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify2[0].association);
    Term const& termToVerify(getTermConstReferenceFromUniquePointer(termsToVerify2[0].baseTermPointer));
    EXPECT_EQ(Term(695), termToVerify);
}

TEST(ExpressionTest, SetWorks) {
    Expression expression;
    TermsWithDetails termsWithDetails{
        TermWithDetails(Term(100), TermAssociationType::Positive),
        TermWithDetails(Term(2), TermAssociationType::Negative)};

    expression.set(OperatorLevel::AdditionAndSubtraction, termsWithDetails);

    Expression expressionToExpect(createExpressionIfPossible({100, "-", 2}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SetTermWorks) {
    Expression expression1(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression2(createExpressionIfPossible({695, "*", "interest"}));
    Expression expression3(createExpressionIfPossible({695, "*", "interest"}));

    expression1.setTerm(Term());
    expression2.setTerm(Term(87));
    expression3.setTerm(Term(createExpressionIfPossible({78, "+", "energy"})));

    Expression expressionToExpect1(createExpressionIfPossible({Term()}));
    Expression expressionToExpect2(createExpressionIfPossible({87}));
    Expression expressionToExpect3(createExpressionIfPossible({78, "+", "energy"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SetCommonOperatorLevelWorks) {
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

TEST(ExpressionTest, SetCommonOperatorLevelIfStillUnknownWorks) {
    Expression expression1;
    Expression expression2;
    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);

    expression1.setCommonOperatorLevelIfStillUnknown(OperatorLevel::MultiplicationAndDivision);
    expression2.setCommonOperatorLevelIfStillUnknown(OperatorLevel::MultiplicationAndDivision);

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression2.getCommonOperatorLevel());
}

TEST(ExpressionTest, SimplifyWorks) {
    Expression expressionToTest(createExpressionIfPossible({100, "+", 200, "-", 50}));

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(250));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksWhenIsSimplifiedIsNotSet) {
    Expression expressionToTest(createExpressionIfPossible({100, "+", 200, "-", 50}));

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(250));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet) {
    Expression expressionToTest(createExpressionIfPossible({100, "+", 200, "-", 50}));
    expressionToTest.setAsSimplified();

    expressionToTest.simplify();

    Expression expressionToExpect(createExpressionIfPossible({100, "+", 200, "-", 50}));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialFirstWithMultiplication) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({100, "+", "a", "-", "b"}));
    Expression expression3(createExpressionIfPossible({200, "*", "a", "/", "b"}));
    Expression expression4(createExpressionIfPossible({"a", "^", "b"}));
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialFirstWithMultiplication(polynomial);
    expression2.putPolynomialFirstWithMultiplication(polynomial);
    expression3.putPolynomialFirstWithMultiplication(polynomial);
    expression4.putPolynomialFirstWithMultiplication(polynomial);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(
        createOrCopyExpressionFromATerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(Polynomial{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}}), Monomial(-1, {{"b", 1}, {"x", 1}}),
        Monomial(-1, {{"b", 1}, {"y", 1}}), Monomial(100, {{"x", 1}}), Monomial(100, {{"y", 1}})}));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(
        Polynomial{Monomial(200, {{"a", 1}, {"b", -1}, {"x", 1}}), Monomial(200, {{"a", 1}, {"b", -1}, {"y", 1}})}));
    Expression subExpression(createExpressionIfPossible({"a", "^", "b"}));
    Expression expressionToExpect4(createExpressionIfPossible(
        {createExpressionIfPossible({"x", "*", subExpression}), "+",
         createExpressionIfPossible({"y", "*", subExpression})}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutPolynomialSecondWithMultiplication) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({100, "+", "a", "-", "b"}));
    Expression expression3(createExpressionIfPossible({200, "*", "a", "/", "b"}));
    Expression expression4(createExpressionIfPossible({"a", "^", "b"}));
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    expression1.putPolynomialSecondWithMultiplication(polynomial);
    expression2.putPolynomialSecondWithMultiplication(polynomial);
    expression3.putPolynomialSecondWithMultiplication(polynomial);
    expression4.putPolynomialSecondWithMultiplication(polynomial);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(
        createOrCopyExpressionFromATerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(Polynomial{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}}), Monomial(-1, {{"b", 1}, {"x", 1}}),
        Monomial(-1, {{"b", 1}, {"y", 1}}), Monomial(100, {{"x", 1}}), Monomial(100, {{"y", 1}})}));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(
        Polynomial{Monomial(200, {{"a", 1}, {"b", -1}, {"x", 1}}), Monomial(200, {{"a", 1}, {"b", -1}, {"y", 1}})}));
    Expression subExpression(createExpressionIfPossible({"a", "^", "b"}));
    Expression expressionToExpect4(createExpressionIfPossible(
        {createExpressionIfPossible({"x", "*", subExpression}), "+",
         createExpressionIfPossible({"y", "*", subExpression})}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SimplifyWorksOnPutExpressionWithMultiplication) {
    Expression subExpression1(createExpressionIfPossible({"a", "^", "b"}));
    Expression subExpression2(createExpressionIfPossible({"c", "^", "d"}));
    Expression subExpression3(createExpressionIfPossible({"x", "^", "x"}));
    Expression subExpression4(createExpressionIfPossible({"y", "^", "y"}));
    Expression expression1;
    Expression expression2(createExpressionIfPossible({subExpression1, "-", subExpression2}));
    Expression expression3(createExpressionIfPossible({subExpression1, "/", subExpression2}));
    Expression expression4(createExpressionIfPossible({subExpression1, "^", subExpression2}));
    Expression expressionToApply1(createExpressionIfPossible({subExpression3, "-", subExpression4}));
    expression1.putExpressionWithMultiplication(expressionToApply1);
    expression2.putExpressionWithMultiplication(expressionToApply1);
    expression3.putExpressionWithMultiplication(expressionToApply1);
    expression4.putExpressionWithMultiplication(expressionToApply1);

    expression1.simplify();
    expression2.simplify();
    expression3.simplify();
    expression4.simplify();

    Expression expressionToExpect1(createExpressionIfPossible({subExpression3, "-", subExpression4}));
    Expression expressionToExpect2(createExpressionIfPossible(
        {createExpressionIfPossible({subExpression1, "*", subExpression3}), "-",
         createExpressionIfPossible({subExpression1, "*", subExpression4}), "-",
         createExpressionIfPossible({subExpression2, "*", subExpression3}), "+",
         createExpressionIfPossible({subExpression2, "*", subExpression4})}));
    Expression expressionToExpect3(createExpressionIfPossible(
        {createExpressionIfPossible({subExpression1, "*", subExpression3, "/", subExpression2}), "-",
         createExpressionIfPossible({subExpression1, "*", subExpression4, "/", subExpression2})}));
    Expression subExpressionToExpect1(createExpressionIfPossible({"c", "^", "d"}));
    Expression subExpressionToExpect2(createExpressionIfPossible({"b", "*", subExpressionToExpect1}));
    Expression subExpressionToExpect3(createExpressionIfPossible({"a", "^", subExpressionToExpect2}));
    Expression expressionToExpect4(createExpressionIfPossible(
        {createExpressionIfPossible({subExpressionToExpect3, "*", subExpression3}), "-",
         createExpressionIfPossible({subExpressionToExpect3, "*", subExpression4})}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(ExpressionTest, SortWorks) {
    Expression expression(createExpressionIfPossible(
        {"-", 2, "-", 3, "+", 4, "+", 5, "-",
         Polynomial{
             Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}),
             Monomial(10, {})}}));

    expression.sort();

    Expression expressionToExpect(createExpressionIfPossible(
        {"+", 4, "+", 5, "-", 2, "-", 3, "-",
         Polynomial{
             Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(100, {}),
             Monomial(10, {})}}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SetAsSimplifiedWorks) {
    Expression expression;

    expression.setAsSimplified();

    EXPECT_TRUE(expression.isSimplified());
}

TEST(ExpressionTest, ClearSimplifiedFlagWorks) {
    Expression expression;
    expression.setAsSimplified();

    expression.clearSimplifiedFlag();

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ClearAllInnerSimplifiedFlagsWorks) {
    Term innerTerm;
    innerTerm.setAsSimplified();
    Expression expression(innerTerm);
    expression.setAsSimplified();
    EXPECT_TRUE(expression.isSimplified());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(expression.getFirstTerm()).isSimplified());

    expression.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(expression.isSimplified());
    EXPECT_FALSE(getTermConstReferenceFromBaseTerm(expression.getFirstTerm()).isSimplified());
}

TEST(ExpressionTest, OutputStreamOperatorWorks) {    stringstream ss;
    Expression expression1;
    Expression expression2(createExpressionIfPossible({695, "-", "interest", "+", "debt"}));
    Expression expression3;    expression3.putTermWithDivisionIfNeeded(Term(96));
    Expression expression4(createExpressionIfPossible({expression2, "^", "cash"}));

    ss << expression1 << "," << expression2 << "," << expression3 << "," << expression4;

    EXPECT_EQ("(),(695-interest+debt),(1/96),((695-interest+debt)^cash)", ss.str());
}

}  // namespace algebra

}  // namespace alba
