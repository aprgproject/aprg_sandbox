#include <BooleanAlgebra/Constructs/TermsAggregator.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithNoTerms) {
    TermsAggregator aggregator({});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithUnaryOperation) {
    TermsAggregator aggregator({"~", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect("x'");
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation) {    TermsAggregator aggregator({"x", "&", "y"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevels_AndOperationPrioritizedBeforeOrOperation) {    TermsAggregator aggregator({"a", "|", "b", "&", "c", "&", "d", "|", "e"});

    aggregator.buildExpressionFromTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression subExpression1(createExpressionIfPossible({"b", "&", "c", "&", "d"}));
    Expression subExpression2(createExpressionIfPossible({"a", "|", subExpression1, "|", "e"}));
    Term termToExpect(subExpression2);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithParenthesis) {    TermsAggregator aggregator({"(", "(", "(", "a", "|", "b", ")", "&", "c", ")", "|", "d", ")"});

    aggregator.buildExpressionFromTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression subExpression1(createExpressionIfPossible({"a", "|", "b"}));
    Expression subExpression2(createExpressionIfPossible({subExpression1, "&", "c"}));
    Expression subExpression3(createExpressionIfPossible({subExpression2, "|", "d"}));
    Term termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNoTerms) {    TermsAggregator aggregator({});

    aggregator.simplifyTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, SimplifyWorksWithUnaryOperation) {
    TermsAggregator aggregator({"~", true});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation) {    TermsAggregator aggregator({true, "&", false});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels) {    TermsAggregator aggregator({false, "|", true, "&", false, "&", true, "|", false});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis) {    TermsAggregator aggregator({"(", "(", "(", false, "|", true, ")", "&", true, ")", "|", false, ")"});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(true);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegatedTermsAndVariousOperations) {    TermsAggregator aggregator(tokenizeToTerms("~a&~b|~c&x|y"));

    aggregator.simplifyTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression subExpression1(createExpressionIfPossible({"a'", "&", "b'"}));
    Expression subExpression2(createExpressionIfPossible({"c'", "&", "x"}));
    Expression subExpression3(createExpressionIfPossible({subExpression1, "|", subExpression2, "|", "y"}));
    Term termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

}  // namespace booleanAlgebra
}  // namespace alba