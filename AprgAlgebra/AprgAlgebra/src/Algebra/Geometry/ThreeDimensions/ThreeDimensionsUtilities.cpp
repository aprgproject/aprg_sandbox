#include "ThreeDimensionsUtilities.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba {

namespace algebra {

namespace ThreeDimensions {

Equation getEllipsoidEquation() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term cSquared(createExpressionIfPossible({c, "^", 2}));
    Term leftHandSide(createExpressionIfPossible(
        {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "+", zSquared, "/", cSquared}));
    return Equation(leftHandSide, "=", 1);
}

Equation getEllipticConeEquation() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term cSquared(createExpressionIfPossible({c, "^", 2}));
    Term leftHandSide(createExpressionIfPossible(
        {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "+", zSquared, "/", cSquared}));
    return Equation(leftHandSide, "=", 0);
}

Equation getEllipticHyperboloidEquation(bool const isOneNegative) {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term cSquared(createExpressionIfPossible({c, "^", 2}));
    Term leftHandSide(createExpressionIfPossible(
        {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "-", zSquared, "/", cSquared}));
    Term oneWithSign = isOneNegative ? -1 : 1;
    return Equation(leftHandSide, "=", oneWithSign);
}

Equation getEllipticParaboloidEquation() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term zOverC(createExpressionIfPossible({zMinusZ0, "/", c}));
    Term leftHandSide(createExpressionIfPossible({xSquared, "/", aSquared, "+", ySquared, "/", bSquared}));
    Term const& rightHandSide(zOverC);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equation getHyperbolicParaboloidEquation() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term aSquared(createExpressionIfPossible({a, "^", 2}));
    Term bSquared(createExpressionIfPossible({b, "^", 2}));
    Term zOverC(createExpressionIfPossible({zMinusZ0, "/", c}));
    Term leftHandSide(createExpressionIfPossible({ySquared, "/", bSquared, "-", xSquared, "/", aSquared}));
    Term const& rightHandSide(zOverC);
    return Equation(leftHandSide, "=", rightHandSide);
}

Equations getLineEquations() {
    Equations result;
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSide(createExpressionIfPossible({xMinusX0, "/", a}));
    Term ySide(createExpressionIfPossible({yMinusY0, "/", b}));
    Term zSide(createExpressionIfPossible({zMinusZ0, "/", c}));
    result.emplace_back(xSide, "=", ySide);
    result.emplace_back(xSide, "=", zSide);
    return result;
}

Equation getPlaneEquation() {
    Term leftHandSide(createExpressionIfPossible({a, "*", x, "+", b, "*", y, "+", c, "*", z, "+", d}));
    return Equation(leftHandSide, "=", 0);
}

Equation getPlaneEquationWithPointCoordinates() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term leftHandSide(createExpressionIfPossible({a, "*", xMinusX0, "+", b, "*", yMinusY0, "+", c, "*", zMinusZ0}));
    return Equation(leftHandSide, "=", 0);
}

Equation getSphereEquation() {
    Term xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term rSquared(createExpressionIfPossible({r, "^", 2}));
    Term leftHandSide(createExpressionIfPossible({xSquared, "+", ySquared, "+", zSquared}));
    Term const& rightHandSide(rSquared);
    return Equation(leftHandSide, "=", rightHandSide);
}

}  // namespace ThreeDimensions

}  // namespace algebra

}  // namespace alba
