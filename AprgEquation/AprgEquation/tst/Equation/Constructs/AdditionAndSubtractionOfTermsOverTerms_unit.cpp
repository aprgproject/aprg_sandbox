#include <Equation/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace equation
{

TEST(AdditionAndSubtractionOfTermsOverTerms, ConstructionWorks)
{
    AdditionAndSubtractionOfTermsOverTerms();
}

TEST(AdditionAndSubtractionOfTermsOverTerms, GetLcmOfDenominatorTermsWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(4)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})})}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});

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

TEST(AdditionAndSubtractionOfTermsOverTerms, GetNewNumeratorTermsOnLcmWorks)
{
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({Term(4)}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})})});
    TermsOverTerms fraction2({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})})}, {Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})});
    TermsOverTerms fraction3({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})})}, {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);
    Terms denominatorTerms(additionAndSubtraction.getLcmOfDenominatorTerms());

    Terms termsToVerify1(additionAndSubtraction.getNewNumeratorTermsOnLcm(0, denominatorTerms));
    Terms termsToVerify2(additionAndSubtraction.getNewNumeratorTermsOnLcm(1, denominatorTerms));
    Terms termsToVerify3(additionAndSubtraction.getNewNumeratorTermsOnLcm(2, denominatorTerms));

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

TEST(AdditionAndSubtractionOfTermsOverTerms, GetCombinedExpressionWorks)
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
    Expression subExpression1(createExpressionIfPossible(Terms{Term(4), Term("*"), Term(polynomial1)}));
    Expression subExpression2(createExpressionIfPossible(Terms{Term(polynomial3)}));
    Expression subExpression3(createExpressionIfPossible(Terms{Term(polynomial4), Term("*"), Term(polynomial2)}));
    Expression subExpression4(createExpressionIfPossible(Terms{Term(subExpression1), Term("+"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible(Terms{Term(subExpression4), Term("/"), Term(polynomial2), Term("/"), Term(polynomial1)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}



}

}
