#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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
    Equation equation(leftHandSide, "=", rightHandSide);
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
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_TRUE(isolation.canBeIsolated("x"));
    EXPECT_TRUE(isolation.canBeIsolated("y"));
    EXPECT_FALSE(isolation.canBeIsolated("z"));
    EXPECT_TRUE(isolation.canBeIsolated("a"));
    EXPECT_TRUE(isolation.canBeIsolated("b"));
    EXPECT_FALSE(isolation.canBeIsolated("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetIdenticalExponentForVariableIfPossibleWorksOnPolynomialEquation)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getIdenticalExponentForVariableIfPossible("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getIdenticalExponentForVariableIfPossible("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getIdenticalExponentForVariableIfPossible("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getIdenticalExponentForVariableIfPossible("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetIdenticalExponentForVariableIfPossibleWorksOnPolynomialEquationWithMultipleVariableMonomials)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getIdenticalExponentForVariableIfPossible("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getIdenticalExponentForVariableIfPossible("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getIdenticalExponentForVariableIfPossible("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getIdenticalExponentForVariableIfPossible("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableOnLeftSideOfEquationWorks)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term expectedIsolatedBLeftSide(Monomial(1, {{"b", 4}}));
    Term expectedIsolatedBRightSide(Polynomial{Monomial(AlbaNumber(-3)/4, {{"a", 3}}), Monomial(AlbaNumber(1)/2, {{"y", 2}}), Monomial(AlbaNumber(1)/4, {{"x", 1}})});
    EXPECT_EQ(Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide), isolation.isolateTermWithVariableOnLeftSideOfEquation("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableOnRightSideOfEquationWorks)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term expectedIsolatedBLeftSide(Polynomial{Monomial(AlbaNumber(-3)/4, {{"a", 3}}), Monomial(AlbaNumber(1)/2, {{"y", 2}}), Monomial(AlbaNumber(1)/4, {{"x", 1}})});
    Term expectedIsolatedBRightSide(Monomial(1, {{"b", 4}}));
    EXPECT_EQ(Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide), isolation.isolateTermWithVariableOnRightSideOfEquation("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetTermByIsolatingVariableWorks)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Polynomial polynomialForX{Monomial(4, {{"b", 4}}), Monomial(3, {{"a", 3}}), Monomial(-2, {{"y", 2}})};
    Polynomial polynomialForY{Monomial(2, {{"b", 4}}), Monomial(AlbaNumber(3)/2, {{"a", 3}}), Monomial(AlbaNumber(-1)/2, {{"x", 1}})};
    Polynomial polynomialForA{Monomial(AlbaNumber(-4)/3, {{"b", 4}}), Monomial(AlbaNumber(2)/3, {{"y", 2}}), Monomial(AlbaNumber(1)/3, {{"x", 1}})};
    Polynomial polynomialForB{Monomial(AlbaNumber(-3)/4, {{"a", 3}}), Monomial(AlbaNumber(1)/2, {{"y", 2}}), Monomial(AlbaNumber(1)/4, {{"x", 1}})};
    Term expectedTermForX(polynomialForX);
    Term expectedTermForY(createExpressionIfPossible({polynomialForY, "^", AlbaNumber::createFraction(1, 2)}));
    Term expectedTermForA(createExpressionIfPossible({polynomialForA, "^", AlbaNumber::createFraction(1, 3)}));
    Term expectedTermForB(createExpressionIfPossible({polynomialForB, "^", AlbaNumber::createFraction(1, 4)}));
    EXPECT_EQ(expectedTermForX, isolation.getEquivalentTermByIsolatingAVariable("x"));
    EXPECT_EQ(expectedTermForY, isolation.getEquivalentTermByIsolatingAVariable("y"));
    EXPECT_EQ(expectedTermForA, isolation.getEquivalentTermByIsolatingAVariable("a"));
    EXPECT_EQ(expectedTermForB, isolation.getEquivalentTermByIsolatingAVariable("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableWorksOnPolynomialEquation)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term expectedTermWithX("x");
    Term expectedTermWithoutX(Polynomial{Monomial(4, {{"b", 4}}), Monomial(3, {{"a", 3}}), Monomial(-2, {{"y", 2}})});
    Term expectedTermWithY(Monomial(1, {{"y", 2}}));
    Term expectedTermWithoutY(Polynomial{Monomial(2, {{"b", 4}}), Monomial(AlbaNumber(3)/2, {{"a", 3}}), Monomial(AlbaNumber(-1)/2, {{"x", 1}})});
    Term expectedTermWithA(Monomial(1, {{"a", 3}}));
    Term expectedTermWithoutA(Polynomial{Monomial(AlbaNumber(-4)/3, {{"b", 4}}), Monomial(AlbaNumber(2)/3, {{"y", 2}}), Monomial(AlbaNumber(1)/3, {{"x", 1}})});
    Term expectedTermWithB(Monomial(1, {{"b", 4}}));
    Term expectedTermWithoutB(Polynomial{Monomial(AlbaNumber(-3)/4, {{"a", 3}}), Monomial(AlbaNumber(1)/2, {{"y", 2}}), Monomial(AlbaNumber(1)/4, {{"x", 1}})});
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ(expectedTermWithoutX, termWithoutVariable);
    isolation.isolateTermWithVariable("y", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithY, termWithVariable);
    EXPECT_EQ(expectedTermWithoutY, termWithoutVariable);
    isolation.isolateTermWithVariable("a", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithA, termWithVariable);
    EXPECT_EQ(expectedTermWithoutA, termWithoutVariable);
    isolation.isolateTermWithVariable("b", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithB, termWithVariable);
    EXPECT_EQ(expectedTermWithoutB, termWithoutVariable);
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableWorksOnPolynomialEquationWithMultipleVariableMonomials)
{
    Polynomial leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term expectedTermWithX("x");
    Term expectedTermWithoutX(Monomial(3, {{"a", 3}, {"b", 4}, {"y", -2}}));
    Term expectedTermWithY(Monomial(1, {{"y", 2}}));
    Term expectedTermWithoutY(Monomial(3, {{"a", 3}, {"b", 4}, {"x", -1}}));
    Term expectedTermWithA(Monomial(1, {{"a", 3}}));
    Term expectedTermWithoutA(Monomial(AlbaNumber(1)/3, {{"b", -4}, {"x", 1}, {"y", 2}}));
    Term expectedTermWithB(Monomial(1, {{"b", 4}}));
    Term expectedTermWithoutB(Monomial(AlbaNumber(1)/3, {{"a", -3}, {"x", 1}, {"y", 2}}));
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ(expectedTermWithoutX, termWithoutVariable);
    isolation.isolateTermWithVariable("y", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithY, termWithVariable);
    EXPECT_EQ(expectedTermWithoutY, termWithoutVariable);
    isolation.isolateTermWithVariable("a", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithA, termWithVariable);
    EXPECT_EQ(expectedTermWithoutA, termWithoutVariable);
    isolation.isolateTermWithVariable("b", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithB, termWithVariable);
    EXPECT_EQ(expectedTermWithoutB, termWithoutVariable);
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableWorksOnExpressionWithAdditionAndSubtractionOperation)
{
    Term leftHandSide(Polynomial{Monomial(1, {{"x", 1}, {"y", 2}})});
    Term rightHandSide(createExpressionIfPossible({2, "^", "z"}));
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term expectedTermWithX("x");
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ("((2^z)/1[y^2])", termWithoutVariable.getDisplayableString());
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableWorksOnPolynomialEquation_Example1UsingDerivatives)
{
    Polynomial leftHandSide{
        Monomial(18, {{"dy/dx", 1}, {"y", 5}}),
                Monomial(5, {{"dy/dx", 1}, {"y", 4}}),
                Monomial(-6, {{"x", 5}}),
                Monomial(-2, {{"dy/dx", 1}, {"y", 1}}),
                Monomial(2, {{}})};
    Polynomial rightHandSide{Monomial(0, {})};
    Equation equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Polynomial numerator{Monomial(6, {{"x", 5}}), Monomial(-2, {})};
    Polynomial denominator{Monomial(18, {{"y", 5}}), Monomial(5, {{"y", 4}}), Monomial(-2, {{"y", 1}})};
    Term expectedTermWithDerivative("dy/dx");
    Term expectedTermWithoutDerivative(createExpressionIfPossible({numerator, "/", denominator}));
    isolation.isolateTermWithVariable("dy/dx", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithDerivative, termWithVariable);
    EXPECT_EQ(expectedTermWithoutDerivative, termWithoutVariable);
}

}

}
