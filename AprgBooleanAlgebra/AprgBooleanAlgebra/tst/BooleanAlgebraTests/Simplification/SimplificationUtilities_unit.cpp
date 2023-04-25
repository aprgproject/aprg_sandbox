#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Simplification/SimplificationUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace booleanAlgebra {

namespace Simplification {

TEST(SimplificationUtilitiesTest, SimplifyTermWithOuterOrAndInnerAndWorks) {
    Term subTerm1(createExpressionIfPossible({"a", "&", "b"}));
    Term subTerm2(createExpressionIfPossible({subTerm1, "|", "c"}));
    Term subTerm3(createExpressionIfPossible({subTerm2, "&", "d"}));
    Term subTerm4(createExpressionIfPossible({subTerm3, "|", "e"}));
    Term termToTest(createExpressionIfPossible({subTerm4, "&", "f"}));

    simplifyTermWithOuterOrAndInnerAnd(termToTest);

    string stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, convertToString(termToTest));
}

TEST(SimplificationUtilitiesTest, SimplifyTermWithOuterAndAndInnerOrWorks) {
    Term subTerm1(createExpressionIfPossible({"a", "&", "b"}));
    Term subTerm2(createExpressionIfPossible({subTerm1, "|", "c"}));
    Term subTerm3(createExpressionIfPossible({subTerm2, "&", "d"}));
    Term subTerm4(createExpressionIfPossible({subTerm3, "|", "e"}));
    Term termToTest(createExpressionIfPossible({subTerm4, "&", "f"}));

    simplifyTermWithOuterAndAndInnerOr(termToTest);

    string stringToExpect("(f&(a|c|e)&(b|c|e)&(d|e))");
    EXPECT_EQ(stringToExpect, convertToString(termToTest));
}

TEST(SimplificationUtilitiesTest, SimplifyByQuineMcKluskeyWorks) {
    Term subTerm1(createExpressionIfPossible({"a", "&", "b"}));
    Term subTerm2(createExpressionIfPossible({subTerm1, "|", "c"}));
    Term subTerm3(createExpressionIfPossible({subTerm2, "&", "d"}));
    Term subTerm4(createExpressionIfPossible({subTerm3, "|", "e"}));
    Term termToTest(createExpressionIfPossible({subTerm4, "&", "f"}));

    simplifyByQuineMcKluskey(termToTest);

    string stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, convertToString(termToTest));
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTerm) {
    WrappedTerms inputWrappedTerms{Term("x")};
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    WrappedTerms outputWrappedTerms;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputWrappedTerms, operatorLevel, inputWrappedTerms);

    WrappedTerms expectedWrappedTerms{Term("x")};
    EXPECT_EQ(expectedWrappedTerms, outputWrappedTerms);
}

TEST(
    SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTermWithManyExpressions) {
    Term oneTerm(createExpressionInAnExpression(createExpressionInAnExpression(createAndWrapExpressionFromATerm("x"))));
    WrappedTerms inputWrappedTerms{oneTerm};
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    WrappedTerms outputWrappedTerms;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputWrappedTerms, operatorLevel, inputWrappedTerms);

    WrappedTerms expectedWrappedTerms{Term("x")};
    EXPECT_EQ(expectedWrappedTerms, outputWrappedTerms);
}

TEST(SimplificationUtilitiesTest, CreateUniqueTermsWorks) {
    WrappedTerms wrappedTerms{Term("b"), Term("d"), Term("c"), Term("a"), Term("a"), Term("c"), Term("c")};

    Terms termsToVerify(createUniqueTerms(wrappedTerms));

    Terms termsToExpect{"a", "b", "c", "d"};
    EXPECT_EQ(termsToExpect, termsToVerify);
}

