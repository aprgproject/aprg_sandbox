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
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term rSquared(createExpressionIfPossible({Term(r), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("+"), ySquared}));
    Term rightHandSide(rSquared);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getEllipseEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("+"), ySquared, Term("/"), bSquared}));
    return Equation(leftHandSide, "=", Term(1));
}

Equation getHyperbolaEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("-"), ySquared, Term("/"), bSquared}));
    return Equation(leftHandSide, "=", Term(1));
}

Equation getLimaconEquation(LimaconTrigonometricFunctionType const type)
{
    Term trigPart;
    if(LimaconTrigonometricFunctionType::Cosine == type)
    {
        trigPart = Term(cos(Term(theta)));
    }
    else if(LimaconTrigonometricFunctionType::Sine == type)
    {
        trigPart = Term(sin(Term(theta)));
    }
    Term leftHandSide(createExpressionIfPossible({Term(a), Term("+"), Term(b), Term("*"), trigPart}));
    Term rightHandSide(r);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getLineEquation()
{
    Term leftHandSide(createExpressionIfPossible({Term(a), Term("*"), Term(x), Term("+"), Term(b), Term("*"), Term(y), Term("+"), Term(c)}));
    return Equation(leftHandSide, "=", Term(0));
}

Equation getParabolaEquation(ParabolaOrientation const parabolaOrientation)
{
    Equation result;
    if(ParabolaOrientation::PolynomialX == parabolaOrientation)
    {
        Term xSquared(createExpressionIfPossible({Term(x), Term("^"), Term(2)}));
        Term leftHandSide(createExpressionIfPossible({Term(a), Term("*"), xSquared, Term("+"), Term(b), Term("*"), Term(x), Term("+"), Term(c)}));
        Term rightHandSide(y);
        result = Equation(leftHandSide, "=", rightHandSide);
    }
    else if(ParabolaOrientation::PolynomialY == parabolaOrientation)
    {
        Term ySquared(createExpressionIfPossible({Term(y), Term("^"), Term(2)}));
        Term leftHandSide(createExpressionIfPossible({Term(a), Term("*"), ySquared, Term("+"), Term(b), Term("*"), Term(y), Term("+"), Term(c)}));
        Term rightHandSide(x);
        result = Equation(leftHandSide, "=", rightHandSide);
    }
    return result;
}

}

}

}
