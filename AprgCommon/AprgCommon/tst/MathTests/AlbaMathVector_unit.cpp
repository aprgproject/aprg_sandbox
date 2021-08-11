#include <Math/AlbaMathVector.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaMathVectorTest, ConstructionWorks)
{
    AlbaMathVector<double, 2> complex1;
    AlbaMathVector<double, 2>::Values values{6, 7};
    AlbaMathVector<double, 2> complex2(values);
    AlbaMathVector<double, 2> complex3({3, 4});

    ASSERT_EQ(2u, complex1.getSize());
    EXPECT_DOUBLE_EQ(0, complex1.getValueAt(0));
    EXPECT_DOUBLE_EQ(0, complex1.getValueAt(1));
    ASSERT_EQ(2u, complex2.getSize());
    EXPECT_DOUBLE_EQ(6, complex2.getValueAt(0));
    EXPECT_DOUBLE_EQ(7, complex2.getValueAt(1));
    ASSERT_EQ(2u, complex3.getSize());
    EXPECT_DOUBLE_EQ(3, complex3.getValueAt(0));
    EXPECT_DOUBLE_EQ(4, complex3.getValueAt(1));
}

TEST(AlbaMathVectorTest, OperatorEqualsWorks)
{
    AlbaMathVector<double, 2> mathVector1({3, 4});    AlbaMathVector<double, 2> mathVector2({3, 4});
    AlbaMathVector<double, 2> mathVector3({3, 3});
    AlbaMathVector<double, 2> mathVector4({4, 4});
    AlbaMathVector<double, 2> mathVector5({5, 5});    AlbaMathVector<double, 2> mathVector6({static_cast<double>(1)/3, static_cast<double>(4)/3});

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

TEST(AlbaMathVectorTest, OperatorAddWorks)
{
    AlbaMathVector<double, 2> mathVector1({3, 4});    AlbaMathVector<double, 2> mathVector2({5, 6});

    AlbaMathVector<double, 2> actualMathVector(mathVector1+mathVector2);
    AlbaMathVector<double, 2> expectedMathVector({8, 10});
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

/*
TEST(AlbaMathVectorTest, OperatorMinusWorks)
{
    AlbaMathVector<double> mathVector1(7, 9);
    AlbaMathVector<double> mathVector2(5, 6);

    AlbaMathVector<double> actualMathVector(mathVector1-mathVector2);

    AlbaMathVector<double> expectedMathVector(2, 3);
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorMultiplyWorks)
{
    AlbaMathVector<double> mathVector1(3, 4);
    AlbaMathVector<double> mathVector2(5, 6);

    AlbaMathVector<double> actualMathVector(mathVector1*mathVector2);

    AlbaMathVector<double> expectedMathVector(-9, 38);
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorDivideWorks)
{
    AlbaMathVector<double> mathVector1(5, 6);
    AlbaMathVector<double> mathVector2(3, 4);

    AlbaMathVector<double> actualMathVector(mathVector1/mathVector2);

    AlbaMathVector<double> expectedMathVector(1.56, -0.08);
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, GetRealPartWorks)
{
    AlbaMathVector<double> mathVector(3.5, 4.5);

    EXPECT_DOUBLE_EQ(3.5, mathVector.getRealPart());
}

TEST(AlbaMathVectorTest, GetImaginaryPartWorks)
{
    AlbaMathVector<double> mathVector(3.5, 4.5);

    EXPECT_DOUBLE_EQ(4.5, mathVector.getImaginaryPart());
}

TEST(AlbaMathVectorTest, GetModulusWorks)
{
    AlbaMathVector<double> mathVector(3, 4);

    EXPECT_DOUBLE_EQ(5, mathVector.getModulus());
}

TEST(AlbaMathVectorTest, GetModulusSquaredWorks)
{
    AlbaMathVector<double> mathVector(3, 4);

    EXPECT_DOUBLE_EQ(25, mathVector.getModulusSquared());
}

TEST(AlbaMathVectorTest, GetConjugateWorks)
{
    AlbaMathVector<double> mathVector1(3, 4);

    AlbaMathVector<double> actualMathVector(mathVector1.getConjugate());

    AlbaMathVector<double> expectedMathVector(3, -4);
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, GetDisplayableStringWorks)
{
    AlbaMathVector<double> mathVector(3.5, 4.5);

    EXPECT_EQ("(3.5 + 4.5i)", mathVector.getDisplayableString());
}*/

}
