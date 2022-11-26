#include "Constant.hpp"

#include <sstream>

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

void Constant::setNumber(AlbaNumber const& constantValue)
{
    m_constantValue = constantValue;
}

ostream & operator<<(ostream & out, Constant const& constant)
{
    out << constant.m_constantValue;
    return out;
}

}

}
