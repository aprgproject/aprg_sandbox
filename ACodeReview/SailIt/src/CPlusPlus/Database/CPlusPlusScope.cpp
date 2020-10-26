#include "CPlusPlusScope.hpp"

namespace codeReview
{

CPlusPlusScope::CPlusPlusScope(CPlusPlusScopeType const scopeType, string const& name)
    : m_scopeType(scopeType)
    , m_name(name)
{}

bool CPlusPlusScope::isClass() const
{
    return CPlusPlusScopeType::Class == m_scopeType;
}

bool CPlusPlusScope::isSpecializedScope() const
{
    return isClass() || isNamespace() || isTemplateClass();
}

bool CPlusPlusScope::isGlobal() const
{
    return CPlusPlusScopeType::Global == m_scopeType;
}

bool CPlusPlusScope::isNamespace() const
{
    return CPlusPlusScopeType::Namespace == m_scopeType;
}

bool CPlusPlusScope::isTemplateClass() const
{
    return CPlusPlusScopeType::TemplateClass == m_scopeType;
}

string CPlusPlusScope::getName() const
{
    return m_name;
}

string CPlusPlusScope::getAliasForThisScope(string const& name) const
{
    if(!m_name.empty())
    {
        return m_name + "::" + name;
    }
    return name;
}

VectorOfStrings& CPlusPlusScope::getClassNamesReference()
{
    return m_classes;
}

VectorOfStrings& CPlusPlusScope::getFunctionNamesReference()
{
    return m_functions;
}

VectorOfStrings& CPlusPlusScope::getNamespaceNamesReference()
{
    return m_namespaces;
}

VectorOfStrings& CPlusPlusScope::getTypeNamesReference()
{
    return m_types;
}

VectorOfStrings& CPlusPlusScope::getVariableNamesReference()
{
    return m_variables;
}

void CPlusPlusScope::addClass(string const& className)
{
    m_classes.push_back(className);
}

void CPlusPlusScope::addFunction(string const& functionName)
{
    m_functions.push_back(functionName);
}

void CPlusPlusScope::addNamespace(string const& namespaceName)
{
    m_namespaces.push_back(namespaceName);
}

void CPlusPlusScope::addType(string const& typeName)
{
    m_types.push_back(typeName);
}

void CPlusPlusScope::addVariable(string const& variableName)
{
    m_variables.push_back(variableName);
}

}


