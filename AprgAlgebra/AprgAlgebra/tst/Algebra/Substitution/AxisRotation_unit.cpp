#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/AxisRotation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(AxisRotationTest, RotateTermByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Term term1(5);
    Term term2("x");
    Term term3(Monomial(7, {{"x", 1}}));
    Term term4(Polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})});
    Term term5(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term6(sin(Term("x")));

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
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, termToVerify3.getDisplayableString());
    EXPECT_EQ(stringToExpect4, termToVerify4.getDisplayableString());
    EXPECT_EQ(stringToExpect5, termToVerify5.getDisplayableString());
    EXPECT_EQ(stringToExpect6, termToVerify6.getDisplayableString());
}

TEST(AxisRotationTest, RotateConstantByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Constant constant(5);

    Term termToVerify(rotation.rotateConstantByAngle(constant));

    string stringToExpect("5");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(AxisRotationTest, RotateVariableByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Variable variable("x");

    Term termToVerify(rotation.rotateVariableByAngle(variable));

    string stringToExpect("-1[x]");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(AxisRotationTest, RotateMonomialByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Monomial monomial(7, {{"x", 1}});

    Term termToVerify(rotation.rotateMonomialByAngle(monomial));

    string stringToExpect("-7[x]");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(AxisRotationTest, RotatePolynomialByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Polynomial polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})};

    Term termToVerify(rotation.rotatePolynomialByAngle(polynomial));

    string stringToExpect("(-9[x] + -11[y])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(AxisRotationTest, RotateExpressionByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    Term termToVerify(rotation.rotateExpressionByAngle(expression));

    string stringToExpect("(-1[x]^-1[y])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(AxisRotationTest, RotateFunctionByAngleWorks)
{
    AxisRotation rotation("x", "y", AlbaNumber(AlbaNumber::Value::pi).getDouble(), false);
    Function functionObject(sin(Term("x")));

    Term termToVerify(rotation.rotateFunctionByAngle(functionObject));

    string stringToExpect("sin(-1[x])");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

}

}
