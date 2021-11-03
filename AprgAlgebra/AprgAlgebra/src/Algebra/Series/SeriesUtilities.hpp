#pragma once

#include <Algebra/Series/SeriesBasedOnSummation.hpp>
#include <Algebra/Series/SeriesBasedOnTerm.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba{

namespace algebra
{

bool isAxiomOfCompletenessTrue(
        SeriesBasedOnTerm const& series);

bool isBoundedMonotonicSeriesConvergent(
        SeriesBasedOnTerm const& series);

bool isConvergentMonotonicSeriesBounded(
        SeriesBasedOnTerm const& series);

bool isConvergentUsingComparisonTest(
        SeriesBasedOnSummation const& seriesToCheck,
        SeriesBasedOnSummation const& convergentSeries,
        unsigned int const numberOfIndexesToTest);

bool isDivergentUsingComparisonTest(
        SeriesBasedOnSummation const& seriesToCheck,
        SeriesBasedOnSummation const& divergentSeries,
        unsigned int const numberOfIndexesToTest);

void performLimitComparisonTest(
        bool & isConvergent,
        bool & isDivergent,
        SeriesBasedOnSummation const& series1,
        SeriesBasedOnSummation const& series2,
        std::string const& variableName);

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(
        Term const& firstTerm,
        Term const& lastTerm,        Term const& count);

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        Term const& firstValue,        Term const& commonMultiplier,
        int const count);

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        Term const& firstValue,
        Term const& commonMultiplier);

}

}
