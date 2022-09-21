#include <BooleanAlgebra/Term/TermTypes/Expression.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(ExpressionTest, ConstructionWorks)
{
    WrappedTerm wrappedTerm1(Term(false));
    WrappedTerm wrappedTerm2(Term(true));
    Expression expression1;
    Expression expression2(Term(false));
    Expression expression3(OperatorLevel::And, {});
    Expression expression4(OperatorLevel::And, {wrappedTerm1, wrappedTerm2});

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify1(expression1.getWrappedTerms());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify2(expression2.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(Term(false), getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
    EXPECT_EQ(OperatorLevel::Unknown, expression3.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify3(expression3.getWrappedTerms());
    EXPECT_TRUE(termsToVerify3.empty());
    EXPECT_EQ(OperatorLevel::And, expression4.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify4(expression4.getWrappedTerms());
    ASSERT_EQ(2U, termsToVerify4.size());
    EXPECT_EQ(Term(false), getTermConstReferenceFromSharedPointer(termsToVerify4.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromSharedPointer(termsToVerify4.at(1).baseTermSharedPointer));
}

TEST(ExpressionTest, ExpressionThatIsDefaultConstructedHasIsSimplifiedFlagNotSet)
{
    Expression expression;

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsCopyConstructedHasIsSimplifiedFlagCopied)
{
    Expression expressionWithSimplifiedNotSet;
    Expression expressionWithSimplifiedSet;
    expressionWithSimplifiedSet.setAsSimplified();

    Expression expression1(expressionWithSimplifiedNotSet);
    Expression expression2(expressionWithSimplifiedSet);

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsConstructedWithTermHasIsSimplifiedFlagCopied)
{
    Term termWithSimplifiedNotSet;
    Term termWithSimplifiedSet;
    termWithSimplifiedSet.setAsSimplified();

    Expression expression1(termWithSimplifiedNotSet);
    Expression expression2(termWithSimplifiedSet);

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsConstructedWithWrappedTermsHasIsSimplifiedFlagNotSet)
{
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm wrappedTerm2(Term(false));
    Expression expression(OperatorLevel::And, {wrappedTerm1, wrappedTerm2});

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, EqualityOperatorWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));
    Expression expression3(createExpressionIfPossible({false, "&", "x"}));
    Expression expression4(createOrCopyExpressionFromATerm(true));
    Expression expression5(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&"})}));
    Expression expression6(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));

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
    Expression expression2(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));
    Expression expression3(createExpressionIfPossible({false, "&", "x"}));
    Expression expression4(createOrCopyExpressionFromATerm(true));
    Expression expression5(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&"})}));
    Expression expression6(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));

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
    Expression expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression expression3(createOrCopyExpressionFromATerm(true));
    Expression expression4(createExpressionIfPossible({true, "&", "x", "&", "y"}));
    Expression expression5(createExpressionIfPossible({false, "&", "x"}));

    EXPECT_FALSE(expression1<expression1);
    EXPECT_FALSE(expression2<expression2);
    EXPECT_FALSE(expression2<expression3);
    EXPECT_TRUE(expression2<expression4);
    EXPECT_FALSE(expression2<expression5);
}

TEST(ExpressionTest, NotOperationWorks)
{
    Expression expressionToTest(createExpressionIfPossible(
    {"x", "&", "x'", "&", "y", "&", "z"}));
    Expression expressionToExpect(createExpressionIfPossible(
    {"x'", "|", "x", "|", "y'", "|", "z'"}));

    EXPECT_EQ(expressionToExpect, ~expressionToTest);
}

TEST(ExpressionTest, IsEmptyWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({true, "&", "x"}));

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_FALSE(expression2.isEmpty());
    EXPECT_FALSE(expression3.isEmpty());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", "x"}));
    Expression expression4(createExpressionIfPossible({"x", "&", "y"}));

    EXPECT_FALSE(expression1.containsOnlyOneTerm());
    EXPECT_TRUE(expression2.containsOnlyOneTerm());
    EXPECT_TRUE(expression3.containsOnlyOneTerm());
    EXPECT_FALSE(expression4.containsOnlyOneTerm());
}

TEST(ExpressionTest, IsSimplifiedWorks)
{
    Expression expression1;
    Expression expression2;
    expression2.setAsSimplified();

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, GetCommonOperatorTypeWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(true));
    Expression expression3(createExpressionIfPossible({"x", "&", "y"}));
    Expression expression4(createExpressionIfPossible({"x", "|", "y"}));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression3.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Or, expression4.getCommonOperatorLevel());
}

