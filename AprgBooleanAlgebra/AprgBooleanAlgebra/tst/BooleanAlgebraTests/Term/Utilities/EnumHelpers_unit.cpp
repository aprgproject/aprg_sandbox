#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(EnumHelpersTest, GetOperatorTypeInversePriorityWorks) {
    EXPECT_EQ(0, getOperatorTypeInversePriority(OperatorType::Unknown));
    EXPECT_EQ(1, getOperatorTypeInversePriority(OperatorType::Not));
    EXPECT_EQ(2, getOperatorTypeInversePriority(OperatorType::And));
    EXPECT_EQ(3, getOperatorTypeInversePriority(OperatorType::Or));
}

TEST(EnumHelpersTest, GetOperatorLevelInversePriorityWorks) {
    EXPECT_EQ(0, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(1, getOperatorLevelInversePriority(OperatorLevel::And));
    EXPECT_EQ(2, getOperatorLevelInversePriority(OperatorLevel::Or));
}

TEST(EnumHelpersTest, GetTermPriorityValueWorks) {
    EXPECT_EQ(0, getTermTypePriorityValue(TermType::Empty));
    EXPECT_EQ(1, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3, getTermTypePriorityValue(TermType::VariableTerm));
    EXPECT_EQ(4, getTermTypePriorityValue(TermType::Expression));
}

TEST(EnumHelpersTest, GetDualOperatorLevelWorks) {    EXPECT_EQ(OperatorLevel::Unknown, getDualOperatorLevel(OperatorLevel::Unknown));
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
