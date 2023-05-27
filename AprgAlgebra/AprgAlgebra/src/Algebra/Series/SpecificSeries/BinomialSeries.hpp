#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class BinomialSeries {
public:
    BinomialSeries(Term const& monomialPart, Term const& exponent);

    Term getMonomialPart() const;
    Term getExponent() const;
    Term getValueAtIndex(int const index) const;

protected:
    Term getBinomialSeriesApproximation(
        Term const& monomialPart, Term const& exponent, int const numberOfTimes) const;

    Term m_monomialPart;
    Term m_exponent;};

}  // namespace algebra
}  // namespace alba
