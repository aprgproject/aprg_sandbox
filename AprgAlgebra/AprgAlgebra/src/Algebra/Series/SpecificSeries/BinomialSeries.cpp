#include "BinomialSeries.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

BinomialSeries::BinomialSeries(Term const& monomialPart, Term const& exponent)
    : m_monomialPart(monomialPart)
    , m_exponent(exponent)
{}

Term BinomialSeries::getMonomialPart() const
{
    return m_monomialPart;
}

Term BinomialSeries::getExponent() const
{
    return m_exponent;
}

Term BinomialSeries::getValueAtIndex(int const index) const
{
    Term result;
    if(index >= 0)
    {
        unsigned int positiveIndex(static_cast<unsigned int>(index));
        result = getBinomialSeriesApproximation(m_monomialPart, m_exponent, positiveIndex);
    }
    return result;
}

Term BinomialSeries::getBinomialSeriesApproximation(
        Term const& monomialPart,
        Term const& exponent,
        unsigned int const numberOfTimes) const
{
    // Approximation:
    // (1+x)^m = Summation of [m*(m-1)*(m-2)....(m-n+1) * (x^n)/(n!)] until n reaches infinity
    Term result(1);
    Term partialProduct(1);
    Term monomialPartRaiseToPower(1);
    AlbaNumber factorialValue(1);
    for(unsigned int n=1; n<=numberOfTimes; n++)
    {
        monomialPartRaiseToPower *= monomialPart;
        Term multiplier(exponent - n + 1);
        partialProduct *= multiplier;
        factorialValue *= n;
        Term currentTerm(partialProduct * monomialPartRaiseToPower / factorialValue);
        result += currentTerm;
    }
    result.simplify();
    return result;
}


}

}
