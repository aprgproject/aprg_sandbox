#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace booleanAlgebra
{

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorTypeWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term5));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorOrNonExpressionTypeWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term4));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term5));
}

TEST(TermUtilitiesTest, GetNoEffectValueInOperationWorks)
{
    EXPECT_FALSE(getNoEffectValueInOperation(OperatorLevel::Unknown));
    EXPECT_TRUE(getNoEffectValueInOperation(OperatorLevel::And));
    EXPECT_FALSE(getNoEffectValueInOperation(OperatorLevel::Or));
}

TEST(TermUtilitiesTest, GetShortCircuitValueEffectInOperationWorks)
{
    EXPECT_FALSE(getShortCircuitValueEffectInOperation(OperatorLevel::Unknown));
    EXPECT_FALSE(getShortCircuitValueEffectInOperation(OperatorLevel::And));
    EXPECT_TRUE(getShortCircuitValueEffectInOperation(OperatorLevel::Or));
}

TEST(TermUtilitiesTest, GetVariableNamesWorks)
{
    Term subTerm1(createExpressionIfPossible({"a", "&", "b"}));
    Term subTerm2(createExpressionIfPossible({"x", "&", "y"}));
    Term termToTest(createExpressionIfPossible({subTerm1, "|", subTerm2}));

    VariableNamesSet namesToVerify(getVariableNames(termToTest));

    VariableNamesSet namesToExpect{"a", "b", "x", "y"};
    EXPECT_EQ(namesToExpect, namesToVerify);
}

TEST(TermUtilitiesTest, GetTermFromVariableAndPrimeValueWorks)
{
    EXPECT_EQ(Term("x'"), getTermFromVariableAndPrimeValue("x", '0'));
    EXPECT_EQ(Term("x"), getTermFromVariableAndPrimeValue("x", '1'));
}

}
}