#include <Equation/Constructs/TermsAggregator.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample1)
{
    VariablesToValuesMap variablesToValues{{"x", 8}};
    Terms terms(tokenizeToTerms("(x+2)*(x+2)*(x+2)*(x+2)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    simplifiedTerm.substituteVariablesToValues(variablesToValues);
    simplifiedTerm.simplify();
    EXPECT_EQ(Term(10000), simplifiedTerm);
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample2)
{
    VariablesToValuesMap variablesToValues{{"x", 3}};
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    simplifiedTerm.substituteVariablesToValues(variablesToValues);
    simplifiedTerm.simplify();
    EXPECT_EQ(Term(5775), simplifiedTerm);
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample3)
{
    VariablesToValuesMap variablesToValues{{"x", 2}};
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)*(11*x-13)"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    simplifiedTerm.substituteVariablesToValues(variablesToValues);
    simplifiedTerm.simplify();
    EXPECT_EQ(Term(12825), simplifiedTerm);
}

TEST(ComboTest, SimplifyToCommonDenominatorAndSubstitutionWorksUsingExample4)
{
    VariablesToValuesMap variablesToValues{{"x", 2}};
    Terms terms(tokenizeToTerms("(((3*x)/(x-3))-((3*x+2)/(x^2-6*x+9)))*(((x+2)/(x+3))-((x)/(x^2+6*x+9)))"));
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms simplifiedTerms(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, simplifiedTerms.size());
    Term & simplifiedTerm(simplifiedTerms.at(0));
    simplifiedTerm.simplifyToCommonDenominator();
    simplifiedTerm.substituteVariablesToValues(variablesToValues);
    simplifiedTerm.simplify();
    EXPECT_EQ(Term(AlbaNumber(-252, 25)), simplifiedTerm);
}

}

}
