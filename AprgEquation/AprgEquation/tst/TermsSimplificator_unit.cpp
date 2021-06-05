#include <TermsSimplificator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermsSimplificatorTest, ThreeTermsCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("+"), Term(2)});

    simplificator.simplifyTerms();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(7, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

}

}
