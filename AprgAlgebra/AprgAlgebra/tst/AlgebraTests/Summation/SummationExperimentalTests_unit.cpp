#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::algebra::Factorization;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(SummationTest, ExperimentalTest)
{
    Polynomial polynomial{Monomial(1, {{"R", 1}, {"C", 1}, {"s", 1}}), Monomial(-1, {{"R", 1}, {"s", 2}}), Monomial(-1, {{"C", 1}, {"s", 2}}), Monomial(1, {{"s", 3}})};
    Summation summation(polynomial, "s");

    unsigned int r=1000;
    unsigned int s=500;
    unsigned int minOfRSMinus1(min(r, s)-1);
    Term summationFormula(summation.getSum(1, "minOfRSMinus1"));
    Polynomials polynomials(factorizeAPolynomial(summationFormula.getPolynomialConstReference()));
    SubstitutionOfVariablesToValues substitution{{"R", r}, {"C", s}, {"minOfRSMinus1", minOfRSMinus1}};
    unsigned long long result = substitution.performSubstitutionTo(summationFormula).getConstantValueConstReference().getInteger();
    unsigned long long display = result%1000000007;

    for(Polynomial const& polynomial : polynomials)
    {
        cout << "Factor: " << polynomial << endl;
    }
    EXPECT_EQ("((1/2)[C][R][minOfRSMinus1^2] + (-1/3)[C][minOfRSMinus1^3] + (-1/3)[R][minOfRSMinus1^3] + (1/4)[minOfRSMinus1^4] + (1/2)[C][R][minOfRSMinus1] + (-1/2)[C][minOfRSMinus1^2] + (-1/2)[R][minOfRSMinus1^2] + (1/2)[minOfRSMinus1^3] + (-1/6)[C][minOfRSMinus1] + (-1/6)[R][minOfRSMinus1] + (1/4)[minOfRSMinus1^2])",
              summationFormula.getDisplayableString());
    EXPECT_EQ(624937395U, display);
}

}

}
