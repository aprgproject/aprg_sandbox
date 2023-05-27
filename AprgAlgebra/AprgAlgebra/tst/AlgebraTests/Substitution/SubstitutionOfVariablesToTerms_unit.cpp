#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

TEST(SubstitutionOfVariablesToTermsTest, ConstructionWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2{{"x", "y"}};
    VariablesToTermsMap variableWithExpressions{{"x", "y"}};
    SubstitutionOfVariablesToTerms substitution3{variableWithExpressions};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(1, substitution2.getSize());
    EXPECT_EQ(Term("y"), substitution2.getTermForVariable("x"));
    EXPECT_EQ(1, substitution3.getSize());
    EXPECT_EQ(Term("y"), substitution3.getTermForVariable("x"));
}
TEST(SubstitutionOfVariablesToTermsTest, IsEmptyWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2({{"x", "y"}});
    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToTermsTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_FALSE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToTermsTest, GetSizeWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2({{"x", "y"}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(1, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToTermsTest, GetValueForVariableWorks) {    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});

    Term termToExpect("y");
    EXPECT_EQ(termToExpect, substitution.getTermForVariable("x"));    EXPECT_EQ(Term{}, substitution.getTermForVariable("y"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("a"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("b"));
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnVariable) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Variable variable1;
    Variable variable2("x");
    Variable variable3("y");

    Term verifyTerm1(substitution.performSubstitutionTo(variable1));
    Term verifyTerm2(substitution.performSubstitutionTo(variable2));
    Term verifyTerm3(substitution.performSubstitutionTo(variable3));

    Term expectTerm1(Variable{});
    Term expectTerm2("y");
    Term expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnMonomial) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Monomial monomial1;
    Monomial monomial2(7, {{"x", 3}});
    Monomial monomial3(11, {{"x", 3}, {"y", 4}});

    Term verifyTerm1(substitution.performSubstitutionTo(monomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(monomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(monomial3));

    Term expectTerm1(0);
    Term expectTerm2(Monomial(7, {{"y", 3}}));
    Term expectTerm3(Monomial(11, {{"y", 7}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnPolynomial) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Polynomial polynomial1;
    Polynomial polynomial2{
        Monomial(100, {}), Monomial(5, {{"x", 5}, {"y", 3}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial polynomial3{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})};
    Polynomial polynomial4{
        Monomial(-2, {{"x", 3}}), Monomial(-3, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(-5, {})};

    Term verifyTerm1(substitution.performSubstitutionTo(polynomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(polynomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(polynomial3));
    Term verifyTerm4(substitution.performSubstitutionTo(polynomial4));

    Term expectTerm1;
    Term expectTerm2(Polynomial{Monomial(14, {{"y", 8}}), Monomial(110, {})});
    Term expectTerm3(Monomial(8, {{"y", 3}}));
    Term expectTerm4(
        Polynomial{Monomial(-2, {{"y", 3}}), Monomial(-3, {{"y", 2}}), Monomial(-4, {{"y", 1}}), Monomial(-5, {})});
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "^", "y"}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Expression expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    Term expectTerm2(expressionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnFunction) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Function function1;
    Function function2(abs("x"));

    Term verifyTerm1(substitution.performSubstitutionTo(function1));
    Term verifyTerm2(substitution.performSubstitutionTo(function2));

    Function functionToExpect(abs("y"));
    Term expectTerm1(Function{});
    Term expectTerm2(functionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Term term1;
    Term term2("x");
    Term term3(Monomial(7, {{"x", 3}}));
    Term term4(Polynomial{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})});
    Term term5(createExpressionIfPossible({"x", "^", "y"}));
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
    Expression expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    Term expectTerm5(expressionToExpect);
    Term expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToTermsTest, VariableToPolynomialSubstitutionWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})}}});
    Term term1;
    Term term2("x");
    Term term3(Monomial(7, {{"x", 3}}));
    Term term4(Polynomial{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})});
    Term term5(createExpressionIfPossible({"x", "^", "y"}));
    Term term6(10);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));
    Term verifyTerm5(substitution.performSubstitutionTo(term5));
    Term verifyTerm6(substitution.performSubstitutionTo(term6));

    Term expectTerm1;
    Term expectTerm2(Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})});
    Term expectTerm3(
        Polynomial{Monomial(7, {{"y", 6}}), Monomial(21, {{"y", 4}}), Monomial(21, {{"y", 2}}), Monomial(7, {})});
    Term expectTerm4(Polynomial{
        Monomial(5, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(16, {{"y", 4}}), Monomial(3, {{"y", 3}}),
        Monomial(16, {{"y", 2}}), Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectTerm2, "^", "y"}));
    Term expectTerm5(expressionToExpect);
    Term expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForMonomialWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", 2}, {"y", 5}});
    Monomial monomial(5, {{"x", 2}, {"y", 3}});

    Expression verifyExpression(substitution.performSubstitutionForMonomial(monomial));

    Expression expectExpression(createOrCopyExpressionFromATerm(2500));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForPolynomialWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", 2}, {"y", 5}});
    Polynomial polynomial{Monomial(5, {{"x", 2}, {"y", 3}}), Monomial(7, {{"x", 3}, {"y", 4}})};

    Expression verifyExpression(substitution.performSubstitutionForPolynomial(polynomial));

    Expression expectExpression(createOrCopyExpressionFromATerm(37500));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForExpressionWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", 2}, {"y", 5}});
    Expression expression(createExpressionIfPossible({"x", "^", "y"}));

    Expression verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression expectExpression(createOrCopyExpressionFromATerm(32));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForFunctionWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", 2}, {"y", 5}});
    Term subTerm(createExpressionIfPossible({"x", "^", "y"}));
    Function functionToTest(abs(subTerm));

    Function verifyFunction(substitution.performSubstitutionForFunction(functionToTest));

    Function expectExpression(abs(Term(32)));
    EXPECT_EQ(expectExpression, verifyFunction);
}

}  // namespace algebra

}  // namespace alba
