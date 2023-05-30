#include <BooleanAlgebra/Satisfiability/Utilities.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityLevelWorks) {
    SatisfiabilityTerms satTermsToTest{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};

    EXPECT_EQ(3, getSatisfiabilityLevel(satTermsToTest));
}

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithTerm) {
    Term term1(true);
    Term term2("x");
    Expression subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Term term3(createExpressionIfPossible({"a", "&", subExpression1, "&", subExpression2}));

    SatisfiabilityTerms satTermsToVerify1(getSatisfiabilityTerms(term1));
    SatisfiabilityTerms satTermsToVerify2(getSatisfiabilityTerms(term2));
    SatisfiabilityTerms satTermsToVerify3(getSatisfiabilityTerms(term3));

    SatisfiabilityTerms satTermsToExpect1;
    SatisfiabilityTerms satTermsToExpect2{{VariableTerm("x")}};
    SatisfiabilityTerms satTermsToExpect3{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};
    EXPECT_EQ(satTermsToExpect1, satTermsToVerify1);
    EXPECT_EQ(satTermsToExpect2, satTermsToVerify2);
    EXPECT_EQ(satTermsToExpect3, satTermsToVerify3);
}

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithExpression) {
    Expression subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Expression expressionToTest(createExpressionIfPossible({"a", "&", subExpression1, "&", subExpression2}));

    SatisfiabilityTerms satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    SatisfiabilityTerms satTermsToExpect{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};
    EXPECT_EQ(satTermsToExpect, satTermsToVerify);
}

TEST(
    SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithExpression_ResultsAreEmptyWithConstantInAndExpression) {
    Expression subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Expression expressionToTest(OperatorLevel::And, {Term(true), Term(subExpression1), Term(subExpression2)});

    SatisfiabilityTerms satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    EXPECT_TRUE(satTermsToVerify.empty());
}

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithExpression_ResultsAreEmptyWithConstantInOrExpression) {
    Expression subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression subExpression2(createExpressionIfPossible({true, "|", "e", "|", "f"}));
    Expression expressionToTest(OperatorLevel::And, {Term("a"), Term(subExpression1), Term(subExpression2)});

    SatisfiabilityTerms satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    EXPECT_TRUE(satTermsToVerify.empty());
}

}  // namespace booleanAlgebra

}  // namespace alba
