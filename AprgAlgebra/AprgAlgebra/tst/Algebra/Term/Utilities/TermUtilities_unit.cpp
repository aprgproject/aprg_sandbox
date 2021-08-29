#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(TermUtilitiesTest, IsNegatedTermSimplerWorks)
{
    Term xToTheX(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Term negativeXToTheX(createExpressionIfPossible({Term(-1), Term("*"), Term("x"), Term("^"), Term("x")}));

    EXPECT_FALSE(isNegatedTermSimpler(xToTheX, negativeXToTheX));
    EXPECT_TRUE(isNegatedTermSimpler(negativeXToTheX, xToTheX));
    EXPECT_FALSE(isNegatedTermSimpler(Term(Monomial(5, {})), Term(Monomial(-5, {}))));
    EXPECT_TRUE(isNegatedTermSimpler(Term(Monomial(-5, {})), Term(Monomial(5, {}))));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorTypeWorks)
{
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

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorOrNonExpressionTypeWorks)
{
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

TEST(TermUtilitiesTest, IsRadicalTermWorks)
{
    Term nonMonomialOrExpressionTerm("x");
    Term monomialWithIntegerExponent(Monomial(1, {{"x", 34}}));
    Term monomialWithDoubleExponent(Monomial(1, {{"x", 3.4}}));
    Term nonRaiseToPowerExpressionTerm(createExpressionIfPossible({Term("x"), Term("*"), Term("x")}));
    Term raiseToIntegerExpressionTerm(createExpressionIfPossible({Term("x"), Term("^"), Term(5)}));
    Term raiseToDoubleExpressionTerm(createExpressionIfPossible({Term("x"), Term("^"), Term(1.79)}));
    Term multipleRaiseToPowerExpressionTerm(createExpressionIfPossible({Term("x"), Term("^"), Term(1.79), Term("^"), Term("y")}));
    Term raiseToMonomialWithDoubleExpressionTerm(createExpressionIfPossible({Term("x"), Term("^"), Term(Monomial(2.84, {{"x", 2}, {"y", 3}}))}));

    EXPECT_FALSE(isRadicalTerm(nonMonomialOrExpressionTerm));
    EXPECT_FALSE(isRadicalTerm(monomialWithIntegerExponent));
    EXPECT_TRUE(isRadicalTerm(monomialWithDoubleExponent));
    EXPECT_FALSE(isRadicalTerm(nonRaiseToPowerExpressionTerm));
    EXPECT_FALSE(isRadicalTerm(raiseToIntegerExpressionTerm));
    EXPECT_TRUE(isRadicalTerm(raiseToDoubleExpressionTerm));
    EXPECT_TRUE(isRadicalTerm(multipleRaiseToPowerExpressionTerm));
    EXPECT_TRUE(isRadicalTerm(raiseToMonomialWithDoubleExpressionTerm));
}

TEST(TermUtilitiesTest, EvaluateAndGetInputOutputPairWorks)
{
    AlbaNumbers inputNumbers{-2,-1,0,1,2};

    AlbaNumberPairs inputAndOutputPairs(
                evaluateAndGetInputOutputPair(
                    inputNumbers,
                    "x",
                    Term(Monomial(-2, {{"x", 3}}))
                    ));

    ASSERT_EQ(5U, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(0).first);
    EXPECT_EQ(AlbaNumber(16), inputAndOutputPairs.at(0).second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs.at(1).first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(1).second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(3).first);
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(3).second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(4).first);
    EXPECT_EQ(AlbaNumber(-16), inputAndOutputPairs.at(4).second);
}

}

}
