#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumber.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{
namespace algebra
{

AlbaNumber getPositiveLogarithmOfLargestNumber(Term const& term);
AlbaNumbers getValuesForDomainSearching(Term const& term);

}
}