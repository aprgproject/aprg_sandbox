#include "TrigonometricEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Equation getTrigonometricPythagoreanIdentity(Term const& term)
{
    // sin(x)^2 + cos(x)^2 = 1

    Term leftSideTerm(createExpressionIfPossible({getSineSquared(term), "+", getCosineSquared(term)}));
    return Equation(leftSideTerm, "=", 1);
}

Equation getSineEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& hypotenuse)
{
    // sin(x) = o/h

    Term leftSideTerm(sin(angle));
    Term rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, "/", hypotenuse}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getCosineEquationOfRightTriangle(
        Term const& angle,
        Term const& adjacentSideOfAngle,
        Term const& hypotenuse)
{
    // cos(x) = a/h

    Term leftSideTerm(cos(angle));
    Term rightSideTerm(createExpressionIfPossible({adjacentSideOfAngle, "/", hypotenuse}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getTangentEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& adjacentSideOfAngle)
{
    // (x) = o/a

    Term leftSideTerm(tan(angle));
    Term rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, "/", adjacentSideOfAngle}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getLawOfSineEquation(
        Term const& side1,
        Term const& oppositeAngleOfSide1,
        Term const& side2,
        Term const& oppositeAngleOfSide2)
{
    // x/sin(angleOppositeOfX) = y/sin(angleOppositeOfY) = z/sin(angleOppositeOfZ)

    Term leftSideTerm(createExpressionIfPossible({side1, "/", sin(oppositeAngleOfSide1)}));
    Term rightSideTerm(createExpressionIfPossible({side2, "/", sin(oppositeAngleOfSide2)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getLawOfCosineEquation(
        Term const& side1,
        Term const& side2,
        Term const& side3,
        Term const& oppositeAngleOfSide1)
{
    // x^2 = y^2 + z^2 - 2*y*z*cos(angleOppositeOfX)

    Term side1Squared(createExpressionIfPossible({side1, "^", 2}));
    Term side2Squared(createExpressionIfPossible({side2, "^", 2}));
    Term side3Squared(createExpressionIfPossible({side3, "^", 2}));
    Term cosinePart(createExpressionIfPossible({2, "*", side2, "*", side3, "*", cos(oppositeAngleOfSide1)}));
    Term const& leftSideTerm(side1Squared);
    Term rightSideTerm(createExpressionIfPossible({side2Squared, "+", side3Squared, "-", cosinePart}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Term getSineSquared(Term const& term)
{
    // sin(x)^2

    return Term(createExpressionIfPossible({sin(term), "^", 2}));
}

Term getSineSquaredInCosine(Term const& term)
{
    // sin(x)^2 = 1 - cos(x)^2

    return Term(createExpressionIfPossible({1, "-", cos(term), "^", 2}));
}

Term getCosineSquared(Term const& term)
{
    // cos(x)^2

    return Term(createExpressionIfPossible({cos(term), "^", 2}));
}

Term getCosineSquaredInSine(Term const& term)
{
    // cos(x)^2 = 1 - sin(x)^2

    return Term(createExpressionIfPossible({1, "-", sin(term), "^", 2}));
}

Term getTangentSquared(Term const& term)
{
    // tan(x)^2

    return Term(createExpressionIfPossible({tan(term), "^", 2}));
}

Term getTangentSquaredInSecant(Term const& term)
{
    // tan(x)^2 = sec(x)^2 - 1

    return Term(createExpressionIfPossible({sec(term), "^", 2, "-", 1}));
}

Term getCosecantSquared(Term const& term)
{
    // csc(x)^2

    return Term(createExpressionIfPossible({csc(term), "^", 2}));
}

Term getCosecantSquaredInCotangent(Term const& term)
{
    // csc(x)^2 = cot(x)^2 + 1

    return Term(createExpressionIfPossible({cot(term), "^", 2, "+", 1}));
}

Term getSecantSquared(Term const& term)
{
    // sec(x)^2

    return Term(createExpressionIfPossible({sec(term), "^", 2}));
}

Term getSecantSquaredInTangent(Term const& term)
{
    // sec(x)^2 = tan(x)^2 + 1

    return Term(createExpressionIfPossible({tan(term), "^", 2, "+", 1}));
}

Term getCotangentSquared(Term const& term)
{
    // cot(x)^2

    return Term(createExpressionIfPossible({cot(term), "^", 2}));
}

Term getCotangentSquaredInCosecant(Term const& term)
{
    // cot(x)^2 = csc(x)^2 - 1

    return Term(createExpressionIfPossible({csc(term), "^", 2, "-", 1}));
}

Term getSineOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // sin(x +- y) =  sin(x)*cos(y) +- cos(x)*sin(y)

    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Term firstPart(createExpressionIfPossible({sin(term1), "*", cos(term2)}));
        Term secondPart(createExpressionIfPossible({cos(term1), "*", sin(term2)}));
        result = Term(createExpressionIfPossible({firstPart, operatorObject, secondPart}));
    }
    return result;
}

Term getCosineOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // cos(x +- y) =  cos(x)*cos(y) -+ sin(x)*sin(y)

    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Term firstPart(createExpressionIfPossible({cos(term1), "*", cos(term2)}));
        Term secondPart(createExpressionIfPossible({sin(term1), "*", sin(term2)}));
        Operator reverseOperator(operatorObject);
        reverseOperator.reverseOperation();
        result = Term(createExpressionIfPossible({firstPart, reverseOperator, secondPart}));
    }
    return result;
}

Term getTangentOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // tan(x +- y) =  (tan(x) +- tan(y)) / (1 -+ tan(x)*tan(y))

    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Operator reverseOperator(operatorObject);
        reverseOperator.reverseOperation();
        Term numerator(createExpressionIfPossible({tan(term1), operatorObject, tan(term2)}));
        Term denominator(createExpressionIfPossible(
        {1, reverseOperator, Term(createExpressionIfPossible({tan(term1), "*", tan(term2)}))}));
        result = Term(createExpressionIfPossible({numerator, "/", denominator}));
    }
    return result;
}

Term getSineOfDoubledValue(Term const& term)
{
    // sin(2*x) =  2*sin(x)*cos(x)

    return Term(createExpressionIfPossible({2, "*", sin(term), "*", cos(term)}));
}

Term getCosineOfDoubledValue(Term const& term)
{
    // cos(2*x) =  cos(x)^2 - sin(x)^2

    return Term(createExpressionIfPossible({getCosineSquared(term), "-", getSineSquared(term)}));
}

Term getTangentOfDoubledValue(Term const& term)
{
    // tan(2*x) =  (2*tan(x)) / (1-tan(x)^2)

    Term numerator(createExpressionIfPossible({2, "*", tan(term)}));
    Term denominator(createExpressionIfPossible({1, "-", getTangentSquared(term)}));
    return Term(createExpressionIfPossible({numerator, "/", denominator}));
}

Term getSineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // sin(x/2) =  +- ((1-cos(x))/2)^(1/2)

    Term result(createExpressionIfPossible({getSineSquaredOfHalvedValue(term), "^", AlbaNumber::createFraction(1, 2)}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getCosineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // cos(x/2) =  +- ((1+cos(x))/2)^(1/2)

    Term result(createExpressionIfPossible({getCosineSquaredOfHalvedValue(term), "^", AlbaNumber::createFraction(1, 2)}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getSineSquaredOfHalvedValue(Term const& term)
{
    // sin(x/2)^2 =  +- ((1-cos(x))/2)

    Term numerator(createExpressionIfPossible({1, "-", cos(term)}));
    return Term(createExpressionIfPossible({numerator, "/", 2}));
}

Term getCosineSquaredOfHalvedValue(Term const& term)
{
    // cos(x/2)^2 =  +- ((1+cos(x))/2)

    Term numerator(createExpressionIfPossible({1, "+", cos(term)}));
    return Term(createExpressionIfPossible({numerator, "/", 2}));
}

}

}
