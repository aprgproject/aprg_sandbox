#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMaximumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    //EXPECT_FALSE(willYieldToAbsoluteMaximumValue(xSquared, "x", 0));
    EXPECT_TRUE(willYieldToAbsoluteMaximumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToAbsoluteMinimumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_TRUE(willYieldToAbsoluteMinimumValue(xSquared, "x", 0));
    EXPECT_FALSE(willYieldToAbsoluteMinimumValue(negativeXSquared, "x", 0));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMaximumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMaximumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToRelativeMinimumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_TRUE(willYieldToRelativeMinimumValue(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createCloseEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createCloseEndpoint(3))));
    EXPECT_FALSE(willYieldToRelativeMinimumValue(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

TEST(ExtremaUtilitiesTest, WillYieldToExtremumValueWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Maximum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Maximum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_TRUE(willYieldToExtremumValue(ExtremumType::Minimum, xSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
    EXPECT_FALSE(willYieldToExtremumValue(ExtremumType::Minimum, negativeXSquared, "x", 0, AlbaNumbers{-3, -2, -1, 0, 1, 2, 3}));
}

TEST(ExtremaUtilitiesTest, IsDerivativeZeroOnExtremumWorks)
{
    Term xSquared(Polynomial({Monomial(1, {{"x", 2}}), Monomial(-9, {})}));
    Term negativeXSquared(Polynomial({Monomial(-1, {{"x", 2}}), Monomial(9, {})}));

    EXPECT_TRUE(isDerivativeZeroOnExtremum(xSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
    EXPECT_TRUE(isDerivativeZeroOnExtremum(negativeXSquared, "x", 0, AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3))));
}

}

}
