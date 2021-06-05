#include "Constant.hpp"

using namespace std;

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

bool Constant::operator==(Constant const& second) const
{
   return  m_constantValue == second.m_constantValue;
}

string Constant::getDisplayableString() const
{
    return m_constantValue.getDisplayableString();
}

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
