#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(NumberOfTermsRetrieverTest, RetrieveFromEquationsWorks)
{
    NumberOfTermsRetriever retriever;
    Equation equation1(Term(Monomial(34, {{"x", 5}})), "=", Term(Monomial(41, {{"y", 6}})));
    Equation equation2(Term(Monomial(95, {{"x", 7}})), "=", Term(Monomial(18, {{"y", 8}})));

    retriever.retrieveFromEquations({equation1, equation2});

    EXPECT_EQ(4U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromEquationWorks)
{
    NumberOfTermsRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    EXPECT_EQ(2U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromTermWorks)
{
    NumberOfTermsRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("a"), Term("^"), Term(2)})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromTerm(Term(Constant(1.234)));
    retriever.retrieveFromTerm(Term(Variable("b")));
    retriever.retrieveFromTerm(Term(Monomial(34, {{"c", 5}, {"d", 6}})));
    retriever.retrieveFromTerm(Term(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})}));
    retriever.retrieveFromTerm(Term(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"g", 9}}))})));
    retriever.retrieveFromTerm(Term(functionObject));

    EXPECT_EQ(12U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromConstantWorks)
{
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    EXPECT_EQ(1U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromVariableWorks)
{
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    EXPECT_EQ(1U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromMonomialWorks)
{
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    EXPECT_EQ(1U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromPolynomialWorks)
{
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    EXPECT_EQ(2U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromExpressionWorks)
{
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))}));

    EXPECT_EQ(3U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromFunctionWorks)
{
    NumberOfTermsRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromFunction(functionObject);

    EXPECT_EQ(4U, retriever.getSavedData());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromPolynomialsWorks)
{
    NumberOfTermsRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    EXPECT_EQ(4U, retriever.getSavedData());
}

}

}
