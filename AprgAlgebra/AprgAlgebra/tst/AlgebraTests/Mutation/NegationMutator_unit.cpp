#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Mutation/NegationMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

TEST(NegationMutatorTest, MutateTermWorks) {
    NegationMutator mutator;
    Term term1(5);
    Term term2("a");
    Term term3(Monomial(7, {{"a", 1}}));
    Term term4(Polynomial{Monomial(9, {{"a", 1}}), Monomial(11, {{"b", 1}})});
    Term term5(createExpressionIfPossible({"a", "^", "b"}));
    Term term6(sin("a"));

    mutator.mutateTerm(term1);
    mutator.mutateTerm(term2);
    mutator.mutateTerm(term3);
    mutator.mutateTerm(term4);
    mutator.mutateTerm(term5);
    mutator.mutateTerm(term6);

    Term termToExpect1(-5);
    Term termToExpect2(Monomial(-1, {{"a", 1}}));
    Term termToExpect3(Monomial(-7, {{"a", 1}}));
    Term termToExpect4(Polynomial{Monomial(-9, {{"a", 1}}), Monomial(-11, {{"b", 1}})});
    Term termToExpect5(createExpressionIfPossible({-1, "*", "a", "^", "b"}));
    Term termToExpect6(createExpressionIfPossible({-1, "*", sin("a")}));
    EXPECT_EQ(termToExpect1, term1);
    EXPECT_EQ(termToExpect2, term2);
    EXPECT_EQ(termToExpect3, term3);
    EXPECT_EQ(termToExpect4, term4);
    EXPECT_EQ(termToExpect5, term5);
    EXPECT_EQ(termToExpect6, term6);
}

TEST(NegationMutatorTest, MutateConstantWorks) {
    NegationMutator mutator;
    Constant constant(5);

    mutator.mutateConstant(constant);

    Constant constantToExpect(-5);
    EXPECT_EQ(constantToExpect, constant);
}

TEST(NegationMutatorTest, MutateVariableWorks) {
    NegationMutator mutator;
    Variable variable("a");

    mutator.mutateVariable(variable);

    Variable variableToExpect("a");
    EXPECT_EQ(variableToExpect, variable);
}

TEST(NegationMutatorTest, MutateMonomialWorks) {
    NegationMutator mutator;
    Monomial monomial(7, {{"a", 1}});

    mutator.mutateMonomial(monomial);

    Monomial monomialToExpect(-7, {{"a", 1}});
    EXPECT_EQ(monomialToExpect, monomial);
}

TEST(NegationMutatorTest, MutatePolynomialWorks) {
    NegationMutator mutator;
    Polynomial polynomial{Monomial(9, {{"a", 1}}), Monomial(11, {{"b", 1}})};

    mutator.mutatePolynomial(polynomial);

    Polynomial polynomiaToExpect{Monomial(-9, {{"a", 1}}), Monomial(-11, {{"b", 1}})};
    EXPECT_EQ(polynomiaToExpect, polynomial);
}

TEST(NegationMutatorTest, MutateExpressionWorks) {
    NegationMutator mutator;
    Expression expression(createExpressionIfPossible({"a", "^", "b"}));

    mutator.mutateExpression(expression);

    Expression expressionToExpect(createExpressionIfPossible({-1, "*", "a", "^", "b"}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(NegationMutatorTest, MutateFunctionWorks) {
    NegationMutator mutator;
    Function functionObject(sin("a"));

    mutator.mutateFunction(functionObject);

    Function functionToExpect(sin("a"));
    EXPECT_EQ(functionToExpect, functionObject);
}

}  // namespace algebra

}  // namespace alba
