#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(DegreeOnlyMutatorTest, MutateEquationWorks)
{
    DegreeOnlyMutator mutator("x");
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    mutator.mutateEquation(equation);

    Term expectedLeftHandTerm(Monomial(1, {{"x", 5}}));
    Term expectedRightHandTerm(1);
    Equation expectedEquation(expectedLeftHandTerm, "=", expectedRightHandTerm);
    EXPECT_EQ(expectedEquation, equation);
}

TEST(DegreeOnlyMutatorTest, MutateTermWorks)
{
    DegreeOnlyMutator mutator("x");
    Term constantTerm(Constant(110));
    Term variableTerm(Variable("x"));
    Term monomialTerm(Monomial(34, {{"x", 5}, {"y", 6}}));
    Term polynomialTerm(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    Term expressionTerm(Expression(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))})));
    Term functionTerm(Function(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    }));

    mutator.mutateTerm(constantTerm);
    mutator.mutateTerm(variableTerm);
    mutator.mutateTerm(monomialTerm);
    mutator.mutateTerm(polynomialTerm);
    mutator.mutateTerm(expressionTerm);
    mutator.mutateTerm(functionTerm);

    EXPECT_EQ(Term(110), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 5}})), monomialTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 7}})), polynomialTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 9}})), expressionTerm);
    Term expectedFunctionTerm(Function(
                "functionName",
                Term(Monomial(1, {{"x", 10}})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    }));
    EXPECT_EQ(expectedFunctionTerm, functionTerm);
}

TEST(DegreeOnlyMutatorTest, MutateConstantWorks)
{
    DegreeOnlyMutator mutator("x");
    Constant constant(110);

    mutator.mutateConstant(constant);

    EXPECT_EQ(Constant(110), constant);
}

TEST(DegreeOnlyMutatorTest, MutateVariableWorks)
{
    DegreeOnlyMutator mutator("x");
    Variable variable("x");

    mutator.mutateVariable(variable);

    EXPECT_EQ(Variable("x"), variable);
}

TEST(DegreeOnlyMutatorTest, MutateMonomialWorks)
{
    DegreeOnlyMutator mutator("x");
    Monomial monomial(34, {{"x", 5}, {"y", 6}});

    mutator.mutateMonomial(monomial);

    Monomial expectedMonomial(1, {{"x", 5}});
    EXPECT_EQ(expectedMonomial, monomial);
}

TEST(DegreeOnlyMutatorTest, MutatePolynomialWorks)
{
    DegreeOnlyMutator mutator("x");
    Polynomial polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})};

    mutator.mutatePolynomial(polynomial);

    Polynomial expectedPolynomial{Monomial(1, {{"x", 7}})};
    EXPECT_EQ(expectedPolynomial, polynomial);
}

TEST(DegreeOnlyMutatorTest, MutateExpressionWorks)
{
    DegreeOnlyMutator mutator("x");
    Expression expression(createExpressionIfPossible({Term(678), Term("+"), Term(Monomial(576, {{"x", 9}}))}));

    mutator.mutateExpression(expression);

    Expression expectedExpression(Term(Monomial(1, {{"x", 9}})));
    EXPECT_EQ(expectedExpression, expression);
}

TEST(DegreeOnlyMutatorTest, MutateExpressionWorksWhenRaiseToPowerFractionalExponent)
{
    DegreeOnlyMutator mutator("x");
    Term base(Polynomial{Monomial(516, {{"x", 16}}), Monomial(643, {{"y", 8}})});
    Expression expression(createExpressionIfPossible({base, Term("^"), Term(AlbaNumber::createFraction(3, 4))}));

    mutator.mutateExpression(expression);

    Expression expectedExpression(Term(Monomial(1, {{"x", 12}})));
    EXPECT_EQ(expectedExpression, expression);
}

TEST(DegreeOnlyMutatorTest, MutateFunctionWorks)
{
    DegreeOnlyMutator mutator("x");
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({Term(4516), Term("+"), Term(Monomial(7895, {{"x", 10}}))})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    mutator.mutateFunction(functionObject);

    Function expectedFunction(
                "functionName",
                Term(Monomial(1, {{"x", 10}})),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    EXPECT_EQ(expectedFunction, functionObject);
}

}

}
