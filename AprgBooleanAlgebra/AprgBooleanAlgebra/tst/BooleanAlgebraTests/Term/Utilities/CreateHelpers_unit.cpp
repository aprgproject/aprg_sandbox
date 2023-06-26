#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(CreateHelpersTest, CreateExpressionInExpressionWorks) {
    Expression expression1(createExpressionIfPossible({false}));
    Expression expression2(createExpressionIfPossible({true}));

    Expression expressionToVerify1(createExpressionInAnExpression(expression1));
    Expression expressionToVerify2(createExpressionInAnExpression(createExpressionInAnExpression(expression2)));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(expression1));
    Expression expressionToExpect2(getBaseTermConstReferenceFromTerm(Expression(Term(expression2))));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateAndWrapExpressionFromATermWorks) {
    Expression expression1(createExpressionIfPossible({false}));
    Expression expression2(createExpressionIfPossible({true}));

    Expression expressionToVerify1(createAndWrapExpressionFromATerm(expression1));
    Expression expressionToVerify2(createAndWrapExpressionFromATerm(true));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(expression1));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateOrCopyExpressionFromATermWorks) {
    Expression expression1(createExpressionIfPossible({false}));
    Expression expression2(createExpressionIfPossible({true}));

    Expression expressionToVerify1(createOrCopyExpressionFromATerm(expression1));
    Expression expressionToVerify2(createOrCopyExpressionFromATerm(true));

    EXPECT_EQ(expression1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleWorks) {
    Expression expressionToTest(createExpressionIfPossible({"x", "&", "y"}));

    EXPECT_EQ(OperatorLevel::And, expressionToTest.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term("x"), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term("y"), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleDoesNotSimplifyExpressionInAExpression) {    Expression expression1(createExpressionIfPossible({true}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));
    Expression expressionToTest1(createExpressionIfPossible({expression3}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest1.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify1(expressionToTest1.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify1.size());
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify1[0].baseTermPointer));
    ASSERT_TRUE(termToVerify1.isExpression());
    Expression const& expressionToTest2(termToVerify1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest2.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify2(expressionToTest2.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify2.size());
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify2[0].baseTermPointer));
    ASSERT_TRUE(termToVerify2.isExpression());
    Expression const& expressionToTest3(termToVerify2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest3.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify3(expressionToTest3.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify3.size());
    Term const& termToVerify3(getTermConstReferenceFromUniquePointer(termsToVerify3[0].baseTermPointer));
    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_EQ(Constant(true), termToVerify3.getConstantConstReference());
}
TEST(CreateHelpersTest, CreateExpressionIfPossibleDoesNotSimplify) {
    Expression expressionToTest(createExpressionIfPossible({"x", "&", "x"}));

    EXPECT_EQ(OperatorLevel::And, expressionToTest.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term("x"), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term("x"), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong) {    Expression expressionToTest(createExpressionIfPossible({"x", "&", "|", "y"}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify(expressionToTest.getWrappedTerms());    ASSERT_TRUE(termsToVerify.empty());
}

TEST(CreateHelpersTest, CreateSimplifiedExpressionIfPossibleWorks) {
    Expression expressionToTest(createSimplifiedExpressionIfPossible({true, "&", false}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(false), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
}

TEST(CreateHelpersTest, CreateSimplifiedExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong) {    Expression expressionToTest(createSimplifiedExpressionIfPossible({"&", "&", "&"}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify(expressionToTest.getWrappedTerms());    ASSERT_TRUE(termsToVerify.empty());
}

TEST(CreateHelpersTest, CreateTermWithAdditionAndSubtractionWrappedTermsWorksWithASingleTerm) {
    WrappedTerms wrappedTerms{Term("x")};

    Term termToExpect(createTermWithAndOperationWrappedTerms(wrappedTerms));

    Term termToVerify("x");
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithAdditionAndSubtractionWrappedTermsWorksWithMultipleTerms) {
    WrappedTerms wrappedTerms{Term("x"), Term("y"), Term("z")};

    Term termToExpect(createTermWithAndOperationWrappedTerms(wrappedTerms));

    Term termToVerify(createExpressionIfPossible({"x", "&", "y", "&", "z"}));
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithMultiplicationAndDivisionWrappedTermsWorksWithASingleTerm) {
    WrappedTerms wrappedTerms{Term("x")};

    Term termToExpect(createTermWithOrOperationWrappedTerms(wrappedTerms));

    Term termToVerify("x");
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithMultiplicationAndDivisionWrappedTermsWorksWithMultipleTerms) {
    WrappedTerms wrappedTerms{Term("x"), Term("y"), Term("z")};

    Term termToExpect(createTermWithOrOperationWrappedTerms(wrappedTerms));

    Term termToVerify(createExpressionIfPossible({"x", "|", "y", "|", "z"}));
    EXPECT_EQ(termToVerify, termToExpect);
}

}  // namespace booleanAlgebra

}  // namespace alba
