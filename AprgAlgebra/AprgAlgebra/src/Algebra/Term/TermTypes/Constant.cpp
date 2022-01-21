#include "Constant.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

Constant::Constant()
{}

Constant::Constant(int const signedValue)
    : m_constantValue(signedValue)
{}

Constant::Constant(unsigned int const unsignedValue)
    : m_constantValue(unsignedValue)
{}

Constant::Constant(double const doubleValue)
    : m_constantValue(doubleValue)
{}

Constant::Constant(AlbaNumber const& constantValue)
    : m_constantValue(constantValue)
{}

bool Constant::operator==(Constant const& second) const
{
   return  m_constantValue == second.m_constantValue;
}

bool Constant::operator!=(Constant const& second) const
{
   return  m_constantValue != second.m_constantValue;
}

bool Constant::operator<(Constant const& second) const
{
    return m_constantValue < second.m_constantValue;
}

AlbaNumber const& Constant::getNumberConstReference() const
{
    return m_constantValue;
}

string Constant::getDisplayableString() const
{
    return m_constantValue.getDisplayableString();
}

void Constant::setNumber(AlbaNumber const& constantValue)
{
    m_constantValue = constantValue;
}

ostream & operator<<(ostream & out, Constant const& constant)
{
    out << constant.getDisplayableString();
    return out;
}

}

}
