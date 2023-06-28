#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilities.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace VectorUtilities {

TEST(MathVectorOfTermsUtilitiesTest, IsDivergenceOfCurlZeroWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms vectorField{x, y, z};

    EXPECT_TRUE(isDivergenceOfCurlZero(vectorField, {"x", "y", "z"}));
}

TEST(MathVectorOfTermsUtilitiesTest, IsGaussDivergenceTheoremInAPlaneTrueWorks) {
    Term xInVectorField(Monomial(2, {{"y", 1}}));
    Term yInVectorField(Monomial(5, {{"x", 1}}));
    MathVectorOfTwoTerms vectorField{xInVectorField, yInVectorField};
    MathVectorOfTwoTerms regionOfLineIntegral{cos("t"), sin("t")};
    MathVectorOfTwoTerms unitOutwardNormal{cos("t"), sin("t")};
    DetailsForDefiniteIntegralWithTerms lineIntegralDetails{"t", 0, 2 * getPiAsATerm()};
    DetailsForDefiniteIntegralWithTerms xDetails{"x", -1, 1};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", -1, 1};

    EXPECT_TRUE(isGaussDivergenceTheoremInAPlaneTrue(
        vectorField, regionOfLineIntegral, unitOutwardNormal, lineIntegralDetails, xDetails, yDetails, {"x", "y"}));
}

