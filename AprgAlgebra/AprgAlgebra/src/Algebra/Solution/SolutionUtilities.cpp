#include "SolutionUtilities.hpp"

#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

AlbaNumber getPositiveLogarithmOfLargestNumber(Term const& term)
{
    AlbaNumbersSet numbers(getNumbers(term));
    AlbaNumber initialValue(0);
    if(!numbers.empty())
    {
        initialValue = log(getAbsoluteValue((*numbers.cbegin()).getDouble()));
    }
    return initialValue;
}

AlbaNumbers getValuesForDomainSearching(Term const& term)
{
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveValuesForDomainSearching(allValues, term);
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

void retrieveValuesForDomainSearching(
        AlbaNumbersSet & allValues,
        Term const& term)
{
    AlbaNumbersSet numbers(getNumbers(term));
    for(AlbaNumber const& number : numbers)
    {
        AlbaNumber positiveNumber(getAbsoluteValue(number));
        AlbaNumber positiveLogarithm(log(positiveNumber.getDouble()));
        allValues.emplace(positiveNumber*-1);
        allValues.emplace(positiveLogarithm*-1);
        allValues.emplace(positiveLogarithm);
        allValues.emplace(positiveNumber);
    }
}

AlbaNumbers getValuesForDomainSearching(Equation const& equation)
{
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveValuesForDomainSearching(allValues, equation.getLeftHandTerm());
    retrieveValuesForDomainSearching(allValues, equation.getRightHandTerm());
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

}

}
