#include "Limit.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

Term getLimitAsVariableApproachesTheValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();
    SubstitutionOfVariablesToValues substitution{{variableName, value}};

    Term limitValue(substitution.performSubstitutionTo(simplifiedTerm));
    if(hasNotANumber(limitValue))
    {
        PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(simplifiedTerm));
        if(popOptional.hasContent())
        {
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(
                        popOptional.getReference().simplifyAndDivide());
            limitValue = substitution.performSubstitutionTo(quotientAndRemainder.quotient);
        }
    }
    return limitValue;
}

}

}
