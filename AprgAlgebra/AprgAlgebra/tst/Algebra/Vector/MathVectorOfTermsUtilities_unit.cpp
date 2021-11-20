#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

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

TEST(MathVectorOfTermsUtilitiesTest, GetDyOverDxWorks)
{
    Term x(Polynomial{Monomial(4, {}), Monomial(-1, {{"t", 2}})});
    Term y(Polynomial{Monomial(1, {{"t", 2}}), Monomial(4, {{"t", 1}})});
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getDyOverDx(termVector, "t"));

    string stringToExpect("(-1 + -2[t^-1])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
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
    Term x(Polynomial{Monomial(1, {{"t", 3}}), Monomial(-3, {{"t", 1}})});
    Term y(Polynomial{Monomial(3, {{"t", 2}})});
    MathVectorOfTwoTerms termVector{x, y};

    Term termToVerify(getCurvature(termVector, "t"));

    string stringToExpect("(2/(3[t^4] + 6[t^2] + 3))");
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
    Term x(Polynomial{Monomial(1, {{"t", 3}}), Monomial(-3, {{"t", 1}})});
    Term y(Polynomial{Monomial(3, {{"t", 2}})});
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitTangentVector(termVector, "t"));

    string stringToExpect("{((1[t^2] + -1)/(1[t^2] + 1)), (2[t]/(1[t^2] + 1))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitNormalVectorWorks)
{
    Term x(Polynomial{Monomial(1, {{"t", 3}}), Monomial(-3, {{"t", 1}})});
    Term y(Polynomial{Monomial(3, {{"t", 2}})});
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getUnitNormalVector(termVector, "t"));

    string stringToExpect("{(2[t]/(1[t^2] + 1)), ((-1[t^2] + 1)/(1[t^2] + 1))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureVectorWorks)
{
    Term x(Polynomial{Monomial(1, {{"t", 3}}), Monomial(-3, {{"t", 1}})});
    Term y(Polynomial{Monomial(3, {{"t", 2}})});
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getCurvatureVector(termVector, "t"));

    string stringToExpect("{(4[t]/(3[t^6] + 9[t^4] + 9[t^2] + 3)), ((-2[t^2] + 2)/(3[t^6] + 9[t^4] + 9[t^2] + 3))}");
    EXPECT_EQ(stringToExpect, vectorToVerify.getDisplayableString());
}

}

}

}
