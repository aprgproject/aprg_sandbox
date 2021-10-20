#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isTheFirstFundamentalTheoremOfCalculusTrue(
        Term const& term,
        std::string const& variableName);

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

Equation getRelationshipOfDerivativeOfTheInverseAndTheDerivative(
        Term const& term,
        std::string const& variableName,
        std::string const& variableForNonInverse,
        std::string const& variableForInverse);

void simplifyDerivativeByDefinition(Term & term);

Term performLogarithmicDifferentiationToYieldDyOverDx(
        Term const& yInTermsOfX,
        std::string const& xVariableName,
        std::string const& yVariableName);

}

}
