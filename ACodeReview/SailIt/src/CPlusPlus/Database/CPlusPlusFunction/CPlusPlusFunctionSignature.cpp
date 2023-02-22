#include "CPlusPlusFunctionSignature.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

namespace codeReview
{

void CPlusPlusFunctionSignature::printSignature() const
{
    cout<<"FunctionSignature: [ReturnType: " << m_returnType << "]";
    for(CPlusPlusFunctionParameter const& parameter : m_parameters)
    {
        cout<<"[Name: "<<parameter.getName()<<" Type: "<<parameter.getType()<<"]";
    }
    cout<<"\n";
}

CPlusPlusType& CPlusPlusFunctionSignature::getReturnTypeReference()
{
    return m_returnType;
}

CPlusPlusType CPlusPlusFunctionSignature::getReturnType() const
{
    return m_returnType;
}

void CPlusPlusFunctionSignature::setReturnType(CPlusPlusType const& type)
{
    m_returnType = type;
}

void CPlusPlusFunctionSignature::addParameter(CPlusPlusType const& type)
{
    m_parameters.emplace_back(type, "");
}

void CPlusPlusFunctionSignature::addParameter(CPlusPlusType const& type, string const& name)
{
    m_parameters.emplace_back(type, name);
}

bool CPlusPlusFunctionSignature::operator==(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    if(!(m_returnType == cPlusPlusFunctionSignature.m_returnType))
    {
        return false;
    }
    if(m_parameters.size() != cPlusPlusFunctionSignature.m_parameters.size())
    {
        return false;
    }
    auto const& parameters = cPlusPlusFunctionSignature.m_parameters;
    auto mismatchPair = std::mismatch (m_parameters.cbegin(), m_parameters.cend(), parameters.cbegin());
    return mismatchPair.first == m_parameters.end();
}

bool CPlusPlusFunctionSignature::isEqualBasedFromFunctionCall(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    unsigned int size = m_parameters.size();
    if(size != cPlusPlusFunctionSignature.m_parameters.size())
    {
        return false;
    }
    auto const& parameters = cPlusPlusFunctionSignature.m_parameters;
    auto it1 = m_parameters.cbegin();
    auto it2 = parameters.cbegin();
    while(it1!=m_parameters.cend())
    {
        if(!(it1->isEqualBasedFromFunctionCall(*it2)))
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}
bool CPlusPlusFunctionSignature::areTheNamesEqual(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    unsigned int size = m_parameters.size();
    if(size != cPlusPlusFunctionSignature.m_parameters.size())
    {
        return false;
    }
    auto const& parameters = cPlusPlusFunctionSignature.m_parameters;
    auto it1 = m_parameters.cbegin();
    auto it2 = parameters.cbegin();
    while(it1!=m_parameters.cend())
    {
        if(!(it1->areTheNamesEqual(*it2)))
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}

CPlusPlusFunctionParameters& CPlusPlusFunctionSignature::getFunctionParametersReference()
{
    return m_parameters;
}

}
