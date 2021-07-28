#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

namespace Domain
{
    using FunctionToCheck=std::function<AlbaNumber(AlbaNumber const&)>;

    SolutionSet calculateDomainForTermWithOneVariable(
            Term const& term);
    SolutionSet calculateDomainForTermWithOneVariable(
            AlbaNumbers const& valuesToCheck,
            Term const& term);
    SolutionSet calculateDomain(
            AlbaNumbers const& valuesToCheck,
            FunctionToCheck const& functionToCheck);

    AlbaNumbers getTransitionValues(
            AlbaNumbers const& valuesToCheck,
            Domain::FunctionToCheck const& functionToCheck);
    AlbaNumber getTransitionValue(
            AlbaNumber const& inputValueYieldsToFiniteValue,
            AlbaNumber const& inputValueYieldsToNonFiniteValue,
            Domain::FunctionToCheck const& functionToCheck);

}

}

}
