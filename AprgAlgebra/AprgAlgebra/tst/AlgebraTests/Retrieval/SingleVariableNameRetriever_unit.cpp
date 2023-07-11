#include <Algebra/Retrieval/SingleVariableNameRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(SingleVariableNameRetrieverTest, RetrieveFromEquationsWorks) {
    SingleVariableNameRetriever retriever;
    Equation equation1("1", "=", "1");
    Equation equation2("0", "=", "0");
    Equation equation3("2", "!=", "g");

    retriever.retrieveFromEquations(Equations{equation1, equation2, equation3});

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("g", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromEquationWorks) {
    SingleVariableNameRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_FALSE(retriever.hasOnlyASingleVariable());
    EXPECT_TRUE(retriever.hasMultipleVariables());
    EXPECT_TRUE(retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty().empty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromTermWorks) {
    SingleVariableNameRetriever retriever;
    Function functionObject(
        "functionName", Term(createExpressionIfPossible({"a", "^", 2})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("b"));
    retriever.retrieveFromTerm(Monomial(34, {{"c", 5}, {"d", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})});
    retriever.retrieveFromTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));
    retriever.retrieveFromTerm(functionObject);

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_FALSE(retriever.hasOnlyASingleVariable());
    EXPECT_TRUE(retriever.hasMultipleVariables());
    EXPECT_TRUE(retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty().empty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromConstantWorks) {
    SingleVariableNameRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    EXPECT_TRUE(retriever.hasNoVariables());
    EXPECT_FALSE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_TRUE(retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty().empty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromVariableWorks) {
    SingleVariableNameRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("x", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromMonomialWorks) {
    SingleVariableNameRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"q", 5}}));

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("q", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromPolynomialWorks) {
    SingleVariableNameRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"x", 8}})});

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("x", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromExpressionWorks) {
    SingleVariableNameRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("x", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromFunctionWorks) {
    SingleVariableNameRetriever retriever;
    Function functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_TRUE(retriever.hasOnlyASingleVariable());
    EXPECT_FALSE(retriever.hasMultipleVariables());
    EXPECT_EQ("x", retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
}

TEST(SingleVariableNameRetrieverTest, RetrieveFromPolynomialsWorks) {
    SingleVariableNameRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    EXPECT_FALSE(retriever.hasNoVariables());
    EXPECT_FALSE(retriever.hasOnlyASingleVariable());
    EXPECT_TRUE(retriever.hasMultipleVariables());
    EXPECT_TRUE(retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty().empty());
}

}  // namespace algebra

}  // namespace alba
