#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMinimumValueWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_TRUE(willYieldToAbsoluteMinimumValue(xSquared, "x", 0));
    EXPECT_FALSE(willYieldToAbsoluteMinimumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMaximumValueWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_FALSE(willYieldToAbsoluteMaximumValue(xSquared, "x", 0));
    EXPECT_TRUE(willYieldToAbsoluteMaximumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMinimumValueWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMaximumValueWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToExtremumValueWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Maximum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Maximum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Minimum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Minimum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
}

TEST(ExtremaUtilitiesTest, IsDerivativeZeroOnPossibleExtremumWorks)
{
    Term xSquared(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-9, {})});
    Term negativeXSquared(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(9, {})});

    EXPECT_TRUE(isDerivativeZeroOnPossibleExtremum(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_TRUE(isDerivativeZeroOnPossibleExtremum(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, IsDecreasingAtWorks)
{
    EXPECT_TRUE(isDecreasingAt(Term(Monomial(1, {{"x", 2}})), "x", -2));
    EXPECT_FALSE(isDecreasingAt(Term(Monomial(1, {{"x", 2}})), "x", 2));
    EXPECT_FALSE(isDecreasingAt(Term(Monomial(-1, {{"x", 2}})), "x", -2));
    EXPECT_TRUE(isDecreasingAt(Term(Monomial(-1, {{"x", 2}})), "x", 2));
}

TEST(ExtremaUtilitiesTest, IsIncreasingAtWorks)
{
    EXPECT_FALSE(isIncreasingAt(Term(Monomial(1, {{"x", 2}})), "x", -2));
    EXPECT_TRUE(isIncreasingAt(Term(Monomial(1, {{"x", 2}})), "x", 2));
    EXPECT_TRUE(isIncreasingAt(Term(Monomial(-1, {{"x", 2}})), "x", -2));
    EXPECT_FALSE(isIncreasingAt(Term(Monomial(-1, {{"x", 2}})), "x", 2));
}

TEST(ExtremaUtilitiesTest, IsConcaveDownwardAtWorks)
{
    EXPECT_TRUE(isConcaveDownwardAt(Term(Monomial(1, {{"x", 3}})), "x", -3));
    EXPECT_FALSE(isConcaveDownwardAt(Term(Monomial(1, {{"x", 3}})), "x", 3));
    EXPECT_FALSE(isConcaveDownwardAt(Term(Monomial(-1, {{"x", 3}})), "x", -3));
    EXPECT_TRUE(isConcaveDownwardAt(Term(Monomial(-1, {{"x", 3}})), "x", 3));
}

TEST(ExtremaUtilitiesTest, IsConcaveUpwardAtWorks)
{
    EXPECT_FALSE(isConcaveUpwardAt(Term(Monomial(1, {{"x", 3}})), "x", -3));
    EXPECT_TRUE(isConcaveUpwardAt(Term(Monomial(1, {{"x", 3}})), "x", 3));
    EXPECT_TRUE(isConcaveUpwardAt(Term(Monomial(-1, {{"x", 3}})), "x", -3));
    EXPECT_FALSE(isConcaveUpwardAt(Term(Monomial(-1, {{"x", 3}})), "x", 3));
}

TEST(ExtremaUtilitiesTest, HasPointOfInflectionAtWorks)
{
    EXPECT_FALSE(hasPointOfInflectionAt(Term(Constant(0)), "x", 0));
    EXPECT_FALSE(hasPointOfInflectionAt(Term(Monomial(1, {{"x", 3}})), "x", -3));
    EXPECT_TRUE(hasPointOfInflectionAt(Term(Monomial(1, {{"x", 3}})), "x", 0));
    EXPECT_FALSE(hasPointOfInflectionAt(Term(Monomial(1, {{"x", 3}})), "x", 3));
}

TEST(ExtremaUtilitiesTest, IsRolleTheoremSatisfiedWorks)
{
    Term termToTest(Polynomial(
    {Monomial(4, {{"x", 3}}),
     Monomial(-9, {{"x", 1}})}));

    EXPECT_FALSE(isRolleTheoremSatisfied(termToTest, "x", 1, 1, 1));
    EXPECT_TRUE(isRolleTheoremSatisfied(termToTest, "x", AlbaNumber::createFraction(-3, 2), 0, AlbaNumber(-0.5*sqrt(3))));
    EXPECT_TRUE(isRolleTheoremSatisfied(termToTest, "x", 0, AlbaNumber::createFraction(3, 2), AlbaNumber(0.5*sqrt(3))));
    EXPECT_TRUE(isRolleTheoremSatisfied(termToTest, "x", AlbaNumber::createFraction(-3, 2), AlbaNumber::createFraction(3, 2), AlbaNumber(-0.5*sqrt(3))));
    EXPECT_TRUE(isRolleTheoremSatisfied(termToTest, "x", AlbaNumber::createFraction(-3, 2), AlbaNumber::createFraction(3, 2), AlbaNumber(0.5*sqrt(3))));
}

TEST(ExtremaUtilitiesTest, GetInputValuesInIntervalWithSameAsMeanOfIntervalWorks)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", 3}}),
     Monomial(-5, {{"x", 2}}),
     Monomial(-3, {{"x", 1}})}));

    AlbaNumbers values(getInputValuesInIntervalWithSameAsMeanOfInterval(termToTest, "x", 1, 3));

    ASSERT_EQ(1U, values.size());
    EXPECT_EQ(AlbaNumber::createFraction(7, 3), values.at(0));
}

