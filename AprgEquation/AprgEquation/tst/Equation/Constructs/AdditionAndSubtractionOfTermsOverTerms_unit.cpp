#include <Equation/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(AdditionAndSubtractionOfTermsOverTermsTest, ConstructionWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getItems().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoTermsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {});
    TermsOverTerms fraction2({Term(1)}, {});
    TermsOverTerms fraction3({Term(1)}, {});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithTermsThatAreEmptyWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term()});
    TermsOverTerms fraction2({Term(1)}, {Term()});
    TermsOverTerms fraction3({Term(1)}, {Term()});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}
TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithAllOneWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term(1)});
    TermsOverTerms fraction2({Term(1)}, {Term(1)});
    TermsOverTerms fraction3({Term(1)}, {Term(1)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithLcmMonomialWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term(Polynomial{Monomial(3, {{"x", 3}})})});
    TermsOverTerms fraction2({Term(1)}, {Term(Monomial(5, {{"x", 5}}))});
    TermsOverTerms fraction3({Term(1)}, {Term(Monomial(7, {{"y", 7}}))});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Monomial(105, {{"x", 5}, {"y", 7}}));
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoCommonFactorsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})});
    TermsOverTerms fraction2({Term(1)}, {Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})})});
    TermsOverTerms fraction3({Term(1)}, {Term(Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Term termToExpect3(Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})});
    ASSERT_EQ(3u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
    EXPECT_EQ(termToExpect3, termsToVerify.at(2));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithCommonFactorsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms fraction1({Term(1)}, {Term(polynomial)});
    TermsOverTerms fraction2({Term(1)}, {Term(), Term(polynomial)});
    TermsOverTerms fraction3({Term(1)}, {Term(polynomial), Term(polynomial), Term(polynomial)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect(polynomial);
    ASSERT_EQ(3u, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
    EXPECT_EQ(termToExpect, termsToVerify.at(1));
    EXPECT_EQ(termToExpect, termsToVerify.at(2));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithFactorsOfDifferenceOfSquaresWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(1)}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(1)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingOutOfRangeIndexReturnsEmpty)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;

    Terms termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));
    Terms termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, {}));
    Terms termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, {}));

    ASSERT_TRUE(termsToVerify1.empty());
    ASSERT_TRUE(termsToVerify2.empty());
    ASSERT_TRUE(termsToVerify3.empty());
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsEmpty)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})})}, {Term(1)});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));

    Term termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsOne)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})})}, {Term(1)});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {Term(1)}));

    Term termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsGcfOfDenominatorAndLcm)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(1)}, {Term(Monomial(4, {{"x", 5}, {"y", 3}}))});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {Term(Monomial(52, {{"x", 7}, {"y", 8}}))}));

    Term termToExpect(Monomial(13, {{"x", 2}, {"y", 5}}));
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsWithCommonFactorsFromDenominatorAndLcmRemoved)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms fraction({Term(1)}, {Term(polynomial)});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {Term(polynomial), Term(polynomial), Term(polynomial)}));

    Term termToExpect(polynomial);
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
    EXPECT_EQ(termToExpect, termsToVerify.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingAComplicatedExampleWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(4)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})})}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);
    Terms denominatorTerms(additionAndSubtraction.getLcmOfDenominatorTerms());

    Terms termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, denominatorTerms));
    Terms termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, denominatorTerms));
    Terms termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, denominatorTerms));

    Term termToExpect1(4);
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term termToExpect3(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term termToExpect4(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect5(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    ASSERT_EQ(2u, termsToVerify1.size());
    EXPECT_EQ(termToExpect1, termsToVerify1.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify1.at(1));
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(termToExpect3, termsToVerify2.at(0));
    ASSERT_EQ(2u, termsToVerify3.size());
    EXPECT_EQ(termToExpect4, termsToVerify3.at(0));
    EXPECT_EQ(termToExpect5, termsToVerify3.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForNumeratorTermsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(7)}, {Term(1)});
    TermsOverTerms fraction2({Term(11)}, {Term(1)});
    TermsOverTerms fraction3({Term(13)}, {Term(1)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({Term(7)}));
    Expression subExpression2(createExpressionIfPossible({Term(11)}));
    Expression subExpression3(createExpressionIfPossible({Term(13)}));
    Expression subExpression4(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForLcmDenominatorWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(1)}, {Term(2)});
    TermsOverTerms fraction2({Term(1)}, {Term(3)});
    TermsOverTerms fraction3({Term(1)}, {Term(4)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({Term(createMonomialFromConstant(6))}));
    Expression subExpression2(createExpressionIfPossible({Term(createMonomialFromConstant(4))}));
    Expression subExpression3(createExpressionIfPossible({Term(createMonomialFromConstant(3))}));
    Expression subExpression4(createExpressionIfPossible({Term(subExpression1), Term("+"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4), Term("/"), Term(12)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForRevisedNumeratorTermsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(7)}, {Term(2)});
    TermsOverTerms fraction2({Term(11)}, {Term(3)});
    TermsOverTerms fraction3({Term(13)}, {Term(4)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({Term(7), Term("*"), Term(createMonomialFromConstant(6))}));
    Expression subExpression2(createExpressionIfPossible({Term(11), Term("*"), Term(createMonomialFromConstant(4))}));
    Expression subExpression3(createExpressionIfPossible({Term(13), Term("*"), Term(createMonomialFromConstant(3))}));
    Expression subExpression4(createExpressionIfPossible({Term(subExpression1), Term("-"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4), Term("/"), Term(12)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionUsingExample1Works)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(4)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})})}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial polynomial4{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Expression subExpression1(createExpressionIfPossible({Term(4), Term("*"), Term(polynomial1)}));
    Expression subExpression2(createExpressionIfPossible({Term(polynomial3)}));
    Expression subExpression3(createExpressionIfPossible({Term(polynomial4), Term("*"), Term(polynomial2)}));
    Expression subExpression4(createExpressionIfPossible({Term(subExpression1), Term("+"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4), Term("/"), Term(polynomial2), Term("/"), Term(polynomial1)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyWorksOnExponentPlusPolynomialDenominator)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression exponentExpression(createExpressionIfPossible({Term(2), Term("^"), Term("x")}));
    TermsOverTerms fraction1({Term(exponentExpression)}, {});
    TermsOverTerms fraction2({}, {Term(polynomial)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("*"), Term(exponentExpression)}));
    Expression subExpression2(createExpressionIfPossible({Term(2), Term("*"), Term(exponentExpression)}));
    Expression subExpression3(createExpressionIfPossible({Term(1), Term("+"), Term(subExpression1), Term("+"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression3), Term("/"), Term(polynomial)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample1Works)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(4)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})})}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial polynomialToExpect1{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression expressionToExpect(createExpressionIfPossible({Term(polynomialToExpect1), Term("/"), Term(polynomialToExpect2)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample2Works)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial1{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomial2{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial polynomial4{Monomial(6, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(-12, {})};
    Polynomial polynomial5{Monomial(2, {{"x", 1}}), Monomial(-3, {})};
    Polynomial polynomial6{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(8, {})};
    TermsOverTerms fraction1({Term(polynomial1)}, {Term(polynomial2)});
    TermsOverTerms fraction2({Term(polynomial3)}, {Term(polynomial4)});
    TermsOverTerms fraction3({Term(polynomial5)}, {Term(polynomial6)});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsSubtraction(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect2{Monomial(6, {{"x", 3}}), Monomial(-11, {{"x", 2}}), Monomial(-14, {{"x", 1}}), Monomial(24, {})};
    Expression expressionToExpect(createExpressionIfPossible({Term(polynomialToExpect1), Term("/"), Term(polynomialToExpect2)}));    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAdditionWorks){
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(487)}, {Term(756)});

    additionAndSubtraction.putAsAddition(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1u, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1u, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1u, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, associationToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsSubtractionWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(487)}, {Term(756)});

    additionAndSubtraction.putAsSubtraction(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1u, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1u, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1u, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAddOrSubtractionWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Term(487)}, {Term(756)});

    additionAndSubtraction.putAsAddOrSubtraction(fraction, TermAssociationType::Negative);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1u, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1u, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1u, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify.at(0));
}

}

}
