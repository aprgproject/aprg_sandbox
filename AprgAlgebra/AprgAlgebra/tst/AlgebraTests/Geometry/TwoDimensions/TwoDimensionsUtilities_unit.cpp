#include <Algebra/Geometry/TwoDimensions/TwoDimensionsUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace TwoDimensions {

TEST(TwoDimensionsUtilitiesTest, GetCircleEquationWorks) {
    Equation equationToVerify(getCircleEquation());

    string stringToExpect("(((x-x0)^2)+((y-y0)^2)) = (r^2)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(TwoDimensionsUtilitiesTest, GetEllipseEquationWorks) {
    Equation equationToVerify(getEllipseEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))) = 1");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(TwoDimensionsUtilitiesTest, GetHyperbolaEquationWorks) {
    Equation equationToVerify(getHyperbolaEquation());

    string stringToExpect("((((x-x0)^2)/(a^2))-(((y-y0)^2)/(b^2))) = 1");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(TwoDimensionsUtilitiesTest, GetLimaconEquationWorks) {
    Equation equationToVerify1(getLimaconEquation(LimaconTrigonometricFunctionType::Cosine));
    Equation equationToVerify2(getLimaconEquation(LimaconTrigonometricFunctionType::Sine));

    string stringToExpect1("(a+(b*cos(theta))) = r");
    string stringToExpect2("(a+(b*sin(theta))) = r");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(TwoDimensionsUtilitiesTest, GetLineEquationWorks) {
    Equation equationToVerify(getLineEquation());

    string stringToExpect("((a*x)+(b*y)+c) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(TwoDimensionsUtilitiesTest, GetParabolaEquationWorks) {
    Equation equationToVerify1(getParabolaEquation(ParabolaOrientation::PolynomialX));
    Equation equationToVerify2(getParabolaEquation(ParabolaOrientation::PolynomialY));

    string stringToExpect1("((a*(x^2))+(b*x)+c) = y");
    string stringToExpect2("((a*(y^2))+(b*y)+c) = x");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(TwoDimensionsUtilitiesTest, GetSurfaceAreaOfAConicalFrustumWorks) {
    Term termToVerify(getSurfaceAreaOfAConicalFrustum());

    string stringToExpect(
        "(((pi)*(rt^2))+((pi)*(rb^2))+((pi)*rb*((((rb-rt)^2)+(h^2))^(1/2)))+((pi)*rt*((((rb-rt)^2)+(h^2))^(1/2))))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(TwoDimensionsUtilitiesTest, GetVolumeOfAConicalFrustumWorks) {
    Term termToVerify(getVolumeOfAConicalFrustum());

    string stringToExpect("(((1/3)*(pi)*h*(rt^2))+((1/3)*(pi)*h*rt*rb)+((1/3)*(pi)*h*(rb^2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

}  // namespace TwoDimensions

}  // namespace algebra

}  // namespace alba
