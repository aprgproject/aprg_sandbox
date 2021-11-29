#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquations.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(IsolationOfOneVariableOnEqualityEquationsTest, IsolateTermWithVariableWorks)
{
    Equations equationsToTest;
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(2, {{"z", 1}}), Monomial(1, {{"l", 1}, {"y", 1}, {"z", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"z", 1}}), Monomial(1, {{"l", 1}, {"x", 1}, {"z", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"l", 1}, {"x", 1}, {"y", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"l", 1}, {"x", 1}, {"y", 1}}), Monomial(-1, {{"V", 1}})}), "=", Term(0));
    IsolationOfOneVariableOnEqualityEquations isolation(equationsToTest);

    Term termWithVariable;
    Term termWithoutVariable;
    isolation.isolateTermWithVariable("l", termWithVariable, termWithoutVariable);

    string stringToExpect1("l");
    string stringToExpect2("-2[z^-1]");
    EXPECT_EQ(stringToExpect1, termWithVariable.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termWithoutVariable.getDisplayableString());
}

TEST(IsolationOfOneVariableOnEqualityEquationsTest, GetEquivalentTermByIsolatingAVariableWorks)
{
    Equations equationsToTest;
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(2, {{"z", 1}}), Monomial(1, {{"l", 1}, {"y", 1}, {"z", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"z", 1}}), Monomial(1, {{"l", 1}, {"x", 1}, {"z", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"l", 1}, {"x", 1}, {"y", 1}})}), "=", Term(0));
    equationsToTest.emplace_back(Term(Polynomial{Monomial(1, {{"l", 1}, {"x", 1}, {"y", 1}}), Monomial(-1, {{"V", 1}})}), "=", Term(0));
    IsolationOfOneVariableOnEqualityEquations isolation(equationsToTest);

    Term termToVerify(isolation.getEquivalentTermByIsolatingAVariable("l"));

    string stringToExpect("-2[z^-1]");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

}

}
