#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

enum class RootType
{
    RealRootsOnly,
    RealAndImaginaryRoots,
};

bool doesThePolynomialHaveOnlyOneConstant(Polynomial const& polynomial);
bool doesThePolynomialHaveOnlyOneVariable(Polynomial const& polynomial);
bool doesThePolynomialHaveDoubleValue(Polynomial const& polynomial);
bool doesOnePolynomialHaveADoubleValue(Polynomials const& polynomials);
bool hasAMonomialWithMultipleVariables(Polynomial const& polynomial);
bool hasAMonomialWithDegreeMoreThanOneOrFractional(Polynomial const& polynomial);
bool isOneMonomial(Polynomial const& polynomial);
bool isVariableExponentInMonomialFound(Polynomial const& polynomial, Monomial const& monomial);

Monomial getFirstMonomial(Polynomial const& polynomial);
AlbaNumber getMaxDegree(Polynomial const& polynomial);
AlbaNumber getDegreeForVariable(Polynomial const& polynomial, std::string const& variableName);
AlbaNumber getCoefficientOfVariableExponent(Polynomial const& polynomial, Monomial const& monomial);
AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(Polynomial const& polynomial, AlbaNumber const& value);

AlbaNumbers getRoots(RootType const rootType, Polynomial const& polynomial);
Polynomial raiseBinomialToAPowerUsingBinomialExpansion(
        Polynomial const& binomial,
        unsigned int const power);

void removeEmptyPolynomials(Polynomials & polynomials);

}

}
