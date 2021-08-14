#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

Equation getSineSquaredPlusCosineSquaredEqualsOne(Term const& term);
Equation getSineEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& hypotenuse);
Equation getCosineEquationOfRightTriangle(
        Term const& angle,
        Term const& adjacentSideOfAngle,
        Term const& hypotenuse);
Equation getTangentEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& adjacentSideOfAngle);
Equation getLawOfSineEquation(
        Term const& side1,
        Term const& oppositeAngleOfSide1,
        Term const& side2,
        Term const& oppositeAngleOfSide2);
Equation getLawOfCosineEquation(
        Term const& side1,
        Term const& side2,
        Term const& side3,
        Term const& oppositeAngleOfSide1);
Term getSineSquared(Term const& term);
Term getCosineSquared(Term const& term);
Term getTangentSquared(Term const& term);
Term getSineOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2);
Term getCosineOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2);
Term getTangentOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2);
Term getSineOfDoubledValue(Term const& term);
Term getCosineOfDoubledValue(Term const& term);
Term getTangentOfDoubledValue(Term const& term);
Term getSineOfHalvedValue(Term const& term, bool const isPositiveRoot);
Term getCosineOfHalvedValue(Term const& term, bool const isPositiveRoot);


}

}
