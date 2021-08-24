#include <Math/Vector/AlbaMathVector.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace
{
using VectorTwoElements = AlbaMathVector<double, 2>;
}

TEST(AlbaMathVectorTest, ConstructionWorks)
{
    VectorTwoElements mathVector1;
    VectorTwoElements::Values values{6, 7};
    VectorTwoElements mathVector2(values);
    VectorTwoElements mathVector3{3, 4};

    ASSERT_EQ(2u, mathVector1.getSize());
    EXPECT_DOUBLE_EQ(0, mathVector1.getValueAt(0));
    EXPECT_DOUBLE_EQ(0, mathVector1.getValueAt(1));
    ASSERT_EQ(2u, mathVector2.getSize());
    EXPECT_DOUBLE_EQ(6, mathVector2.getValueAt(0));
    EXPECT_DOUBLE_EQ(7, mathVector2.getValueAt(1));
    ASSERT_EQ(2u, mathVector3.getSize());
    EXPECT_DOUBLE_EQ(3, mathVector3.getValueAt(0));
    EXPECT_DOUBLE_EQ(4, mathVector3.getValueAt(1));
}

TEST(AlbaMathVectorTest, OperatorEqualsWorks)
{
    VectorTwoElements mathVector1{3, 4};
    VectorTwoElements mathVector2{3, 4};
    VectorTwoElements mathVector3{3, 3};
    VectorTwoElements mathVector4{4, 4};
    VectorTwoElements mathVector5{5, 5};
    VectorTwoElements mathVector6{static_cast<double>(1)/3, static_cast<double>(4)/3};

    EXPECT_TRUE(mathVector1==mathVector1);
    EXPECT_TRUE(mathVector1==mathVector2);
    EXPECT_FALSE(mathVector1==mathVector3);
    EXPECT_FALSE(mathVector1==mathVector4);
    EXPECT_FALSE(mathVector1==mathVector5);
    EXPECT_TRUE(mathVector6==mathVector6);
}

TEST(AlbaMathVectorTest, OperatorNotEqualsWorks)
{
    VectorTwoElements mathVector1{3, 4};
    VectorTwoElements mathVector2{3, 4};
    VectorTwoElements mathVector3{3, 3};
    VectorTwoElements mathVector4{4, 4};
    VectorTwoElements mathVector5{5, 5};
    VectorTwoElements mathVector6{static_cast<double>(1)/3, static_cast<double>(4)/3};

    EXPECT_FALSE(mathVector1!=mathVector1);
    EXPECT_FALSE(mathVector1!=mathVector2);
    EXPECT_TRUE(mathVector1!=mathVector3);
    EXPECT_TRUE(mathVector1!=mathVector4);
    EXPECT_TRUE(mathVector1!=mathVector5);
    EXPECT_FALSE(mathVector6!=mathVector6);
}

TEST(AlbaMathVectorTest, OperatorLessThanWorks)
{
    VectorTwoElements mathVector1{3, 4};
    VectorTwoElements mathVector2{3, 4};
    VectorTwoElements mathVector3{3, 3};
    VectorTwoElements mathVector4{4, 4};
    VectorTwoElements mathVector5{5, 5};
    VectorTwoElements mathVector6{static_cast<double>(1)/3, static_cast<double>(4)/3};

    EXPECT_FALSE(mathVector1<mathVector1);
    EXPECT_FALSE(mathVector1<mathVector2);
    EXPECT_FALSE(mathVector1<mathVector3);
    EXPECT_TRUE(mathVector1<mathVector4);
    EXPECT_TRUE(mathVector1<mathVector5);
    EXPECT_TRUE(mathVector3<mathVector1);
    EXPECT_FALSE(mathVector4<mathVector1);
    EXPECT_FALSE(mathVector5<mathVector1);
    EXPECT_FALSE(mathVector6<mathVector6);
}

TEST(AlbaMathVectorTest, OperatorBinaryAddWorks)
{
    VectorTwoElements mathVector1{3, 4};
    VectorTwoElements mathVector2{5, 6};

    VectorTwoElements actualMathVector(mathVector1+mathVector2);

    VectorTwoElements expectedMathVector{8, 10};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMinusWorks)
{
    VectorTwoElements mathVector1{7, 9};
    VectorTwoElements mathVector2{5, 6};

    VectorTwoElements actualMathVector(mathVector1-mathVector2);

    VectorTwoElements expectedMathVector{2, 3};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryAddWorks)
{
    VectorTwoElements mathVector{3, 4};

    VectorTwoElements actualMathVector(+mathVector);

    VectorTwoElements expectedMathVector{3, 4};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryMinusWorks)
{
    VectorTwoElements mathVector{7, 9};

    VectorTwoElements actualMathVector(-mathVector);

    VectorTwoElements expectedMathVector{-7, -9};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMultiplyScalarWorks)
{
    VectorTwoElements mathVector{3, 4};

    VectorTwoElements actualMathVector(mathVector*2);

    VectorTwoElements expectedMathVector{6, 8};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryDivideScalarWorks)
{
    VectorTwoElements mathVector{7, 9};

    VectorTwoElements actualMathVector(mathVector/2);

    VectorTwoElements expectedMathVector{3.5, 4.5};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorAdditionAssignmentWorks)
{
    VectorTwoElements actualMathVector{3, 4};
    VectorTwoElements anotherMathVector{5, 6};

    actualMathVector+=anotherMathVector;

    VectorTwoElements expectedMathVector{8, 10};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorSubtractionAssignmentWorks)
{
    VectorTwoElements actualMathVector{7, 9};
    VectorTwoElements anotherMathVector{5, 6};

    actualMathVector-=anotherMathVector;

    VectorTwoElements expectedMathVector{2, 3};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, GetSizeWorks)
{
    VectorTwoElements mathVector{3.5, 4.5};

    EXPECT_EQ(2u, mathVector.getSize());
}

TEST(AlbaMathVectorTest, GetValueAtWorks)
{
    VectorTwoElements mathVector{3.5, 4.5};

    ASSERT_EQ(2u, mathVector.getSize());
    EXPECT_DOUBLE_EQ(3.5, mathVector.getValueAt(0));
    EXPECT_DOUBLE_EQ(4.5, mathVector.getValueAt(1));
}

TEST(AlbaMathVectorTest, GetMagnitudeWorks)
{
    VectorTwoElements mathVector1{3, 4};
    VectorTwoElements mathVector2{6, 7};

    EXPECT_DOUBLE_EQ(5, mathVector1.getMagnitude());
    EXPECT_DOUBLE_EQ(9.2195444572928871, mathVector2.getMagnitude());
}

TEST(AlbaMathVectorTest, GetValuesWorks)
{
    VectorTwoElements mathVector{3.5, 4.5};

    VectorTwoElements::Values values(mathVector.getValues());

    ASSERT_EQ(2u, values.size());
    EXPECT_DOUBLE_EQ(3.5, values.at(0));
    EXPECT_DOUBLE_EQ(4.5, values.at(1));
}

TEST(AlbaMathVectorTest, GetDisplayableStringWorks)
{
    VectorTwoElements mathVector{3.5, 4.5};

    EXPECT_EQ("{3.5, 4.5}", mathVector.getDisplayableString());
}

}