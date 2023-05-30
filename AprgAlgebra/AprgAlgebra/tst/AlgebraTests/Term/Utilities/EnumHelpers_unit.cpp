#include <Algebra/Term/Utilities/EnumHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(EnumHelpersTest, GetAssociationPriorityWorks) {
    EXPECT_EQ(1, getAssociationPriority(TermAssociationType::Positive));
    EXPECT_EQ(2, getAssociationPriority(TermAssociationType::Negative));
}

TEST(EnumHelpersTest, GetOperatorLevelInversePriorityWorks) {
    EXPECT_EQ(0, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(3, getOperatorLevelInversePriority(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ(2, getOperatorLevelInversePriority(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ(1, getOperatorLevelInversePriority(OperatorLevel::RaiseToPower));
}

TEST(EnumHelpersTest, GetTermPriorityValueWorks) {
    EXPECT_EQ(0, getTermTypePriorityValue(TermType::Empty));
    EXPECT_EQ(1, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3, getTermTypePriorityValue(TermType::Variable));
    EXPECT_EQ(4, getTermTypePriorityValue(TermType::Monomial));
    EXPECT_EQ(5, getTermTypePriorityValue(TermType::Polynomial));
    EXPECT_EQ(6, getTermTypePriorityValue(TermType::Expression));
    EXPECT_EQ(7, getTermTypePriorityValue(TermType::Function));
}

TEST(EnumHelpersTest, GetReversedAssociationTypeWorks) {
    EXPECT_EQ(TermAssociationType::Negative, getReversedAssociationType(TermAssociationType::Positive));
    EXPECT_EQ(TermAssociationType::Positive, getReversedAssociationType(TermAssociationType::Negative));
}

TEST(EnumHelpersTest, GetEnumShortStringForTermTypeWorks) {
    EXPECT_EQ("Empty", getEnumShortString(TermType::Empty));
    EXPECT_EQ("Constant", getEnumShortString(TermType::Constant));
    EXPECT_EQ("Variable", getEnumShortString(TermType::Variable));
    EXPECT_EQ("Operator", getEnumShortString(TermType::Operator));
    EXPECT_EQ("Monomial", getEnumShortString(TermType::Monomial));
    EXPECT_EQ("Polynomial", getEnumShortString(TermType::Polynomial));
    EXPECT_EQ("Expression", getEnumShortString(TermType::Expression));
    EXPECT_EQ("Function", getEnumShortString(TermType::Function));
}

TEST(EnumHelpersTest, GetEnumShortStringForTermAssociationTypeWorks) {
    EXPECT_EQ("{POS}", getEnumShortString(TermAssociationType::Positive));
    EXPECT_EQ("{NEG}", getEnumShortString(TermAssociationType::Negative));
}

TEST(EnumHelpersTest, GetEnumShortStringForOperatorLevelWorks) {
    EXPECT_EQ("{?}", getEnumShortString(OperatorLevel::Unknown));
    EXPECT_EQ("{+-}", getEnumShortString(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ("{*/}", getEnumShortString(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ("{^}", getEnumShortString(OperatorLevel::RaiseToPower));
}

}  // namespace algebra

}  // namespace alba
