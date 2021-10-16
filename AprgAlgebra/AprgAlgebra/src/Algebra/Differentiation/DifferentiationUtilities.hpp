#pragma once

#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
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
        std::string const& variableName);

Term getDerivativeAtUsingLimit(
        Term const& term,
        std::string const& variableName,
        Term const& termSubstituteToBack,
        LimitAtAValueApproachType const approachType);

void simplifyDerivativeByDefinition(Term & term);
}

}