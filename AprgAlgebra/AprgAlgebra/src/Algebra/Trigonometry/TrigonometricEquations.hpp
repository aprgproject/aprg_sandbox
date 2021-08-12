#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

Equation getSineSquaredPlusCosineSquaredEqualsOne(Term const& term);
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
