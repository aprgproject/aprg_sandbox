#include <Algebra/Induction/ProofByInduction.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(ProofByInductionTest, ProveTheSumOfOddIntegers)
{
    //Prove that: 1 + 3 + 5 + ... + (2n-1) = n^2
    ProofByInduction proof("n", Monomial(1, {{"n", 2}}), [](AlbaNumber const& n)
    {
        AlbaNumber result(0);
        AlbaNumber lastValue = (n*2)-1;
        for(AlbaNumber i=1; i<=lastValue; i+=2)
        {
            result+=i;        }
        return result;
    });
    EXPECT_TRUE(proof.isVerificationOnASpecificValueSuccessful(5));
    Term lastTermInSeries(Polynomial{Monomial(2, {{"n", 1}}), Monomial(-1, {})});
    SubstitutionOfVariablesToTerms substitutionForNextTerm{{"n", Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})}}};
    Term expectedDifference = substitutionForNextTerm.performSubstitutionTo(lastTermInSeries);
    expectedDifference.simplify();
    Term firstTerm(Monomial(1, {{"n", 1}}));
    Term secondTerm(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    EXPECT_TRUE(proof.isVerificationOnInductionStepSuccessful(firstTerm, secondTerm, expectedDifference));
}

TEST(ProofByInductionTest, ProveTheSumOfSquareOfOddIntegers)
{
    //Prove that: 1^2 + 3^2 + 5^2 + ... + (2n-1)^2 = (4n^3 - n)/3
    Term expressionToCheck(Polynomial{Monomial(AlbaNumber::createFraction(4, 3), {{"n", 3}}), Monomial(AlbaNumber::createFraction(-1, 3), {{"n", 1}})});
    ProofByInduction proof(
                "n",
                expressionToCheck,
                [](AlbaNumber const& n)
    {
        AlbaNumber result(0);
        AlbaNumber lastValue = (n*2)-1;
        for(AlbaNumber i=1; i<=lastValue; i+=2)
        {
            result+=i^2;        }
        return result;
    });
    EXPECT_TRUE(proof.isVerificationOnASpecificValueSuccessful(5));
    Term lastTermInSeries=Polynomial{Monomial(2, {{"n", 1}}), Monomial(-1, {})} ^ Constant(2);
    SubstitutionOfVariablesToTerms substitutionForNextTerm{{"n", Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})}}};
    Term expectedDifference = substitutionForNextTerm.performSubstitutionTo(lastTermInSeries);
    expectedDifference.simplify();
    Term firstTerm(Monomial(1, {{"n", 1}}));
    Term secondTerm(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    EXPECT_TRUE(proof.isVerificationOnInductionStepSuccessful(firstTerm, secondTerm, expectedDifference));
}

}

}
