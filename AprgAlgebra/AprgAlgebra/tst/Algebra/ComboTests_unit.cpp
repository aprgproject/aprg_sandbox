#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Utilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample1)
{
    SubstitutionOfVariablesToValues substitution({{"x", 8}});
    Terms terms(tokenizeToTerms("(x+2)*(x+2)*(x+2)*(x+2)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    EXPECT_EQ(Term(10000), substitution.performSubstitutionTo(simplifiedTerm));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample2)
{
    SubstitutionOfVariablesToValues substitution({{"x", 3}});
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    EXPECT_EQ(Term(5775), substitution.performSubstitutionTo(simplifiedTerm));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample3)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)*(11*x-13)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    EXPECT_EQ(Term(12825), substitution.performSubstitutionTo(simplifiedTerm));
}

TEST(ComboTest, SimplifyToCommonDenominatorAndSubstitutionWorksUsingExample4)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Terms terms(tokenizeToTerms("(((3*x)/(x-3))-((3*x+2)/(x^2-6*x+9)))*(((x+2)/(x+3))-((x)/(x^2+6*x+9)))"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Expression simplifiedExpression(createExpressionIfPossible(simplifiedTerms));
    SimplificationOfExpression simplification(simplifiedExpression);
    simplification.setAsShouldSimplifyToACommonDenominator(true);
    simplification.simplify();
    EXPECT_EQ(Term(AlbaNumber(-252, 25)), substitution.performSubstitutionTo(simplification.getExpression()));
}

}

}
