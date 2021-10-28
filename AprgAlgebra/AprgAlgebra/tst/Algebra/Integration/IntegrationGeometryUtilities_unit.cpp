#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>#include <Math/AlbaMathHelper.hpp>

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

    Term termToVerify(getVolumeUsingOnCrossSectionalArea(crossSectionalArea, "z", Term(Constant(0)), height));

    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"height", 1}, {"side", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownCone)
{
    Term height("height");
    Term edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheConeInY, "y", Term(Constant(0)), height));
    Term termToExpect(Monomial(AlbaNumber(1.047197551196598), {{"height", 1}, {"radius", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownConeWithUpsideDownConeHole)
{
    Term height("height");
    Term edgeOfTheCone1InY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));
    Term edgeOfTheCone2InY(Polynomial
    {Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}), Monomial(1, {{"edgeDistance", 1}})});

    Term termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheCone1InY, edgeOfTheCone2InY, "y", Term(Constant(0)), height));
    Term termToExpect(Monomial(getPi(), {{"edgeDistance", 2}, {"height", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetVolumeUsingCylindricalShellsWorksOnParabolaCupHole)
{
    Term radius("radius");
    Term edgeOfTheParabolaInX(Monomial(1, {{"x", 2}}));

    Term termToVerify(getVolumeUsingCylindricalShells(edgeOfTheParabolaInX, "x", Term(Constant(0)), radius));
    Term termToExpect(Monomial(1.570796326794897, {{"radius", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfTheEdgeWorks)
{
    Term termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}));

    Term termToVerify(getLengthOfTheEdge(termToTest, "x", Term(1), Term(8)));
    Term termToExpect(7.63370541601624);
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfARod(termToTest, "x", Term(Constant(0)), l));
    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"l", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getMomentOfMassOfARod(termToTest, "x", Term(Constant(0)), l));
    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 4), {{"l", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getCenterOfMassOfARod(termToTest, "x", Term(Constant(0)), l));
    Term termToExpect(Monomial(AlbaNumber::createFraction(3, 4), {{"l", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    Term termToVerify(getTotalMassOfALamina(termToTest, "x", Term(Constant(0)), x));
    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getMomentOfMassOfALamina(termToTest, "x", Term(Constant(0)), x));
    Term termToExpectInX(Monomial(AlbaNumber::createFraction(1, 10), {{"x", 5}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, "x", Term(Constant(0)), x));
    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x",1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCentroidWorks)
{
    Term x("x");
    Term termToTest(Monomial(1, {{"x", 2}}));

    TermPair termPairToVerify(getCentroid(termToTest, "x", Term(Constant(0)), x));
    Term termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetWorkWorks)
{
    Term x("x");
    Term force(Monomial(1, {{"x", 2}}));

    Term termToVerify(getWork(force, "x", Term(Constant(0)), x));
    Term termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}
TEST(IntegrationGeometryUtilitiesTest, GetLiquidPressureWorks)
{
    Term raw("raw");
    Term g("g");
    Term length(Monomial(1, {{"depth", 2}}));

    Term termToVerify(getLiquidPressure(raw, g, length, "depth", Term(Constant(0)), Term(2)));
    Term termToExpect(Monomial(4, {{"g", 1}, {"raw", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, IntegrateInPolarCoordinatesWorks)
{
    string thetaName("theta");
    Term theta(thetaName);
    Term limacon(createExpressionIfPossible({Term(2), Term("+"), Term(2), Term("*"), Term(cos(theta))}));

    Term termToVerify(integrateInPolarCoordinates(limacon, thetaName, Term(Constant(0)), Term(AlbaNumber(AlbaNumber::Value::pi))));

    Term termToExpect(18.84955592153876);
    EXPECT_EQ(termToExpect, termToVerify);
}

}

}