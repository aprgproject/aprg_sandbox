#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/AlbaNumber.hpp>
#include <Math/AlbaNumberTypes.hpp>

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
