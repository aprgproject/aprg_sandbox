#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/AxisRotation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(AxisRotationTest, RotateTermByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Term term1(5);
    Term term2("x");
    Term term3(Monomial(7, {{"x", 1}}));
    Term term4(Polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})});
    Term term5(createExpressionIfPossible({"x", "^", "y"}));
    Term term6(sin("x"));

    Term termToVerify1(rotation.rotateTermByAngle(term1));
    Term termToVerify2(rotation.rotateTermByAngle(term2));
    Term termToVerify3(rotation.rotateTermByAngle(term3));
    Term termToVerify4(rotation.rotateTermByAngle(term4));
    Term termToVerify5(rotation.rotateTermByAngle(term5));
    Term termToVerify6(rotation.rotateTermByAngle(term6));

    string stringToExpect1("5");
    string stringToExpect2("-1[x]");
    string stringToExpect3("-7[x]");
    string stringToExpect4("(-9[x] + -11[y])");
    string stringToExpect5("(-1[x]^-1[y])");
    string stringToExpect6("sin(-1[x])");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(termToVerify3));
    EXPECT_EQ(stringToExpect4, convertToString(termToVerify4));
    EXPECT_EQ(stringToExpect5, convertToString(termToVerify5));
    EXPECT_EQ(stringToExpect6, convertToString(termToVerify6));
}

TEST(AxisRotationTest, RotateConstantByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Constant constant(5);

    Term termToVerify(rotation.rotateConstantByAngle(constant));

    string stringToExpect("5");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateVariableByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Variable variable("x");

    Term termToVerify(rotation.rotateVariableByAngle(variable));

    string stringToExpect("-1[x]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateMonomialByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Monomial monomial(7, {{"x", 1}});

    Term termToVerify(rotation.rotateMonomialByAngle(monomial));

    string stringToExpect("-7[x]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotatePolynomialByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Polynomial polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})};

    Term termToVerify(rotation.rotatePolynomialByAngle(polynomial));

    string stringToExpect("(-9[x] + -11[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateExpressionByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Expression expression(createExpressionIfPossible({"x", "^", "y"}));

    Term termToVerify(rotation.rotateExpressionByAngle(expression));

    string stringToExpect("(-1[x]^-1[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateFunctionByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Function functionObject(sin("x"));

    Term termToVerify(rotation.rotateFunctionByAngle(functionObject));

    string stringToExpect("sin(-1[x])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

}  // namespace algebra

}  // namespace alba