TEST(ExpressionTest, GetFirstTermConstReferenceWorks)
{
    Expression expression1(createOrCopyExpressionFromATerm(true));
    Expression expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression expression3(createExpressionIfPossible({"~", false}));

    EXPECT_EQ(Term(true), getTermConstReferenceFromBaseTerm(expression1.getFirstTermConstReference()));
    EXPECT_EQ(Term("x"), getTermConstReferenceFromBaseTerm(expression2.getFirstTermConstReference()));
    EXPECT_EQ(Term(true), getTermConstReferenceFromBaseTerm(expression3.getFirstTermConstReference()));
}

TEST(ExpressionTest, GetWrappedTermsWorks)
{
    Expression expression(createExpressionIfPossible({true, "&", "x", "|", "y"}));

    WrappedTerms const& wrappedTermsToVerify(expression.getWrappedTerms());

    ASSERT_EQ(2U, wrappedTermsToVerify.size());
    EXPECT_EQ(Term("x"), getTermConstReferenceFromSharedPointer(wrappedTermsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term("y"), getTermConstReferenceFromSharedPointer(wrappedTermsToVerify.at(1).baseTermSharedPointer));
}

TEST(ExpressionTest, GetDisplayableStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));
    Expression expression3;
    expression3.putTermWithAndOperationIfNeeded(Term(true));
    Expression expression4(createExpressionIfPossible({expression2, "&", "z"}));

    EXPECT_EQ("()", expression1.getDisplayableString());
    EXPECT_EQ("(x|y)", expression2.getDisplayableString());
    EXPECT_EQ("([true])", expression3.getDisplayableString());
    EXPECT_EQ("((x|y)&z)", expression4.getDisplayableString());
}

TEST(ExpressionTest, GetDebugStringWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));
    Expression expression3;
    expression3.putTermWithAndOperationIfNeeded(Term(true));
    Expression expression4(createExpressionIfPossible({expression2, "&", "z"}));

    EXPECT_EQ("( {?}|| )", expression1.getDebugString());
    EXPECT_EQ("( {|}|||x{VariableTerm}|y{VariableTerm} )", expression2.getDebugString());
    EXPECT_EQ("( {?}||[true]{Constant} )", expression3.getDebugString());
    EXPECT_EQ("( {&}||&( {|}|||x{VariableTerm}|y{VariableTerm} ){Expression}&z{VariableTerm} )", expression4.getDebugString());
}

TEST(ExpressionTest, GetWrappedTermsReferenceWorks)
{
    Expression expressionToTest(createExpressionIfPossible({"x", "&", "y"}));

    WrappedTerms & wrappedTerms(expressionToTest.getWrappedTermsReference());
    wrappedTerms.emplace_back(Term("a"));
    wrappedTerms.emplace_back(Term("b"));

    Expression expressionToExpect(createExpressionIfPossible({"x", "&", "y", "&", "a", "&", "b"}));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, ClearWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "&", "y", "|", "z"}));

    expression1.clear();
    expression2.clear();

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_TRUE(expression2.isEmpty());
}

TEST(ExpressionTest, ClearAndPutTermInWrappedTermsWorks)
{
    Expression expression1;
    Expression expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));

    expression1.clearAndPutTermInWrappedTerms(Term(true));
    expression2.clearAndPutTermInWrappedTerms(Term(true));

    EXPECT_EQ(createOrCopyExpressionFromATerm(true), expression1);
    EXPECT_EQ(createOrCopyExpressionFromATerm(true), expression2);
}

