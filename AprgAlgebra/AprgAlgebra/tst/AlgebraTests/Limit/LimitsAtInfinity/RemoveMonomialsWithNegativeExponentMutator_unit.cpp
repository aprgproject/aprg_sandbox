#include <Algebra/Limit/LimitsAtInfinity/RemoveMonomialsWithNegativeExponentMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateEquationWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Term leftHandTerm(Monomial(34, {{"x", 5}}));
    Term rightHandTerm(Monomial(41, {{"x", -6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    mutator.mutateEquation(equation);

    Term expectedLeftHandTerm(Monomial(34, {{"x", 5}}));
    Term expectedRightHandTerm(0);
    Equation expectedEquation(expectedLeftHandTerm, "=", expectedRightHandTerm);
    EXPECT_EQ(expectedEquation, equation);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateTermWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Term constantTerm(Constant(110));
    Term variableTerm(Variable("x"));
    Term monomialTerm(Monomial(34, {{"x", -5}}));
    Term polynomialTerm(Polynomial{Monomial(516, {{"x", -7}}), Monomial(643, {{"x", 8}})});
    Term expressionTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"x", -9}})}));
    Term functionTerm(Function(
                "functionName",
                Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", -10}})})),
                [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    }));
    mutator.mutateTerm(constantTerm);
    mutator.mutateTerm(variableTerm);
    mutator.mutateTerm(monomialTerm);    mutator.mutateTerm(polynomialTerm);
    mutator.mutateTerm(expressionTerm);
    mutator.mutateTerm(functionTerm);

    EXPECT_EQ(Term(110), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(0), monomialTerm);
    EXPECT_EQ(Term(Monomial(643, {{"x", 8}})), polynomialTerm);
    EXPECT_EQ(Term(678), expressionTerm);
    EXPECT_EQ(Term(4516), functionTerm);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateConstantWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Constant constant(110);

    mutator.mutateConstant(constant);

    EXPECT_EQ(Constant(110), constant);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateVariableWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Variable variable("x");

    mutator.mutateVariable(variable);

    EXPECT_EQ(Variable("x"), variable);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateMonomialWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Monomial monomial1(34, {{"x", -5}, {"y", 6}});
    Monomial monomial2(34, {{"x", -5}});

    mutator.mutateMonomial(monomial1);
    mutator.mutateMonomial(monomial2);

    Monomial expectedMonomial1(34, {{"x", -5}, {"y", 6}});
    Monomial expectedMonomial2(0, {});
    EXPECT_EQ(expectedMonomial1, monomial1);
    EXPECT_EQ(expectedMonomial2, monomial2);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutatePolynomialWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Polynomial polynomial{Monomial(516, {{"x", -7}}), Monomial(75, {{"x", 14}}), Monomial(643, {{"y", 8}})};

    mutator.mutatePolynomial(polynomial);

    Polynomial expectedPolynomial{Monomial(75, {{"x", 14}}), Monomial(643, {{"y", 8}})};
    EXPECT_EQ(expectedPolynomial, polynomial);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateExpressionWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Expression expression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", -9}})}));

    mutator.mutateExpression(expression);

    Expression expectedExpression(Term(678));
    EXPECT_EQ(expectedExpression, expression);
}

TEST(RemoveMonomialsWithNegativeExponentMutatorTest, MutateFunctionWorks)
{
    RemoveMonomialsWithNegativeExponentMutator mutator("x");
    Function functionObject(
                "functionName",
                Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", -10}})})),
                [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    mutator.mutateFunction(functionObject);

    Function expectedFunction(
                "functionName",
                Term(4516),
                [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });    EXPECT_EQ(expectedFunction, functionObject);
}

}
}
