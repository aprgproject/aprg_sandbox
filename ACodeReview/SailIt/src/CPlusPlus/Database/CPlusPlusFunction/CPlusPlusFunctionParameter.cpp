#include "CPlusPlusFunctionParameter.hpp"

namespace codeReview
{

CPlusPlusFunctionParameter::CPlusPlusFunctionParameter(CPlusPlusType const& type, string const& name)
    : m_type(type)
    , m_name(name)
{}

bool CPlusPlusFunctionParameter::operator==(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const
{
    return m_type == cPlusPlusFunctionParameter.m_type;
}

bool CPlusPlusFunctionParameter::isEqualBasedFromFunctionCall(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const
{
    return m_type.isEqualIgnoreReference(cPlusPlusFunctionParameter.m_type);
}

bool CPlusPlusFunctionParameter::areTheNamesEqual(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const
{
    return m_name == cPlusPlusFunctionParameter.m_name;
}

string CPlusPlusFunctionParameter::getName() const
{
    return m_name;
}

CPlusPlusType CPlusPlusFunctionParameter::getType() const
{
    return m_type;
}

void CPlusPlusFunctionParameter::set(CPlusPlusType const& type, string const& name)
{
    m_type = type;
    m_name = name;
}

}


