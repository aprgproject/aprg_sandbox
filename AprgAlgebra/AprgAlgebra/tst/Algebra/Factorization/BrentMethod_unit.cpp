#include <Algebra/Factorization/BrentMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(BrentMethodTest, ConstructionWorks)
{
    BrentMethod(AlbaNumbers{});
    BrentMethod(AlbaNumbers{1, 2, 3});
}

TEST(BrentMethodTest, CalculateRootWithNoRealRoots)
{
    BrentMethod brentMethod(AlbaNumbers{1, 1, 1});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-1, 1));

    ASSERT_FALSE(numberOptionalToVerify.hasContent());
}

TEST(BrentMethodTest, CalculateRootWorksOnPerfectSquare)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-4, 4));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnPerfectSquareWithACoefficient)
{
    BrentMethod brentMethod(AlbaNumbers{9, 6, 1});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-9, 9));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-1, 3), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuadraticExample)
{
    BrentMethod brentMethod(AlbaNumbers{24, -2, -35});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-35, 35));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-7, 6), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksDifferenceOfSquares)
{
    BrentMethod brentMethod(AlbaNumbers{1, 0, -256});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-256, 256));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-16), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksDifferenceOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, -27});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-27, 27));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(3, 2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksSumOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, 27});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-27, 27));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-3, 2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnCubicExample)
{
    BrentMethod brentMethod(AlbaNumbers{192, 200, -298, -315});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-315, 315));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(5, 4), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuarticExample_FailedExampleBasedOnInitialValues)
{
    BrentMethod brentMethod(AlbaNumbers{2112, -296, -5878, 409, 4095});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-4095, 4095));

    ASSERT_FALSE(numberOptionalToVerify.hasContent());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuarticExample_SuccessfulExampleBasedOnInitialValues)
{
    BrentMethod brentMethod(AlbaNumbers{8448, -888, -11756, 409});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-8448, -0.646933510774966));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_DOUBLE_EQ(-1.1460171174121716, numberOptionalToVerify.getConstReference().getDouble());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuarticExample)
{
    BrentMethod brentMethod(AlbaNumbers{1, 8, 24, 32, 16});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot(-16, 16));

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-2), numberOptionalToVerify.getConstReference());
}

}

}
