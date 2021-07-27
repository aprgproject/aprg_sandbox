#include "SolutionUtilities.hpp"

#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;

namespace alba
{

namespace algebra
{

AlbaNumber getInitialValueForNewtonMethod(Term const& term)
{
    AlbaNumbersSet numbers(getNumbers(term));
    AlbaNumber initialValue(0);
    if(!numbers.empty())
    {
        initialValue = log(getAbsoluteValue((*numbers.cbegin()).getDouble()));
    }
    return initialValue;
}

}

}
