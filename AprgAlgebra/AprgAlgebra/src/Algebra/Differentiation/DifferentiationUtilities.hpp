#pragma once

#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
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

Term getDerivativeDefinitionForFiniteCalculus(
        Term const& term,
        std::string const& variableName);

Term getDerivativeAtUsingLimit(
        Term const& term,
        std::string const& variableName,
        Term const& termSubstituteToBack,
        LimitAtAValueApproachType const approachType);

SolutionSet getDifferentiabilityDomain(
        Term const& term,
        std::string const& variableName);

void simplifyDerivativeByDefinition(Term & term);

}

}
