#pragma once

#include <Optional/AlbaOptional.hpp>
#include "CPlusPlusClass/CPlusPlusClass.hpp"
#include "CPlusPlusFunction/CPlusPlusFunction.hpp"
#include "CPlusPlusMacro.hpp"
#include "CPlusPlusNamespace.hpp"
#include "CPlusPlusVariable.hpp"
#include "CPlusPlusScope.hpp"
#include <functional>
#include <set>
#include <string>
#include <map>
#include <vector>
#include "../Utilities.hpp"

using std::string;
using std::set;
using std::map;
using std::pair;
using std::function;
using std::vector;

namespace codeReview
{

typedef set<string> IncludeFiles;
typedef string IncludeFile;
typedef map<string, CPlusPlusClass> Classes;
typedef pair<string, CPlusPlusClass> ClassPair;
typedef map<string, CPlusPlusTemplateClass> TemplateClasses;
typedef pair<string, CPlusPlusTemplateClass> TemplateClassPair;
typedef map<string, CPlusPlusFunction> Functions;
typedef pair<string, CPlusPlusFunction> FunctionPair;
typedef map<string, CPlusPlusMacro> Macros;
typedef pair<string, CPlusPlusMacro> MacroPair;
typedef map<string, CPlusPlusNamespace> Namespaces;
typedef pair<string, CPlusPlusNamespace> NamespacePair;
typedef map<string, CPlusPlusType> Types;
typedef pair<string, CPlusPlusType> TypePair;
typedef map<string, CPlusPlusVariable> Variables;
typedef pair<string, CPlusPlusVariable> VariablePair;
typedef vector<CPlusPlusScope> Scopes;

class CPlusPlusDatabase
{
public:
    CPlusPlusDatabase();
    void initializeCStyleArray();

    void print(ostream& outputStream);
    bool isDatabaseModified() const;
    bool isClass(string const& className) const;
    bool isClassWithAlias(string const& className);
    bool isFunction(string const& functionName) const;
    bool isFunctionWithAlias(string const& functionName);
    bool isMacro(string const& macroName) const;
    bool isNamespace(string const& namespaceName) const;
    bool isNamespaceWithAlias(string const& namespaceName);
    bool isType(string const& typeDefName) const;
    bool isVariable(string const& variableName) const;
    bool isVariableWithAlias(string const& variableName);
    bool isTemplateClass(string const& className) const;
    bool isTemplateClassWithAlias(string const& className);

    string getCorrectClassName(string const& className);
    string getCorrectTemplateClassName(string const& templateClassName);
    CPlusPlusClass& getClassReference(string const& className);
    CPlusPlusClass& getClassReferenceWithAlias(string const& className);
    CPlusPlusScope& getCurrentScope();
    CPlusPlusFunction& getFunctionReference(string const& functionName);
    CPlusPlusFunctionOptional getFunctionOptionalInClass(string const& className, string const& functionName);
    CPlusPlusFunctionOptional getFunctionOptionalInTemplateClass(string const& templateClassName, string const& functionName, int instantiationIndex);
    CPlusPlusFunction& getFunctionReferenceWithAlias(string const& functionName);
    CPlusPlusNamespace& getNamespaceReference(string const& namespaceName);
    CPlusPlusMacro& getMacroReference(string const& macroName);
    VectorOfTerms& getMacroEquivalentReference(string const& macroName);
    CPlusPlusTemplateClass& getTemplateClassReference(string const& className);
    CPlusPlusTemplateClass& getTemplateClassReferenceWithAlias(string const& className);
    CPlusPlusType& getTypeReferenceWithAlias(string const& typeName);
    CPlusPlusVariable& getVariableReferenceWithAlias(string const& variableName);

    Classes& getClassesReference();
    Functions& getFunctionsReference();
    IncludeFiles& getIncludeFilesReference();
    Macros& getMacrosReference();
    Namespaces& getNamespacesReference();
    TemplateClasses& getTemplateClassesReference();
    Types& getTypesReference();
    VectorOfStrings& getUsingNamespacesReference();
    Variables& getVariablesReference();

    void clearIsDatabaseModified();
    void addClass(string const& className);
    void addFunction(string const& functionName);
    void addIncludeFile(string const& includeFileName);
    void addMacro(string const& macroName);
    void addNamespace(string const& namespaceName);
    void addTemplateClass(string const& templateClassName, CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature);
    void addType(string const& typeDefName, CPlusPlusType const& type);
    void addUsingNamespace(string const& usingNamespace);
    void addVariable(string const& variableName, CPlusPlusType const& cPlusPlusType);
    void removeMacro(string const& macroName);
    void copyContentsOf(CPlusPlusDatabase const& cPlusPlusDatabase);
    void performInNewScope(function<void(void)> perform);
    void performInClass(string const& className, function<void(void)> perform);
    void performInNamespace(string const& namespaceName, function<void(void)> perform);
    void performInTemplateClass(string const& templateClassName, function<void(void)> perform);

private:
    void addClassToScope(string const& className);
    void addFunctionToScope(string const& functionName);
    void addNamespaceToScope(string const& namespaceName);
    void addTypeToScope(string const& namespaceName);
    void addVariableToScope(string const& variableName);
    string getAliasWithCurrentScope(string const& name);
    void enterScope(CPlusPlusScopeType const scopeType, string const& name);
    void exitScope();
    Classes m_classes;
    Functions m_functions;
    IncludeFiles m_includedFiles;
    Macros m_macros;
    Namespaces m_namespaces;
    TemplateClasses m_templateClasses;
    Types m_types;
    Variables m_variables;
    VectorOfStrings m_usingNamespaces;
    Scopes m_scopes;
    bool m_isModified;
};

}// namespace codeReview
