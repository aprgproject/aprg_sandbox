#include <Algebra/Term/Utilities/EnumHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(EnumHelpersTest, GetAssociationPriorityWorks)
{
    EXPECT_EQ(1u, getAssociationPriority(TermAssociationType::Positive));
    EXPECT_EQ(2u, getAssociationPriority(TermAssociationType::Negative));
}

TEST(EnumHelpersTest, GetOperatorLevelInversePriorityWorks)
{
    EXPECT_EQ(0u, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(3u, getOperatorLevelInversePriority(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ(2u, getOperatorLevelInversePriority(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ(1u, getOperatorLevelInversePriority(OperatorLevel::RaiseToPower));
}

TEST(EnumHelpersTest, GetTermPriorityValueWorks)
{
    EXPECT_EQ(0u, getTermTypePriorityValue(TermType::Empty));
    EXPECT_EQ(1u, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2u, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3u, getTermTypePriorityValue(TermType::Variable));
    EXPECT_EQ(4u, getTermTypePriorityValue(TermType::Monomial));
    EXPECT_EQ(5u, getTermTypePriorityValue(TermType::Polynomial));
    EXPECT_EQ(6u, getTermTypePriorityValue(TermType::Expression));
    EXPECT_EQ(7u, getTermTypePriorityValue(TermType::Function));
}

TEST(EnumHelpersTest, GetEnumShortStringForTermTypeWorks)
{
    EXPECT_EQ("Empty", getEnumShortString(TermType::Empty));
    EXPECT_EQ("Constant", getEnumShortString(TermType::Constant));
    EXPECT_EQ("Variable", getEnumShortString(TermType::Variable));
    EXPECT_EQ("Operator", getEnumShortString(TermType::Operator));
    EXPECT_EQ("Monomial", getEnumShortString(TermType::Monomial));
    EXPECT_EQ("Polynomial", getEnumShortString(TermType::Polynomial));
    EXPECT_EQ("Expression", getEnumShortString(TermType::Expression));
    EXPECT_EQ("Function", getEnumShortString(TermType::Function));
}

TEST(EnumHelpersTest, GetEnumShortStringForTermAssociationTypeWorks)
{
    EXPECT_EQ("{POS}", getEnumShortString(TermAssociationType::Positive));
    EXPECT_EQ("{NEG}", getEnumShortString(TermAssociationType::Negative));
}

TEST(EnumHelpersTest, GetEnumShortStringForOperatorLevelWorks)
{
    EXPECT_EQ("{?}", getEnumShortString(OperatorLevel::Unknown));
    EXPECT_EQ("{+-}", getEnumShortString(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ("{*/}", getEnumShortString(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ("{^}", getEnumShortString(OperatorLevel::RaiseToPower));
}

}

}
