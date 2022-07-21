#include <BooleanAlgebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(SubstitutionOfTermsToTermsTest, ConstructionWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2{{"x", false}, {"y", true}};
    TermToTermMap variableWithValues{{"x", false}, {"y", true}};
    SubstitutionOfTermsToTerms substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2U, substitution2.getSize());
    EXPECT_EQ(Term(false), substitution2.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution2.getTermForTerm("y"));
    EXPECT_EQ(2U, substitution3.getSize());
    EXPECT_EQ(Term(false), substitution3.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution3.getTermForTerm("y"));
}

TEST(SubstitutionOfTermsToTermsTest, IsEmptyWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfTermsToTermsTest, IsTermFoundWorks)
{
    SubstitutionOfTermsToTerms substitution({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution.isTermFound("x"));
    EXPECT_TRUE(substitution.isTermFound("y"));
    EXPECT_FALSE(substitution.isTermFound("a"));
    EXPECT_FALSE(substitution.isTermFound("b"));
}

TEST(SubstitutionOfTermsToTermsTest, GetSizeWorks)
{
    SubstitutionOfTermsToTerms substitution1;
    SubstitutionOfTermsToTerms substitution2({{"x", false}, {"y", true}});

    EXPECT_EQ(0U, substitution1.getSize());
    EXPECT_EQ(2U, substitution2.getSize());
}

TEST(SubstitutionOfTermsToTermsTest, GetTermForTermWorks)
{
    SubstitutionOfTermsToTerms substitution({{"x", false}, {"y", true}});

    EXPECT_EQ(Term(false), substitution.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution.getTermForTerm("y"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("a"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("b"));
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnExpression)
{
    SubstitutionOfTermsToTerms substitution({{"x", false}, {"y", true}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Term expectTerm2(false);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnTerm)
{
    SubstitutionOfTermsToTerms substitution({{"x", false}, {"y", true}});
    Term term1;
    Term term2("x");
    Term term3(createExpressionIfPossible({"x", "&", "y"}));
    Term term4(true);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));

    Term expectTerm1;
    Term expectTerm2(false);
    Term expectTerm3(false);
    Term expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionForExpressionWorks)
{
    SubstitutionOfTermsToTerms substitution({{"x", "a"}, {"y", true}});
    Expression expression(createExpressionIfPossible({"x", "&", "y"}));

    Expression verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression expectExpression(createExpressionIfPossible({"a", "&", true}));
    EXPECT_EQ(expectExpression, verifyExpression);
}

}

}
