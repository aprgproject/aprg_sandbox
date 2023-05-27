#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(PolynomialHelpersTest, DoesThePolynomialHaveOnlyOneConstantWorks) {
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneConstant(
        Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneConstant(Polynomial{Monomial(-16, {}), Monomial(32, {})}));
    EXPECT_TRUE(doesThePolynomialHaveOnlyOneConstant(Polynomial{Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, DoesThePolynomialHaveOnlyOneVariableWorks) {
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneVariable(
        Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));
    EXPECT_TRUE(doesThePolynomialHaveOnlyOneVariable(
        Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, DoesThePolynomialHaveDoubleValueWorks) {
    EXPECT_FALSE(doesThePolynomialHaveDoubleValue(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
    EXPECT_TRUE(doesThePolynomialHaveDoubleValue(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-0.75, {})}));
    EXPECT_TRUE(doesThePolynomialHaveDoubleValue(Polynomial{Monomial(1, {{"x", 0.75}}), Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, DoesOnePolynomialHaveADoubleValueWorks) {
    Polynomial polynomialWithoutDouble{Monomial(1, {{"x", 3}}), Monomial(-16, {})};
    Polynomial polynomialWithDouble{Monomial(1, {{"x", 3}}), Monomial(-0.75, {})};

    Polynomials polynomials1{polynomialWithoutDouble, polynomialWithoutDouble};
    Polynomials polynomials2{polynomialWithoutDouble, polynomialWithDouble};
    Polynomials polynomials3{polynomialWithDouble, polynomialWithDouble};
    EXPECT_FALSE(doesOnePolynomialHaveADoubleValue(polynomials1));
    EXPECT_TRUE(doesOnePolynomialHaveADoubleValue(polynomials2));
    EXPECT_TRUE(doesOnePolynomialHaveADoubleValue(polynomials3));
}

TEST(PolynomialHelpersTest, HasAMonomialWithMultipleVariablesWorks) {
    EXPECT_FALSE(hasAMonomialWithMultipleVariables(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
    EXPECT_TRUE(hasAMonomialWithMultipleVariables(Polynomial{Monomial(1, {{"x", 3}, {"y", 4}}), Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, HasAMonomialWithDegreeMoreThanOneOrFractionalWorks) {
    EXPECT_FALSE(hasAMonomialWithDegreeMoreThanOneOrFractional(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-16, {})}));
    EXPECT_TRUE(hasAMonomialWithDegreeMoreThanOneOrFractional(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-16, {})}));
    EXPECT_TRUE(hasAMonomialWithDegreeMoreThanOneOrFractional(
        Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, IsOneMonomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_FALSE(isOneMonomial(polynomial1));
    EXPECT_TRUE(isOneMonomial(polynomial2));
    EXPECT_FALSE(isOneMonomial(polynomial3));
}

TEST(PolynomialHelpersTest, IsVariableExponentMapContentFoundWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {{"x", 1}})};
    Polynomial polynomial3{Monomial(6, {{"x", 1}}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_FALSE(isVariableExponentInMonomialFound(polynomial1, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})));
    EXPECT_FALSE(isVariableExponentInMonomialFound(polynomial2, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})));
    EXPECT_TRUE(isVariableExponentInMonomialFound(polynomial3, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})));
}

TEST(PolynomialHelpersTest, GetBinomialCoefficientWorks) {
    EXPECT_EQ(6, getBinomialCoefficient(4U, 2U));
    EXPECT_EQ(252, getBinomialCoefficient(10U, 5U));
}

TEST(PolynomialHelpersTest, GetMultinomialCoefficientWorks) {    // The third power of the trinomial a + b + c is given by
    // (a+b+c)^3 = a^3 + b^3 + c^3 + 3*a^2*b + 3*a^2*c + 3*a*b^2 + 3*b^2*c + 3*a*c^2 + 3*b*c^2 + 6*a*b*c

    // The coefficient of a^2 * b^0 * c^1 = 3
    EXPECT_EQ(3, getMultinomialCoefficient(3U, {2U, 0U, 1U}));

    // The coefficient of a^1 * b^1 * c^1 = 6
    EXPECT_EQ(6, getMultinomialCoefficient(3U, {1U, 1U, 1U}));
}

TEST(PolynomialHelpersTest, GetFirstMonomialWorks) {    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};
    Monomial monomial1(getFirstMonomial(polynomial1));
    Monomial monomial2(getFirstMonomial(polynomial2));
    Monomial monomial3(getFirstMonomial(polynomial3));

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());

    EXPECT_DOUBLE_EQ(6, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());

    EXPECT_DOUBLE_EQ(6, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap3.empty());
}

TEST(PolynomialHelpersTest, GetMaxDegreeWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_DOUBLE_EQ(0, getMaxDegree(polynomial1).getDouble());
    EXPECT_DOUBLE_EQ(0, getMaxDegree(polynomial2).getDouble());
    EXPECT_DOUBLE_EQ(9, getMaxDegree(polynomial3).getDouble());
}

TEST(PolynomialHelpersTest, GetDegreeForVariableWorks) {
    Polynomial polynomial{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_DOUBLE_EQ(0, getDegreeForVariable(polynomial, "a").getDouble());
    EXPECT_DOUBLE_EQ(2, getDegreeForVariable(polynomial, "x").getDouble());
    EXPECT_DOUBLE_EQ(3, getDegreeForVariable(polynomial, "y").getDouble());
    EXPECT_DOUBLE_EQ(4, getDegreeForVariable(polynomial, "z").getDouble());
}

TEST(PolynomialHelpersTest, GetCoefficientOfVariableExponentWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {{"x", 1}})};
    Polynomial polynomial3{Monomial(6, {{"x", 1}}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_DOUBLE_EQ(
        0, getCoefficientOfVariableExponent(polynomial1, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})).getDouble());
    EXPECT_DOUBLE_EQ(
        0, getCoefficientOfVariableExponent(polynomial2, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})).getDouble());
    EXPECT_DOUBLE_EQ(
        -7, getCoefficientOfVariableExponent(polynomial3, Monomial(98, {{"x", 2}, {"y", 3}, {"z", 4}})).getDouble());
}

