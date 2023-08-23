#pragma once

#include "../Utilities.hpp"

#include <map>
#include <string>

using std::map;
using std::pair;
using std::string;

namespace codeReview {

enum class CPlusPlusScopeType { Class, Global, Normal, Namespace, TemplateClass };

class CPlusPlusScope {
public:
    CPlusPlusScope(CPlusPlusScopeType const scopeType, string const& name);
    bool isClass() const;
    bool isSpecializedScope() const;
    bool isGlobal() const;
    bool isNamespace() const;
    bool isTemplateClass() const;
    string getName() const;
    string getAliasForThisScope(string const& name) const;

    VectorOfStrings& getClassNamesReference();
    VectorOfStrings& getFunctionNamesReference();
    VectorOfStrings& getNamespaceNamesReference();
    VectorOfStrings& getTypeNamesReference();
    VectorOfStrings& getVariableNamesReference();

    void addClass(string const& className);
    void addFunction(string const& functionName);
    void addNamespace(string const& namespaceName);
    void addType(string const& typeName);
    void addVariable(string const& variableName);

private:
    CPlusPlusScopeType m_scopeType;
    string m_name;
    VectorOfStrings m_classes;
    VectorOfStrings m_functions;
    VectorOfStrings m_namespaces;
    VectorOfStrings m_types;
    VectorOfStrings m_variables;
};

}  // namespace codeReview
