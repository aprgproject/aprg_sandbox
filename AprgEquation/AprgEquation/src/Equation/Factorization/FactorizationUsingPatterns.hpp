#pragma once

#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizeUsingPatterns(Polynomial const& polynomial);
Polynomials factorizeUsingPatternsIfPossible(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfSquaresIfPossible(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfCubesIfPossible(Polynomial const& polynomial);
Polynomials factorizeSumOfCubesIfPossible(Polynomial const& polynomial);
void addFactorsOfDifferenceOfSquares(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfDifferenceOfCubes(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfSumOfCubes(Polynomials & result, Polynomial const& polynomial);
bool isDifferenceOfSquares(Polynomial const& polynomial);
bool isDifferenceOfCubes(Polynomial const& polynomial);
bool isSumOfCubes(Polynomial const& polynomial);

}

}

}