TEST(SimplificationUtilitiesTest, CombineComplementaryTermsWorks) {
    Terms termsToTest1{"x", "x'"};
    Terms termsToTest2{"x", "x'"};
    Terms termsToTest3{"a", "b'", "x", "c", "d'", "x'", "e", "f'"};
    Terms termsToTest4{"a", "b'", "x", "c", "d'", "x'", "e", "f'"};

    combineComplementaryTerms(termsToTest1, OperatorLevel::And);
    combineComplementaryTerms(termsToTest2, OperatorLevel::Or);
    combineComplementaryTerms(termsToTest3, OperatorLevel::And);
    combineComplementaryTerms(termsToTest4, OperatorLevel::Or);

    EXPECT_EQ((Terms{false}), termsToTest1);
    EXPECT_EQ((Terms{true}), termsToTest2);
    EXPECT_EQ((Terms{"a", "b'", false, "c", "d'", "e", "f'"}), termsToTest3);
    EXPECT_EQ((Terms{"a", "b'", true, "c", "d'", "e", "f'"}), termsToTest4);
}

TEST(SimplificationUtilitiesTest, CombineTermsByCheckingCommonFactorWorks) {
    Term xAndY(createExpressionIfPossible({"x", "&", "y"}));
    Term xOrY(createExpressionIfPossible({"x", "|", "y"}));
    Terms termsToTest1{"x", xAndY};
    Terms termsToTest2{"x", xAndY};
    Terms termsToTest3{"x", xOrY};
    Terms termsToTest4{"x", xOrY};
    Terms termsToTest5{"a", "b'", "x", "c", "d'", xAndY, "e", "f'"};
    Terms termsToTest6{"a", "b'", "x", "c", "d'", xAndY, "e", "f'"};
    Terms termsToTest7{"a", "b'", "x", "c", "d'", xOrY, "e", "f'"};
    Terms termsToTest8{"a", "b'", "x", "c", "d'", xOrY, "e", "f'"};

    combineTermsByCheckingCommonFactor(termsToTest1, OperatorLevel::And);
    combineTermsByCheckingCommonFactor(termsToTest2, OperatorLevel::Or);
    combineTermsByCheckingCommonFactor(termsToTest3, OperatorLevel::And);
    combineTermsByCheckingCommonFactor(termsToTest4, OperatorLevel::Or);
    combineTermsByCheckingCommonFactor(termsToTest5, OperatorLevel::And);
    combineTermsByCheckingCommonFactor(termsToTest6, OperatorLevel::Or);
    combineTermsByCheckingCommonFactor(termsToTest7, OperatorLevel::And);
    combineTermsByCheckingCommonFactor(termsToTest8, OperatorLevel::Or);

    EXPECT_EQ((Terms{xAndY}), termsToTest1);
    EXPECT_EQ((Terms{"x"}), termsToTest2);
    EXPECT_EQ((Terms{"x"}), termsToTest3);
    EXPECT_EQ((Terms{xOrY}), termsToTest4);
    EXPECT_EQ((Terms{"a", "b'", xAndY, "c", "d'", "e", "f'"}), termsToTest5);
    EXPECT_EQ((Terms{"a", "b'", "x", "c", "d'", "e", "f'"}), termsToTest6);
    EXPECT_EQ((Terms{"a", "b'", "x", "c", "d'", "e", "f'"}), termsToTest7);
    EXPECT_EQ((Terms{"a", "b'", xOrY, "c", "d'", "e", "f'"}), termsToTest8);
}

