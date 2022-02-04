#include <Algebra/Retrieval/FunctionsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(FunctionsRetrieverTest, RetrieveFromEquationsWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });
    Equation equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromEquationWorks)
{
    FunctionsRetriever::FunctionCondition conditionThatWillMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    };
    FunctionsRetriever::FunctionCondition conditionThatWillNotMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    };
    FunctionsRetriever retriever1(conditionThatWillMatch);
    FunctionsRetriever retriever2(conditionThatWillNotMatch);
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({"x", "^", "y"})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Term leftHandTerm(functionObject);
    Term rightHandTerm(1);
    Equation equation(leftHandTerm, "=", rightHandTerm);

    retriever1.retrieveFromEquation(equation);
    retriever2.retrieveFromEquation(equation);

    FunctionsSet const& functionsSets1(retriever1.getSavedData());
    FunctionsSet const& functionsSets2(retriever2.getSavedData());
    ASSERT_EQ(1U, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
    EXPECT_TRUE(functionsSets2.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromTermWorks)
{
    FunctionsRetriever::FunctionCondition conditionThatWillMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    };
    FunctionsRetriever::FunctionCondition conditionThatWillNotMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    };
    FunctionsRetriever retriever1(conditionThatWillMatch);
    FunctionsRetriever retriever2(conditionThatWillNotMatch);
    FunctionsRetriever retriever3(conditionThatWillMatch);
    FunctionsRetriever retriever4(conditionThatWillNotMatch);
    FunctionsRetriever retriever5(conditionThatWillMatch);
    FunctionsRetriever retriever6(conditionThatWillNotMatch);
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({"x", "^", "y"})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Expression expression(createExpressionIfPossible({1, "+", functionObject}));
    Term constantTerm(4756);
    Term expressionTerm(expression);
    Term functionTerm(functionObject);

    retriever1.retrieveFromTerm(constantTerm);
    retriever2.retrieveFromTerm(constantTerm);
    retriever3.retrieveFromTerm(expressionTerm);
    retriever4.retrieveFromTerm(expressionTerm);
    retriever5.retrieveFromTerm(functionTerm);
    retriever6.retrieveFromTerm(functionTerm);

    FunctionsSet const& functionsSets1(retriever1.getSavedData());
    FunctionsSet const& functionsSets2(retriever2.getSavedData());
    FunctionsSet const& functionsSets3(retriever3.getSavedData());
    FunctionsSet const& functionsSets4(retriever4.getSavedData());
    FunctionsSet const& functionsSets5(retriever5.getSavedData());
    FunctionsSet const& functionsSets6(retriever6.getSavedData());
    EXPECT_TRUE(functionsSets1.empty());
    EXPECT_TRUE(functionsSets2.empty());
    ASSERT_EQ(1U, functionsSets3.size());
    EXPECT_EQ(functionObject, *(functionsSets3.begin()));
    EXPECT_TRUE(functionsSets4.empty());
    ASSERT_EQ(1U, functionsSets5.size());
    EXPECT_EQ(functionObject, *(functionsSets5.begin()));
    EXPECT_TRUE(functionsSets6.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromConstantWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });

    retriever.retrieveFromConstant(Constant(1.234));

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromVariableWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });

    retriever.retrieveFromVariable(Variable("x"));

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromMonomialWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromPolynomialWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromExpressionWorks)
{
    FunctionsRetriever::FunctionCondition conditionThatWillMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    };
    FunctionsRetriever::FunctionCondition conditionThatWillNotMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    };
    FunctionsRetriever retriever1(conditionThatWillMatch);
    FunctionsRetriever retriever2(conditionThatWillNotMatch);
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({"x", "^", "y"})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Expression expression(createExpressionIfPossible({1, "+", functionObject}));

    retriever1.retrieveFromExpression(expression);
    retriever2.retrieveFromExpression(expression);

    FunctionsSet const& functionsSets1(retriever1.getSavedData());
    FunctionsSet const& functionsSets2(retriever2.getSavedData());
    ASSERT_EQ(1U, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
    EXPECT_TRUE(functionsSets2.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromFunctionWorks)
{
    FunctionsRetriever::FunctionCondition conditionThatWillMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    };
    FunctionsRetriever::FunctionCondition conditionThatWillNotMatch = [](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    };
    FunctionsRetriever retriever1(conditionThatWillMatch);
    FunctionsRetriever retriever2(conditionThatWillNotMatch);
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({"x", "^", "y"})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retriever1.retrieveFromFunction(functionObject);
    retriever2.retrieveFromFunction(functionObject);

    FunctionsSet const& functionsSets1(retriever1.getSavedData());
    FunctionsSet const& functionsSets2(retriever2.getSavedData());
    ASSERT_EQ(1U, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
    EXPECT_TRUE(functionsSets2.empty());
}

TEST(FunctionsRetrieverTest, RetrieveFromPolynomialsWorks)
{
    FunctionsRetriever retriever([](Function const&)
    {
        return false;
    });
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retriever.retrieveFromPolynomials(polynomials);

    FunctionsSet const& functionsSet(retriever.getSavedData());
    EXPECT_TRUE(functionsSet.empty());
}

}

}
