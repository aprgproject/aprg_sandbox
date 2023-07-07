#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

Term getSummationOfArithmeticSeries(std::string const& countVariable);
Term getSummationOfArithmeticSeriesForSquares(std::string const& countVariable);
Term getSummationOfArithmeticSeriesForCubes(std::string const& countVariable);
Term getSummationOfFiniteGeometricSeries(std::string const& base, std::string const& exponent);
Term getSummationOfInfiniteGeometricSeries(std::string const& base);
Term getSummationOfHarmonicSeries(std::string const& countVariable);

}  // namespace algebra

}  // namespace alba
