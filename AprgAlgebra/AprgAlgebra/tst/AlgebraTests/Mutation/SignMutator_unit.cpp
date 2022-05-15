#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Mutation/SignMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(SignMutatorTest, MutateTermWorks)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Term term1(5);
    Term term2("a");
    Term term3(Monomial(7, {{"a", 1}}));
    Term term4(Polynomial{Monomial(9, {{"a", 1}}), Monomial(-11, {{"b", 1}})});
    Term term5(createExpressionIfPossible({"a", "^", "b"}));
    Term term6(sin("a"));

    mutator.mutateTerm(term1);
    mutator.mutateTerm(term2);
    mutator.mutateTerm(term3);
    mutator.mutateTerm(term4);
    mutator.mutateTerm(term5);
    mutator.mutateTerm(term6);

    EXPECT_EQ(Term(1), term1);
    EXPECT_EQ(Term(1), term2);
    EXPECT_EQ(Term(1), term3);
    EXPECT_EQ(Term(1), term4);
    EXPECT_EQ(Term(1), term5);
    EXPECT_TRUE(isNan(term6));
}

TEST(SignMutatorTest, MutateTermWorksOnVariable)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Term variableTerm1("a");
    Term variableTerm2("b");
    Term variableTerm3("c");

    mutator.mutateTerm(variableTerm1);
    mutator.mutateTerm(variableTerm2);
    mutator.mutateTerm(variableTerm3);

    EXPECT_EQ(Term(1), variableTerm1);
    EXPECT_EQ(Term(-1), variableTerm2);
    EXPECT_TRUE(isNan(variableTerm3));
}

TEST(SignMutatorTest, MutateTermWorksOnFunction)
{
    SignMutator mutator;
    Term functionTerm1(abs("a"));
    Term functionTerm2(sin("a"));

    mutator.mutateTerm(functionTerm1);
    mutator.mutateTerm(functionTerm2);

    EXPECT_EQ(Term(1), functionTerm1);
    EXPECT_TRUE(isNan(functionTerm2));
}

TEST(SignMutatorTest, MutateConstantWorks)
{
    SignMutator mutator;
    Constant constant(5);

    mutator.mutateConstant(constant);

    EXPECT_EQ(Constant(1), constant);
}

TEST(SignMutatorTest, MutateVariableWorks)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    Variable variable("a");

    mutator.mutateVariable(variable);

    EXPECT_EQ(Variable("a"), variable);
}

TEST(SignMutatorTest, MutateMonomialWorks)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    Monomial monomial(7, {{"a", 1}});

    mutator.mutateMonomial(monomial);

    Monomial monomialToExpect(1, {});
    EXPECT_EQ(monomialToExpect, monomial);
}

TEST(SignMutatorTest, MutatePolynomialWorks)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Polynomial polynomial1{Monomial(9, {{"a", 1}}), Monomial(11, {{"b", 1}})};
    Polynomial polynomial2{Monomial(-9, {{"a", 1}}), Monomial(11, {{"b", 1}})};
    Polynomial polynomial3{Monomial(9, {{"a", 1}}), Monomial(-11, {{"b", 1}})};
    Polynomial polynomial4{Monomial(-9, {{"a", 1}}), Monomial(-11, {{"b", 1}})};

    mutator.mutatePolynomial(polynomial1);
    mutator.mutatePolynomial(polynomial2);
    mutator.mutatePolynomial(polynomial3);
    mutator.mutatePolynomial(polynomial4);

    Polynomial polynomiaToExpect2{Monomial(-1, {})};
    Polynomial polynomiaToExpect3{Monomial(1, {})};
    EXPECT_TRUE(isNan(polynomial1));
    EXPECT_EQ(polynomiaToExpect2, polynomial2);
    EXPECT_EQ(polynomiaToExpect3, polynomial3);
    EXPECT_TRUE(isNan(polynomial4));
}

TEST(SignMutatorTest, MutateExpressionWorksOnAdditionAndSubtraction)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Expression expression1(createExpressionIfPossible({25, "+", "a"}));
    Expression expression2(createExpressionIfPossible({-25, "+", "b"}));
    Expression expression3(createExpressionIfPossible({"a", "+", "b"}));
    Expression expression4(createExpressionIfPossible({"a", "+", abs("b")}));

    mutator.mutateExpression(expression1);
    mutator.mutateExpression(expression2);
    mutator.mutateExpression(expression3);
    mutator.mutateExpression(expression4);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(-1));
    Expression expressionToExpect4(createOrCopyExpressionFromATerm(1));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_TRUE(isNan(expression3));
    EXPECT_EQ(expressionToExpect4, expression4);
}

TEST(SignMutatorTest, MutateExpressionWorksOnMultiplicationAndDivision)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Expression expression1(createExpressionIfPossible({"a", "*", "b"}));
    Expression expression2(createExpressionIfPossible({"a", "/", "b"}));

    mutator.mutateExpression(expression1);
    mutator.mutateExpression(expression2);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(-1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(-1));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
}

TEST(SignMutatorTest, MutateExpressionWorksOnRaiseToPower)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    mutator.putVariableWithSign("b", TermAssociationType::Negative);
    Expression expression1(createExpressionIfPossible({25, "^", "a"}));
    Expression expression2(createExpressionIfPossible({25, "^", "b"}));
    Expression expression3(createExpressionIfPossible({"b", "^", 0}));
    Expression expression4(createExpressionIfPossible({"b", "^", 2}));
    Expression expression5(createExpressionIfPossible({"b", "^", 3}));

    mutator.mutateExpression(expression1);
    mutator.mutateExpression(expression2);
    mutator.mutateExpression(expression3);
    mutator.mutateExpression(expression4);
    mutator.mutateExpression(expression5);

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect3(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect4(createOrCopyExpressionFromATerm(1));
    Expression expressionToExpect5(createOrCopyExpressionFromATerm(-1));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(SignMutatorTest, MutateFunctionWorks)
{
    SignMutator mutator;
    mutator.putVariableWithSign("a", TermAssociationType::Positive);
    Function functionObject(sin("a"));

    mutator.mutateFunction(functionObject);

    Function functionToExpect(sin("a"));
    EXPECT_EQ(functionToExpect, functionObject);
}

}

}
