#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace ThreeDimensions
{

TEST(ThreeDimensionsUtilitiesTest, GetEllipsoidEquationWorks)
{
    Equation equationToVerify(getEllipsoidEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))+(((z-z0)^2)/(c^2))) = 1");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticConeEquationWorks)
{
    Equation equationToVerify(getEllipticConeEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))+(((z-z0)^2)/(c^2))) = 0");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticHyperboloidEquationEquationWorks)
{
    Equation equationToVerify1(getEllipticHyperboloidEquation(false));
    Equation equationToVerify2(getEllipticHyperboloidEquation(true));

    string stringToExpect1("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = 1");
    string stringToExpect2("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = -1");
    EXPECT_EQ(stringToExpect1, equationToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationToVerify2.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticParaboloidEquationEquationWorks)
{
    Equation equationToVerify(getEllipticParaboloidEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetHyperbolicParaboloidEquationEquationWorks)
{
    Equation equationToVerify(getHyperbolicParaboloidEquation());

    string stringToExpect("((((y-y0)^2)/(b^2))-(((x-x0)^2)/(a^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetLineEquationsWorks)
{
    Equations equationsToVerify(getLineEquations());

    string stringToExpect1("((x-x0)/a) = ((y-y0)/b)");
    string stringToExpect2("((x-x0)/a) = ((z-z0)/c)");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, equationsToVerify.at(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationsToVerify.at(1).getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneEquationWorks)
{
    Equation equationToVerify(getPlaneEquation());

    string stringToExpect("((a*x)+(b*y)+(c*z)+d) = 0");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(ThreeDimensionsUtilitiesTest, GetSphereEquationWorks)
{
    Equation equationToVerify(getSphereEquation());

    string stringToExpect("(((x-x0)^2)+((y-y0)^2)+((z-z0)^2)) = (r^2)");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

}

}

}
