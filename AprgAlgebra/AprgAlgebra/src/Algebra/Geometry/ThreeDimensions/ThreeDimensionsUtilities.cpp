#include "ThreeDimensionsUtilities.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba
{

namespace algebra
{

namespace ThreeDimensions
{

Equation getEllipsoidEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term cSquared(createExpressionIfPossible({Term(c), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("+"), ySquared, Term("/"), bSquared, Term("+"), zSquared, Term("/"), cSquared}));
    return Equation(leftHandSide, "=", 1);
}

Equation getEllipticConeEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term cSquared(createExpressionIfPossible({Term(c), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("+"), ySquared, Term("/"), bSquared, Term("+"), zSquared, Term("/"), cSquared}));
    return Equation(leftHandSide, "=", Term(0));
}

Equation getEllipticHyperboloidEquation(bool const isOneNegative)
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term cSquared(createExpressionIfPossible({Term(c), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("+"), ySquared, Term("/"), bSquared, Term("-"), zSquared, Term("/"), cSquared}));
    Term oneWithSign = isOneNegative ? -1 : 1;
    return Equation(leftHandSide, "=", oneWithSign);
}

Equation getEllipticParaboloidEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term zOverC(createExpressionIfPossible({zMinusZ0, Term("/"), Term(c)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("/"), aSquared, Term("+"), ySquared, Term("/"), bSquared}));
    Term rightHandSide(zOverC);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getHyperbolicParaboloidEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term aSquared(createExpressionIfPossible({Term(a), Term("^"), Term(2)}));
    Term bSquared(createExpressionIfPossible({Term(b), Term("^"), Term(2)}));
    Term zOverC(createExpressionIfPossible({zMinusZ0, Term("/"), Term(c)}));
    Term leftHandSide(createExpressionIfPossible({ySquared, Term("/"), bSquared, Term("-"), xSquared, Term("/"), aSquared}));
    Term rightHandSide(zOverC);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equations getLineEquations()
{
    Equations result;
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSide(createExpressionIfPossible({xMinusX0, Term("/"), Term(a)}));
    Term ySide(createExpressionIfPossible({yMinusY0, Term("/"), Term(b)}));
    Term zSide(createExpressionIfPossible({zMinusZ0, Term("/"), Term(c)}));
    result.emplace_back(xSide, "=", ySide);
    result.emplace_back(xSide, "=", zSide);
    return result;
}

Equation getPlaneEquation()
{
    Term leftHandSide(createExpressionIfPossible(
    {Term(a), Term("*"), Term(x), Term("+"), Term(b), Term("*"), Term(y), Term("+"), Term(c), Term("*"), Term(z), Term("+"), Term(d)}));
    return Equation(leftHandSide, "=", Term(0));
}

Equation getPlaneEquationWithPointCoordinates()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term leftHandSide(createExpressionIfPossible(
    {Term(a), Term("*"), xMinusX0, Term("+"), Term(b), Term("*"), yMinusY0, Term("+"), Term(c), Term("*"), zMinusZ0}));
    return Equation(leftHandSide, "=", Term(0));
}

Equation getSphereEquation()
{
    Term xMinusX0(createExpressionIfPossible({Term(x), Term("-"), Term(x0)}));
    Term yMinusY0(createExpressionIfPossible({Term(y), Term("-"), Term(y0)}));
    Term zMinusZ0(createExpressionIfPossible({Term(z), Term("-"), Term(z0)}));
    Term xSquared(createExpressionIfPossible({xMinusX0, Term("^"), Term(2)}));
    Term ySquared(createExpressionIfPossible({yMinusY0, Term("^"), Term(2)}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, Term("^"), Term(2)}));
    Term rSquared(createExpressionIfPossible({Term(r), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({xSquared, Term("+"), ySquared, Term("+"), zSquared}));
    Term rightHandSide(rSquared);
    return Equation(leftHandSide, "=", rightHandSide);
}

}

}

}
