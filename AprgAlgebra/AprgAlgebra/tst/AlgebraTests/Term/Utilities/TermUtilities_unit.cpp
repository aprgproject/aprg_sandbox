#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;

namespace alba {

namespace algebra {

TEST(TermUtilitiesTest, IsNegatedTermSimplerWorks) {
    Term xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term negativeXToTheX(createExpressionIfPossible({-1, "*", "x", "^", "x"}));

    EXPECT_FALSE(isNegatedTermSimpler(xToTheX, negativeXToTheX));
    EXPECT_TRUE(isNegatedTermSimpler(negativeXToTheX, xToTheX));
    EXPECT_FALSE(isNegatedTermSimpler(Monomial(5, {}), Monomial(-5, {})));
    EXPECT_TRUE(isNegatedTermSimpler(Monomial(-5, {}), Monomial(5, {})));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorTypeWorks) {
    Term term1;
    Term term2(1);
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term6));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term8));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorOrNonExpressionTypeWorks) {
    Term term1;
    Term term2(1);
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term6));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term8));
}

TEST(TermUtilitiesTest, IsARadicalTermWorks) {
    Term nonMonomialOrExpressionTerm("x");
    Term monomialWithIntegerExponent(Monomial(1, {{"x", 34}}));
    Term monomialWithDoubleExponent(Monomial(1, {{"x", 3.4}}));
    Term nonRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "*", "x"}));
    Term raiseToIntegerExpressionTerm(createExpressionIfPossible({"x", "^", 5}));
    Term raiseToDoubleExpressionTerm(createExpressionIfPossible({"x", "^", 1.79}));
    Term multipleRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "^", 1.79, "^", "y"}));
    Term raiseToMonomialWithDoubleExpressionTerm(
        createExpressionIfPossible({"x", "^", Monomial(2.84, {{"x", 2}, {"y", 3}})}));

    EXPECT_FALSE(isARadicalTerm(nonMonomialOrExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(monomialWithIntegerExponent));
    EXPECT_TRUE(isARadicalTerm(monomialWithDoubleExponent));
    EXPECT_FALSE(isARadicalTerm(nonRaiseToPowerExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(raiseToIntegerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToDoubleExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(multipleRaiseToPowerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToMonomialWithDoubleExpressionTerm));
}

TEST(TermUtilitiesTest, GetNumberOfTermsWorks) {
    EXPECT_EQ(7, getNumberOfTerms(createExpressionIfPossible({"w", "+", "x", "*", "y", "^", "z"})));
}

TEST(TermUtilitiesTest, GetConstantFactorWorks) {
    EXPECT_EQ(AlbaNumber(5), getConstantFactor(5));
    EXPECT_EQ(AlbaNumber(6), getConstantFactor(Monomial(6, {{"x", 7}})));
    EXPECT_EQ(AlbaNumber(4), getConstantFactor(Polynomial{Monomial(8, {{"x", 3}}), Monomial(12, {{"x", 4}})}));
    EXPECT_EQ(AlbaNumber(1), getConstantFactor("x"));
}

TEST(TermUtilitiesTest, EvaluateAndGetInputOutputPairWorks) {
    AlbaNumbers inputNumbers{-2, -1, 0, 1, 2};

    AlbaNumberPairs inputAndOutputPairs(evaluateAndGetInputOutputPair(inputNumbers, "x", Monomial(-2, {{"x", 3}})));

    ASSERT_EQ(5U, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs[0].first);
    EXPECT_EQ(AlbaNumber(16), inputAndOutputPairs[0].second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs[1].first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[1].second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs[3].first);
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs[3].second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[4].first);
    EXPECT_EQ(AlbaNumber(-16), inputAndOutputPairs[4].second);
}

TEST(TermUtilitiesTest, GetPiAsTermWorks) { EXPECT_EQ(Term(ALBA_NUMBER_PI), getPiAsATerm()); }
TEST(TermUtilitiesTest, GetEAsTermWorks) { EXPECT_EQ(Term(ALBA_NUMBER_E), getEAsATerm()); }

TEST(TermUtilitiesTest, GetPositiveInfinityAsATermWorks) {    EXPECT_EQ(Term(ALBA_NUMBER_POSITIVE_INFINITY), getPositiveInfinityAsATerm());
}

TEST(TermUtilitiesTest, GetNegativeInfinityAsATermWorks) {
    EXPECT_EQ(Term(ALBA_NUMBER_NEGATIVE_INFINITY), getNegativeInfinityAsATerm());
}

TEST(TermUtilitiesTest, ConvertPositiveTermIfNegativeWorks) {
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(-5));
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(5));
}

