#include "TwoDimensionsUtilities.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

using namespace alba::algebra::Functions;
namespace alba
{
namespace algebra
{

namespace TwoDimensions
{

Equation getCircleEquation()
{
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term rSquared(createExpressionIfPossible({r, "^", 2}));
    Term leftHandSide(createExpressionIfPossible({xSquared, "+", ySquared}));
    Term rightHandSide(rSquared);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getEllipseEquation()
{
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term leftHandSide(createExpressionIfPossible({xSquared, "/", aSquared, "+", ySquared, "/", bSquared}));
    return Equation(leftHandSide, "=", 1);
}

Equation getHyperbolaEquation()
{
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term leftHandSide(createExpressionIfPossible({xSquared, "/", aSquared, "-", ySquared, "/", bSquared}));
    return Equation(leftHandSide, "=", 1);
}

Equation getLimaconEquation(LimaconTrigonometricFunctionType const type)
{
    Term trigPart;
    if(LimaconTrigonometricFunctionType::Cosine == type)
    {
        trigPart = cos(theta);
    }
    else if(LimaconTrigonometricFunctionType::Sine == type)
    {
        trigPart = sin(theta);
    }
    Term leftHandSide(createExpressionIfPossible({a, "+", b, "*", trigPart}));
    Term rightHandSide(r);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getLineEquation()
{
    Term leftHandSide(createExpressionIfPossible({a, "*", x, "+", b, "*", y, "+", c}));
    return Equation(leftHandSide, "=", 0);
}

Equation getParabolaEquation(ParabolaOrientation const parabolaOrientation)
{
    Equation result;
    if(ParabolaOrientation::PolynomialX == parabolaOrientation)
    {
        Term xSquared(createExpressionIfPossible({x, "^", 2}));
        Term leftHandSide(createExpressionIfPossible({a, "*", xSquared, "+", b, "*", x, "+", c}));
        Term rightHandSide(y);
        result = Equation(leftHandSide, "=", rightHandSide);
    }
    else if(ParabolaOrientation::PolynomialY == parabolaOrientation)
    {
        Term ySquared(createExpressionIfPossible({y, "^", 2}));
        Term leftHandSide(createExpressionIfPossible({a, "*", ySquared, "+", b, "*", y, "+", c}));
        Term rightHandSide(x);
        result = Equation(leftHandSide, "=", rightHandSide);
    }
    return result;
}

// A conical frustum is a frustum created by slicing the top off a cone (with the cut made parallel to the base).
// For a right circular cone, let h be height, rb as bottom radius and rt as bottom radius.

Term getSurfaceAreaOfAConicalFrustum()
{
    Term topCircleArea(createExpressionIfPossible({getPiAsATerm(), "*", "rt", "^", 2}));
    Term bottomCircleArea(createExpressionIfPossible({getPiAsATerm(), "*", "rb", "^", 2}));
    Term sideArea(createExpressionIfPossible(
    {getPiAsATerm(), "*", "(", "rb", "+", "rt", ")", "*", "(", "(", "rb", "-", "rt", ")", "^", 2, "+", "h", "^", 2, ")", "^", AlbaNumber::createFraction(1, 2)}));

    return Term(createExpressionIfPossible({topCircleArea, "+", bottomCircleArea, "+", sideArea}));
}

Term getVolumeOfAConicalFrustum()
{
    Term radiusPart(createExpressionIfPossible({"rt", "^", 2, "+", "rt", "*", "rb", "+", "rb", "^", 2}));
    return Term(createExpressionIfPossible({AlbaNumber::createFraction(1, 3), "*", getPiAsATerm(), "*", "h", "*", radiusPart}));
}

}

}

}