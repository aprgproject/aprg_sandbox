#pragma once

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>
namespace alba
{
namespace algebra
{

bool isDifferentiableAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

Term getDerivativeDefinition(
        Term const& term,
        std::string const& variableName,
        Term const& x);

Term getDerivativeUsingLimit(
        Term const& term,
        std::string const& variableName,
        Term const& x,
        LimitAtAValueApproachType const approachType);

void simplifyDerivativeByDefinition(Term & term);

}
}