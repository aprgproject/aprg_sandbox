#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(FirstCoefficientRetrieverTest, RetrieveFromEquationsWorks)
{
    FirstCoefficientRetriever retriever;
    Equation equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    EXPECT_EQ(AlbaNumber(34), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromEquationWorks)
{
    FirstCoefficientRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    EXPECT_EQ(AlbaNumber(34), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromTermWorks)
{
    FirstCoefficientRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({"x", "^", 2})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("x"));
    retriever.retrieveFromTerm(Monomial(34, {{"x", 5}, {"y", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    retriever.retrieveFromTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));
    retriever.retrieveFromTerm(functionObject);

    EXPECT_EQ(AlbaNumber(1.234), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromConstantWorks)
{
    FirstCoefficientRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    EXPECT_EQ(AlbaNumber(1.234), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromVariableWorks)
{
    FirstCoefficientRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    EXPECT_EQ(AlbaNumber(1), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromMonomialWorks)
{
    FirstCoefficientRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    EXPECT_EQ(AlbaNumber(34), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromPolynomialWorks)
{
    FirstCoefficientRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    EXPECT_EQ(AlbaNumber(516), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromExpressionWorks)
{
    FirstCoefficientRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    EXPECT_EQ(AlbaNumber(678), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromFunctionWorks)
{
    FirstCoefficientRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromFunction(functionObject);

    EXPECT_EQ(AlbaNumber(4516), retriever.getSavedData());
}

TEST(FirstCoefficientRetrieverTest, RetrieveFromPolynomialsWorks)
{
    FirstCoefficientRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    EXPECT_EQ(AlbaNumber(516), retriever.getSavedData());
}

}

}
