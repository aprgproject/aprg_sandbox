#include <Algebra/Geometry/TwoDimensions/TwoDimensionsUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace TwoDimensions
{

TEST(TwoDimensionsUtilitiesTest, GetCircleEquationWorks)
{
    Equation equationToVerify(getCircleEquation());

    string stringToExpect("(((x-x0)^2)+((y-y0)^2)) = (r^2)");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(TwoDimensionsUtilitiesTest, GetEllipseEquationWorks)
{
    Equation equationToVerify(getEllipseEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))) = 1");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(TwoDimensionsUtilitiesTest, GetHyperbolaEquationWorks)
{
    Equation equationToVerify(getHyperbolaEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))-(((y-y0)^2)/(b^2))) = 1");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(TwoDimensionsUtilitiesTest, GetLimaconEquationWorks)
{
    Equation equationToVerify1(getLimaconEquation(LimaconTrigonometricFunctionType::Cosine));
    Equation equationToVerify2(getLimaconEquation(LimaconTrigonometricFunctionType::Sine));

    string stringToExpect1("(a+(b*cos(theta))) = r");
    string stringToExpect2("(a+(b*sin(theta))) = r");
    EXPECT_EQ(stringToExpect1, equationToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationToVerify2.getDisplayableString());
}

TEST(TwoDimensionsUtilitiesTest, GetLineEquationWorks)
{
    Equation equationToVerify(getLineEquation());

    string stringToExpect("((a*x)+(b*y)+c) = 0");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(TwoDimensionsUtilitiesTest, GetParabolaEquationWorks)
{
    Equation equationToVerify1(getParabolaEquation(ParabolaOrientation::PolynomialX));
    Equation equationToVerify2(getParabolaEquation(ParabolaOrientation::PolynomialY));

    string stringToExpect1("((a*(x^2))+(b*x)+c) = y");
    string stringToExpect2("((a*(y^2))+(b*y)+c) = x");
    EXPECT_EQ(stringToExpect1, equationToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationToVerify2.getDisplayableString());
}

}

}

}
