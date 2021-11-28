#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

namespace ThreeDimensions
{

Equation getEllipsoidEquation();
Equation getEllipticConeEquation();
Equation getEllipticHyperboloidEquation(bool const isOneNegative);
Equation getEllipticParaboloidEquation();
Equation getHyperbolicParaboloidEquation();
Equations getLineEquations();
Equation getPlaneEquation();
Equation getPlaneEquationWithPointCoordinates();
Equation getSphereEquation();

}
}

}