#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba
{
namespace algebra
{
AlbaNumber getPositiveLogarithmOfLargestNumber(Term const& term);

AlbaNumbers getInitialValuesForIteratingMethods(Term const& term);
void retrieveInitialValuesForIteratingMethods(
        AlbaNumbersSet & allValues,
        Term const& term);

AlbaNumbers getInitialValuesForIteratingMethods(Equation const& equation);

}

}
