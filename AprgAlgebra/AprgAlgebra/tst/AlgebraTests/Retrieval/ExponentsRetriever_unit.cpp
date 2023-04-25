#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(ExponentsRetrieverTest, RetrieveFromEquationsWorks) {
    ExponentsRetriever retriever;
    Equation equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(4U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromEquationWorks) {
    ExponentsRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(2U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromTermWorks) {
    ExponentsRetriever retriever;
    Function functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("x"));
    retriever.retrieveFromTerm(Monomial(34, {{"x", 5}, {"y", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    retriever.retrieveFromTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));
    retriever.retrieveFromTerm(functionObject);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(6U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(10), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromConstantWorks) {
    ExponentsRetriever retriever;

    retriever.retrieveFromConstant(Constant(110));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    EXPECT_TRUE(numbersSet.empty());
}

TEST(ExponentsRetrieverTest, RetrieveFromVariableWorks) {
    ExponentsRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    EXPECT_TRUE(numbersSet.empty());
}

TEST(ExponentsRetrieverTest, RetrieveFromMonomialWorks) {
    ExponentsRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(2U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromPolynomialWorks) {
    ExponentsRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(2U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromExpressionWorks) {
    ExponentsRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(1U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(9), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromFunctionWorks) {
    ExponentsRetriever retriever;
    Function functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(1U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(10), *(it++));
}

TEST(ExponentsRetrieverTest, RetrieveFromPolynomialsWorks) {
    ExponentsRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(4U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(10), *(it++));
}

}  // namespace algebra

}  // namespace alba
