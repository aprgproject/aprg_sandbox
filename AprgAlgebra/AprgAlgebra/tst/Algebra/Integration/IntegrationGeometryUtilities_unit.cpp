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

    Term expectedTerm(Monomial(AlbaNumber::createFraction(1, 2), {{"PI", 1}, {"radius", 4}}));
    EXPECT_EQ(expectedTerm, getLengthOfTheEdge(termToTest, "x", Term(Constant(0)), Term(8)));
}

}

}
