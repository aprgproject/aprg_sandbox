#include "TwoDimensionsUtilities.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
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

Equation getParabolaEquation(ParabolaOrientation const parabolaOrientation){
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
    }    return result;
}

}
}

}
