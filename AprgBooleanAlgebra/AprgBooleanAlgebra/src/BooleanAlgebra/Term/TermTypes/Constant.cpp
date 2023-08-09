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

bool Constant::getBooleanValue() const
{
    return m_booleanValue;
}

string Constant::getDisplayableString() const
{
    if(m_booleanValue)
    {
        return "[true]";
    }
    else
    {
        return "[false]";
    }
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
    out << constant.getDisplayableString();
    return out;
}

}

}
