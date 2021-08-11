#include <Math/AlbaComplexNumber.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaComplexNumberTest, ConstructionWorks)
{
    AlbaComplexNumber<double> complex1;
    AlbaComplexNumber<double> complex2(3, 4);

    EXPECT_DOUBLE_EQ(0, complex1.getRealPart());
    EXPECT_DOUBLE_EQ(0, complex1.getImaginaryPart());
    EXPECT_DOUBLE_EQ(3, complex2.getRealPart());
    EXPECT_DOUBLE_EQ(4, complex2.getImaginaryPart());
}

TEST(AlbaComplexNumberTest, OperatorEqualsWorks)
{
    AlbaComplexNumber<double> complex1(3, 4);
    AlbaComplexNumber<double> complex2(3, 4);
    AlbaComplexNumber<double> complex3(3, 3);
    AlbaComplexNumber<double> complex4(4, 4);
    AlbaComplexNumber<double> complex5(5, 5);
    AlbaComplexNumber<double> complex6(static_cast<double>(1)/3, static_cast<double>(4)/3);

    EXPECT_TRUE(complex1==complex1);
    EXPECT_TRUE(complex1==complex2);
    EXPECT_FALSE(complex1==complex3);
    EXPECT_FALSE(complex1==complex4);
    EXPECT_FALSE(complex1==complex5);
    EXPECT_TRUE(complex6==complex6);
}

TEST(AlbaComplexNumberTest, OperatorBinaryAddWorks)
{
    AlbaComplexNumber<double> complex1(3, 4);
    AlbaComplexNumber<double> complex2(5, 6);

    AlbaComplexNumber<double> actualComplex(complex1+complex2);

    AlbaComplexNumber<double> expectedComplex(8, 10);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorBinaryMinusWorks)
{
    AlbaComplexNumber<double> complex1(7, 9);
    AlbaComplexNumber<double> complex2(5, 6);

    AlbaComplexNumber<double> actualComplex(complex1-complex2);

    AlbaComplexNumber<double> expectedComplex(2, 3);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorUnaryAddWorks)
{
    AlbaComplexNumber<double> complex(3, 4);

    AlbaComplexNumber<double> actualComplex(+complex);

    AlbaComplexNumber<double> expectedComplex(3, 4);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorUnaryMinusWorks)
{
    AlbaComplexNumber<double> complex(7, 9);

    AlbaComplexNumber<double> actualComplex(-complex);

    AlbaComplexNumber<double> expectedComplex(-7, -9);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorMultiplyWorks)
{
    AlbaComplexNumber<double> complex1(3, 4);
    AlbaComplexNumber<double> complex2(5, 6);

    AlbaComplexNumber<double> actualComplex(complex1*complex2);

    AlbaComplexNumber<double> expectedComplex(-9, 38);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorDivideWorks)
{
    AlbaComplexNumber<double> complex1(5, 6);
    AlbaComplexNumber<double> complex2(3, 4);

    AlbaComplexNumber<double> actualComplex(complex1/complex2);

    AlbaComplexNumber<double> expectedComplex(1.56, -0.08);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorRaiseToPowerWorks)
{
    AlbaComplexNumber<double> complex(-0.5, sqrt(3)/2);

    AlbaComplexNumber<double> actualComplex(complex^3);

    AlbaComplexNumber<double> expectedComplex(1, 0);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorAdditionAssignmentWorks)
{
    AlbaComplexNumber<double> actualComplex(3, 4);    AlbaComplexNumber<double> anotherComplex(5, 6);

    actualComplex+=anotherComplex;

    AlbaComplexNumber<double> expectedComplex(8, 10);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorSubtractionAssignmentWorks)
{
    AlbaComplexNumber<double> actualComplex(7, 9);
    AlbaComplexNumber<double> anotherComplex(5, 6);

    actualComplex-=anotherComplex;

    AlbaComplexNumber<double> expectedComplex(2, 3);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorMultiplicationAssignmentWorks)
{
    AlbaComplexNumber<double> actualComplex(3, 4);
    AlbaComplexNumber<double> anotherComplex(5, 6);

    actualComplex*=anotherComplex;

    AlbaComplexNumber<double> expectedComplex(-9, 38);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorDivisionAssignmentWorks)
{
    AlbaComplexNumber<double> actualComplex(5, 6);
    AlbaComplexNumber<double> anotherComplex(3, 4);

    actualComplex/=anotherComplex;

    AlbaComplexNumber<double> expectedComplex(1.56, -0.08);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, GetRealPartWorks)
{
    AlbaComplexNumber<double> complex(3.5, 4.5);

    EXPECT_DOUBLE_EQ(3.5, complex.getRealPart());
}

TEST(AlbaComplexNumberTest, GetImaginaryPartWorks)
{
    AlbaComplexNumber<double> complex(3.5, 4.5);

    EXPECT_DOUBLE_EQ(4.5, complex.getImaginaryPart());
}

TEST(AlbaComplexNumberTest, GetModulusWorks)
{
    AlbaComplexNumber<double> complex(3, 4);

    EXPECT_DOUBLE_EQ(5, complex.getModulus());
}

TEST(AlbaComplexNumberTest, GetModulusSquaredWorks)
{
    AlbaComplexNumber<double> complex(3, 4);

    EXPECT_DOUBLE_EQ(25, complex.getModulusSquared());
}

TEST(AlbaComplexNumberTest, GetAngleInRadiansWorks)
{
    AlbaComplexNumber<double> complex(3, 4);

    EXPECT_DOUBLE_EQ(0.92729521800161219, complex.getAngleInRadians());
}

TEST(AlbaComplexNumberTest, GetConjugateWorks)
{
    AlbaComplexNumber<double> complex1(3, 4);
    AlbaComplexNumber<double> actualComplex(complex1.getConjugate());

    AlbaComplexNumber<double> expectedComplex(3, -4);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, GetNthRootWorks)
{
    AlbaComplexNumber<double> complex(1, 0);

    AlbaComplexNumber<double> actualComplex1(complex.getNthRoot(0u, 4u));
    AlbaComplexNumber<double> actualComplex2(complex.getNthRoot(1u, 4u));
    AlbaComplexNumber<double> actualComplex3(complex.getNthRoot(2u, 4u));
    AlbaComplexNumber<double> actualComplex4(complex.getNthRoot(3u, 4u));

    AlbaComplexNumber<double> expectedComplex1(1, 0);
    AlbaComplexNumber<double> expectedComplex2(0, 1);
    AlbaComplexNumber<double> expectedComplex3(-1, 0);
    AlbaComplexNumber<double> expectedComplex4(0, -1);
    EXPECT_EQ(expectedComplex1, actualComplex1);
    EXPECT_EQ(expectedComplex2, actualComplex2);
    EXPECT_EQ(expectedComplex3, actualComplex3);
    EXPECT_EQ(expectedComplex4, actualComplex4);
}

TEST(AlbaComplexNumberTest, GetDisplayableStringWorks)
{
    AlbaComplexNumber<double> complex(3.5, 4.5);
    EXPECT_EQ("(3.5 + 4.5i)", complex.getDisplayableString());
}

}
