#include <Algebra/Retrieval/ExpressionAndFunctionsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromEquationsWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Equation equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromEquationWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromTermWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Term expesssionTerm1(createExpressionIfPossible({"a", "^", 2}));
    Term expesssionTerm2(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));
    Function functionObject(
        "functionName", expesssionTerm1, [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term functionTerm1(functionObject);

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("b"));
    retriever.retrieveFromTerm(Monomial(34, {{"c", 5}, {"d", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})});
    retriever.retrieveFromTerm(expesssionTerm2);
    retriever.retrieveFromTerm(functionTerm1);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(3U, termsSet.size());
    TermSet::const_iterator it = termsSet.cbegin();
    EXPECT_EQ(expesssionTerm1, *(it++));
    EXPECT_EQ(expesssionTerm2, *(it++));
    EXPECT_EQ(functionTerm1, *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromConstantWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromVariableWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromMonomialWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromPolynomialWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromExpressionWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Expression expression(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));

    retriever.retrieveFromExpression(expression);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(1U, termsSet.size());
    TermSet::const_iterator it = termsSet.cbegin();
    EXPECT_EQ(Term(expression), *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromFunctionWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Expression expression(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})}));
    Function functionObject(
        "functionName", Term(expression), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(2U, termsSet.size());
    TermSet::const_iterator it = termsSet.cbegin();
    EXPECT_EQ(Term(expression), *(it++));
    EXPECT_EQ(Term(functionObject), *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromPolynomialsWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

}  // namespace algebra

}  // namespace alba
