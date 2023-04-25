#pragma once

#include <Algebra/Integration/DetailsForDefiniteIntegralWithValues.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba {

namespace algebra {

Term getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, unsigned int const numberOfSamples);

Term getAnApproximateOfDefiniteIntegralUsingSimpsonRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, unsigned int const numberOfSamples);

Term getActualTruncationErrorInTrapezoidalRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, unsigned int const numberOfSamples);

Term getActualTruncationErrorInSimpsonRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, unsigned int const numberOfSamples);

Term getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, AlbaNumber const& valueToCheckAt,
    AlbaNumber const& deltaX);

Term getAnApproximateOfTruncationErrorInSimpsonRuleAt(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, AlbaNumber const& valueToCheckAt,
    AlbaNumber const& deltaX);

AlbaNumber getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(
    AlbaNumber const& input, unsigned int const numberOfSamples);

AlbaNumber getAnApproximateOfNaturalLogarithmUsingSimpsonRule(
    AlbaNumber const& input, unsigned int const numberOfSamples);

}  // namespace algebra

}  // namespace alba
