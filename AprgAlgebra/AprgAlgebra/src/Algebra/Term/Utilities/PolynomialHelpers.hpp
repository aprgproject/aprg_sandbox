#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

bool doesThePolynomialHaveOnlyOneVariable(Polynomial const& polynomial);
AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(
        Polynomial const& polynomial,
        AlbaNumber const& value);
AlbaNumbers getRoots(Polynomial const& polynomial);

}

}
