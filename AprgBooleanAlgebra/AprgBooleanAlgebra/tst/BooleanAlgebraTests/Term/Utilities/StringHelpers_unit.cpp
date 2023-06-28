#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(StringHelpersTest, IsOperatorWorks) {
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("~"));
    EXPECT_TRUE(isOperator("&"));
    EXPECT_TRUE(isOperator("|"));
    EXPECT_TRUE(isOperator("("));
    EXPECT_TRUE(isOperator(")"));
    EXPECT_FALSE(isOperator("notAnOperator"));
}

TEST(StringHelpersTest, GetOperatorTypeValueWorks) {
    EXPECT_EQ(1, getOperatorPriority("("));
    EXPECT_EQ(2, getOperatorPriority(")"));
    EXPECT_EQ(3, getOperatorPriority("~"));
    EXPECT_EQ(4, getOperatorPriority("&"));
    EXPECT_EQ(5, getOperatorPriority("|"));
    EXPECT_EQ(0, getOperatorPriority("notAnOperator"));
}

TEST(StringHelpersTest, GetStringWorksForOperatorType) {
    EXPECT_TRUE(getString(OperatorType::Unknown).empty());
    EXPECT_EQ("~", getString(OperatorType::Not));
    EXPECT_EQ("&", getString(OperatorType::And));
    EXPECT_EQ("|", getString(OperatorType::Or));
}

TEST(StringHelpersTest, GetStringWorksForOperatorLevel) {
    EXPECT_TRUE(getString(OperatorLevel::Unknown).empty());
    EXPECT_EQ("&", getString(OperatorLevel::And));
    EXPECT_EQ("|", getString(OperatorLevel::Or));
}

TEST(StringHelpersTest, GetStringForWrappedTermsWorks) {
    WrappedTerms wrappedTerms;
    wrappedTerms.emplace_back(Term(true));
    wrappedTerms.emplace_back(Term(true));

    EXPECT_EQ("[true], [true]", getString(wrappedTerms));
}

TEST(StringHelpersTest, CreateVariableTermNameForSubstitutionWorks) {
    Term term(createVariableTermNameForSubstitution(Term("x")));

    EXPECT_EQ("{{x}}", createVariableTermNameForSubstitution(term));
}

TEST(StringHelpersTest, BuildTermIfPossibleWorks) {
    Term termToVerify(buildTermIfPossible("x&y"));

    Term termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(StringHelpersTest, TokenizeToTermsWorks) {
    Terms termsToVerify(tokenizeToTerms(" 5yyy & x1 & y1 | ~2015"));

    Terms termsToExpect{"5yyy", "&", "x1", "&", "y1", "|", "~", true};
    EXPECT_EQ(termsToExpect, termsToVerify);
}

TEST(StringHelpersTest, AddValueTermIfNotEmptyWorks) {
    Terms termsToVerify1;

    addValueTermIfNotEmpty(termsToVerify1, "true");

    ASSERT_EQ(1U, termsToVerify1.size());
    ASSERT_EQ(TermType::Constant, termsToVerify1[0].getTermType());
    EXPECT_TRUE(termsToVerify1[0].getBooleanValue());
}

}  // namespace booleanAlgebra

}  // namespace alba
