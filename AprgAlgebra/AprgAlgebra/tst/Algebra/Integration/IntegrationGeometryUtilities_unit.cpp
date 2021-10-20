#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

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

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 3), {{"height", 1}, {"side", 2}}));
    EXPECT_EQ(expectedTerm, getVolumeUsingOnCrossSectionalArea(crossSectionalArea, "z", Term(Constant(0)), height));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownCone)
{
    Term height("height");
    Term edgeOfTheConeInY = Term(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 3), {{"PI", 1}, {"height", 1}, {"radius", 2}}));
    EXPECT_EQ(expectedTerm, getVolumeUsingOnSolidOfRevolution(edgeOfTheConeInY, "y", Term(Constant(0)), height));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownConeWithUpsideDownConeHole)
{
    Term height("height");
    Term edgeOfTheCone1InY = Term(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));
    Term edgeOfTheCone2InY = Term(Polynomial
    {Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}), Monomial(1, {{"edgeDistance", 1}})});

    Term expectedTerm(Monomial(1, {{"PI", 1}, {"edgeDistance", 2}, {"height", 1}}));
    EXPECT_EQ(expectedTerm, getVolumeUsingOnSolidOfRevolution(edgeOfTheCone1InY, edgeOfTheCone2InY, "y", Term(Constant(0)), height));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeUsingCylindricalShellsWorksOnParabolaCupHole)
{
    Term radius("radius");
    Term edgeOfTheParabolaInX = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 2), {{"PI", 1}, {"radius", 4}}));
    EXPECT_EQ(expectedTerm, getVolumeUsingCylindricalShells(edgeOfTheParabolaInX, "x", Term(Constant(0)), radius));
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfTheEdgeWorks)
{
    Term termToTest = Term(Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}));

    Term expectedTerm(7.63370541601624);
    EXPECT_EQ(expectedTerm, getLengthOfTheEdge(termToTest, "x", Term(1), Term(8)));
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfARodWorks)
{
    Term l("l");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 3), {{"l", 3}}));
    EXPECT_EQ(expectedTerm, getTotalMassOfARod(termToTest, "x", Term(Constant(0)), l));
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 4), {{"l", 4}}));
    EXPECT_EQ(expectedTerm, getMomentOfMassOfARod(termToTest, "x", Term(Constant(0)), l));
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfARodWorks)
{
    Term l("l");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(3, 4), {{"l", 1}}));
    EXPECT_EQ(expectedTerm, getCenterOfMassOfARod(termToTest, "x", Term(Constant(0)), l));
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(expectedTerm, getTotalMassOfALamina(termToTest, "x", Term(Constant(0)), x));
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTermInX(Monomial(AlbaNumber::createFraction(1, 10), {{"x", 5}}));
    Term expectedTermInY(Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}));
    TermPair termPairToVerify(getMomentOfMassOfALamina(termToTest, "x", Term(Constant(0)), x));
    EXPECT_EQ(expectedTermInX, termPairToVerify.first);
    EXPECT_EQ(expectedTermInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorks)
{
    Term x("x");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTermInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term expectedTermInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x",1}}));
    TermPair termPairToVerify(getCenterOfMassOfALamina(termToTest, "x", Term(Constant(0)), x));
    EXPECT_EQ(expectedTermInX, termPairToVerify.first);
    EXPECT_EQ(expectedTermInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCentroidWorks)
{
    Term x("x");
    Term termToTest = Term(Monomial(1, {{"x", 2}}));

    Term expectedTermInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term expectedTermInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    TermPair termPairToVerify(getCentroid(termToTest, "x", Term(Constant(0)), x));
    EXPECT_EQ(expectedTermInX, termPairToVerify.first);
    EXPECT_EQ(expectedTermInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetWorkWorks)
{
    Term x("x");
    Term force = Term(Monomial(1, {{"x", 2}}));

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(expectedTerm, getWork(force, "x", Term(Constant(0)), x));
}

TEST(IntegrationGeometryUtilitiesTest, GetLiquidPressureWorks)
{
    Term raw("raw");
    Term g("g");
    Term length = Term(Monomial(1, {{"depth", 2}}));

    Term expectedTerm(Monomial(4, {{"g", 1}, {"raw", 1}}));
    EXPECT_EQ(expectedTerm, getLiquidPressure(raw, g, length, "depth", Term(Constant(0)), Term(2)));
}

}

}
