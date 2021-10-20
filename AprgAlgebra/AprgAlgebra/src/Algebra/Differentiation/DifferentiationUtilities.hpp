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

bool isFirstOrderDifferentialEquation(
        Equation const& equation,
        std::string const& xVariableName,
        std::string const& yVariableName);

Term getDerivativeDefinition(
        Term const& term,
        std::string const& variableName);

Term getDerivativeAtUsingLimit(
        Term const& term,
        std::string const& variableName,
        Term const& termSubstituteToBack,
        LimitAtAValueApproachType const approachType);

Term getDerivativeDefinitionForFiniteCalculus(
        Term const& term,
        std::string const& variableName);

Term getLogarithmicDifferentiationToYieldDyOverDx(
        Term const& yInTermsOfX,
        std::string const& xVariableName,
        std::string const& yVariableName);

SolutionSet getDifferentiabilityDomain(
        Term const& term,
        std::string const& variableName);

Equation getRelationshipOfDerivativeOfTheInverseAndTheDerivative(
        Term const& term,
        std::string const& variableName,
        std::string const& variableForNonInverse,
        std::string const& variableForInverse);

Equation getIntegralEquationForFirstOrderDifferentialEquation(
        Equation const& equation,
        std::string const& xVariableName,
        std::string const& yVariableName);

Equation getIntegralEquationForFirstOrderDifferentialEquation(
        Term const& p,
        Term const& q,
        std::string const& xVariableName,
        std::string const& yVariableName);

void simplifyDerivativeByDefinition(Term & term);

void simplifyToNonDoubleFactors(
        Term& term);

}

}
