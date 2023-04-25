#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(EnumHelpersTest, GetOperatorTypeInversePriorityWorks) {
    EXPECT_EQ(0U, getOperatorTypeInversePriority(OperatorType::Unknown));
    EXPECT_EQ(1U, getOperatorTypeInversePriority(OperatorType::Not));
    EXPECT_EQ(2U, getOperatorTypeInversePriority(OperatorType::And));
    EXPECT_EQ(3U, getOperatorTypeInversePriority(OperatorType::Or));
}

TEST(EnumHelpersTest, GetOperatorLevelInversePriorityWorks) {
    EXPECT_EQ(0U, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(1U, getOperatorLevelInversePriority(OperatorLevel::And));
    EXPECT_EQ(2U, getOperatorLevelInversePriority(OperatorLevel::Or));
}

TEST(EnumHelpersTest, GetTermPriorityValueWorks) {
    EXPECT_EQ(0U, getTermTypePriorityValue(TermType::Empty));
    EXPECT_EQ(1U, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2U, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3U, getTermTypePriorityValue(TermType::VariableTerm));
    EXPECT_EQ(4U, getTermTypePriorityValue(TermType::Expression));
}

TEST(EnumHelpersTest, GetDualOperatorLevelWorks) {
    EXPECT_EQ(OperatorLevel::Unknown, getDualOperatorLevel(OperatorLevel::Unknown));
    EXPECT_EQ(OperatorLevel::Or, getDualOperatorLevel(OperatorLevel::And));
    EXPECT_EQ(OperatorLevel::And, getDualOperatorLevel(OperatorLevel::Or));
}

TEST(EnumHelpersTest, GetEnumShortStringForTermTypeWorks) {
    EXPECT_EQ("Empty", getEnumShortString(TermType::Empty));
    EXPECT_EQ("Constant", getEnumShortString(TermType::Constant));
    EXPECT_EQ("VariableTerm", getEnumShortString(TermType::VariableTerm));
    EXPECT_EQ("Operator", getEnumShortString(TermType::Operator));
    EXPECT_EQ("Expression", getEnumShortString(TermType::Expression));
}

TEST(EnumHelpersTest, GetEnumShortStringForOperatorTypeWorks) {
    EXPECT_EQ("{?}", getEnumShortString(OperatorType::Unknown));
    EXPECT_EQ("{~}", getEnumShortString(OperatorType::Not));
    EXPECT_EQ("{&}", getEnumShortString(OperatorType::And));
    EXPECT_EQ("{|}", getEnumShortString(OperatorType::Or));
}

TEST(EnumHelpersTest, GetEnumShortStringForOperatorLevelWorks) {
    EXPECT_EQ("{?}", getEnumShortString(OperatorLevel::Unknown));
    EXPECT_EQ("{&}", getEnumShortString(OperatorLevel::And));
    EXPECT_EQ("{|}", getEnumShortString(OperatorLevel::Or));
}

}  // namespace booleanAlgebra

}  // namespace alba
