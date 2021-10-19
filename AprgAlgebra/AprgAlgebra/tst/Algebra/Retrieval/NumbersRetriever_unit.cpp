#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(NumbersRetrieverTest, RetrieveFromEquationsWorks)
{
    NumbersRetriever retriever;
    Equation equation1(Term(Monomial(34, {{"x", 5}})), "=", Term(Monomial(41, {{"y", 6}})));
    Equation equation2(Term(Monomial(95, {{"x", 7}})), "=", Term(Monomial(18, {{"y", 8}})));

    retriever.retrieveFromEquations({equation1, equation2});

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(8U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(18), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
    EXPECT_EQ(AlbaNumber(41), *(it++));
    EXPECT_EQ(AlbaNumber(95), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromEquationWorks)
{
    NumbersRetriever retriever;
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(4U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
    EXPECT_EQ(AlbaNumber(41), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromTermWorks)
{
    NumbersRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term(2)})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromTerm(Term(Constant(1.234)));
    retriever.retrieveFromTerm(Term(Variable("x")));
    retriever.retrieveFromTerm(Term(Monomial(34, {{"x", 5}, {"y", 6}})));
    retriever.retrieveFromTerm(Term(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})}));
    retriever.retrieveFromTerm(Term(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))})));
    retriever.retrieveFromTerm(Term(functionObject));
    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(13U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();    EXPECT_EQ(AlbaNumber(1), *(it++));
    EXPECT_EQ(AlbaNumber(1.234), *(it++));
    EXPECT_EQ(AlbaNumber(2), *(it++));
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
    EXPECT_EQ(AlbaNumber(516), *(it++));
    EXPECT_EQ(AlbaNumber(576), *(it++));
    EXPECT_EQ(AlbaNumber(643), *(it++));
    EXPECT_EQ(AlbaNumber(678), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromConstantWorks)
{
    NumbersRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(1U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1.234), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromVariableWorks)
{
    NumbersRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(1U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromMonomialWorks)
{
    NumbersRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(3U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromPolynomialWorks)
{
    NumbersRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(4U, numbersSet.size());    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(516), *(it++));    EXPECT_EQ(AlbaNumber(643), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromExpressionWorks)
{
    NumbersRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))}));

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(3U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(576), *(it++));
    EXPECT_EQ(AlbaNumber(678), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromFunctionWorks)
{
    NumbersRetriever retriever;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever.retrieveFromFunction(functionObject);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(3U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(10), *(it++));
    EXPECT_EQ(AlbaNumber(4516), *(it++));
    EXPECT_EQ(AlbaNumber(7895), *(it++));
}

TEST(NumbersRetrieverTest, RetrieveFromPolynomialsWorks)
{
    NumbersRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    AlbaNumbersSet const& numbersSet(retriever.getSavedData());
    ASSERT_EQ(8U, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(10), *(it++));
    EXPECT_EQ(AlbaNumber(516), *(it++));
    EXPECT_EQ(AlbaNumber(587), *(it++));
    EXPECT_EQ(AlbaNumber(643), *(it++));
    EXPECT_EQ(AlbaNumber(975), *(it++));
}

}

}
