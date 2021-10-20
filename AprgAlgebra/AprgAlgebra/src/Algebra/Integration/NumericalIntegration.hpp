#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

Term getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        unsigned int const numberOfSamples);

Term getAnApproximateOfDefiniteIntegralUsingSimpsonRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        unsigned int const numberOfSamples);

Term getActualTruncationErrorInTrapezoidalRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        unsigned int const numberOfSamples);

Term getActualTruncationErrorInSimpsonRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        unsigned int const numberOfSamples);

Term getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        AlbaNumber const& valueToCheckAt,
        AlbaNumber const& deltaX);

Term getAnApproximateOfTruncationErrorInSimpsonRuleAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval,
        AlbaNumber const& valueToCheckAt,
        AlbaNumber const& deltaX);

AlbaNumber getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(
        AlbaNumber const& input,
        unsigned int const numberOfSamples);

AlbaNumber getAnApproximateOfNaturalLogarithmUsingSimpsonRule(
        AlbaNumber const& input,
        unsigned int const numberOfSamples);

}

}