TEST(SimplificationUtilitiesTest, CombineTwoTermsByCheckingCommonFactorIfPossibleWorks) {
    Term xAndY(createExpressionIfPossible({"x", "&", "y"}));
    Term xOrY(createExpressionIfPossible({"x", "|", "y"}));

    Term termToVerify1(combineTwoTermsByCheckingCommonFactorIfPossible("x", xAndY, OperatorLevel::And));
    Term termToVerify2(combineTwoTermsByCheckingCommonFactorIfPossible("x", xAndY, OperatorLevel::Or));
    Term termToVerify3(combineTwoTermsByCheckingCommonFactorIfPossible("x", xOrY, OperatorLevel::And));
    Term termToVerify4(combineTwoTermsByCheckingCommonFactorIfPossible("x", xOrY, OperatorLevel::Or));
    Term termToVerify5(combineTwoTermsByCheckingCommonFactorIfPossible("x", xAndY, OperatorLevel::And));
    Term termToVerify6(combineTwoTermsByCheckingCommonFactorIfPossible("x", xAndY, OperatorLevel::Or));
    Term termToVerify7(combineTwoTermsByCheckingCommonFactorIfPossible("x", xOrY, OperatorLevel::And));
    Term termToVerify8(combineTwoTermsByCheckingCommonFactorIfPossible("x", xOrY, OperatorLevel::Or));

    EXPECT_EQ("(x&y)", convertToString(termToVerify1));
    EXPECT_EQ("x", convertToString(termToVerify2));
    EXPECT_EQ("x", convertToString(termToVerify3));
    EXPECT_EQ("(x|y)", convertToString(termToVerify4));
    EXPECT_EQ("(x&y)", convertToString(termToVerify5));
    EXPECT_EQ("x", convertToString(termToVerify6));
    EXPECT_EQ("x", convertToString(termToVerify7));
    EXPECT_EQ("(x|y)", convertToString(termToVerify8));
}

TEST(SimplificationUtilitiesTest, DistributeTermsIfNeededWorks) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    SimplificationOfExpression::ScopeObject scopeObject;

    Term xAndY(createExpressionIfPossible({"x", "&", "y"}));
    Term xOrY(createExpressionIfPossible({"x", "|", "y"}));
    Term termToTest1("a");
    Term termToTest2("b");
    Term termToTest3("c");
    Term termToTest4("d");

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = false;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    distributeTermsIfNeeded(termToTest1, {"x", xAndY, xOrY}, OperatorLevel::And, OperatorLevel::Or);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = false;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    distributeTermsIfNeeded(termToTest2, {"x", xAndY, xOrY}, OperatorLevel::Or, OperatorLevel::And);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = false;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    distributeTermsIfNeeded(termToTest3, {"x", xAndY, xOrY}, OperatorLevel::And, OperatorLevel::Or);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = false;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    distributeTermsIfNeeded(termToTest4, {"x", xAndY, xOrY}, OperatorLevel::Or, OperatorLevel::And);

    EXPECT_EQ("(a|(x&x&y&x)|(x&x&y&y))", convertToString(termToTest1));
    EXPECT_EQ("(b&(x|x|y|x)&(x|x|y|y))", convertToString(termToTest2));
    EXPECT_EQ("(c|(x&x&y&x)|(x&x&y&y))", convertToString(termToTest3));
    EXPECT_EQ("(d&(x|x|y|x)&(x|x|y|y))", convertToString(termToTest4));
}

TEST(SimplificationUtilitiesTest, RetrieveTargetOperationsWorks) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    SimplificationOfExpression::ScopeObject scopeObject;

    OperatorLevel targetOuter, targetInner;

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = false;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = false;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    retrieveTargetOperations(targetOuter, targetInner);
    EXPECT_EQ(OperatorLevel::Or, targetOuter);
    EXPECT_EQ(OperatorLevel::And, targetInner);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = false;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    retrieveTargetOperations(targetOuter, targetInner);
    EXPECT_EQ(OperatorLevel::Or, targetOuter);
    EXPECT_EQ(OperatorLevel::And, targetInner);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = false;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    retrieveTargetOperations(targetOuter, targetInner);
    EXPECT_EQ(OperatorLevel::And, targetOuter);
    EXPECT_EQ(OperatorLevel::Or, targetInner);

    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    retrieveTargetOperations(targetOuter, targetInner);
    EXPECT_EQ(OperatorLevel::Or, targetOuter);
    EXPECT_EQ(OperatorLevel::And, targetInner);
}

}  // namespace Simplification

}  // namespace booleanAlgebra

}  // namespace alba