TEST(ExtremaUtilitiesTest, GetAbsoluteExtremumBasedOnRelativeExtremaOnIntervalWorks)
{
    Term termToTest(Polynomial(
    {Monomial(3, {{"x", 4}}),
     Monomial(-8, {{"x", 3}}),
     Monomial(12, {{"x", 2}}),
     Monomial(-12, {{"x", 1}}),
     Monomial(3, {})}));
    Extrema relativeExtrema(getRelativeExtrema(termToTest, "x"));

    Extremum expectedAbsoluteExtremum(getAbsoluteExtremumBasedOnRelativeExtremaOnInterval(relativeExtrema, createAllRealValuesInterval()));

    EXPECT_EQ(ExtremumType::Minimum, expectedAbsoluteExtremum.extremumType);
    EXPECT_EQ(AlbaNumber(1), expectedAbsoluteExtremum.inputOutputValues.first);
    EXPECT_EQ(AlbaNumber(-2), expectedAbsoluteExtremum.inputOutputValues.second);
}

TEST(ExtremaUtilitiesTest, GetCriticalNumbersWorks)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", AlbaNumber::createFraction(4, 3)}}),
     Monomial(4, {{"x", AlbaNumber::createFraction(1, 3)}})}));

    AlbaNumbers criticalNumbers(getCriticalNumbers(termToTest, "x"));

    ASSERT_EQ(2U, criticalNumbers.size());
    EXPECT_EQ(AlbaNumber(-1), criticalNumbers.at(0));
    EXPECT_EQ(AlbaNumber(0), criticalNumbers.at(1));
}

TEST(ExtremaUtilitiesTest, GetInputValuesAtPointsOfInflectionWorksWithExample1)
{
    Term termToTest(Monomial(1, {{"x", 3}}));

    AlbaNumbers values(getInputValuesAtPointsOfInflection(termToTest, "x"));

    ASSERT_EQ(1U, values.size());
    EXPECT_EQ(AlbaNumber(0), values.at(0));
}

TEST(ExtremaUtilitiesTest, GetInputValuesAtPointsOfInflectionWorksWithExample2)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(-2, {{"x", AlbaNumber::createFraction(1, 3)}})}));

    AlbaNumbers values(getInputValuesAtPointsOfInflection(termToTest, "x"));

    ASSERT_EQ(2U, values.size());
    EXPECT_EQ(AlbaNumber(8), values.at(0));
    EXPECT_EQ(AlbaNumber(0), values.at(1));
}

