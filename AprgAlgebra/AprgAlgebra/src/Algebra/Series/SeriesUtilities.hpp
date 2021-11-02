#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(
        Term const& firstTerm,
        Term const& lastTerm,
        Term const& count);

double getSumOfArithmeticSeriesUsingFirstAndLastValue(
        double const firstValue,
        double const lastValue,
        int const count);
double getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        double const firstValue,
        double const commonMultiplier,
        int const count);
double getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        double const firstValue,
        double const commonMultiplier);

}

}