TEST(MathVectorOfTermsUtilitiesTest, IsStokesTheoremInAPlaneTrueWorks) {
    Term xInVectorField(Monomial(2, {{"y", 1}}));
    Term yInVectorField(Monomial(5, {{"x", 1}}));
    MathVectorOfTwoTerms vectorField{xInVectorField, yInVectorField};
    MathVectorOfTwoTerms regionOfLineIntegral{cos("t"), sin("t")};
    MathVectorOfTwoTerms unitTangent{sin("t") * -1, cos("t")};
    DetailsForDefiniteIntegralWithTerms lineIntegralDetails{"t", 0, 2 * getPiAsATerm()};
    DetailsForDefiniteIntegralWithTerms xDetails{"x", 0, 1};
    DetailsForDefiniteIntegralWithTerms yDetails{"y", 0, getPiAsATerm()};

    EXPECT_TRUE(isStokesTheoremInAPlaneTrue(
        vectorField, regionOfLineIntegral, unitTangent, lineIntegralDetails, xDetails, yDetails, {"x", "y"}));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDyOverDxWorks) {
    Term x(Polynomial{Monomial(4, {}), Monomial(-1, {{"t", 2}})});
    Term y(Polynomial{Monomial(1, {{"t", 2}}), Monomial(4, {{"t", 1}})});
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getDyOverDx(termVector, "t"));

    string stringToExpect("(-1 + -2[t^-1])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInTwoDimensionsWorks) {
    Term termToTest(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 9), {{"y", 2}})});
    AlbaAngle angle(AngleUnitType::Radians, getPi() / 4);

    Term termToVerify(getDirectionalDerivativeInTwoDimensions(termToTest, {"x", "y"}, angle));

    string stringToExpect("(0.0883883[x] + 0.157135[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInThreeDimensionsWorks) {
    Term termToTest(Polynomial{
        Monomial(3, {{"x", 2}}), Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(-2, {{"y", 2}}),
        Monomial(-1, {{"y", 1}, {"z", 1}}), Monomial(1, {{"z", 2}})});
    AlbaAngle alpha(AngleUnitType::Radians, getPi() / 4);
    AlbaAngle beta(AngleUnitType::Radians, getPi() / 5);
    AlbaAngle gamma(AngleUnitType::Radians, getPi() / 6);

    Term termToVerify(getDirectionalDerivativeInThreeDimensions(termToTest, {"x", "y", "z"}, {alpha, beta, gamma}));

    string stringToExpect("(5.05166[x] + -3.39499[y] + 0.923034[z])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralOfAClosedNonIntersectingPathUsingGreensTheoremWorks) {
    Term xInVectorField(Monomial(1, {{"y", 2}}));
    Term yInVectorField(Monomial(4, {{"x", 1}, {"y", 1}}));
    MathVectorOfTwoTerms vectorField{xInVectorField, yInVectorField};
    DetailsForDefiniteIntegralWithTerms xDetailsForLinePath{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms yDetailsForLinePath{"y", Monomial(2, {{"x", 1}}), Monomial(1, {{"x", 2}})};

    Term termToVerify(getLineIntegralOfAClosedNonIntersectingPathUsingGreensTheorem(
        vectorField, {"x", "y"}, xDetailsForLinePath, yDetailsForLinePath));

    string stringToExpect("(-64/15)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetAreaOfAClosedNonIntersectingPathUsingGreensTheoremWorks) {
    // Get area of ellipse
    Term xInLinePath("a" * cos("t"));  // ellipse parameterized in X
    Term yInLinePath("b" * sin("t"));  // ellipse parameterized in Y
    MathVectorOfTwoTerms linePath{xInLinePath, yInLinePath};

    Term termToVerify(
        getAreaOfAClosedNonIntersectingPathUsingGreensTheorem({"x", "y"}, linePath, {"t", 0, 2 * getPiAsATerm()}));

    string stringToExpect("(pi)[a][b]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetNormalOfASurfaceOnAPointWorks) {
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", 0);

    MathVectorOfThreeTerms vectorToVerify(getNormalOfASurfaceOnAPoint(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect("{16, 8, -16}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetTangentPlaneOnAPointOfASurfaceWorks) {
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", 0);

    Equation equationToVerify(getTangentPlaneOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect("(2[x] + 1[y] + -2[z] + -4) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetPerpendicularLineOnAPointOfASurfaceWorks) {
    Term surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation equationToTest(surfaceLeftPart, "=", 0);

    Equations equationsToVerify(getPerpendicularLineOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string stringToExpect1("(1[x] + -2[y] + 6) = 0");
    string stringToExpect2("(1[x] + 1[z] + -4) = 0");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(equationsToVerify[0]));
    EXPECT_EQ(stringToExpect2, convertToString(equationsToVerify[1]));
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurlWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms vectorField{x, y, z};

    MathVectorOfThreeTerms vectorToVerify(getCurl(vectorField, {"x", "y", "z"}));

    string stringToExpect("{(-3[x^2][y] + 4[y][z]), -1, 6[x][y][z]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, IsContinuousAtWorks) {
    Term x(cos("t"));
    Term y(createExpressionIfPossible({2, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms termVector{x, y};

    EXPECT_TRUE(isContinuousAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, IsDifferentiableAtWorks) {
    Term x("t");
    Term y("t");
    MathVectorOfTwoTerms termVector{x, y};

    EXPECT_TRUE(isDifferentiableAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, AreOriginalAndDerivativeVectorsOrthogonalWorks) {
    MathVectorOfTwoTerms termVector{7, 8};

    EXPECT_TRUE(areOriginalAndDerivativeVectorsOrthogonal(termVector));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcDerivativeWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArcDerivative(termVector, "t"));

    string stringToExpect("((9[t^4] + 16[t^2])^(1/2))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArc(termVector, "t"));

    string stringToExpect("(((9[t^2] + 16)^(3/2))/27)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcFromStartToEndWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getLengthOfArcFromStartToEnd(termVector, {"t", -2, 0}));

    EXPECT_EQ(Term(-11.5176789869724), termToVerify);
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getCurvature(termVector, "t"));

    string stringToExpect("(12[t^-1]/((9[t^2] + 16)^(3/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample1) {
    Term x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms gradient{x, y};

    bool isExactDifferential(false);
    Term termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y"}, isExactDifferential));

    string stringToExpect("(1[x][y^2] + 1[x^2] + 2[y^2] + 4[x] + -5[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample2) {
    Term x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term y(5);
    MathVectorOfTwoTerms gradient{x, y};

    bool isExactDifferential(false);
    Term termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y"}, isExactDifferential));

    string stringToExpect("{EmptyTerm}");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_FALSE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample3) {
    Term eToTheX(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    Term x(createExpressionIfPossible({eToTheX, "*", sin("z"), "+", Monomial(2, {{"y", 1}, {"z", 1}})}));
    Term y(Polynomial{Monomial(2, {{"x", 1}, {"z", 1}}), Monomial(2, {{"y", 1}})});
    Term z(createExpressionIfPossible(
        {eToTheX, "*", cos("z"), "+", Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"z", 2}})}}));
    MathVectorOfThreeTerms gradient{x, y, z};

    bool isExactDifferential(false);
    Term termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y", "z"}, isExactDifferential));

    string stringToExpect("((2[x][y][z] + 1[z^3] + 1[y^2])+(((e)^x)*sin(z)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetPotentialFunctionForVectorFieldGradientWorks) {
    Term x(Monomial(1, {{"y", -1}}));
    Term y(Monomial(-1, {{"x", 1}, {"y", -2}}));
    MathVectorOfTwoTerms gradient{x, y};

    bool isConservative(false);
    Term termToVerify(getPotentialFunctionForVectorFieldGradient(gradient, {"x", "y"}, isConservative));

    string stringToExpect("1[x][y^-1]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isConservative);
}

TEST(MathVectorOfTermsUtilitiesTest, GetDivergenceWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms vectorField{x, y, z};

    Term termToVerify(getDivergence(vectorField, {"x", "y", "z"}));

    string stringToExpect("((2*((e)^2[x]))+3[x^2][z]+2[y^2])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLaplaceTermWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term y(Monomial(3, {{"x", 2}, {"y", 2}, {"z", 1}}));
    Term z(Polynomial{Monomial(2, {{"y", 2}, {"z", 2}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms vectorField{x, y, z};

    Term termToVerify(getLaplaceTerm(vectorField, {"x", "y", "z"}));

    string stringToExpect("((4*((e)^2[x]))+6[x^2][z]+4[y^2])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralWorksOnExample1) {
    // Suppose a particle moves along the parabola y=x^2 from the point (-1,1) to the point (2,4).
    // Find the total work done if the motion is caused by the force field F(x, y) = (x^2 + y^2)i + (3*x^2*y)j

    Term forceInX(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term forceInY(Monomial(3, {{"x", 2}, {"y", 1}}));
    MathVectorOfTwoTerms vectorField{forceInX, forceInY};
    MathVectorOfTwoTerms linePath{"t", Monomial(1, {{"t", 2}})};  // this is a parabola

    Term termToVerify(getLineIntegral(vectorField, {"x", "y"}, linePath, {"t", -1, 2}));

    string stringToExpect("(363/5)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralWorksOnExample2) {
    Term fieldInX(Monomial(3, {{"x", 1}, {"d[x]", 1}}));
    Term fieldInY(Monomial(2, {{"x", 1}, {"y", 1}, {"d[y]", 1}}));
    Term fieldInZ(Monomial(1, {{"z", 1}, {"d[z]", 1}}));
    MathVectorOfThreeTerms vectorField{fieldInX, fieldInY, fieldInZ};
    MathVectorOfThreeTerms linePath{cos("t"), sin("t"), "t"};

    Term termToVerify(getLineIntegral(vectorField, {"x", "y", "z"}, linePath, {"t", 0, 2 * getPiAsATerm()}));

    string stringToExpect("19.7392");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralIndependentOfPathWorksOnExample1) {
    Term x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms vectorField{x, y};

    Term termToVerify(getLineIntegralIndependentOfPath(vectorField, {"x", "y"}, {0, 0}, {1, 1}));

    string stringToExpect("3");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralIndependentOfPathWorksOnExample2) {
    Term x(Polynomial{Monomial(4, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(-1, {{"z", 1}})});
    Term y(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-2, {{"y", 1}}), Monomial(1, {{"z", 1}})});
    Term z(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(2, {{"z", 1}})});
    MathVectorOfThreeTerms vectorField{x, y, z};

    Term termToVerify(getLineIntegralIndependentOfPath(vectorField, {"x", "y", "z"}, {4, -2, 1}, {-1, 2, 0}));

    string stringToExpect("-13");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralEqualsGetLineIntegralIndependentOfPath) {
    Term x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms vectorField{x, y};
    MathVectorOfTwoTerms linePath{"t", "t"};

    Term lineIntegral(getLineIntegral(vectorField, {"x", "y"}, linePath, {"t", 0, 1}));
    Term lineIntegralIndependentOfPath(getLineIntegralIndependentOfPath(vectorField, {"x", "y"}, {0, 0}, {1, 1}));

    EXPECT_EQ(lineIntegral, lineIntegralIndependentOfPath);
}

TEST(MathVectorOfTermsUtilitiesTest, GetLimitWorks) {
    Term x(cos("t"));
    Term y(createExpressionIfPossible({2, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getLimit(termVector, "t", 0));

    string stringToExpect("{1, 2}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, DifferentiateWorks) {
    Term x(createExpressionIfPossible({2, "+", sin("t")}));
    Term y(cos("t"));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(differentiate(termVector, "t"));

    string stringToExpect("{cos(t), (-1*sin(t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, IntegrateWorks) {
    Term x(sin("t"));
    Term y(createExpressionIfPossible({-3, "*", cos("t")}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(integrate(termVector, "t"));

    string stringToExpect("{(-1*cos(t)), (-3*sin(t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitTangentVectorWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitTangentVector(termVector, "t"));

    string stringToExpect("{(3[t]/((9[t^2] + 16)^(1/2))), (4/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitNormalVectorWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitNormalVector(termVector, "t"));

    string stringToExpect("{(4/((9[t^2] + 16)^(1/2))), (-3[t]/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureVectorWorks) {
    Term x(Monomial(1, {{"t", 3}}));
    Term y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getCurvatureVector(termVector, "t"));

    string stringToExpect("{(48/(81[t^5] + 288[t^3] + 256[t])), (-36/(81[t^4] + 288[t^2] + 256))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetGradientWorks) {
    Term termToTest(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 9), {{"y", 2}})});

    MathVectorOfTwoTerms vectorToVerify(getGradient<2U>(termToTest, {"x", "y"}));

    string stringToExpect("{(1/8)[x], (2/9)[y]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDelWorks) {
    Term x(Monomial(1, {{"x", 1}, {"y", 2}}));
    Term y(Monomial(1, {{"x", 3}, {"y", 4}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getDel(termVector, {"x", "y"}));

    string stringToExpect("{1[y^2], 4[x^3][y^3]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

}  // namespace VectorUtilities

}  // namespace algebra

}  // namespace alba
