#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace algebra
{

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMinimumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_TRUE(willYieldToAbsoluteMinimumValue(xSquared, "x", 0));
    EXPECT_FALSE(willYieldToAbsoluteMinimumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMaximumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToAbsoluteMaximumValue(xSquared, "x", 0));
    EXPECT_TRUE(willYieldToAbsoluteMaximumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMinimumValueWorks){
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMaximumValueWorks){
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToExtremumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Maximum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Maximum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Minimum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Minimum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
}

TEST(ExtremaUtilitiesTest, IsDerivativeZeroOnExtremumWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_TRUE(isDerivativeZeroOnExtremum(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_TRUE(isDerivativeZeroOnExtremum(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
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

TEST(ExtremaUtilitiesTest, GetMaximumAndMinimumAtClosedIntervalWorksOnExample1)
{
    Term termToTest(Polynomial(
    {Monomial(1, {{"x", 3}}),
     Monomial(1, {{"x", 2}}),
     Monomial(-1, {{"x", 1}}),
     Monomial(1, {})}));
    AlbaNumberInterval closedInterval(createCloseEndpoint(-2), createCloseEndpoint(AlbaNumber::createFraction(1, 2)));

    MinimumAndMaximum minmax(getMinimumAndMaximumAtClosedInterval(termToTest, "x", closedInterval));

    EXPECT_EQ(AlbaNumber(-2), minmax.minimumInputOutput.first);
    EXPECT_EQ(AlbaNumber(-1), minmax.minimumInputOutput.second);
    EXPECT_EQ(AlbaNumber(-1), minmax.maximumInputOutput.first);
    EXPECT_EQ(AlbaNumber(2), minmax.maximumInputOutput.second);
}

TEST(ExtremaUtilitiesTest, GetMaximumAndMinimumAtClosedIntervalWorksOnExample2)
{
    Term subPolynomial(Polynomial({Monomial(1, {{"x", 1}}), Monomial(-2, {})}));
    Term termToTest(createExpressionIfPossible({subPolynomial, Term("^"), Term(AlbaNumber::createFraction(2, 3))}));
    AlbaNumberInterval closedInterval(createCloseEndpoint(1), createCloseEndpoint(5));

    MinimumAndMaximum minmax(getMinimumAndMaximumAtClosedInterval(termToTest, "x", closedInterval));

    EXPECT_EQ(AlbaNumber(2), minmax.minimumInputOutput.first);
    EXPECT_EQ(AlbaNumber(0), minmax.minimumInputOutput.second);
    EXPECT_EQ(AlbaNumber(5), minmax.maximumInputOutput.first);
    EXPECT_EQ(AlbaNumber(AlbaNumber(9)^AlbaNumber::createFraction(1, 3)), minmax.maximumInputOutput.second);
}

}

}