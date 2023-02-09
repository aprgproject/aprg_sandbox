#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
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
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticConeEquationWorks)
{
    Equation equationToVerify(getEllipticConeEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))+(((z-z0)^2)/(c^2))) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticHyperboloidEquationEquationWorks)
{
    Equation equationToVerify1(getEllipticHyperboloidEquation(false));
    Equation equationToVerify2(getEllipticHyperboloidEquation(true));

    string stringToExpect1("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = 1");
    string stringToExpect2("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = -1");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticParaboloidEquationEquationWorks)
{
    Equation equationToVerify(getEllipticParaboloidEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetHyperbolicParaboloidEquationEquationWorks)
{
    Equation equationToVerify(getHyperbolicParaboloidEquation());

    string stringToExpect("((((y-y0)^2)/(b^2))-(((x-x0)^2)/(a^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetLineEquationsWorks)
{
    Equations equationsToVerify(getLineEquations());

    string stringToExpect1("((x-x0)/a) = ((y-y0)/b)");
    string stringToExpect2("((x-x0)/a) = ((z-z0)/c)");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(equationsToVerify.at(0)));
    EXPECT_EQ(stringToExpect2, convertToString(equationsToVerify.at(1)));
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneEquationWorks)
{
    Equation equationToVerify(getPlaneEquation());

    string stringToExpect("((a*x)+(b*y)+(c*z)+d) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneEquationWithPointCoordinatesWorks)
{
    Equation equationToVerify(getPlaneEquationWithPointCoordinates());

    string stringToExpect("((a*x)-(a*x0)+(b*y)-(b*y0)+(c*z)-(c*z0)) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetSphereEquationWorks)
{
    Equation equationToVerify(getSphereEquation());

    string stringToExpect("(((x-x0)^2)+((y-y0)^2)+((z-z0)^2)) = (r^2)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

}

}

}
