#include <Equation/Constructs/TermsAggregator.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

namespace equation
{

TEST(DeleteThisTest, DeleteThis1)
{
    Terms terms(tokenizeToTerms("(x+2)*(x+2)*(x+2)*(x+2)"));
    TermsAggregator aggregator(terms);

    aggregator.simplifyTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
}

TEST(DeleteThisTest, DeleteThis2)
{
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)"));
    TermsAggregator aggregator(terms);

    aggregator.simplifyTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
}

TEST(DeleteThisTest, DeleteThis3)
{
    Terms terms(tokenizeToTerms("(4*x-5)*(6*x+7)*(8*x+9)*(11*x-13)"));
    TermsAggregator aggregator(terms);

    aggregator.simplifyTerms();
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
}

}

}
