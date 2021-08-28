#include "TermRaiseToANumber.hpp"

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

bool TermRaiseToANumber::isRadical() const
{
    return m_exponent.isDoubleType() || m_exponent.isFractionType();
}

Term TermRaiseToANumber::getBase() const
{
    return m_base;
}

AlbaNumber TermRaiseToANumber::getExponent() const
{
    return m_exponent;
}

}

}
