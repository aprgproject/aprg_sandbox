#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

namespace Simplification
{

TEST(SimplificationOfExpressionTest, SimplifyWorksOnSimplifyingInnerTerms)
{
    Expression subExpression1(createExpressionIfPossible({"x", "&", "x"}));
    Expression subExpression2(createExpressionIfPossible({"y", "|", "y"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForAMultipleTermExpression)
{
    Term expressionTerm(createExpressionIfPossible({"x", "&", "y"}));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationDifferentExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({"c", "&", "d"}));
    Term expressionTermLevel2(createExpressionIfPossible({"b", "&", expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({"a", "&", expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationDifferentExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({"c", "|", "d"}));
    Term expressionTermLevel2(createExpressionIfPossible({"b", "|", expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({"a", "|", expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForASingleTermExpression)
{
    Term expressionTerm(createAndWrapExpressionFromATerm("x"));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithNullExpressions)
{
    Expression nullExpression(createExpressionInAnExpression(Expression()));
    Expression expressionToTest(createExpressionIfPossible({nullExpression, "&", nullExpression, "&", nullExpression}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect;
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithTrue)
{
    Expression expressionToTest(createExpressionIfPossible({"a", "&", "b", "&", true, "&", "c", "&", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithFalse)
{
    Expression expressionToTest(createExpressionIfPossible({"a", "&", "b", "&", false, "&", "c", "&", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationWithTrue)
{
    Expression expressionToTest(createExpressionIfPossible({"a", "|", "b", "|", false, "|", "c", "|", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationWithFalse)
{
    Expression expressionToTest(createExpressionIfPossible({"a", "|", "b", "|", true, "|", "c", "|", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRemovingSameTermsInAndOperationInDifferentLevels)
{
    Expression subExpression1(createExpressionIfPossible({"x", "&", "x"}));
    Expression subExpression2(createExpressionIfPossible({"x", "&", subExpression1}));
    Expression expressionToTest(createExpressionIfPossible({"x", "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRemovingSameTermsInOrOperationInDifferentLevels)
{
    Expression subExpression1(createExpressionIfPossible({"x", "|", "x"}));
    Expression subExpression2(createExpressionIfPossible({"x", "|", subExpression1}));
    Expression expressionToTest(createExpressionIfPossible({"x", "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksBySortingTermsInAndOperationInDifferentLevels)
{
    Expression subExpression1(createExpressionIfPossible({"b", "&", "a"}));
    Expression subExpression2(createExpressionIfPossible({"c", "&", subExpression1}));
    Expression expressionToTest(createExpressionIfPossible({"d", "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksBySortingTermsInOrOperationInDifferentLevels)
{
    Expression subExpression1(createExpressionIfPossible({"b", "|", "a"}));
    Expression subExpression2(createExpressionIfPossible({"c", "|", subExpression1}));
    Expression expressionToTest(createExpressionIfPossible({"d", "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByComplimentaryTermsInAndOperation)
{
    Expression expressionToTest(createExpressionIfPossible({"x", "&", VariableTerm("x", true)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByComplimentaryTermsInOrOperation)
{
    Expression expressionToTest(createExpressionIfPossible({"x", "|", VariableTerm("x", true)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByWithOuterOrAndInnerAnd)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyByQuineMcKluskey = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression subExpression2(createExpressionIfPossible({VariableTerm("x", true), "|", "z"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((x&z)|(x'&y))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithOuterAndAndInnerOr)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    configurationDetails.shouldSimplifyByQuineMcKluskey = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression subExpression1(createExpressionIfPossible({VariableTerm("x", true), "|", "y"}));
    Expression subExpression2(createExpressionIfPossible({"x", "|", "z"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((x|z)&(x'|y))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}
TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperation_WithDefaultConfiguration)
{
    Expression subExpression1(createExpressionIfPossible({"a", "&", "b"}));    Expression subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));
    Expression subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperation_WithOuterOrAndInnerAnd)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"a", "&", "b"}));
    Expression subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));    Expression subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperation_WithOuterAndAndInnerOr)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"a", "&", "b"}));
    Expression subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));    Expression subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("(f&(a|c|e)&(b|c|e)&(d|e))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByRemovingNeededTerms_WithOuterOrAndInnerAnd)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"x", "|", VariableTerm("y", true)}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "&", "y"}));
    SimplificationOfExpression simplification(expressionToTest);
    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByRemovingNeededTerms_WithOuterAndAndInnerOr)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"x", "&", VariableTerm("y", true)}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "|", "y"}));
    SimplificationOfExpression simplification(expressionToTest);
    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactor_Pattern1)
{
    Expression subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression subExpression2(createExpressionIfPossible({"x", "&", VariableTerm("y", true)}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactor_Pattern2)
{
    Expression subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression subExpression2(createExpressionIfPossible({"x", "|", VariableTerm("y", true)}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactor_Pattern3)
{
    Expression subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression expressionToTest(createExpressionIfPossible({"x", "|", subExpression1}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactor_Pattern4)
{
    Expression subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression expressionToTest(createExpressionIfPossible({"x", "&", subExpression1}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConsensusTheoremPattern1)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyByQuineMcKluskey = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression subExpression2(createExpressionIfPossible({"y", "&", "z"}));
    Expression subExpression3(createExpressionIfPossible({VariableTerm("x", true), "&", "z"}));    Expression expressionToTest(createExpressionIfPossible({subExpression1, "|", subExpression2, "|", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((x&y)|(x'&z))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConsensusTheoremPattern2)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    configurationDetails.shouldSimplifyByQuineMcKluskey = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression subExpression2(createExpressionIfPossible({"y", "|", "z"}));
    Expression subExpression3(createExpressionIfPossible({VariableTerm("x", true), "|", "z"}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2, "&", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string stringToVerify(simplification.getExpression().getDisplayableString());
    string stringToExpect("((x|y)&(x'|z))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

}

}

}