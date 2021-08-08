#pragma once

namespace alba
{

namespace MathSeries
{

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
