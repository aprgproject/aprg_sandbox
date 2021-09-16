#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationTest, IsDifferentiableAtWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAt(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAt(termToTest, "x", 2));
}

TEST(DifferentiationTest, GetDerivativeByDefinitionWorksWhenInputIsAConstant)
{
    Term termToTest(5);

    Term derivative(getDerivativeUsingLimit(termToTest, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Constant(0)), derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksWhenXIsAValue)
{
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term derivative(getDerivativeUsingLimit(termToTest, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(4), derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksWhenXIsAVariable)
{
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term derivative(getDerivativeUsingLimit(termToTest, "x", Term("y"), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Monomial(2, {{"y", 1}})), derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksForPolynomialAndWhenXIsAValue)
{
    Term polynomialTerm(Polynomial{Monomial(3, {{"x", 2}}), Monomial(12, {})});

    Term derivative(getDerivativeUsingLimit(polynomialTerm, "x", Term(2), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(12), derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksForPolynomialAndWhenXIsAVariable)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-3, {{"x", 1}}), Monomial(4, {})});

    Term derivative(getDerivativeUsingLimit(polynomialTerm, "x", Term("z"), LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"z", 2}}), Monomial(-3, {})}), derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksForRadicalAndWhenXIsAVariable)
{
    //Does not work because of simplification should rationalize the numerator
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term radicalTerm(createExpressionIfPossible({polynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term derivative(getDerivativeUsingLimit(radicalTerm, "x", Term("a"), LimitAtAValueApproachType::BothSides));

    Term expectedSubPolynomial(Polynomial{Monomial(1, {{"a", 1}}), Monomial(-3, {})});
    Term expectedRadicalTerm(createExpressionIfPossible({expectedSubPolynomial, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));    Term expectedTerm(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("/"), expectedRadicalTerm}));
    EXPECT_EQ(expectedTerm, derivative);
}
TEST(DifferentiationTest, GetDerivativeByDefinitionWorksForPolynomialOverPolynomialAndWhenXIsAVariable)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term derivative(getDerivativeUsingLimit(polynomialOverPolynomialTerm, "x", Term("a"), LimitAtAValueApproachType::BothSides));

    Term expectedDenominator(Polynomial{Monomial(1, {{"a", 2}}), Monomial(-6, {{"a", 1}}), Monomial(9, {})});
    Term expectedTerm(createExpressionIfPossible({Term(5), Term("/"), expectedDenominator}));    EXPECT_EQ(expectedTerm, derivative);
}

}

}
