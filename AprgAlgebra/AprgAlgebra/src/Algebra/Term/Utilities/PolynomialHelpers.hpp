#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

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

AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(
        Polynomial const& polynomial,
        AlbaNumber const& value);

AlbaNumbers getRoots(RootType const rootType, Polynomial const& polynomial);
Polynomial raiseBinomialToAPowerUsingBinomialExpansion(
        Polynomial const& binomial,
        unsigned int const power);

void removeEmptyPolynomials(Polynomials & polynomials);

}

}
