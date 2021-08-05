#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{



TEST(RetrieveHelpersTest, GetCoefficientForVariableOnlyWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})};
    Polynomial polynomial3{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})};

    EXPECT_EQ(AlbaNumber(0), getCoefficientForVariableOnly("x", polynomial1));
    EXPECT_EQ(AlbaNumber(516), getCoefficientForVariableOnly("a", polynomial2));
    EXPECT_EQ(AlbaNumber(975), getCoefficientForVariableOnly("y", polynomial3));
}

TEST(RetrieveHelpersTest, RetrieveAndReturnExponentsWorksForTerm)
{
    AlbaNumbersSet numbersSet(retrieveAndReturnExponents(Term(Monomial(34, {{"x", 521}, {"y", 4531}}))));

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(521), *(it++));
    EXPECT_EQ(AlbaNumber(4531), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForTerm)
{
    AlbaNumbersSet numbersSet1;
    AlbaNumbersSet numbersSet2;
    AlbaNumbersSet numbersSet3;
    AlbaNumbersSet numbersSet4;
    AlbaNumbersSet numbersSet5;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveExponents(numbersSet1, Term(Constant(1.234)));
    retrieveExponents(numbersSet2, Term(Monomial(34, {{"x", 5}, {"y", 6}})));
    retrieveExponents(numbersSet3, Term(Polynomial({Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})})));
    retrieveExponents(numbersSet4, Term(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))})));
    retrieveExponents(numbersSet5, Term(functionObject));

    EXPECT_TRUE(numbersSet1.empty());
    ASSERT_EQ(2u, numbersSet2.size());
    AlbaNumbersSet::const_iterator it2 = numbersSet2.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it2++));
    EXPECT_EQ(AlbaNumber(6), *(it2++));
    ASSERT_EQ(2u, numbersSet3.size());
    AlbaNumbersSet::const_iterator it3 = numbersSet3.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it3++));
    EXPECT_EQ(AlbaNumber(8), *(it3++));
    ASSERT_EQ(1u, numbersSet4.size());
    AlbaNumbersSet::const_iterator it4 = numbersSet4.cbegin();
    EXPECT_EQ(AlbaNumber(9), *(it4++));
    ASSERT_EQ(1u, numbersSet5.size());
    AlbaNumbersSet::const_iterator it5 = numbersSet5.cbegin();
    EXPECT_EQ(AlbaNumber(10), *(it5++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForMonomial)
{
    AlbaNumbersSet numbersSet;

    retrieveExponents(numbersSet, Monomial(34, {{"x", 5}, {"y", 6}}));

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(5), *(it++));
    EXPECT_EQ(AlbaNumber(6), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForPolynomial)
{
    AlbaNumbersSet numbersSet;

    retrieveExponents(numbersSet, Polynomial({Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})}));

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForExpression)
{
    AlbaNumbersSet numbersSet;

    retrieveExponents(numbersSet, createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))}));

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(9), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForFunction)
{
    AlbaNumbersSet numbersSet;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveExponents(numbersSet, functionObject);

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(10), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveExponentsWorksForPolynomials)
{
    AlbaNumbersSet numbersSet;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retrieveExponents(numbersSet, polynomials);

    ASSERT_EQ(4u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(7), *(it++));
    EXPECT_EQ(AlbaNumber(8), *(it++));
    EXPECT_EQ(AlbaNumber(9), *(it++));
    EXPECT_EQ(AlbaNumber(10), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveAndReturnNumbersWorksForTerm)
{
    AlbaNumbersSet numbersSet(retrieveAndReturnNumbers(Term(Constant(1.234))));

    ASSERT_EQ(1u, numbersSet.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet.cbegin()));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForTerm)
{
    AlbaNumbersSet numbersSet1;
    AlbaNumbersSet numbersSet2;
    AlbaNumbersSet numbersSet3;
    AlbaNumbersSet numbersSet4;
    AlbaNumbersSet numbersSet5;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term(68)})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveNumbers(numbersSet1, Term(Constant(1.234)));
    retrieveNumbers(numbersSet2, Term(Monomial(34, {{"x", 1}, {"y", 1}})));
    retrieveNumbers(numbersSet3, Term(Polynomial({Monomial(1, {{"x", 56}}), Monomial(1, {{"y", 1}})})));
    retrieveNumbers(numbersSet4, Term(createExpressionIfPossible({Term("x"), Term("^"), Term(68)})));
    retrieveNumbers(numbersSet5, Term(functionObject));

    ASSERT_EQ(1u, numbersSet1.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet1.cbegin()));
    ASSERT_EQ(2u, numbersSet2.size());
    AlbaNumbersSet::const_iterator it2 = numbersSet2.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it2++));
    EXPECT_EQ(AlbaNumber(34), *(it2++));
    ASSERT_EQ(2u, numbersSet3.size());
    AlbaNumbersSet::const_iterator it3 = numbersSet3.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it3++));
    EXPECT_EQ(AlbaNumber(56), *(it3++));
    ASSERT_EQ(1u, numbersSet4.size());
    AlbaNumbersSet::const_iterator it4 = numbersSet4.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it4++));
    ASSERT_EQ(1u, numbersSet5.size());
    AlbaNumbersSet::const_iterator it5 = numbersSet5.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it5++));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForConstant)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(numbersSet, Constant(1.234));

    ASSERT_EQ(1u, numbersSet.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet.cbegin()));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForMonomial)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(numbersSet, Monomial(34, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForPolynomial)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(numbersSet, Polynomial({Monomial(1, {{"x", 56}}), Monomial(1, {{"y", 1}})}));

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it++));
    EXPECT_EQ(AlbaNumber(56), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForExpression)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(numbersSet, createExpressionIfPossible({Term("x"), Term("^"), Term(68)}));

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveNumbersWorksForFunction)
{
    AlbaNumbersSet numbersSet;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term(68)})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveNumbers(numbersSet, functionObject);

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it++));
}

