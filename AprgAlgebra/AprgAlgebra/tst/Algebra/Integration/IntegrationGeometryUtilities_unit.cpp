#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationGeometryUtilitiesTest, GetAreaInBetweenTwoTermsInAnIntervalWorks)
{
    Term lowerTerm(Monomial(1, {{"x", 2}}));
    Term higherTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(AlbaNumber::createFraction(8, 3)), getAreaInBetweenTwoTermsInAnInterval(lowerTerm, higherTerm, "x", 0, 2));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnCrossSectionalAreaWorksOnPyramidWithSquareBase)
{
    Term side("side");
    Term height("height");
    Term z("z");
    Term ratio = side/height;
    Term crossSectionalArea(createExpressionIfPossible({Term("("), ratio, Term("*"), z, Term(")"), Term("^"), Term(2)}));

    Term termToVerify(getVolumeUsingOnCrossSectionalArea(crossSectionalArea, "z", Term(0), height));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"height", 1}, {"side", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownCone)
{
    Term height("height");
    Term edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheConeInY, "y", Term(0), height));

    Term termToExpect(Monomial(AlbaNumber(1.047197551196598), {{"height", 1}, {"radius", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownConeWithUpsideDownConeHole)
{
    Term height("height");
    Term edgeOfTheCone1InY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));
    Term edgeOfTheCone2InY(Polynomial
    {Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}), Monomial(1, {{"edgeDistance", 1}})});

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheCone1InY, edgeOfTheCone2InY, "y", Term(0), height));

    Term termToExpect(Monomial(getPi(), {{"edgeDistance", 2}, {"height", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeUsingCylindricalShellsWorksOnParabolaCupHole)
{
    Term radius("radius");
    Term edgeOfTheParabolaInX(Monomial(1, {{"x", 2}}));

    Term termToVerify(getVolumeUsingCylindricalShells(edgeOfTheParabolaInX, "x", Term(0), radius));

    Term termToExpect(Monomial(1.570796326794897, {{"radius", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}));

    Term termToVerify(getLengthOfArc(termToTest, "x", Term(1), Term(8)));

    Term termToExpect(7.63370541601624);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcInPolarCoordinatesWorks)
{
    string thetaName("theta");
    Term radiusOfLimacon(Monomial(2, {{"theta", 1}}));

    Term termToVerify(getLengthOfArcInPolarCoordinates(radiusOfLimacon, thetaName, Term(0), Term(AlbaNumber(AlbaNumber::Value::pi))));

    Term termToExpect(12.21983866791859);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfARod(termToTest, "x", Term(0), l));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"l", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getMomentOfMassOfARod(termToTest, "x", Term(0), l));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 4), {{"l", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getCenterOfMassOfARod(termToTest, "x", Term(0), l));

    Term termToExpect(Monomial(AlbaNumber::createFraction(3, 4), {{"l", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfALamina(termToTest, "x", Term(0), x));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getMomentOfMassOfALamina(termToTest, "x", Term(0), x));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(1, 10), {{"x", 5}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, "x", Term(0), x));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x",1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCentroidWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCentroid(termToTest, "x", Term(0), x));

    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetWorkWorks)
{
    Term x("x");
    Term force(Monomial(1, {{"x", 2}}));

    Term termToVerify(getWork(force, "x", Term(0), x));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLiquidPressureWorks)
{
    Term raw("raw");
    Term g("g");
    Term length(Monomial(1, {{"depth", 2}}));

    Term termToVerify(getLiquidPressure(raw, g, length, "depth", Term(0), Term(2)));

    Term termToExpect(Monomial(4, {{"g", 1}, {"raw", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, IntegrateInPolarCoordinatesWorks)
{
    string thetaName("theta");
    Term theta(thetaName);
    Term radiusOfLimacon(createExpressionIfPossible({Term(2), Term("+"), Term(2), Term("*"), Term(cos(theta))}));

    Term termToVerify(integrateInPolarCoordinates(radiusOfLimacon, thetaName, Term(0), Term(AlbaNumber(AlbaNumber::Value::pi))));

    Term termToExpect(18.84955592153876);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample1)
{
    // Evaluate the double integral Integral[3y-2*x^2]dA
    // if R is the region consisting of all points (x, y) for which -1<x<2 and 1<y<3

    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample2)
{
    // Find the volume z = 4 - 1/9*x^2 - 1/16*y^2
    // bounded by the surface x=3, y=2 and the three coordinate planes

    Term termToTest(Polynomial{Monomial(4, {}), Monomial(AlbaNumber::createFraction(-1, 9), {{"x", 2}}), Monomial(AlbaNumber::createFraction(-1, 16), {{"y", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(0), Term(3)};
    CoordinateDetailsForIntegral yDetails{"y", Term(0), Term(2)};

    Term termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(43, 2));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToXAxisWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getMomentOfMassOfALaminaWithRespectToXAxis(termToTest, xDetails, yDetails));

    Term termToExpect(54);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToYAxisWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getMomentOfMassOfALaminaWithRespectToYAxis(termToTest, xDetails, yDetails));

    Term termToExpect(3);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, xDetails, yDetails));

    Term termToExpect1(AlbaNumber::createFraction(1, 8));
    Term termToExpect2(AlbaNumber::createFraction(9, 4));
    EXPECT_EQ(termToExpect1, termPairToVerify.first);
    EXPECT_EQ(termToExpect2, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheXAxisWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getMomentOfInertiaAboutTheXAxis(termToTest, xDetails, yDetails));

    Term termToExpect(128);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheYAxisWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(48, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheOriginWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};

    Term termToVerify(getMomentOfInertiaAboutTheOrigin(termToTest, xDetails, yDetails));

    Term termToExpect(AlbaNumber::createFraction(688, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetRadiusOfGyrationWorksWithXDetailsAndYDetails)
{
    Term termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    CoordinateDetailsForIntegral xDetails{"x", Term(-1), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(1), Term(3)};
    Term momentOfInertiaAboutTheYAxis(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));
    Term totalMassOfALamina(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term termToVerify(getRadiusOfGyration(momentOfInertiaAboutTheYAxis, totalMassOfALamina));

    Term termToExpect(0.6324555320336759);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample1)
{
    //Find the volume of the soild in the first octant bounded by the code z = r and the cylinder r = 3 sin(theta)
    Term termToTest("r");
    CoordinateDetailsForIntegral radiusDetails{"r", Term(0), Term(3)*Term(sin(Term("theta")))};
    CoordinateDetailsForIntegral thetaDetails{"theta", Term(0), getPiAsTerm()/2};

    Term termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term termToExpect(6);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample2)
{
    //Find the area of the region enclosed by one leaf of the rose r =  sin(3 * theta)
    Term termToTest(1);
    CoordinateDetailsForIntegral radiusDetails{"r", Term(0), Term(sin(Term(Monomial(3, {{"theta", 1}}))))};
    CoordinateDetailsForIntegral thetaDetails{"theta", Term(0), getPiAsTerm()/3};

    Term termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term termToExpect(0.2617993877991494);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, DISABLED_GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample1)
{
    // Disabled because integration does not work here (possible trig sub problem)

    // Find the area of the surface that is cut from the cylinder x^2 + z^2 = 16 by the planes x=0, x=2, y=0, y=3
    Term insideSquareRoot(Polynomial{Monomial(16, {}), Monomial(-1, {{"x", 2}})});
    Term z(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    CoordinateDetailsForIntegral xDetails{"x", Term(0), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(0), Term(3)};

    Term termToVerify(getSurfaceAreaWithZInCartesianCoordinates(z, xDetails, yDetails));

    Term termToExpect(1);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample2)
{
    Term z(5);
    CoordinateDetailsForIntegral xDetails{"x", Term(0), Term(3)};
    CoordinateDetailsForIntegral yDetails{"y", Term(0), Term(4)};

    Term termToVerify(getSurfaceAreaWithZInCartesianCoordinates(z, xDetails, yDetails));

    Term termToExpect(12);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCartesianCoordinatesWorks)
{
    // Find by triple integration the volume of the solid bounded by elliptic paraboloid z = x^2 + 4*y^2 and cylinder x^2 + 4*y^2 = 4

    Term termToTest(4); // because this is done for each quadrant
    CoordinateDetailsForIntegral xDetails{"x", Term(0), Term(2)};
    CoordinateDetailsForIntegral yDetails{"y", Term(0), Term(createExpressionIfPossible(
        {Term(Polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2)), Term("/"), Term(2)}))};
    CoordinateDetailsForIntegral zDetails{"z", Term(0), Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"y", 2}})})};

    Term termToVerify(getTripleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails, zDetails));

    Term termToExpect(12.56637061435917);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCylindricalCoordinatesWorks)
{
    // Get volume of cylinder with radius=2 and height=3

    Term termToTest(1);
    CoordinateDetailsForIntegral radiusDetails{"r", Term(0), Term(2)};
    CoordinateDetailsForIntegral thetaDetails{"theta", Term(0), getPiAsTerm()*Term(2)};
    CoordinateDetailsForIntegral zDetails{"z", Term(0), Term(3)};

    Term termToVerify(getTripleIntegralInCylindricalCoordinates(termToTest, radiusDetails, thetaDetails, zDetails));

    Term termToExpect(37.69911184307752);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInSphericalCoordinatesWorks)
{
    // Get volume of sphere with raw=2

    Term termToTest(8); // integrate a sphere on each quadrant
    CoordinateDetailsForIntegral rawDetails{"raw", Term(0), Term(2)};
    CoordinateDetailsForIntegral thetaDetails{"theta", Term(0), getPiAsTerm()/Term(2)};
    CoordinateDetailsForIntegral phiDetails{"phi", Term(0), getPiAsTerm()/Term(2)};

    Term termToVerify(getTripleIntegralInSphericalCoordinates(termToTest, rawDetails, thetaDetails, phiDetails));

    Term termToExpect(33.51032163829112);
    EXPECT_EQ(termToExpect, termToVerify);
}

}

}