TEST(ExpressionTest, PutTermWorks)
{
    Expression expressionToTest;

    expressionToTest.putTerm(Term("a"));
    expressionToTest.putTerm(Term("b"));
    expressionToTest.putTerm(Term("c"));
    expressionToTest.putTerm(Term("d"));

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(Term("a"), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term("b"), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term("c"), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
    EXPECT_EQ(Term("d"), getTermConstReferenceFromSharedPointer(termsToVerify.at(3).baseTermSharedPointer));
}

TEST(ExpressionTest, PutTermWithOperationLevelWorks)
{
    Expression expressionToTest;

    expressionToTest.putTerm(Term("a"), OperatorLevel::And);
    expressionToTest.putTerm(Term("b"), OperatorLevel::Or);
    expressionToTest.putTerm(Term("c"), OperatorLevel::And);
    expressionToTest.putTerm(Term("d"), OperatorLevel::Or);

    EXPECT_EQ("(((a|b)&c)|d)", expressionToTest.getDisplayableString());
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression nullExpression;
    expression1.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression2.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression3.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression4.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression5.putTermWithAndOperationIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term noEffectTerm(true);
    expression1.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression2.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression3.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression4.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression5.putTermWithAndOperationIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression2);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingShortCircuitValueWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term shortCircuitValue(false);
    expression1.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression2.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression3.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression4.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression5.putTermWithAndOperationIfNeeded(shortCircuitValue);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect4(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect5(createOrCopyExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "&", "y"}));
    expression1.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithAndOperationIfNeeded(Term(expressionToApply));

    Expression expressionToExpect1(createExpressionIfPossible({"x", "&", "y"}));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createExpressionIfPossible({"x", "&", "y"}));
    Expression expressionToExpect4(createExpressionIfPossible({"x", "&", "x", "&", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x", "&", "x", "&", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "|", "y"}));
    expression1.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithAndOperationIfNeeded(Term(expressionToApply));

    Expression expressionToExpect1(createExpressionIfPossible({"x", "|", "y"}));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createExpressionIfPossible({"x", "|", "y"}));
    Expression expressionToExpect4(createExpressionIfPossible({"x", "&", expressionToApply}));
    Expression expressionToExpect5(createExpressionIfPossible({"x", "&", expressionToApply}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingNullExpressionWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression nullExpression;
    expression1.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression2.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression3.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression4.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression5.putTermWithOrOperationIfNeeded(Term(nullExpression));

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingTermWithNoEffectWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term noEffectTerm(false);
    expression1.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression2.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression3.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression4.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression5.putTermWithOrOperationIfNeeded(noEffectTerm);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingShortCircuitValueWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term shortCircuitValue(true);
    expression1.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression2.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression3.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression4.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression5.putTermWithOrOperationIfNeeded(shortCircuitValue);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect5(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingExpressionWithSameOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "|", "y"}));
    expression1.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithOrOperationIfNeeded(Term(expressionToApply));

    Expression expressionToExpect1(createExpressionIfPossible({"x", "|", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({"x", "|", "y"}));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createExpressionIfPossible({"x", "|", "x", "|", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x", "|", "x", "|", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingExpressionWithDifferentOperationLevelWorks)
{
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression expressionToApply(createExpressionIfPossible({"x", "&", "y"}));
    expression1.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithOrOperationIfNeeded(Term(expressionToApply));

    Expression expressionToExpect1(createExpressionIfPossible({"x", "&", "y"}));
    Expression expressionToExpect2(createExpressionIfPossible({"x", "&", "y"}));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect4(createExpressionIfPossible({"x", "|", "x", "&", "y"}));
    Expression expressionToExpect5(createExpressionIfPossible({"x", "|", "x", "&", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutWrappedTermWorks)
{
    Expression expressionToTest;
    WrappedTerm wrappedTerm1(Term(true));
    WrappedTerm wrappedTerm2(Term(false));
    WrappedTerm wrappedTerm3(Term(true));

    expressionToTest.putWrappedTerm(wrappedTerm1);
    expressionToTest.putWrappedTerm(wrappedTerm2);
    expressionToTest.putWrappedTerm(wrappedTerm3);

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(true), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(false), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
}

TEST(ExpressionTest, PutWrappedTermsWorks)
{
    Expression expressionToTest;
    WrappedTerms wrappedTerms;
    wrappedTerms.emplace_back(Term(true));
    wrappedTerms.emplace_back(Term(false));
    wrappedTerms.emplace_back(Term(true));

    expressionToTest.putWrappedTerms(wrappedTerms);

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(true), getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(false), getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromSharedPointer(termsToVerify.at(2).baseTermSharedPointer));
}

TEST(ExpressionTest, SetWorks)
{
    Expression expression;
    WrappedTerms wrappedTerms{Term(true), Term(false)};

    expression.set(OperatorLevel::And, wrappedTerms);

    EXPECT_EQ("([true]&[false])", expression.getDisplayableString());
}

TEST(ExpressionTest, SetTermWorks)
{
    Expression expression1(createExpressionIfPossible({true, "&", "x"}));
    Expression expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression expression3(createExpressionIfPossible({true, "&", "x"}));

    expression1.setTerm(Term());
    expression2.setTerm(Term(true));
    expression3.setTerm(Term(createExpressionIfPossible({false, "|", "energy"})));

    Expression expressionToExpect1;
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(true));
    Expression expressionToExpect3(createExpressionIfPossible({"energy"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SetCommonOperatorLevelWorks)
{
    Expression expression1;
    Expression expression2;
    Expression expression3;

    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::And);
    expression3.setCommonOperatorLevel(OperatorLevel::Or);

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Or, expression3.getCommonOperatorLevel());
}

TEST(ExpressionTest, SetCommonOperatorTypeIfStillUnknownWorks)
{
    Expression expression1;
    Expression expression2;
    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::And);

    expression1.setCommonOperatorLevelIfStillUnknown(OperatorLevel::Or);
    expression2.setCommonOperatorLevelIfStillUnknown(OperatorLevel::Or);

    EXPECT_EQ(OperatorLevel::Or, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression2.getCommonOperatorLevel());
}

TEST(ExpressionTest, SimplifyWorks)
{
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksWhenIsSimplifiedIsNotSet)
{
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet)
{
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));
    expressionToTest.setAsSimplified();

    expressionToTest.simplify();

    Expression expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SortWorks)
{
    Expression expression(createExpressionIfPossible(
    {"x", "&", "x'", "&", "y", "&", "z"}));

    expression.sort();

    Expression expressionToExpect(createExpressionIfPossible(
    {"x", "&", "x'", "&", "y", "&", "z"}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, NegateWorks)
{
    Expression expression(createExpressionIfPossible(
    {"x", "&", "x'", "&", "y", "&", "z"}));

    expression.negate();

    Expression expressionToExpect(createExpressionIfPossible(
    {"x'", "|", "x", "|", "y'", "|", "z'"}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, SetAsSimplifiedWorks)
{
    Expression expression;

    expression.setAsSimplified();

    EXPECT_TRUE(expression.isSimplified());
}

TEST(ExpressionTest, ClearSimplifiedFlagWorks)
{
    Expression expression;
    expression.setAsSimplified();

    expression.clearSimplifiedFlag();

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ClearAllInnerSimplifiedFlagsWorks)
{
    Term innerTerm;
    innerTerm.setAsSimplified();
    Expression expression(innerTerm);
    expression.setAsSimplified();
    EXPECT_TRUE(expression.isSimplified());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference()).isSimplified());

    expression.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(expression.isSimplified());
    EXPECT_FALSE(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference()).isSimplified());
}

}

}
