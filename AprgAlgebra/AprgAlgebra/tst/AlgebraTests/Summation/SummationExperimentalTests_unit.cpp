#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::algebra::Factorization;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(SummationTest, ExperimentalTest1) {
    // https://www.geeksforgeeks.org/total-number-of-non-decreasing-numbers-with-n-digits/

    // Total number of non-decreasing numbers with n digits
    // A number is non-decreasing if every digit (except the first one) is greater than or equal to previous digit.
    // For example, 223, 4455567, 899, are non-decreasing numbers.
    // So, given the number of digits n, you are required to find the count of total non-decreasing numbers with n
    // digits.

    Term formula(1);
    for (int i = 1; i < 10; i++)  // continue to integrate for number of digits
    {
        Summation summation(formula, "x");
        formula = summation.getSummationModelWithUnknownConstant();
        formula = formula - Term("C");
    }
    EXPECT_EQ(
        "((1/362880)[x^9] + (1/8064)[x^8] + (29/12096)[x^7] + (5/192)[x^6] + (3013/17280)[x^5] + (95/128)[x^4] + "
        "(4523/2268)[x^3] + (6515/2016)[x^2] + (7129/2520)[x] + 1)",
        convertToString(formula));

    SubstitutionOfVariablesToValues substitution{{"x", 5}};
    EXPECT_EQ("2002", convertToString(substitution.performSubstitutionTo(formula)));
}

TEST(SummationTest, ExperimentalTest2) {
    Polynomial polynomial{
        Monomial(1, {{"R", 1}, {"C", 1}, {"s", 1}}), Monomial(-1, {{"R", 1}, {"s", 2}}),
        Monomial(-1, {{"C", 1}, {"s", 2}}), Monomial(1, {{"s", 3}})};
    Summation summation(polynomial, "s");

    int r = 1000;
    int s = 500;
    int minOfRSMinus1(min(r, s) - 1);
    Term summationFormula(summation.getSum(1, "minOfRSMinus1"));
    Polynomials polynomials(factorizeAPolynomial(summationFormula.getAsPolynomial()));
    SubstitutionOfVariablesToValues substitution{{"R", r}, {"C", s}, {"minOfRSMinus1", minOfRSMinus1}};
    long long result =
        substitution.performSubstitutionTo(summationFormula).getAsNumber().getInteger();
    long long display = result % 1000000007;

    for (Polynomial const& polynomial : polynomials) {
        cout << "Factor: " << polynomial << "\n";
    }
    EXPECT_EQ(
        "((1/2)[C][R][minOfRSMinus1^2] + (-1/3)[C][minOfRSMinus1^3] + (-1/3)[R][minOfRSMinus1^3] + "
        "(1/4)[minOfRSMinus1^4] + (1/2)[C][R][minOfRSMinus1] + (-1/2)[C][minOfRSMinus1^2] + (-1/2)[R][minOfRSMinus1^2] "
        "+ (1/2)[minOfRSMinus1^3] + (-1/6)[C][minOfRSMinus1] + (-1/6)[R][minOfRSMinus1] + (1/4)[minOfRSMinus1^2])",
        convertToString(summationFormula));
    EXPECT_EQ(624937395U, display);
}

}  // namespace algebra

}  // namespace alba
