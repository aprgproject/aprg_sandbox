#pragma once

#include "../Utilities.hpp"

#include <map>
#include <string>

using std::string;
using std::map;
using std::pair;

namespace codeReview
{

class CPlusPlusNamespace
{
public:
    bool isVariable(string const& variableName) const;
    bool isFunction(string const& functionName) const;
    bool isClass(string const& className) const;
    bool isNamespace(string const& namespaceName) const;

    VectorOfStrings& getVariableNamesReference();
    VectorOfStrings& getFunctionNamesReference();
    VectorOfStrings& getClassNamesReference();
    VectorOfStrings& getNamespaceNamesReference();

    void addVariable(string const& variableName);
    void addFunction(string const& functionName);
    void addClass(string const& className);
    void addNamespace(string const& namespaceName);

private:
    VectorOfStrings m_variables;
    VectorOfStrings m_functions;
    VectorOfStrings m_classes;
    VectorOfStrings m_namespaces;
};

}
