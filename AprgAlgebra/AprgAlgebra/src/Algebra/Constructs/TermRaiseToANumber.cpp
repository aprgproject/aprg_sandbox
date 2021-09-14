#include "TermRaiseToANumber.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>

namespace alba
{
namespace algebra
{
TermRaiseToANumber::TermRaiseToANumber()
{}

TermRaiseToANumber::TermRaiseToANumber(
        Term const& base,
        AlbaNumber const& exponent)
    : m_base(base)
    , m_exponent(exponent)
{}

Term TermRaiseToANumber::getCombinedTerm() const
{
    return Term(createExpressionIfPossible({m_base, Term("^"), Term(m_exponent)}));
}

bool TermRaiseToANumber::isRadical() const
{
    return m_exponent.isDoubleType() || m_exponent.isFractionType();
}

Term const& TermRaiseToANumber::getBase() const
{
    return m_base;
}

AlbaNumber const& TermRaiseToANumber::getExponent() const
{
    return m_exponent;
}

void TermRaiseToANumber::setBase(Term const& base)
{
    m_base = base;
}

}

}