#include "Constant.hpp"

namespace alba
{

namespace equation
{

Constant::Constant()
{}

Constant::Constant(AlbaNumber const& constantValue)
    : m_constantValue(constantValue)
{}

Constant::Constant(int const signedValue)
    : m_constantValue(signedValue)
{}

Constant::Constant(unsigned int const unsignedValue)
    : m_constantValue(unsignedValue)
{}

Constant::Constant(int const numerator, unsigned int const denominator)
    : m_constantValue(numerator, denominator)
{}

Constant::Constant(double const doubleValue)
    : m_constantValue(doubleValue)
{}

AlbaNumber const& Constant::getNumberConstReference() const
{
    return m_constantValue;
}

void Constant::setNumber(AlbaNumber const& constantValue)
{
    m_constantValue = constantValue;
}

}

}
