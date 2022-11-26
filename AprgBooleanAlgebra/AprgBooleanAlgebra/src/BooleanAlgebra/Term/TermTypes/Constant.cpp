#include "Constant.hpp"

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

Constant::Constant()
    : m_booleanValue{}
{}

Constant::Constant(bool const boolValue)
    : m_booleanValue(boolValue)
{}

bool Constant::operator==(Constant const& second) const
{
   return  m_booleanValue == second.m_booleanValue;
}

bool Constant::operator!=(Constant const& second) const
{
   return  m_booleanValue != second.m_booleanValue;
}

bool Constant::operator<(Constant const& second) const
{
    return m_booleanValue < second.m_booleanValue;
}

Constant Constant::operator~() const
{
    Constant result(*this);
    result.negate();
    return result;
}

bool Constant::getBooleanValue() const
{
    return m_booleanValue;
}

void Constant::setValue(bool const boolValue)
{
    m_booleanValue = boolValue;
}

void Constant::negate()
{
    m_booleanValue = !m_booleanValue;
}

ostream & operator<<(ostream & out, Constant const& constant)
{
    if(constant.m_booleanValue)
    {
        out << "[true]";
    }
    else
    {
        out << "[false]";
    }
    return out;
}

}

}
