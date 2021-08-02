#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(IsolationOfOneVariableOnEqualityEquationTest, CanBeIsolatedWorksOnPolynomialEquation)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_TRUE(isolation.canBeIsolated("x"));
    EXPECT_TRUE(isolation.canBeIsolated("y"));
    EXPECT_FALSE(isolation.canBeIsolated("z"));
    EXPECT_TRUE(isolation.canBeIsolated("a"));
    EXPECT_TRUE(isolation.canBeIsolated("b"));
    EXPECT_FALSE(isolation.canBeIsolated("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, CanBeIsolatedWorksOnPolynomialEquationWithMultipleVariableMonomials)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_TRUE(isolation.canBeIsolated("x"));
    EXPECT_TRUE(isolation.canBeIsolated("y"));
    EXPECT_FALSE(isolation.canBeIsolated("z"));
    EXPECT_TRUE(isolation.canBeIsolated("a"));
    EXPECT_TRUE(isolation.canBeIsolated("b"));
    EXPECT_FALSE(isolation.canBeIsolated("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetExponentOfIsolatedVariableWorksOnPolynomialEquation)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getExponentOfIsolatedVariable("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getExponentOfIsolatedVariable("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getExponentOfIsolatedVariable("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getExponentOfIsolatedVariable("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getExponentOfIsolatedVariable("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getExponentOfIsolatedVariable("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetExponentOfIsolatedVariableWorksOnPolynomialEquationWithMultipleVariableMonomials)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getExponentOfIsolatedVariable("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getExponentOfIsolatedVariable("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getExponentOfIsolatedVariable("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getExponentOfIsolatedVariable("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getExponentOfIsolatedVariable("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getExponentOfIsolatedVariable("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateWorksOnPolynomialEquation)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term expectedIsolatedXLeftSide(Polynomial{Monomial(4, {{"b", 4}}), Monomial(3, {{"a", 3}}), Monomial(-2, {{"y", 2}})});
    Term expectedIsolatedXRightSide("x");
    EXPECT_EQ(Equation(expectedIsolatedXLeftSide, "=", expectedIsolatedXRightSide), isolation.isolate("x"));
    Term expectedIsolatedYLeftSide(Polynomial{Monomial(2, {{"b", 4}}), Monomial(AlbaNumber(3)/2, {{"a", 3}}), Monomial(AlbaNumber(-1)/2, {{"x", 1}})});
    Term expectedIsolatedYRightSide(Monomial(1, {{"y", 2}}));
    EXPECT_EQ(Equation(expectedIsolatedYLeftSide, "=", expectedIsolatedYRightSide), isolation.isolate("y"));
    Term expectedIsolatedALeftSide(Polynomial{Monomial(AlbaNumber(-4)/3, {{"b", 4}}), Monomial(AlbaNumber(2)/3, {{"y", 2}}), Monomial(AlbaNumber(1)/3, {{"x", 1}})});
    Term expectedIsolatedARightSide(Monomial(1, {{"a", 3}}));
    EXPECT_EQ(Equation(expectedIsolatedALeftSide, "=", expectedIsolatedARightSide), isolation.isolate("a"));
    Term expectedIsolatedBLeftSide(Polynomial{Monomial(AlbaNumber(-3)/4, {{"a", 3}}), Monomial(AlbaNumber(1)/2, {{"y", 2}}), Monomial(AlbaNumber(1)/4, {{"x", 1}})});
    Term expectedIsolatedBRightSide(Monomial(1, {{"b", 4}}));
    EXPECT_EQ(Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide), isolation.isolate("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateWorksOnPolynomialEquationWithMultipleVariableMonomials)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation equation(Term(leftHandSide), "=", Term(rightHandSide));
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term expectedIsolatedXLeftSide(Monomial(3, {{"a", 3}, {"b", 4}, {"y", -2}}));
    Term expectedIsolatedXRightSide("x");
    EXPECT_EQ(Equation(expectedIsolatedXLeftSide, "=", expectedIsolatedXRightSide), isolation.isolate("x"));
    Term expectedIsolatedYLeftSide(Monomial(3, {{"a", 3}, {"b", 4}, {"x", -1}}));
    Term expectedIsolatedYRightSide(Monomial(1, {{"y", 2}}));
    EXPECT_EQ(Equation(expectedIsolatedYLeftSide, "=", expectedIsolatedYRightSide), isolation.isolate("y"));
    Term expectedIsolatedALeftSide(Monomial(AlbaNumber(1)/3, {{"b", -4}, {"x", 1}, {"y", 2}}));
    Term expectedIsolatedARightSide(Monomial(1, {{"a", 3}}));
    EXPECT_EQ(Equation(expectedIsolatedALeftSide, "=", expectedIsolatedARightSide), isolation.isolate("a"));
    Term expectedIsolatedBLeftSide(Monomial(AlbaNumber(1)/3, {{"a", -3}, {"x", 1}, {"y", 2}}));
    Term expectedIsolatedBRightSide(Monomial(1, {{"b", 4}}));
    EXPECT_EQ(Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide), isolation.isolate("b"));
}

}

}
