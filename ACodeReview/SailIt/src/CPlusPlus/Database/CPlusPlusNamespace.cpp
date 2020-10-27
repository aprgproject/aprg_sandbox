#include "CPlusPlusNamespace.hpp"

#include <algorithm>

using namespace std;

namespace codeReview
{

bool CPlusPlusNamespace::isVariable(string const& variableName) const
{
    return find(m_variables.begin(), m_variables.end(), variableName)!=m_variables.end();
}

bool CPlusPlusNamespace::isFunction(string const& functionName) const
{
    return find(m_functions.begin(), m_functions.end(), functionName)!=m_functions.end();
}

bool CPlusPlusNamespace::isClass(string const& className) const
{
    return find(m_classes.begin(), m_classes.end(), className)!=m_classes.end();
}

bool CPlusPlusNamespace::isNamespace(string const& namespaceName) const
{
    return find(m_namespaces.begin(), m_namespaces.end(), namespaceName)!=m_namespaces.end();
}

VectorOfStrings& CPlusPlusNamespace::getClassNamesReference()
{
    return m_classes;
}

VectorOfStrings& CPlusPlusNamespace::getFunctionNamesReference()
{
    return m_functions;
}

VectorOfStrings& CPlusPlusNamespace::getNamespaceNamesReference()
{
    return m_namespaces;
}

VectorOfStrings& CPlusPlusNamespace::getVariableNamesReference()
{
    return m_variables;
}

void CPlusPlusNamespace::addClass(string const& className)
{
    m_classes.push_back(className);
}

void CPlusPlusNamespace::addFunction(string const& functionName)
{
    m_functions.push_back(functionName);
}

void CPlusPlusNamespace::addNamespace(string const& namespaceName)
{
    m_namespaces.push_back(namespaceName);
}

void CPlusPlusNamespace::addVariable(string const& variableName)
{
    m_variables.push_back(variableName);
}

}
