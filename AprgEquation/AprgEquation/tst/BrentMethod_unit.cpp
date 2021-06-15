#include <BrentMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(BrentMethodTest, ConstructionWorks)
{
    BrentMethod(AlbaNumbers{});
    BrentMethod(AlbaNumbers{1, 2, 3});
}

TEST(BrentMethodTest, CalculateRootWithNoRealRoots)
{
    BrentMethod brentMethod(AlbaNumbers{1, 1, 1});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_FALSE(numberOptionalToVerify.hasContent());
}

TEST(BrentMethodTest, CalculateRootWorksOnPerfectSquare)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnPerfectSquareWithACoefficient)
{
    BrentMethod brentMethod(AlbaNumbers{9, 6, 1});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-1, 3), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuadraticExample)
{
    BrentMethod brentMethod(AlbaNumbers{24, -2, -35});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-7, 6), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksDifferenceOfSquares)
{
    BrentMethod brentMethod(AlbaNumbers{1, 0, -256});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-16), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksDifferenceOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, -27});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(3, 2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksSumOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, 27});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-3, 2), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnCubicExample)
{
    BrentMethod brentMethod(AlbaNumbers{192, 200, -298, -315});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(5, 4), numberOptionalToVerify.getConstReference());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuarticExample_FailedExample)
{
    BrentMethod brentMethod(AlbaNumbers{2112, -296, -5878, 409, 4095});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_FALSE(numberOptionalToVerify.hasContent());
}

TEST(BrentMethodTest, CalculateRootWorksOnQuarticExample)
{
    BrentMethod brentMethod(AlbaNumbers{1, 8, 24, 32, 16});

    AlbaNumberOptional numberOptionalToVerify(brentMethod.calculateRoot());

    ASSERT_TRUE(numberOptionalToVerify.hasContent());
    EXPECT_EQ(AlbaNumber(-2), numberOptionalToVerify.getConstReference());
}

}

}
