#include <Algebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(StringHelpersTest, IsOperatorWorks) {
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));
    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_TRUE(isOperator("("));
    EXPECT_TRUE(isOperator(")"));
    EXPECT_FALSE(isOperator("notAnOperator"));
}

TEST(StringHelpersTest, IsFunctionWorks) {
    EXPECT_FALSE(isFunction(""));
    EXPECT_TRUE(isFunction("abs"));
    EXPECT_FALSE(isFunction("notAnFunction"));
}

TEST(StringHelpersTest, GetOperatorLevelValueWorks) {
    EXPECT_EQ(1, getOperatorPriority("("));
    EXPECT_EQ(2, getOperatorPriority(")"));
    EXPECT_EQ(3, getOperatorPriority("+"));
    EXPECT_EQ(4, getOperatorPriority("-"));
    EXPECT_EQ(5, getOperatorPriority("*"));
    EXPECT_EQ(6, getOperatorPriority("/"));
    EXPECT_EQ(7, getOperatorPriority("^"));
    EXPECT_EQ(0, getOperatorPriority("operator"));
}
TEST(StringHelpersTest, GetOperatingStringWorks) {
    EXPECT_TRUE(getOperatingString(OperatorLevel::Unknown, TermAssociationType::Positive).empty());    EXPECT_TRUE(getOperatingString(OperatorLevel::Unknown, TermAssociationType::Negative).empty());
    EXPECT_EQ("+", getOperatingString(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Positive));
    EXPECT_EQ("-", getOperatingString(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Negative));
    EXPECT_EQ("*", getOperatingString(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Positive));    EXPECT_EQ("/", getOperatingString(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Negative));
    EXPECT_EQ("^", getOperatingString(OperatorLevel::RaiseToPower, TermAssociationType::Positive));
    EXPECT_TRUE(getOperatingString(OperatorLevel::RaiseToPower, TermAssociationType::Negative).empty());
}

TEST(StringHelpersTest, GetFirstStringIfNegativeAssociationWorks) {
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::Unknown, TermAssociationType::Positive).empty());
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::Unknown, TermAssociationType::Negative).empty());
    EXPECT_TRUE(
        getFirstStringIfNegativeAssociation(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Positive)
            .empty());
    EXPECT_EQ(
        "-", getFirstStringIfNegativeAssociation(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Negative));
    EXPECT_TRUE(
        getFirstStringIfNegativeAssociation(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Positive)
            .empty());
    EXPECT_EQ(
        "1/",
        getFirstStringIfNegativeAssociation(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Negative));
    EXPECT_TRUE(
        getFirstStringIfNegativeAssociation(OperatorLevel::RaiseToPower, TermAssociationType::Positive).empty());
    EXPECT_TRUE(
        getFirstStringIfNegativeAssociation(OperatorLevel::RaiseToPower, TermAssociationType::Negative).empty());
}

TEST(StringHelpersTest, CreateVariableNameForSubstitutionWorks) {
    Term term(Polynomial{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    EXPECT_EQ("{(6 + -7[x^2][y^3][z^4])}", createVariableNameForSubstitution(term));
}

TEST(StringHelpersTest, BuildTermIfPossibleWorks) {
    Term termToVerify(buildTermIfPossible("x^2*y^-3*z^4"));

    Term termToExpect(Monomial(1, {{"x", 2}, {"y", -3}, {"z", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(StringHelpersTest, TokenizeToTermsWorks) {
    Terms termsToVerify1(tokenizeToTerms(" 5yyy + x1*y1^20.15"));

    ASSERT_EQ(7U, termsToVerify1.size());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(1).getTermType());
    EXPECT_EQ("+", termsToVerify1.at(1).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, termsToVerify1.at(2).getTermType());
    EXPECT_EQ("x1", termsToVerify1.at(2).getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(3).getTermType());
    EXPECT_EQ("*", termsToVerify1.at(3).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, termsToVerify1.at(4).getTermType());
    EXPECT_EQ("y1", termsToVerify1.at(4).getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(5).getTermType());
    EXPECT_EQ("^", termsToVerify1.at(5).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(6).getTermType());
    EXPECT_DOUBLE_EQ(20.15, termsToVerify1.at(6).getConstantValueConstReference().getDouble());
}

TEST(StringHelpersTest, AddValueTermIfNotEmptyWorks) {
    Terms termsToVerify1;

    addValueTermIfNotEmpty(termsToVerify1, "5");

    ASSERT_EQ(1U, termsToVerify1.size());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantValueConstReference().getDouble());
}

}  // namespace algebra

}  // namespace alba
