#include <Math/Vector/AlbaMathVectorUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;

namespace alba
{

namespace
{
using VectorTwoElements = AlbaMathVector<double, 2>;
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
    EXPECT_EQ((AlbaMathVector<double, 1>{0}), (createZeroVector<double, 1>()));    EXPECT_EQ((AlbaMathVector<double, 2>{0, 0}), (createZeroVector<double, 2>()));
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

TEST(AlbaMathVectorUtilitiesTest, GetDotProductWorks)
{
    VectorTwoElements mathVector1{2, 4};    VectorTwoElements mathVector2{-1, 2};

    EXPECT_DOUBLE_EQ(6, getDotProduct(mathVector1, mathVector2));
}
TEST(AlbaMathVectorUtilitiesTest, GetAngleBetweenTwoVectorsWorks)
{
    VectorTwoElements mathVector1{0, 4};
    VectorTwoElements mathVector2{10, 0};

    EXPECT_DOUBLE_EQ(getPi()/2, getAngleBetweenTwoVectors(mathVector1, mathVector2));
}

TEST(AlbaMathVectorUtilitiesTest, GetScalarProjectionWorks)
{
    VectorTwoElements vectorToProjectTo{0, 5};
    VectorTwoElements vectorToProjectFrom{10, 10};

    EXPECT_DOUBLE_EQ(10, getScalarProjection(vectorToProjectTo, vectorToProjectFrom));
}

}