TEST(ExtremaUtilitiesTest, GetMaximumAndMinimumAtClosedIntervalWorksOnExample1)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", 3}}),
     Monomial(1, {{"x", 2}}),
     Monomial(-1, {{"x", 1}}),
     Monomial(1, {})}));
    AlbaNumberInterval closedInterval(createCloseEndpoint(-2), createCloseEndpoint(AlbaNumber::createFraction(1, 2)));

    MinimumAndMaximum minmax(getMinimumAndMaximumAtClosedInterval(termToTest, "x", closedInterval));

    EXPECT_EQ(AlbaNumber(-2), minmax.minimumInputOutputValues.first);
    EXPECT_EQ(AlbaNumber(-1), minmax.minimumInputOutputValues.second);
    EXPECT_EQ(AlbaNumber(-1), minmax.maximumInputOutputValues.first);
    EXPECT_EQ(AlbaNumber(2), minmax.maximumInputOutputValues.second);
}

TEST(ExtremaUtilitiesTest, GetMaximumAndMinimumAtClosedIntervalWorksOnExample2)
{
    Term subPolynomial(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term termToTest(createExpressionIfPossible({subPolynomial, Term("^"), Term(AlbaNumber::createFraction(2, 3))}));
    AlbaNumberInterval closedInterval(createCloseEndpoint(1), createCloseEndpoint(5));

    MinimumAndMaximum minmax(getMinimumAndMaximumAtClosedInterval(termToTest, "x", closedInterval));

    EXPECT_EQ(AlbaNumber(2), minmax.minimumInputOutputValues.first);
    EXPECT_EQ(AlbaNumber(0), minmax.minimumInputOutputValues.second);
    EXPECT_EQ(AlbaNumber(5), minmax.maximumInputOutputValues.first);
    EXPECT_EQ(AlbaNumber(AlbaNumber(9)^AlbaNumber::createFraction(1, 3)), minmax.maximumInputOutputValues.second);
}

TEST(ExtremaUtilitiesTest, GetRelativeExtremaWorksOnExample1)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", 4}}),
     Monomial(AlbaNumber::createFraction(4, 3), {{"x", 3}}),
     Monomial(-4, {{"x", 2}})}));

    Extrema extrema(getRelativeExtrema(termToTest, "x"));

    ASSERT_EQ(3U, extrema.size());
    EXPECT_EQ(ExtremumType::Minimum, extrema.at(0).extremumType);
    EXPECT_EQ(AlbaNumber(-2), extrema.at(0).inputOutputValues.first);
    EXPECT_EQ(AlbaNumber::createFraction(-32, 3), extrema.at(0).inputOutputValues.second);
    EXPECT_EQ(ExtremumType::Maximum, extrema.at(1).extremumType);
    EXPECT_EQ(AlbaNumber(0), extrema.at(1).inputOutputValues.first);
    EXPECT_EQ(AlbaNumber(0), extrema.at(1).inputOutputValues.second);
    EXPECT_EQ(ExtremumType::Minimum, extrema.at(2).extremumType);
    EXPECT_EQ(AlbaNumber(1), extrema.at(2).inputOutputValues.first);
    EXPECT_EQ(AlbaNumber::createFraction(-5, 3), extrema.at(2).inputOutputValues.second);
}

TEST(ExtremaUtilitiesTest, GetRelativeExtremaWorksOnExample2)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}),
     Monomial(-2, {{"x", AlbaNumber::createFraction(1, 3)}})}));

    Extrema extrema(getRelativeExtrema(termToTest, "x"));

    ASSERT_EQ(1U, extrema.size());
    EXPECT_EQ(ExtremumType::Minimum, extrema.at(0).extremumType);
    EXPECT_EQ(AlbaNumber(1), extrema.at(0).inputOutputValues.first);
    EXPECT_EQ(AlbaNumber(-1), extrema.at(0).inputOutputValues.second);
}

}

}
