#include <Algebra/Simplification/SimplificationMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationMutatorTest, MutateEquationWorks)
{
    SimplificationMutator mutator;
    Equation equation(Term("x"), "<", Term("y"));

    mutator.mutateEquation(equation);

    EXPECT_EQ(Term(Polynomial({Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})})), equation.getLeftHandTerm());
    EXPECT_EQ("<", equation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), equation.getRightHandTerm());
}

TEST(SimplificationMutatorTest, MutateTermWorks)
{
    SimplificationMutator mutator;
    Term constantTerm(1475);
    Term variableTerm("x");
    Term monomialTerm(Monomial(1475,{}));
    Term polynomialTerm(Polynomial{Monomial(1475,{})});
    Term expressionTerm(Expression{createExpressionIfPossible({Term(1475)})});
    Function functionObject("functionName", Term(1475), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Term functionTerm(functionObject);

    mutator.mutateTerm(constantTerm);
    mutator.mutateTerm(variableTerm);
    mutator.mutateTerm(monomialTerm);
    mutator.mutateTerm(polynomialTerm);
    mutator.mutateTerm(expressionTerm);
    mutator.mutateTerm(functionTerm);

    EXPECT_EQ(Term(1475), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(1475), monomialTerm);
    EXPECT_EQ(Term(1475), polynomialTerm);
    EXPECT_EQ(Term(1475), expressionTerm);
    EXPECT_EQ(Term(1475), functionTerm);
}

TEST(SimplificationMutatorTest, MutateConstantWorks)
{
    SimplificationMutator mutator;
    Constant constant(110);

    mutator.mutateConstant(constant);

    EXPECT_EQ(Constant(110), constant);
}

TEST(SimplificationMutatorTest, MutateVariableWorks)
{
    SimplificationMutator mutator;
    Variable variable("x");

    mutator.mutateVariable(variable);

    EXPECT_EQ(Variable("x"), variable);
}

TEST(SimplificationMutatorTest, MutateMonomialWorks)
{
    SimplificationMutator mutator;
    Monomial monomial1;
    Monomial monomial2(6, {});
    Monomial monomial3(1, {{"x", 1}});
    Monomial monomial4(10, {{"x", 0}});
    Monomial monomial5(58, {{"x", 7}, {"y", 0}});

    mutator.mutateMonomial(monomial1);
    mutator.mutateMonomial(monomial2);
    mutator.mutateMonomial(monomial3);
    mutator.mutateMonomial(monomial4);
    mutator.mutateMonomial(monomial5);

    Monomial expectedMonomial1;
    Monomial expectedMonomial2(6, {});
    Monomial expectedMonomial3(1, {{"x", 1}});
    Monomial expectedMonomial4(10, {});
    Monomial expectedMonomial5(58, {{"x", 7}});

    EXPECT_EQ(expectedMonomial1, monomial1);
    EXPECT_EQ(expectedMonomial2, monomial2);
    EXPECT_EQ(expectedMonomial3, monomial3);
    EXPECT_EQ(expectedMonomial4, monomial4);
    EXPECT_EQ(expectedMonomial5, monomial5);
}

TEST(SimplificationMutatorTest, MutatePolynomialWorks)
{
    SimplificationMutator mutator;
    Polynomial polynomial1{Monomial(0, {{"x", 1}}), Monomial(0, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-6, {})};
    Polynomial polynomial4{Monomial(-6, {{"y", 0}, {"z", 0}})};

    mutator.mutatePolynomial(polynomial1);
    mutator.mutatePolynomial(polynomial2);
    mutator.mutatePolynomial(polynomial3);
    mutator.mutatePolynomial(polynomial4);

    Polynomial expectedPolynomial1{};
    Polynomial expectedPolynomial2{Monomial(6, {})};
    Polynomial expectedPolynomial3{};
    Polynomial expectedPolynomial4{Monomial(-6, {})};

    EXPECT_EQ(expectedPolynomial1, polynomial1);
    EXPECT_EQ(expectedPolynomial2, polynomial2);
    EXPECT_EQ(expectedPolynomial3, polynomial3);
    EXPECT_EQ(expectedPolynomial4, polynomial4);
}

TEST(SimplificationMutatorTest, MutateExpressionWorks)
{
    SimplificationMutator mutator;
    Expression expression(createExpressionIfPossible({Term(100), Term("+"), Term(200), Term("-"), Term(50)}));

    mutator.mutateExpression(expression);

    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(250)));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(SimplificationMutatorTest, MutateFunctionWorks)
{
    SimplificationMutator mutator;
    Function functionObject("functionName", Term(createExpressionIfPossible({Term(5), Term("+"), Term(5)})), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    mutator.mutateFunction(functionObject);

    Function expectedFunction(
                "functionName",
                Term(10),
                [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    EXPECT_EQ(expectedFunction, functionObject);
}

}

}

}