TEST(PolynomialHelpersTest, GetRemainderForOneVariablePolynomialDividedByVariableMinusConstantValueWorks) {
    Polynomial polynomial{Monomial(5, {{"x", 3}}), Monomial(-8, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(4, {})};

    AlbaNumber expectedRemainder(24);
    EXPECT_EQ(
        expectedRemainder, getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(polynomial, 2));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootsIsEmptyWhenConstantIsGiven) {
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootsIsEmptyWhenMultipleVariablesAreGiven) {
    AlbaNumbers roots(getRoots(
        RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndFactorizesAPolynomial) {
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", 2}}), Monomial(-16, {})}));

    ASSERT_EQ(2U, roots.size());
    EXPECT_EQ(AlbaNumber(-4), roots.at(0));
    EXPECT_EQ(AlbaNumber(4), roots.at(1));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootIsZeroWhenExponentIsPositive) {
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(4) / 3}})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(0), roots.at(0));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndZeroIsNotIncludedWhenExponentIsNegative) {
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(-4) / 3}})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndWhenPolynomialIsNotSorted) {
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(-16, {}), Monomial(1, {{"x", 1}})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(16), roots.at(0));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootIsCorrectlyCalculatedWhenExponentIsNotAnInteger) {
    AlbaNumbers roots(
        getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(4) / 3}}), Monomial(-16, {})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(8), roots.at(0));
}

TEST(PolynomialHelpersTest, RaiseBinomialToAPowerUsingBinomialExpansionWorks) {
    Polynomial binomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};

    Polynomial actualExpansion(raiseBinomialToAPowerUsingBinomialExpansion(binomial, 4));

    Polynomial expectedExpansion{
        Monomial(1, {{"x", 4}}), Monomial(4, {{"x", 3}, {"y", 1}}), Monomial(6, {{"x", 2}, {"y", 2}}),
        Monomial(4, {{"x", 1}, {"y", 3}}), Monomial(1, {{"y", 4}})};
    EXPECT_EQ(expectedExpansion, actualExpansion);
}

TEST(PolynomialHelpersTest, RemoveEmptyPolynomialsWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial polynomial3;
    Polynomial polynomial4{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomial5;
    Polynomials polynomials{polynomial1, polynomial2, polynomial3, polynomial4, polynomial5};

    removeEmptyPolynomials(polynomials);

    ASSERT_EQ(2U, polynomials.size());
    EXPECT_EQ(polynomial2, polynomials.at(0));
    EXPECT_EQ(polynomial4, polynomials.at(1));
}

}  // namespace algebra

}  // namespace alba
