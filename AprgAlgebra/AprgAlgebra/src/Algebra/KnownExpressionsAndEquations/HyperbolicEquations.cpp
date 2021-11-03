#include "HyperbolicEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Term getEToTheX(
        Term const& term)
{
    // e^x

    return Term(createExpressionIfPossible({getEAsTerm(), Term("^"), term}));
}

Term getEToTheNegativeX(
        Term const& term)
{
    // e^(-x)

    return Term(createExpressionIfPossible({getEAsTerm(), Term("^"), negateTerm(term)}));
}

Term getEToTheXPlusEToTheNegativeX(
        Term const& term)
{
    // e^x + e^(-x)

    return Term(createExpressionIfPossible({getEToTheX(term), Term("+"), getEToTheNegativeX(term)}));
}

Term getEToTheXMinusEToTheNegativeX(
        Term const& term)
{
    // e^x - e^(-x)

    return Term(createExpressionIfPossible({getEToTheX(term), Term("-"), getEToTheNegativeX(term)}));
}

Equation getHyperbolicSineDefinition(
        Term const& term)
{
    // sinh(x) = (e^x - e^(-x)) / 2

    Term leftSideTerm(sinh(term));
    Term rightSideTerm(createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), Term("/"), Term(2)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicCosineDefinition(
        Term const& term)
{
    // cosh(x) = (e^x + e^(-x)) / 2

    Term leftSideTerm(cosh(term));
    Term rightSideTerm(createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), Term("/"), Term(2)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicTangentDefinition(
        Term const& term)
{
    // tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))

    Term leftSideTerm(tanh(term));
    Term rightSideTerm(createExpressionIfPossible(
    {getEToTheXMinusEToTheNegativeX(term), Term("/"), getEToTheXPlusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicCosecantDefinition(
        Term const& term)
{
    // csch(x) = 2 / (e^x - e^(-x))

    Term leftSideTerm(csch(term));
    Term rightSideTerm(createExpressionIfPossible({Term(2), Term("/"), getEToTheXMinusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicSecantDefinition(
        Term const& term)
{
    // sech(x) = 2 / (e^x + e^(-x))

    Term leftSideTerm(sech(term));
    Term rightSideTerm(createExpressionIfPossible({Term(2), Term("/"), getEToTheXPlusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicCotangentDefinition(
        Term const& term)
{
    // coth(x) = (e^x + e^(-x)) / (e^x - e^(-x))

    Term leftSideTerm(coth(term));
    Term rightSideTerm(createExpressionIfPossible(
    {getEToTheXPlusEToTheNegativeX(term), Term("/"), getEToTheXMinusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicFunctionIdentityEquation(
        Term const& term)
{
    // cosh(x)^2 - sinh(x)^2 = 1

    Term leftSideTerm(createExpressionIfPossible(
    {Term(cosh(term)), Term("^"), Term(2), Term("-"), Term(sinh(term)), Term("^"), Term(2)}));
    return Equation(leftSideTerm, "=", Term(1));
}

Equation getEToTheXFromHyperbolicFunctionsEquation(
        Term const& term)
{
    // e^x = cosh(x) + sinh(x)

    Term leftSideTerm(getEToTheX(term));
    Term rightSideTerm(createExpressionIfPossible({Term(cosh(term)), Term("+"), Term(sinh(term))}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getEToTheNegativeXFromHyperbolicFunctionsEquation(
        Term const& term)
{
    // e^(-x) = cosh(x) - sinh(x)

    Term leftSideTerm(getEToTheNegativeX(term));
    Term rightSideTerm(createExpressionIfPossible({Term(cosh(term)), Term("-"), Term(sinh(term))}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Term getHyperbolicSineOfSumOfTwoTerms(
        Term const& term1,
        Term const& term2)
{
    // sinh(x + y) =  sinh(x)*cosh(y) + cosh(x)*sinh(y)

    Term firstPart(createExpressionIfPossible({Term(sinh(term1)), Term("*"), Term(cosh(term2))}));
    Term secondPart(createExpressionIfPossible({Term(cosh(term1)), Term("*"), Term(sinh(term2))}));
    return Term(createExpressionIfPossible({firstPart, Term("+"), secondPart}));
}

Term getHyperbolicCosineOfSumOfTwoTerms(
        Term const& term1,
        Term const& term2)
{
    // cosh(x + y) =  cosh(x)*cosh(y) + sinh(x)*sinh(y)

    Term firstPart(createExpressionIfPossible({Term(cosh(term1)), Term("*"), Term(cosh(term2))}));
    Term secondPart(createExpressionIfPossible({Term(sinh(term1)), Term("*"), Term(sinh(term2))}));
    return Term(createExpressionIfPossible({firstPart, Term("+"), secondPart}));
}

Term getHyperbolicSineOfDoubledValue(Term const& term)
{
    // sinh(2*x) =  2*sinh(x)*cosh(x)

    return Term(createExpressionIfPossible({Term(2), Term("*"), Term(sinh(term)), Term("*"), Term(cosh(term))}));
}

Term getHyperbolicCosineOfDoubledValue(Term const& term)
{
    // cosh(2*x) =  cosh(x)^2 + sinh(x)^2

    return Term(createExpressionIfPossible(
    {Term(cosh(term)), Term("^"), Term(2), Term("+"), Term(sinh(term)), Term("^"), Term(2)}));
}

Term getHyperbolicSineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // sinh(x/2) =  +- ((cosh(x)-1)/2)^(1/2)

    Term numerator(createExpressionIfPossible({Term(cosh(term)), Term("-"), Term(1)}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({Term(-1), Term("*"), Term(result)}));
    }
    return result;
}

Term getHyperbolicCosineOfHalvedValue(Term const& term)
{
    // sinh(x/2) = ((cosh(x)+1)/2)^(1/2)

    Term numerator(createExpressionIfPossible({Term(cosh(term)), Term("+"), Term(1)}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    return result;
}

Equation getHyperbolicArcSineDefinition(
        Term const& term)
{
    Term leftSideTerm(arcsinh(term));
    Term insideSquareRoot(createExpressionIfPossible({term, Term("^"), Term(2), Term("+"), Term(1)}));
    Term squareRootTerm(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term insideLogarithm(createExpressionIfPossible({term, Term("+"), squareRootTerm}));
    Term rightSideTerm(ln(insideLogarithm));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicArcCosineDefinition(
        Term const& term)
{
    Term leftSideTerm(arccosh(term));
    Term insideSquareRoot(createExpressionIfPossible({term, Term("^"), Term(2), Term("-"), Term(1)}));
    Term squareRootTerm(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term insideLogarithm(createExpressionIfPossible({term, Term("+"), squareRootTerm}));
    Term rightSideTerm(ln(insideLogarithm));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicArcTangentDefinition(
        Term const& term)
{
    Term leftSideTerm(arctanh(term));
    Term oneMinusTerm(createExpressionIfPossible({Term(1), Term("-"), term}));
    Term onePlusTerm(createExpressionIfPossible({Term(1), Term("+"), term}));
    Term insideLogarithm(createExpressionIfPossible({oneMinusTerm, Term("/"), onePlusTerm}));
    Term logarithmTerm(ln(insideLogarithm));
    Term rightSideTerm(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("*"), logarithmTerm}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getHyperbolicArcCotangentDefinition(
        Term const& term)
{
    Term leftSideTerm(arccoth(term));
    Term termPlusOne(createExpressionIfPossible({term, Term("+"), Term(1)}));
    Term termMinusOne(createExpressionIfPossible({term, Term("-"), Term(1)}));
    Term insideLogarithm(createExpressionIfPossible({termPlusOne, Term("/"), termMinusOne}));
    Term logarithmTerm(ln(insideLogarithm));
    Term rightSideTerm(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("*"), logarithmTerm}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

}

}