TEST(TermUtilitiesTest, NegateTermWorks) {
    Term sinX(sin("x"));
    Term sinY(sin("y"));
    Term sinZ(sin("z"));
    Term term1(createExpressionIfPossible({sinX, "+", sinY, "-", sinZ}));
    Term term2(createExpressionIfPossible({sinX, "*", sinY, "/", sinZ}));
    Term term3(createExpressionIfPossible({sinX, "^", sinY, "^", sinZ}));

    Term termToVerify1(negateTerm(5));
    Term termToVerify2(negateTerm("x"));
    Term termToVerify3(negateTerm(term1));
    Term termToVerify4(negateTerm(term2));
    Term termToVerify5(negateTerm(term3));

    Term termToExpect1(-5);
    Term termToExpect2(Monomial(-1, {{"x", 1}}));
    Term termToExpect3(createExpressionIfPossible({sinZ, "-", sinX, "-", sinY}));
    Term termToExpect4(createExpressionIfPossible({-1, "*", sinX, "*", sinY, "/", sinZ}));
    Term termToExpect5(createExpressionIfPossible({-1, "*", sinX, "^", "(", sinY, "*", sinZ, ")"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, FlipTermWorks) { EXPECT_EQ(Term(AlbaNumber::createFraction(1, 5)), flipTerm(5)); }

TEST(TermUtilitiesTest, NegateTermIfHasNegativeAssociationWorks) {
    EXPECT_EQ(Term(5), negateTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Positive}));
    EXPECT_EQ(Term(-5), negateTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Negative}));
}

TEST(TermUtilitiesTest, FlipTermIfHasNegativeAssociationWorks) {
    EXPECT_EQ(Term(5), flipTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Positive}));
    EXPECT_EQ(
        Term(AlbaNumber::createFraction(1, 5)),
        flipTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Negative}));
}

TEST(TermUtilitiesTest, InvertTermWorks) {
    Term termToTest1(5);
    Term termToTest2("x");
    Term termToTest3(Monomial(1, {{"x", 4}}));
    Term termToTest4(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    Term termToTest5(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", AlbaNumber::createFraction(1, 2)}));

    Term termToVerify1(invertTerm(termToTest1, "x"));
    Term termToVerify2(invertTerm(termToTest2, "x"));
    Term termToVerify3(invertTerm(termToTest3, "x"));
    Term termToVerify4(invertTerm(termToTest4, "x"));
    Term termToVerify5(invertTerm(termToTest5, "x"));

    Term termToExpect1;
    Term termToExpect2("x");
    Term termToExpect3(Monomial(1, {{"x", AlbaNumber::createFraction(1, 4)}}));
    Term termToExpect4(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", AlbaNumber::createFraction(1, 2)}));
    Term termToExpect5(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, NegateExpressionWorks) {
    Expression expression1(createExpressionIfPossible({-5, "+", "x"}));
    Expression expression2(createExpressionIfPossible({5, "+", "x"}));
    Expression expression3(createExpressionIfPossible({-5, "*", "x"}));
    Expression expression4(createExpressionIfPossible({-5, "*", -3}));
    Expression expression5(createExpressionIfPossible({-5, "^", "x"}));

    Expression expressionToVerify1(negateExpression(expression1));
    Expression expressionToVerify2(negateExpression(expression2));
    Expression expressionToVerify3(negateExpression(expression3));
    Expression expressionToVerify4(negateExpression(expression4));
    Expression expressionToVerify5(negateExpression(expression5));

    Expression expectedExpression1(createExpressionIfPossible({Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}}));
    Expression expectedExpression2(
        createExpressionIfPossible({Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}}));
    Expression expectedExpression3(createExpressionIfPossible({Monomial(5, {{"x", 1}})}));
    Expression expectedExpression4(createExpressionIfPossible({-15}));
    Expression subExpression5(createExpressionIfPossible({-5, "^", "x"}));
    Expression expectedExpression5(createExpressionIfPossible({-1, "*", subExpression5}));
    EXPECT_EQ(expectedExpression1, expressionToVerify1);
    EXPECT_EQ(expectedExpression2, expressionToVerify2);
    EXPECT_EQ(expectedExpression3, expressionToVerify3);
    EXPECT_EQ(expectedExpression4, expressionToVerify4);
    EXPECT_EQ(expectedExpression5, expressionToVerify5);
}

}  // namespace algebra

}  // namespace alba
