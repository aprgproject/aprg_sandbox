#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(IntegrationGeometryUtilitiesTest, GetAreaInBetweenTwoTermsInAnIntervalWorks) {
    Term lowerTerm(Monomial(1, {{"x", 2}}));
    Term higherTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(
        Term(AlbaNumber::createFraction(8, 3)),
        getAreaInBetweenTwoTermsInAnInterval(lowerTerm, higherTerm, {"x", 0, 2}));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnCrossSectionalAreaWorksOnPyramidWithSquareBase) {
    Term ratio = Term("side") / Term("height");
    Term crossSectionalArea(createExpressionIfPossible({"(", ratio, "*", "z", ")", "^", 2}));

    Term termToVerify(getVolumeUsingOnCrossSectionalArea(crossSectionalArea, {"z", 0, "height"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"height", 1}, {"side", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownCone) {
    Term edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheConeInY, {"y", 0, "height"}));

    Term termToExpect(Monomial(AlbaNumber(1.047197551196598), {{"height", 1}, {"radius", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetSurfaceAreaBasedOnSolidOfRevolutionWorksOnUpsideDownCone) {
    Term edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term termToVerify(getSurfaceAreaUsingOnSolidOfRevolution(edgeOfTheConeInY, {"y", 0, "height"}));

    string stringToExpect("((pi)[radius]*((1[height^2] + 1[radius^2])^(1/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeAndSurfaceAreaBasedOnSolidOfRevolutionWorksOnGabrielsHorn) {
    // The painters paradox (volume is definite, but surface are is infinite).
    // Computation of the volume:
    // The horn follows the form y=1/x and starts at x=1 and ends at infinity
    Term edgeOfHornInX(Monomial(1, {{"x", -1}}));

    Term actualVolume(getVolumeUsingOnSolidOfRevolution(edgeOfHornInX, {"x", 1, getPositiveInfinityAsATerm()}));
    // Term actualSurfaceArea(getSurfaceAreaUsingOnSolidOfRevolution(edgeOfHornInX, {"x", 1,
    // getPositiveInfinityAsATerm()}));
    // The surface area is hard to integrate: (((1[x^4] + 1)^(1/2))/1[x^3])
    // This can be solved via integration by parts u = (1+x4)^(1/2), v' = 1/(x^3), check symbolab.com

    Term expectedVolume(getPiAsATerm());
    // Term expectedSurfaceArea(getPositiveInfinityAsATerm());
    EXPECT_EQ(expectedVolume, actualVolume);
    // EXPECT_EQ(expectedSurfaceArea, actualSurfaceArea);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownConeWithUpsideDownConeHole) {
    Term edgeOfTheCone1InY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));
    Term edgeOfTheCone2InY(
        Polynomial{Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}), Monomial(1, {{"edgeDistance", 1}})});

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheCone1InY, edgeOfTheCone2InY, {"y", 0, "height"}));

    Term termToExpect(Monomial(getPi(), {{"edgeDistance", 2}, {"height", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeUsingCylindricalShellsWorksOnParabolaCupHole) {
    Term edgeOfTheParabolaInX(Monomial(1, {{"x", 2}}));

    Term termToVerify(getVolumeUsingCylindricalShells(edgeOfTheParabolaInX, {"x", 0, "radius"}));

    Term termToExpect(Monomial(1.570796326794897, {{"radius", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcWorks) {
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}));

    Term termToVerify(getLengthOfArc(termToTest, {"x", 1, 8}));

    Term termToExpect(7.63370541601624);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcInPolarCoordinatesWorks) {
    Term radiusOfLimacon(Monomial(2, {{"theta", 1}}));

    Term termToVerify(getLengthOfArcInPolarCoordinates(radiusOfLimacon, {"theta", 0, getPiAsATerm()}));

    Term termToExpect(12.21983866791859);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfARodWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfARod(termToTest, {"x", 0, "l"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"l", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfARodWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getMomentOfMassOfARod(termToTest, {"x", 0, "l"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 4), {{"l", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfARodWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getCenterOfMassOfARod(termToTest, {"x", 0, "l"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(3, 4), {{"l", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfALamina(termToTest, {"x", 0, "x"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getMomentOfMassOfALamina(termToTest, {"x", 0, "x"}));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(1, 10), {{"x", 5}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, {"x", 0, "x"}));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCentroidWorks) {
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCentroid(termToTest, {"x", 0, "x"}));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetWorkWorks) {
    Term force(Monomial(1, {{"x", 2}}));

    Term termToVerify(getWork(force, {"x", 0, "x"}));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLiquidPressureWorks) {
    Term length(Monomial(1, {{"depth", 2}}));

    Term termToVerify(getLiquidPressure("raw", "g", length, {"depth", 0, 2}));

    Term termToExpect(Monomial(4, {{"g", 1}, {"raw", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, IntegrateInPolarCoordinatesWorks) {
    Term radiusOfLimacon(createExpressionIfPossible({2, "+", 2, "*", cos("theta")}));

    Term termToVerify(integrateInPolarCoordinates(radiusOfLimacon, {"theta", 0, getPiAsATerm()}));

    Term termToExpect(18.84955592153876);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample1) {
    // Evaluate the double integral Integral[3y-2*x^2]dA
    // if R is the region consisting of all points (x, y) for which -1<x<2 and 1<y<3

    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample2) {
    // Find the volume z = 4 - 1/9*x^2 - 1/16*y^2
    // bounded by the surface x=3, y=2 and the three coordinate planes

    Term termToTest(Polynomial{
        Monomial(4, {}), Monomial(AlbaNumber::createFraction(-1, 9), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 16), {{"y", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", 0, 3};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 0, 2};

    Term termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(43, 2));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToXAxisWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getMomentOfMassOfALaminaWithRespectToXAxis(termToTest, xDetails, yDetails));

    Term termToExpect(54);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToYAxisWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getMomentOfMassOfALaminaWithRespectToYAxis(termToTest, xDetails, yDetails));

    Term termToExpect(3);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, xDetails, yDetails));

    Term termToExpect1(AlbaNumber::createFraction(1, 8));
    Term termToExpect2(AlbaNumber::createFraction(9, 4));
    EXPECT_EQ(termToExpect1, termPairToVerify.first);
    EXPECT_EQ(termToExpect2, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheXAxisWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getMomentOfInertiaAboutTheXAxis(termToTest, xDetails, yDetails));

    Term termToExpect(128);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheYAxisWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(48, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheOriginWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};

    Term termToVerify(getMomentOfInertiaAboutTheOrigin(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(688, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetRadiusOfGyrationWorksWithXDetailsAndYDetails) {
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 1, 3};
    Term momentOfInertiaAboutTheYAxis(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));
    Term totalMassOfALamina(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term termToVerify(getRadiusOfGyration(momentOfInertiaAboutTheYAxis, totalMassOfALamina));

    Term termToExpect(0.6324555320336759);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample1) {
    // Find the volume of the soild in the first octant bounded by the code z = r and the cylinder r = 3 sin(theta)
    Term termToTest("r");
    DetailsForDefiniteIntegralWithTerms radiusDetails{"r", 0, 3 * sin("theta")};
    DetailsForDefiniteIntegralWithTerms thetaDetails{"theta", 0, getPiAsATerm() / 2};

    Term termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term termToExpect(6);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample2) {
    // Find the area of the region enclosed by one leaf of the rose r =  sin(3 * theta)
    Term termToTest(1);
    DetailsForDefiniteIntegralWithTerms radiusDetails{"r", 0, sin(Monomial(3, {{"theta", 1}}))};
    DetailsForDefiniteIntegralWithTerms thetaDetails{"theta", 0, getPiAsATerm() / 3};

    Term termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term termToExpect(0.2617993877991494);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, DISABLED_GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample1) {
    // Disabled because integration does not work here (possible trig sub problem)

    // Find the area of the surface that is cut from the cylinder x^2 + z^2 = 16 by the planes x=0, x=2, y=0, y=3
    Term insideSquareRoot(Polynomial{Monomial(16, {}), Monomial(-1, {{"x", 2}})});
    Term z(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    DetailsForDefiniteIntegralWithTerms xDetails{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 0, 3};

    Term termToVerify(getSurfaceAreaWithZInCartesianCoordinates(z, xDetails, yDetails));

    Term termToExpect(1);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample2) {
    DetailsForDefiniteIntegralWithTerms xDetails{"x", 0, 3};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 0, 4};

    Term termToVerify(getSurfaceAreaWithZInCartesianCoordinates("z", xDetails, yDetails));

    Term termToExpect(12);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCartesianCoordinatesWorks) {
    // Find by triple integration the volume of the solid bounded by elliptic paraboloid z = x^2 + 4*y^2 and cylinder
    // x^2 + 4*y^2 = 4

    Term termToTest(4);  // because this is done for each quadrant
    DetailsForDefiniteIntegralWithTerms xDetails{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms yDetails{
        "y", 0,
        createExpressionIfPossible(
            {Polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})}, "^", AlbaNumber::createFraction(1, 2), "/", 2})};
    DetailsForDefiniteIntegralWithTerms zDetails{"z", 0, Polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"y", 2}})}};

    Term termToVerify(getTripleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails, zDetails));

    Term termToExpect(12.56637061435917);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCylindricalCoordinatesWorks) {
    // Get volume of cylinder with radius=2 and height=3

    Term termToTest(1);
    DetailsForDefiniteIntegralWithTerms radiusDetails{"r", 0, 2};
    DetailsForDefiniteIntegralWithTerms thetaDetails{"theta", 0, getPiAsATerm() * 2};
    DetailsForDefiniteIntegralWithTerms zDetails{"z", 0, 3};

    Term termToVerify(getTripleIntegralInCylindricalCoordinates(termToTest, radiusDetails, thetaDetails, zDetails));

    Term termToExpect(37.69911184307752);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInSphericalCoordinatesWorks) {
    // Get volume of sphere with raw=2

    Term termToTest(8);  // integrate a sphere on each quadrant
    DetailsForDefiniteIntegralWithTerms rawDetails{"raw", 0, 2};
    DetailsForDefiniteIntegralWithTerms thetaDetails{"theta", 0, getPiAsATerm() / 2};
    DetailsForDefiniteIntegralWithTerms phiDetails{"phi", 0, getPiAsATerm() / 2};

    Term termToVerify(getTripleIntegralInSphericalCoordinates(termToTest, rawDetails, thetaDetails, phiDetails));

    Term termToExpect(33.51032163829112);
    EXPECT_EQ(termToExpect, termToVerify);
}

}  // namespace algebra

}  // namespace alba
