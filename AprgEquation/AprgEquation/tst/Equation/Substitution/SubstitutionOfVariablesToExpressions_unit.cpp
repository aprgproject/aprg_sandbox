#include <Equation/Functions/CommonFunctionLibrary.hpp>
#include <Equation/Substitution/SubstitutionOfVariablesToExpressions.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(SubstitutionOfVariablesToExpressionsTest, ConstructionWorks)
{
    SubstitutionOfVariablesToExpressions();
    SubstitutionOfVariablesToExpressions({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    VariablesToExpressionsMap variableWithExpressions{{"x", createOrCopyExpressionFromATerm(Term("y"))}};
    SubstitutionOfVariablesToExpressions{variableWithExpressions};
}

TEST(SubstitutionOfVariablesToExpressionsTest, IsVariableFoundWorks)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_FALSE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToExpressionsTest, GetValueForVariableWorks)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});

    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term("y")));
    EXPECT_EQ(expressionToExpect, substitution.getExpressionForVariable("x"));
    EXPECT_EQ(Expression{}, substitution.getExpressionForVariable("y"));
    EXPECT_EQ(Expression{}, substitution.getExpressionForVariable("a"));
    EXPECT_EQ(Expression{}, substitution.getExpressionForVariable("b"));
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnVariable)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Variable variable1;
    Variable variable2("x");
    Variable variable3("y");

    Term verifyTerm1(substitution.performSubstitutionTo(variable1));
    Term verifyTerm2(substitution.performSubstitutionTo(variable2));
    Term verifyTerm3(substitution.performSubstitutionTo(variable3));

    Term expectTerm1(Variable(""));
    Term expectTerm2("y");
    Term expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnMonomial)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Monomial monomial1;
    Monomial monomial2(7, {{"x", 3}});
    Monomial monomial3(11, {{"x", 3}, {"y", 4}});

    Term verifyTerm1(substitution.performSubstitutionTo(monomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(monomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(monomial3));

    Term expectTerm1(Constant(0));
    Term expectTerm2(Monomial(7, {{"y", 3}}));
    Term expectTerm3(Monomial(11, {{"y", 7}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnPolynomial)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(100, {}), Monomial(5, {{"x", 5}, {"y", 3}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial polynomial3{Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 3}})};

    Term verifyTerm1(substitution.performSubstitutionTo(polynomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(polynomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(polynomial3));

    Term expectTerm1;
    Term expectTerm2(Polynomial{Monomial(14, {{"y", 8}}), Monomial(110, {})});
    Term expectTerm3(Monomial(8, {{"y", 3}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnExpression)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Expression expressionToExpect(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Term expectTerm2(expressionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnFunction)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Function function1;
    Function function2(Functions::abs(Term("x")));

    Term verifyTerm1(substitution.performSubstitutionTo(function1));
    Term verifyTerm2(substitution.performSubstitutionTo(function2));

    Function functionToExpect(Functions::abs(Term("y")));
    Term expectTerm1(Function{});
    Term expectTerm2(functionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToExpressionsTest, PerformSubstitutionToWorksOnTerm)
{
    SubstitutionOfVariablesToExpressions substitution({{"x", createOrCopyExpressionFromATerm(Term("y"))}});
    Term term1;
    Term term2("x");
    Term term3(Monomial(7, {{"x", 3}}));
    Term term4(Polynomial{Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 3}})});
    Term term5(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term6(10);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));
    Term verifyTerm5(substitution.performSubstitutionTo(term5));
    Term verifyTerm6(substitution.performSubstitutionTo(term6));

    Term expectTerm1;
    Term expectTerm2("y");
    Term expectTerm3(Monomial(7, {{"y", 3}}));
    Term expectTerm4(Monomial(8, {{"y", 3}}));
    Expression expressionToExpect(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Term expectTerm5(expressionToExpect);
    Term expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToExpressionsTest, VariableToPolynomialSubstitutionWorks)
{
    SubstitutionOfVariablesToExpressions substitution(
    {{"x",
      createOrCopyExpressionFromATerm(Term(Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})}))}});
    Term term1;
    Term term2("x");
    Term term3(Monomial(7, {{"x", 3}}));
    Term term4(Polynomial{Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 3}})});
    Term term5(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term6(10);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));
    Term verifyTerm5(substitution.performSubstitutionTo(term5));
    Term verifyTerm6(substitution.performSubstitutionTo(term6));

    Term expectTerm1;
    Term expectTerm2(Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})});
    Term expectTerm3(Polynomial{Monomial(7, {{"y", 6}}), Monomial(21, {{"y", 4}}),Monomial(21, {{"y", 2}}), Monomial(7, {})});
    Term expectTerm4(Polynomial{Monomial(5, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(16, {{"y", 4}}),
                                Monomial(3, {{"y", 3}}), Monomial(16, {{"y", 2}}), Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Expression expressionToExpect(createExpressionIfPossible({Term(expectTerm2), Term("^"), Term("y")}));
    Term expectTerm5(expressionToExpect);
    Term expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

}

}
