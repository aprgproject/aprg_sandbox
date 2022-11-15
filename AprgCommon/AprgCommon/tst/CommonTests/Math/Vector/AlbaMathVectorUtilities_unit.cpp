#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>
#include <CommonTests/Math/Vector/AlbaMathVectorInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;

namespace alba
{

namespace
{
using VectorTwoElements = AlbaMathVector<double, 2>;
using VectorThreeElements = AlbaMathVector<double, 3>;
}

TEST(AlbaMathVectorUtilitiesTest, AreVectorsPerpendicularWorks)
{
    EXPECT_TRUE(areVectorsPerpendicular(VectorTwoElements{0, 5}, VectorTwoElements{10, 0}));
    EXPECT_FALSE(areVectorsPerpendicular(VectorTwoElements{0, 5}, VectorTwoElements{0, 10}));
    EXPECT_FALSE(areVectorsPerpendicular(VectorTwoElements{2, 3}, VectorTwoElements{4, 5}));
}

TEST(AlbaMathVectorUtilitiesTest, AreVectorsParallelWorks)
{
    EXPECT_TRUE(areVectorsParallel(VectorTwoElements{0, 5}, VectorTwoElements{0, 10}));
    EXPECT_FALSE(areVectorsParallel(VectorTwoElements{0, 5}, VectorTwoElements{10, 0}));
    EXPECT_FALSE(areVectorsParallel(VectorTwoElements{2, 3}, VectorTwoElements{4, 5}));
}

// This is always true.
TEST(AlbaMathVectorUtilitiesTest, IsCauchySchwarzInequalitySatisfiedWorksAndAlwaysTrue)
{
    EXPECT_TRUE(isCauchySchwarzInequalitySatisfied(VectorTwoElements{0, 5}, VectorTwoElements{0, 10}));
    EXPECT_TRUE(isCauchySchwarzInequalitySatisfied(VectorTwoElements{0, 5}, VectorTwoElements{10, 0}));
    EXPECT_TRUE(isCauchySchwarzInequalitySatisfied(VectorTwoElements{2, 3}, VectorTwoElements{4, 5}));
}

// This is always true.
TEST(AlbaMathVectorUtilitiesTest, IsTriangleInequalitySatisfiedWorksAndAlwaysTrue)
{
    EXPECT_TRUE(isTriangleInequalitySatisfied(VectorTwoElements{0, 5}, VectorTwoElements{0, 10}));
    EXPECT_TRUE(isTriangleInequalitySatisfied(VectorTwoElements{0, 5}, VectorTwoElements{10, 0}));
    EXPECT_TRUE(isTriangleInequalitySatisfied(VectorTwoElements{2, 3}, VectorTwoElements{4, 5}));
}

// This is always true.
TEST(AlbaMathVectorUtilitiesTest, IsDotProductEqualToProductOfMagnitudesWithCosineOfAngleWorksAndAlwaysTrue)
{
    EXPECT_TRUE(isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(VectorTwoElements{0, 5}, VectorTwoElements{0, 10}));
    EXPECT_TRUE(isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(VectorTwoElements{0, 5}, VectorTwoElements{10, 0}));
    EXPECT_TRUE(isDotProductEqualToProductOfMagnitudesWithCosineOfAngle(VectorTwoElements{2, 3}, VectorTwoElements{4, 5}));
}

TEST(AlbaMathVectorUtilitiesTest, CreateZeroVectorWorks)
{
    EXPECT_EQ((AlbaMathVector<double, 1>{0}), (createZeroVector<double, 1>()));
    EXPECT_EQ((AlbaMathVector<double, 2>{0, 0}), (createZeroVector<double, 2>()));
    EXPECT_EQ((AlbaMathVector<double, 3>{0, 0, 0}), (createZeroVector<double, 3>()));
}

TEST(AlbaMathVectorUtilitiesTest, GetUnitVectorWorks)
{
    EXPECT_EQ((VectorTwoElements{0, 1}), (getUnitVector(VectorTwoElements{0, 5})));
    EXPECT_EQ((VectorTwoElements{1, 0}), (getUnitVector(VectorTwoElements{10, 0})));
    double squareRootOf2Over2 = sqrt(static_cast<double>(2))/2;
    EXPECT_EQ((VectorTwoElements{squareRootOf2Over2, squareRootOf2Over2}), (getUnitVector(VectorTwoElements{10, 10})));
}

TEST(AlbaMathVectorUtilitiesTest, GetVectorProjectionWorks)
{
    VectorTwoElements vectorToProjectTo{10, 10};
    VectorTwoElements vectorToProjectFrom{0, 5};

    VectorTwoElements vectorToExpect{2.5, 2.5};
    EXPECT_EQ(vectorToExpect, getVectorProjection(vectorToProjectTo, vectorToProjectFrom));
}

TEST(AlbaMathVectorUtilitiesTest, GetVectorProjectionWorksForThreeDimensions)
{
    VectorThreeElements vectorToProjectTo{6, -3, 2};
    VectorThreeElements vectorToProjectFrom{2, 1, -3};

    VectorThreeElements vectorToExpect{static_cast<double>(18)/49, static_cast<double>(-9)/49, static_cast<double>(6)/49};
    EXPECT_EQ(vectorToExpect, getVectorProjection(vectorToProjectTo, vectorToProjectFrom));
}

TEST(AlbaMathVectorUtilitiesTest, GetDotProductWorks)
{
    VectorTwoElements mathVector1{2, 4};
    VectorTwoElements mathVector2{-1, 2};

    EXPECT_DOUBLE_EQ(6, getDotProduct(mathVector1, mathVector2));
}

TEST(AlbaMathVectorUtilitiesTest, GetCrossProductWorksForTwoDimensions)
{
    VectorTwoElements mathVector1{2, 1};
    VectorTwoElements mathVector2{3, -1};

    EXPECT_DOUBLE_EQ(-5, getCrossProduct(mathVector1, mathVector2));
}

TEST(AlbaMathVectorUtilitiesTest, GetCrossProductWorksForThreeDimensions)
{
    VectorThreeElements mathVector1{2, 1, -3};
    VectorThreeElements mathVector2{3, -1, 4};

    VectorThreeElements vectorToExpect{1, -17, -5};
    EXPECT_EQ(vectorToExpect, getCrossProduct(mathVector1, mathVector2));
}

TEST(AlbaMathVectorUtilitiesTest, GetAngleBetweenTwoVectorsWorks)
{
    VectorTwoElements mathVector1{0, 4};
    VectorTwoElements mathVector2{10, 0};

    AlbaAngle expectedAngle(AngleUnitType::Radians, getPi()/2);
    EXPECT_EQ(expectedAngle, getAngleBetweenTwoVectors(mathVector1, mathVector2));
}

TEST(AlbaMathVectorUtilitiesTest, GetScalarProjectionWorks){
    VectorTwoElements vectorToProjectTo{0, 5};
    VectorTwoElements vectorToProjectFrom{10, 10};
    EXPECT_DOUBLE_EQ(10, getScalarProjection(vectorToProjectTo, vectorToProjectFrom));
}

TEST(AlbaMathVectorUtilitiesTest, GetScalarProjectionWorksForThreeDimensions)
{
    VectorThreeElements vectorToProjectTo{6, -3, 2};
    VectorThreeElements vectorToProjectFrom{2, 1, -3};

    EXPECT_DOUBLE_EQ(0.42857142857142855, getScalarProjection(vectorToProjectTo, vectorToProjectFrom));
}

TEST(AlbaMathVectorUtilitiesTest, RotateVectorCounterClockwiseWorks)
{
    VectorTwoElements mathVector{3, 4};

    VectorTwoElements expectedMathVector{-4, 3};
    EXPECT_EQ(expectedMathVector, rotateVectorCounterClockwise(mathVector, AlbaAngle(AngleUnitType::Degrees, 90)));
}

}