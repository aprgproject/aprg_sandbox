#include <Algebra/Simplification/SimplificationOfExpression.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

namespace Simplification {

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyToACommonDenominator());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToACommonDenominator = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyToACommonDenominator());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyToACommonDenominator());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyByCombiningRadicalsInMultiplicationAndDivisionWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyByRationalizingNumeratorWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByRationalizingNumerator());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByRationalizingNumerator = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByRationalizingNumerator());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByRationalizingNumerator());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyByRationalizingDenominatorWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByRationalizingDenominator());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByRationalizingDenominator = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByRationalizingDenominator());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByRationalizingDenominator());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyBySubstitutingExpressionAndFunctionsToVariablesWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToFactorsWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyToFactors());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToFactors = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyToFactors());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyToFactors());
}

TEST(SimplificationOfExpressionTest, ShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValueWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
}

TEST(SimplificationOfExpressionTest, ShouldNotSimplifyByDistributingConstantExponentToEachBaseWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldNotSimplifyByDistributingConstantExponentToEachBase());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldNotSimplifyByDistributingConstantExponentToEachBase = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldNotSimplifyByDistributingConstantExponentToEachBase());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldNotSimplifyByDistributingConstantExponentToEachBase());
}

TEST(SimplificationOfExpressionTest, ShouldPerformDebugWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldPerformDebug());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldPerformDebug = true;
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldPerformDebug());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldPerformDebug());
}

}  // namespace Simplification

}  // namespace algebra

}  // namespace alba
