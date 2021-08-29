#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SubstitutionOfTermsToTermsTest, ConstructionWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2{{Term("x"), Term(2)}, {Term("y"), Term(5)}};
    TermToTermMap variableWithValues{{Term("x"), Term(2)}, {Term("y"), Term(5)}};
    SubstitutionOfTermsToTerms substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2U, substitution2.getSize());
    EXPECT_EQ(Term(2), substitution2.getTermForTerm(Term("x")));
    EXPECT_EQ(Term(5), substitution2.getTermForTerm(Term("y")));
    EXPECT_EQ(2U, substitution3.getSize());
    EXPECT_EQ(Term(2), substitution3.getTermForTerm(Term("x")));
    EXPECT_EQ(Term(5), substitution3.getTermForTerm(Term("y")));
}

TEST(SubstitutionOfTermsToTermsTest, IsEmptyWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2({{Term("x"), Term(2)}, {Term("y"), Term(5)}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfTermsToTermsTest, IsTermFoundWorks)
{
    SubstitutionOfTermsToTerms substitution({{Term("x"), Term(2)}, {Term("y"), Term(5)}});

    EXPECT_TRUE(substitution.isTermFound(Term("x")));
    EXPECT_TRUE(substitution.isTermFound(Term("y")));
    EXPECT_FALSE(substitution.isTermFound(Term("a")));
    EXPECT_FALSE(substitution.isTermFound(Term("b")));
}

TEST(SubstitutionOfTermsToTermsTest, GetSizeWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2({{Term("x"), Term(2)}, {Term("y"), Term(5)}});

    EXPECT_EQ(0U, substitution1.getSize());
    EXPECT_EQ(2U, substitution2.getSize());
}

TEST(SubstitutionOfTermsToTermsTest, GetTermForTermWorks)
{
    SubstitutionOfTermsToTerms substitution({{Term("x"), Term(2)}, {Term("y"), Term(5)}});

    EXPECT_EQ(Term(2), substitution.getTermForTerm(Term("x")));
    EXPECT_EQ(Term(5), substitution.getTermForTerm(Term("y")));
    EXPECT_EQ(Term(), substitution.getTermForTerm(Term("a")));
    EXPECT_EQ(Term(), substitution.getTermForTerm(Term("b")));
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnExpression)
{
    SubstitutionOfTermsToTerms substitution({{Term("x"), Term(2)}, {Term("y"), Term(5)}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Term expectTerm2(32);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnFunction)
{
    SubstitutionOfTermsToTerms substitution({{Term("x"), Term(-2)}});
    Function function1;
    Function function2(Functions::abs(Term("x")));

    Term verifyTerm1(substitution.performSubstitutionTo(function1));
    Term verifyTerm2(substitution.performSubstitutionTo(function2));

    Term expectTerm1(Function{});
    Term expectTerm2(2);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnTerm)
{
    SubstitutionOfTermsToTerms substitution({{Term("x"), Term(2)}, {Term("y"), Term(5)}});
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
    Term expectTerm2(2);
    Term expectTerm3(term3);
    Term expectTerm4(term4);
    Term expectTerm5(32);
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
