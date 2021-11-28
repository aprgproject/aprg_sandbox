#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

TEST(MathVectorOfTermsUtilitiesTest, GetDyOverDxWorks)
{
    Term x(Polynomial{Monomial(4, {}), Monomial(-1, {{"t", 2}})});
    Term y(Polynomial{Monomial(1, {{"t", 2}}), Monomial(4, {{"t", 1}})});
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getDyOverDx(termVector, "t"));

    string stringToExpect("(-1 + -2[t^-1])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInTwoDimensionsWorks)
{
    Term termToTest(Polynomial{Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}), Monomial(AlbaNumber::createFraction(1, 9), {{"y", 2}})});
    AlbaAngle angle(AngleUnitType::Radians, getPi()/4);

    Term termToVerify(getDirectionalDerivativeInTwoDimensions(termToTest, {"x", "y"}, angle));

    string stringToExpect("(0.08838834764831845[x] + 0.1571348402636772[y])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInThreeDimensionsWorks)
{
    Term termToTest(Polynomial
    {Monomial(3, {{"x", 2}}), Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(-2, {{"y", 2}}), Monomial(-1, {{"y", 1}, {"z", 1}}), Monomial(1, {{"z", 2}})});
    AlbaAngle alpha(AngleUnitType::Radians, getPi()/4);
    AlbaAngle beta(AngleUnitType::Radians, getPi()/5);
    AlbaAngle gamma(AngleUnitType::Radians, getPi()/6);

    Term termToVerify(getDirectionalDerivativeInThreeDimensions(termToTest, {"x", "y", "z"}, {alpha, beta, gamma}));

    string stringToExpect("(5.051657681494233[x] + -3.394986600097681[y] + 0.92303381319393[z])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetNormalOfASurfaceOnAPointWorks)
{
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", Term(0));

    MathVectorOfThreeTerms vectorToVerify(getNormalOfASurfaceOnAPoint(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect("{16, 8, -16}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetTangentPlaneOnAPointOfASurfaceWorks)
{
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", Term(0));

    Equation equationToVerify(getTangentPlaneOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect("(2[x] + 1[y] + -2[z] + -4) = 0");
    EXPECT_EQ(stringToExpect, equationToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetPerpendicularLineOnAPointOfASurfaceWorks)
{
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", Term(0));

    Equations equationsToVerify(getPerpendicularLineOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect1("(1[x] + -2[y] + 6) = 0");
    string stringToExpect2("(1[x] + 1[z] + -4) = 0");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, equationsToVerify.at(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationsToVerify.at(1).getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, IsContinuousAtWorks)
{
    Term t("t");
    Term x(cos(t));
    Term y(createExpressionIfPossible({Term(2), Term("*"), getEAsTerm(), Term("^"), t}));
    MathVectorOfTwoTerms termVector{x, y};

    EXPECT_TRUE(isContinuousAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, IsDifferentiableAtWorks)
{
    Term t("t");
    Term x(t);
    Term y(t);
    MathVectorOfTwoTerms termVector{x, y};

    EXPECT_TRUE(isDifferentiableAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, AreOriginalAndDerivativeVectorsOrthogonalWorks)
{
    MathVectorOfTwoTerms termVector{Term(7), Term(8)};

    EXPECT_TRUE(areOriginalAndDerivativeVectorsOrthogonal(termVector));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcDerivativeWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArcDerivative(termVector, "t"));

    string stringToExpect("((9[t^4] + 16[t^2])^(1/2))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArc(termVector, "t"));

    string stringToExpect("(((9[t^2] + 16)^(3/2))/27)");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcFromStartToEndWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArcFromStartToEnd(termVector, "t", Term(-2), Term(0)));

    EXPECT_EQ(Term(-11.5176789869724), termToVerify);
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getCurvature(termVector, "t"));

    string stringToExpect("(12[t^-1]/((9[t^2] + 16)^(3/2)))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetLimitWorks)
{
    Term t("t");
    Term x(cos(t));
    Term y(createExpressionIfPossible({Term(2), Term("*"), getEAsTerm(), Term("^"), t}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getLimit(termVector, "t", 0));

    string stringToExpect("{1, 2}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, DifferentiateWorks)
{
    Term t("t");
    Term x(createExpressionIfPossible({Term(2), Term("+"), Term(sin(t))}));
    Term y(cos(t));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(differentiate(termVector, "t"));

    string stringToExpect("{cos(t), (-1*sin(t))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, IntegrateWorks)
{
    Term t("t");
    Term x(sin(t));
    Term y(createExpressionIfPossible({Term(-3), Term("*"), Term(cos(t))}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(integrate(termVector, "t"));

    string stringToExpect("{(-1*cos(t)), (-3*sin(t))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitTangentVectorWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitTangentVector(termVector, "t"));

    string stringToExpect("{(3[t]/((9[t^2] + 16)^(1/2))), (4/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitNormalVectorWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitNormalVector(termVector, "t"));

    string stringToExpect("{(4/((9[t^2] + 16)^(1/2))), (-3[t]/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureVectorWorks)
{
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getCurvatureVector(termVector, "t"));

    string stringToExpect("{(48/(81[t^5] + 288[t^3] + 256[t])), (-36/(81[t^4] + 288[t^2] + 256))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

}

}

}
