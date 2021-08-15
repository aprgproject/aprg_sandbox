#include <Math/AlbaMathVector.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaMathVectorTest, ConstructionWorks)
{
    AlbaMathVector<double, 2> mathVector1;
    AlbaMathVector<double, 2>::Values values{6, 7};
    AlbaMathVector<double, 2> mathVector2(values);
    AlbaMathVector<double, 2> mathVector3({3, 4});

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
    AlbaMathVector<double, 2> mathVector1({3, 4});
    AlbaMathVector<double, 2> mathVector2({3, 4});
    AlbaMathVector<double, 2> mathVector3({3, 3});
    AlbaMathVector<double, 2> mathVector4({4, 4});
    AlbaMathVector<double, 2> mathVector5({5, 5});
    AlbaMathVector<double, 2> mathVector6({static_cast<double>(1)/3, static_cast<double>(4)/3});

    EXPECT_TRUE(mathVector1==mathVector1);
    EXPECT_TRUE(mathVector1==mathVector2);
    EXPECT_FALSE(mathVector1==mathVector3);
    EXPECT_FALSE(mathVector1==mathVector4);
    EXPECT_FALSE(mathVector1==mathVector5);
    EXPECT_TRUE(mathVector6==mathVector6);
}

TEST(AlbaMathVectorTest, OperatorNotEqualsWorks)
{
    AlbaMathVector<double, 2> mathVector1({3, 4});
    AlbaMathVector<double, 2> mathVector2({3, 4});
    AlbaMathVector<double, 2> mathVector3({3, 3});
    AlbaMathVector<double, 2> mathVector4({4, 4});
    AlbaMathVector<double, 2> mathVector5({5, 5});
    AlbaMathVector<double, 2> mathVector6({static_cast<double>(1)/3, static_cast<double>(4)/3});

    EXPECT_FALSE(mathVector1!=mathVector1);
    EXPECT_FALSE(mathVector1!=mathVector2);
    EXPECT_TRUE(mathVector1!=mathVector3);
    EXPECT_TRUE(mathVector1!=mathVector4);
    EXPECT_TRUE(mathVector1!=mathVector5);
    EXPECT_FALSE(mathVector6!=mathVector6);
}

TEST(AlbaMathVectorTest, OperatorLessThanWorks)
{
    AlbaMathVector<double, 2> mathVector1({3, 4});
    AlbaMathVector<double, 2> mathVector2({3, 4});
    AlbaMathVector<double, 2> mathVector3({3, 3});
    AlbaMathVector<double, 2> mathVector4({4, 4});
    AlbaMathVector<double, 2> mathVector5({5, 5});
    AlbaMathVector<double, 2> mathVector6({static_cast<double>(1)/3, static_cast<double>(4)/3});

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
    AlbaMathVector<double, 2> mathVector1({3, 4});
    AlbaMathVector<double, 2> mathVector2({5, 6});

    AlbaMathVector<double, 2> actualMathVector(mathVector1+mathVector2);

    AlbaMathVector<double, 2> expectedMathVector({8, 10});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMinusWorks)
{
    AlbaMathVector<double, 2> mathVector1({7, 9});
    AlbaMathVector<double, 2> mathVector2({5, 6});

    AlbaMathVector<double, 2> actualMathVector(mathVector1-mathVector2);

    AlbaMathVector<double, 2> expectedMathVector({2, 3});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryAddWorks)
{
    AlbaMathVector<double, 2> mathVector({3, 4});

    AlbaMathVector<double, 2> actualMathVector(+mathVector);

    AlbaMathVector<double, 2> expectedMathVector({3, 4});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryMinusWorks)
{
    AlbaMathVector<double, 2> mathVector({7, 9});

    AlbaMathVector<double, 2> actualMathVector(-mathVector);

    AlbaMathVector<double, 2> expectedMathVector({-7, -9});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMultiplyScalarWorks)
{
    AlbaMathVector<double, 2> mathVector({3, 4});

    AlbaMathVector<double, 2> actualMathVector(mathVector*2);

    AlbaMathVector<double, 2> expectedMathVector({6, 8});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryDivideScalarWorks)
{
    AlbaMathVector<double, 2> mathVector({7, 9});

    AlbaMathVector<double, 2> actualMathVector(mathVector/2);

    AlbaMathVector<double, 2> expectedMathVector({3.5, 4.5});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorAdditionAssignmentWorks)
{
    AlbaMathVector<double, 2> actualMathVector({3, 4});
    AlbaMathVector<double, 2> anotherMathVector({5, 6});

    actualMathVector+=anotherMathVector;

    AlbaMathVector<double, 2> expectedMathVector({8, 10});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorSubtractionAssignmentWorks)
{
    AlbaMathVector<double, 2> actualMathVector({7, 9});
    AlbaMathVector<double, 2> anotherMathVector({5, 6});

    actualMathVector-=anotherMathVector;

    AlbaMathVector<double, 2> expectedMathVector({2, 3});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, GetSizeWorks)
{
    AlbaMathVector<double, 2> mathVector({3.5, 4.5});

    EXPECT_EQ(2u, mathVector.getSize());
}

TEST(AlbaMathVectorTest, GetValueAtWorks)
{
    AlbaMathVector<double, 2> mathVector({3.5, 4.5});

    ASSERT_EQ(2u, mathVector.getSize());
    EXPECT_DOUBLE_EQ(3.5, mathVector.getValueAt(0));
    EXPECT_DOUBLE_EQ(4.5, mathVector.getValueAt(1));
}

TEST(AlbaMathVectorTest, GetMagnitudeWorks)
{
    AlbaMathVector<double, 2> mathVector1({3, 4});
    AlbaMathVector<double, 2> mathVector2({6, 7});

    EXPECT_DOUBLE_EQ(5, mathVector1.getMagnitude());
    EXPECT_DOUBLE_EQ(9.2195444572928871, mathVector2.getMagnitude());
}

TEST(AlbaMathVectorTest, GetValuesWorks)
{
    AlbaMathVector<double, 2> mathVector({3.5, 4.5});

    AlbaMathVector<double, 2>::Values values(mathVector.getValues());

    ASSERT_EQ(2u, values.size());
    EXPECT_DOUBLE_EQ(3.5, values.at(0));
    EXPECT_DOUBLE_EQ(4.5, values.at(1));
}

TEST(AlbaMathVectorTest, GetDisplayableStringWorks)
{
    AlbaMathVector<double, 2> mathVector({3.5, 4.5});

    EXPECT_EQ("{3.5, 4.5}", mathVector.getDisplayableString());
}

}