TEST(RetrieveHelpersTest, RetrieveAndReturnVariableNamesWorksForTerm)
{
    VariableNamesSet variableNamesSet(retrieveAndReturnVariableNames(Term(Variable("VariableName"))));

    ASSERT_EQ(1u, variableNamesSet.size());
    EXPECT_EQ("VariableName", *(variableNamesSet.cbegin()));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForTerm)
{
    VariableNamesSet variableNamesSet1;
    VariableNamesSet variableNamesSet2;
    VariableNamesSet variableNamesSet3;
    VariableNamesSet variableNamesSet4;
    VariableNamesSet variableNamesSet5;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveVariableNames(variableNamesSet1, Term(Variable("VariableName")));
    retrieveVariableNames(variableNamesSet2, Term(Monomial(1, {{"x", 1}, {"y", 1}})));
    retrieveVariableNames(variableNamesSet3, Term(Polynomial({Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})})));
    retrieveVariableNames(variableNamesSet4, Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})));
    retrieveVariableNames(variableNamesSet5, Term(functionObject));

    ASSERT_EQ(1u, variableNamesSet1.size());
    EXPECT_EQ("VariableName", *(variableNamesSet1.cbegin()));
    ASSERT_EQ(2u, variableNamesSet2.size());
    VariableNamesSet::const_iterator it2 = variableNamesSet2.cbegin();
    EXPECT_EQ("x", *(it2++));
    EXPECT_EQ("y", *(it2++));
    ASSERT_EQ(2u, variableNamesSet3.size());
    VariableNamesSet::const_iterator it3 = variableNamesSet3.cbegin();
    EXPECT_EQ("x", *(it3++));
    EXPECT_EQ("y", *(it3++));
    ASSERT_EQ(2u, variableNamesSet4.size());
    VariableNamesSet::const_iterator it4 = variableNamesSet4.cbegin();
    EXPECT_EQ("x", *(it4++));
    EXPECT_EQ("y", *(it4++));
    ASSERT_EQ(2u, variableNamesSet5.size());
    VariableNamesSet::const_iterator it5 = variableNamesSet5.cbegin();
    EXPECT_EQ("x", *(it5++));
    EXPECT_EQ("y", *(it5++));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForVariable)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(variableNamesSet, Variable("VariableName"));

    ASSERT_EQ(1u, variableNamesSet.size());
    EXPECT_EQ("VariableName", *(variableNamesSet.cbegin()));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForMonomial)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(variableNamesSet, Monomial(1, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForPolynomial)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(variableNamesSet, Polynomial({Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}));

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForExpression)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(variableNamesSet, createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForFunction)
{
    VariableNamesSet variableNamesSet;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveVariableNames(variableNamesSet, functionObject);

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(RetrieveHelpersTest, RetrieveVariableNamesWorksForPolynomials)
{
    VariableNamesSet variableNamesSet;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Polynomial{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});

    retrieveVariableNames(variableNamesSet, polynomials);

    ASSERT_EQ(4u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(RetrieveHelpersTest, RetrieveAndReturnFunctionsWithConditionWorksForExpression)
{
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Expression expression(createExpressionIfPossible({Term(1), Term("+"), Term(functionObject)}));

    FunctionsSet functionsSets1(
                retrieveAndReturnFunctionsWithCondition(Term(expression), [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    }));

    ASSERT_EQ(1u, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
}

TEST(RetrieveHelpersTest, RetrieveFunctionsWithConditionWorksForTerm)
{
    FunctionsSet functionsSets1;
    FunctionsSet functionsSets2;
    FunctionsSet functionsSets3;
    FunctionsSet functionsSets4;
    FunctionsSet functionsSets5;
    FunctionsSet functionsSets6;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Expression expression(createExpressionIfPossible({Term(1), Term("+"), Term(functionObject)}));
    FunctionCondition conditionThatWillMatch = [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    };
    FunctionCondition conditionThatWillNotMatch = [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    };
    Term constantTerm(4756);
    Term expressionTerm(expression);
    Term functionTerm(functionObject);

    retrieveFunctionsWithCondition(functionsSets1, constantTerm, conditionThatWillMatch);
    retrieveFunctionsWithCondition(functionsSets2, constantTerm, conditionThatWillNotMatch);
    retrieveFunctionsWithCondition(functionsSets3, expressionTerm, conditionThatWillMatch);
    retrieveFunctionsWithCondition(functionsSets4, expressionTerm, conditionThatWillNotMatch);
    retrieveFunctionsWithCondition(functionsSets5, functionTerm, conditionThatWillMatch);
    retrieveFunctionsWithCondition(functionsSets6, functionTerm, conditionThatWillNotMatch);

    EXPECT_TRUE(functionsSets1.empty());
    EXPECT_TRUE(functionsSets2.empty());
    ASSERT_EQ(1u, functionsSets3.size());
    EXPECT_EQ(functionObject, *(functionsSets3.begin()));
    EXPECT_TRUE(functionsSets4.empty());
    ASSERT_EQ(1u, functionsSets5.size());
    EXPECT_EQ(functionObject, *(functionsSets5.begin()));
    EXPECT_TRUE(functionsSets6.empty());
}

TEST(RetrieveHelpersTest, RetrieveFunctionsWithConditionWorksForExpression)
{
    FunctionsSet functionsSets1;
    FunctionsSet functionsSets2;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Expression expression(createExpressionIfPossible({Term(1), Term("+"), Term(functionObject)}));

    retrieveFunctionsWithCondition(functionsSets1, expression, [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    });
    retrieveFunctionsWithCondition(functionsSets2, expression, [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    });

    ASSERT_EQ(1u, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
    EXPECT_TRUE(functionsSets2.empty());
}

TEST(RetrieveHelpersTest, RetrieveFunctionsWithConditionWorksForFunction)
{
    FunctionsSet functionsSets1;
    FunctionsSet functionsSets2;
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    retrieveFunctionsWithCondition(functionsSets1, functionObject, [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "functionName";
    });
    retrieveFunctionsWithCondition(functionsSets2, functionObject, [](Function const functionObject)
    {
        return functionObject.getFunctionName() == "WillNotMatch";
    });

    ASSERT_EQ(1u, functionsSets1.size());
    EXPECT_EQ(functionObject, *(functionsSets1.begin()));
    EXPECT_TRUE(functionsSets2.empty());
}

}

}
