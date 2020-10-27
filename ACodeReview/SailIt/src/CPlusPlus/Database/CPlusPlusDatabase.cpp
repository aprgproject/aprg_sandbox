#include "CPlusPlusDatabase.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

namespace codeReview
{

CPlusPlusDatabase::CPlusPlusDatabase()
    : m_isModified(true)
{
    m_scopes.emplace_back(CPlusPlusScopeType::Global, "");

    initializeCStyleArray();
}

void CPlusPlusDatabase::initializeCStyleArray()
{
    CPlusPlusClassTemplateSignature templateSignature;
    templateSignature.addParameter(CPlusPlusType("__CStyleArray_ElementType", CPlusPlusTypeType::TemplateType), "__CStyleArray_ElementType");
    addTemplateClass("__CStyleArray", templateSignature);
    performInTemplateClass("__CStyleArray", [&]()
    {
        addFunction("operator[]");
        CPlusPlusFunction& cPlusPlusFunction(getFunctionReferenceWithAlias("operator[]"));
        CPlusPlusFunctionSignature cPlusPlusFunctionSignature;
        cPlusPlusFunctionSignature.setReturnType(CPlusPlusType("__CStyleArray_ElementType", CPlusPlusTypeType::TemplateType));
        cPlusPlusFunctionSignature.addParameter(CPlusPlusType("int", CPlusPlusTypeType::Primitive), "__CStyleArray_Index");
        cPlusPlusFunction.addFunctionSignature(cPlusPlusFunctionSignature);
    });
}

void CPlusPlusDatabase::print(ostream& outputStream)
{
    //accumulate anyone?
    outputStream<<"Include Files: ";
    copy(m_includedFiles.begin(), m_includedFiles.end(), std::ostream_iterator<IncludeFile>(outputStream, ", "));
    outputStream<<endl;
    outputStream<<"Variables: ";
    for(VariablePair variablePair :m_variables)
    {
        outputStream<<variablePair.first<<", ";
    }
    outputStream<<endl;
    outputStream<<"Functions: ";
    for(FunctionPair functionPair :m_functions)
    {
        outputStream<<functionPair.first<<", ";
    }
    outputStream<<endl;
    outputStream<<"Macros: ";
    for(MacroPair macroPair :m_macros)
    {
        outputStream<<macroPair.first<<", ";
    }
    outputStream<<endl;
    outputStream<<"Types: ";
    for(TypePair typePair :m_types)
    {
        outputStream<<typePair.first<<", ";
    }
    outputStream<<endl;
}

bool CPlusPlusDatabase::isDatabaseModified() const
{
    return m_isModified;
}

bool CPlusPlusDatabase::isClass(string const& className) const
{
    return m_classes.find(className) != m_classes.end();
}

bool CPlusPlusDatabase::isClassWithAlias(string const& className)
{
    if(isClass(getAliasWithCurrentScope(className)))
    {
        return true;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        if(isNamespace(usingNamespace) && isClass(usingNamespace+"::"+className))
        {
            return true;
        }
    }
    if(isClass(className))
    {
        return true;
    }
    return false;
}

bool CPlusPlusDatabase::isFunction(string const& functionName) const
{
    return m_functions.find(functionName) != m_functions.end();
}

bool CPlusPlusDatabase::isFunctionWithAlias(string const& functionName)
{
    if(isFunction(getAliasWithCurrentScope(functionName)))
    {
        return true;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        if(isNamespace(usingNamespace) && isFunction(usingNamespace+"::"+functionName))
        {
            return true;
        }
    }
    if(isFunction(functionName))
    {
        return true;
    }
    return false;
}

bool CPlusPlusDatabase::isMacro(string const& macroName) const
{
    return m_macros.find(macroName) != m_macros.end();
}

bool CPlusPlusDatabase::isNamespace(string const& namespaceName) const
{
    return m_namespaces.find(namespaceName) != m_namespaces.end();
}

bool CPlusPlusDatabase::isNamespaceWithAlias(string const& namespaceName)
{
    if(isNamespace(getAliasWithCurrentScope(namespaceName)))
    {
        return true;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        if(isNamespace(usingNamespace) && isNamespace(usingNamespace+"::"+namespaceName))
        {
            return true;
        }
    }
    if(isNamespace(namespaceName))
    {
        return true;
    }
    return false;
}

bool CPlusPlusDatabase::isTemplateClass(string const& className) const
{
    return m_templateClasses.find(className) != m_templateClasses.end();
}

bool CPlusPlusDatabase::isTemplateClassWithAlias(string const& className)
{
    if(isTemplateClass(getAliasWithCurrentScope(className)))
    {
        return true;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        if(isNamespace(usingNamespace) && isTemplateClass(usingNamespace+"::"+className))
        {
            return true;
        }
    }
    if(isTemplateClass(className))
    {
        return true;
    }
    return false;
}

bool CPlusPlusDatabase::isType(string const& typeName) const
{
    return m_types.find(typeName) != m_types.end();
}

bool CPlusPlusDatabase::isVariable(string const& variableName) const
{
    return m_variables.find(variableName) != m_variables.end();
}

bool CPlusPlusDatabase::isVariableWithAlias(string const& variableName)
{
    if(isVariable(getAliasWithCurrentScope(variableName)))
    {
        return true;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        if(isNamespace(usingNamespace) && isVariable(usingNamespace+"::"+variableName))
        {
            return true;
        }
    }
    if(isVariable(variableName))
    {
        return true;
    }
    return false;
}

string CPlusPlusDatabase::getCorrectClassName(string const& className)
{
    string const classNameAlias = getAliasWithCurrentScope(className);
    if(isClass(classNameAlias))
    {
        return classNameAlias;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string const usingNamespaceAlias = usingNamespace+"::"+className;
        if(isNamespace(usingNamespace) && isClass(usingNamespaceAlias))
        {
            return usingNamespaceAlias;
        }
    }
    return className;
}

string CPlusPlusDatabase::getCorrectTemplateClassName(string const& templateClassName)
{
    string const templateClassNameAlias = getAliasWithCurrentScope(templateClassName);
    if(isTemplateClass(templateClassNameAlias))
    {
        return templateClassNameAlias;
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string const usingNamespaceAlias = usingNamespace+"::"+templateClassName;
        if(isNamespace(usingNamespace) && isTemplateClass(usingNamespaceAlias))
        {
            return usingNamespaceAlias;
        }
    }
    return templateClassName;
}

CPlusPlusClass& CPlusPlusDatabase::getClassReference(string const& className)
{
    return m_classes[className];
}

CPlusPlusClass& CPlusPlusDatabase::getClassReferenceWithAlias(string const& className)
{
    string classAlias(getAliasWithCurrentScope(className));
    if(isClass(classAlias))
    {
        return m_classes[classAlias];
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string classNameWithUsingNamespace(usingNamespace+"::"+className);
        if(isNamespace(usingNamespace) && isClass(classNameWithUsingNamespace))
        {
            return m_classes[classNameWithUsingNamespace];
        }
    }
    return m_classes[className];
}

CPlusPlusScope& CPlusPlusDatabase::getCurrentScope()
{
    return m_scopes.back();
}

CPlusPlusFunction& CPlusPlusDatabase::getFunctionReference(string const& functionName)
{
    return m_functions[functionName];
}

CPlusPlusFunctionOptional CPlusPlusDatabase::getFunctionOptionalInClass(string const& className, string const& functionName)
{
    CPlusPlusFunctionOptional functionOptional;
    if(isClassWithAlias(className))
    {
        string const correctFunctionName = getCorrectClassName(className) + "::" + functionName;
        if(isFunction(correctFunctionName))
        {
            functionOptional.setReference(m_functions[correctFunctionName]);
        }
    }
    return functionOptional;
}

CPlusPlusFunctionOptional CPlusPlusDatabase::getFunctionOptionalInTemplateClass(string const& templateClassName, string const& functionName, int instantiationIndex)
{
    CPlusPlusFunctionOptional functionOptional;
    if(isTemplateClassWithAlias(templateClassName))
    {
        string const correctFunctionName = getCorrectTemplateClassName(templateClassName) + "::" + functionName;
        if(isFunction(correctFunctionName))
        {
            CPlusPlusTemplateClass templateClass = getTemplateClassReference(templateClassName);
            CPlusPlusFunction myFunction = m_functions[correctFunctionName];
            myFunction.replaceTemplateParameters(
                        templateClass.getTemplateSignatureReference(),
                        templateClass.getTemplateSignatureInstantiationReference(instantiationIndex));
            functionOptional.setReference(myFunction);
        }
    }
    return functionOptional;
}

CPlusPlusFunction& CPlusPlusDatabase::getFunctionReferenceWithAlias(string const& functionName)
{
    string functionAlias(getAliasWithCurrentScope(functionName));
    if(isFunction(functionAlias))
    {
        return m_functions[functionAlias];
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string functionNameWithUsingNamespace(usingNamespace+"::"+functionName);
        if(isNamespace(usingNamespace) && isFunction(functionNameWithUsingNamespace))
        {
            return m_functions[functionNameWithUsingNamespace];
        }
    }
    return m_functions[functionName];
}

CPlusPlusNamespace& CPlusPlusDatabase::getNamespaceReference(string const& namespaceName)
{
    return m_namespaces[namespaceName];
}

CPlusPlusMacro& CPlusPlusDatabase::getMacroReference(string const& macroName)
{
    return m_macros[macroName];
}

VectorOfTerms& CPlusPlusDatabase::getMacroEquivalentReference(string const& macroName)
{
    return m_macros[macroName].getMacroEquivalent();
}

CPlusPlusTemplateClass& CPlusPlusDatabase::getTemplateClassReference(string const& className)
{
    return m_templateClasses[className];
}

CPlusPlusTemplateClass& CPlusPlusDatabase::getTemplateClassReferenceWithAlias(string const& className)
{
    string templateClassAlias(getAliasWithCurrentScope(className));
    if(isTemplateClass(templateClassAlias))
    {
        return m_templateClasses[templateClassAlias];
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string classNameWithUsingNamespace(usingNamespace+"::"+className);
        if(isNamespace(usingNamespace) && isTemplateClass(classNameWithUsingNamespace))
        {
            return m_templateClasses[classNameWithUsingNamespace];
        }
    }
    return m_templateClasses[className];
}

CPlusPlusType& CPlusPlusDatabase::getTypeReferenceWithAlias(string const& typeName)
{
    string typeAlias(getAliasWithCurrentScope(typeName));
    if(isType(typeAlias))
    {
        return m_types[typeAlias];
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string typeNameWithUsingNamespace(usingNamespace+"::"+typeName);
        if(isNamespace(usingNamespace) && isType(typeNameWithUsingNamespace))
        {
            return m_types[typeNameWithUsingNamespace];
        }
    }
    return m_types[typeName];
}

CPlusPlusVariable& CPlusPlusDatabase::getVariableReferenceWithAlias(string const& variableName)
{
    string variableAlias(getAliasWithCurrentScope(variableName));
    if(isVariable(variableAlias))
    {
        return m_variables[variableAlias];
    }
    for(string const& usingNamespace : m_usingNamespaces)
    {
        string variableNameWithUsingNamespace(usingNamespace+"::"+variableName);
        if(isNamespace(usingNamespace) && isVariable(variableNameWithUsingNamespace))
        {
            return m_variables[variableNameWithUsingNamespace];
        }
    }
    return m_variables[variableName];
}

Classes& CPlusPlusDatabase::getClassesReference()
{
    return m_classes;
}

Functions& CPlusPlusDatabase::getFunctionsReference()
{
    return m_functions;
}

IncludeFiles& CPlusPlusDatabase::getIncludeFilesReference()
{
    return m_includedFiles;
}

Macros& CPlusPlusDatabase::getMacrosReference()
{
    return m_macros;
}

Namespaces& CPlusPlusDatabase::getNamespacesReference()
{
    return m_namespaces;
}

TemplateClasses& CPlusPlusDatabase::getTemplateClassesReference()
{
    return m_templateClasses;
}

Types& CPlusPlusDatabase::getTypesReference()
{
    return m_types;
}

VectorOfStrings& CPlusPlusDatabase::getUsingNamespacesReference()
{
    return m_usingNamespaces;
}

Variables& CPlusPlusDatabase::getVariablesReference()
{
    return m_variables;
}

void CPlusPlusDatabase::clearIsDatabaseModified()
{
    m_isModified = false;
}

void CPlusPlusDatabase::addClass(string const& className)
{
    m_isModified = true;
    m_classes.emplace(getAliasWithCurrentScope(className), CPlusPlusClass(className));
    addClassToScope(className);
}

void CPlusPlusDatabase::addFunction(string const& functionName)
{
    m_isModified = true;
    m_functions.emplace(getAliasWithCurrentScope(functionName), CPlusPlusFunction());
    addFunctionToScope(functionName);
}

void CPlusPlusDatabase::addIncludeFile(string const& includeFileName)
{
    m_isModified = true;
    m_includedFiles.emplace(includeFileName);
}

void CPlusPlusDatabase::addMacro(string const& macroName)
{
    m_isModified = true;
    m_macros.emplace(macroName, CPlusPlusMacro());
}

void CPlusPlusDatabase::addNamespace(string const& namespaceName)
{
    m_isModified = true;
    m_namespaces.emplace(getAliasWithCurrentScope(namespaceName), CPlusPlusNamespace());
    addNamespaceToScope(namespaceName);
}

void CPlusPlusDatabase::addTemplateClass(string const& templateClassName, CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature)
{
    m_isModified = true;
    m_templateClasses.emplace(getAliasWithCurrentScope(templateClassName), CPlusPlusTemplateClass(templateClassName, cPlusPlusClassTemplateSignature));
}

void CPlusPlusDatabase::addType(string const& typeDefName, CPlusPlusType const& type)
{
    m_isModified = true;
    m_types.emplace(getAliasWithCurrentScope(typeDefName), type);
    addTypeToScope(typeDefName);
}

void CPlusPlusDatabase::addUsingNamespace(string const& usingNamespace)
{
    m_isModified = true;
    m_usingNamespaces.push_back(usingNamespace);
}

void CPlusPlusDatabase::addVariable(string const& variableName, CPlusPlusType const& cPlusPlusType)
{
    m_isModified = true;
    m_variables.emplace(getAliasWithCurrentScope(variableName), CPlusPlusVariable(cPlusPlusType));
    addVariableToScope(variableName);
}

void CPlusPlusDatabase::removeMacro(string const& macroName)
{
    m_macros.erase(macroName);
}

void CPlusPlusDatabase::copyContentsOf(CPlusPlusDatabase const& cPlusPlusDatabase)
{
    m_isModified = true;
    copy(cPlusPlusDatabase.m_classes.begin(), cPlusPlusDatabase.m_classes.end(), inserter(m_classes, m_classes.begin()));
    copy(cPlusPlusDatabase.m_functions.begin(), cPlusPlusDatabase.m_functions.end(), inserter(m_functions, m_functions.begin()));
    //copy(cPlusPlusDatabase.m_includedFiles.begin(), cPlusPlusDatabase.m_includedFiles.end(), inserter(m_includedFiles, m_includedFiles.begin()));
    copy(cPlusPlusDatabase.m_macros.begin(), cPlusPlusDatabase.m_macros.end(), inserter(m_macros, m_macros.begin()));
    copy(cPlusPlusDatabase.m_namespaces.begin(), cPlusPlusDatabase.m_namespaces.end(), inserter(m_namespaces, m_namespaces.begin()));
    copy(cPlusPlusDatabase.m_templateClasses.begin(), cPlusPlusDatabase.m_templateClasses.end(), inserter(m_templateClasses, m_templateClasses.begin()));
    copy(cPlusPlusDatabase.m_types.begin(), cPlusPlusDatabase.m_types.end(), inserter(m_types, m_types.begin()));
    copy(cPlusPlusDatabase.m_variables.begin(), cPlusPlusDatabase.m_variables.end(), inserter(m_variables, m_variables.begin()));
}

void CPlusPlusDatabase::performInNewScope(function<void(void)> perform)
{
    enterScope(CPlusPlusScopeType::Normal, getCurrentScope().getName());
    perform();
    exitScope();
}

void CPlusPlusDatabase::performInClass(string const& className, function<void(void)> perform)
{
    string correctName(getAliasWithCurrentScope(className));
    addClass(correctName);
    enterScope(CPlusPlusScopeType::Class, correctName);
    perform();
    exitScope();
}

void CPlusPlusDatabase::performInNamespace(string const& namespaceName, function<void(void)> perform)
{
    string correctName(getAliasWithCurrentScope(namespaceName));
    addNamespace(correctName);
    enterScope(CPlusPlusScopeType::Namespace, correctName);
    perform();
    exitScope();
}

void CPlusPlusDatabase::performInTemplateClass(string const& templateClassName, function<void(void)> perform)
{
    string correctName(getAliasWithCurrentScope(templateClassName));
    enterScope(CPlusPlusScopeType::TemplateClass, correctName);
    perform();
    exitScope();
}

void CPlusPlusDatabase::addClassToScope(string const& className)
{
    CPlusPlusScope& cPlusPlusScope = getCurrentScope();
    cPlusPlusScope.addClass(className);
    if(getCurrentScope().isSpecializedScope())
    {
        if(cPlusPlusScope.isClass())
        {
            m_classes[cPlusPlusScope.getName()].addClass(className);
        }
        else if(cPlusPlusScope.isNamespace())
        {
            m_namespaces[cPlusPlusScope.getName()].addClass(className);
        }
        else if(cPlusPlusScope.isTemplateClass())
        {
            m_templateClasses[cPlusPlusScope.getName()].addClass(className);
        }
    }
}

void CPlusPlusDatabase::addFunctionToScope(string const& functionName)
{
    CPlusPlusScope& cPlusPlusScope = getCurrentScope();
    cPlusPlusScope.addFunction(functionName);
    if(getCurrentScope().isSpecializedScope())
    {
        if(cPlusPlusScope.isClass())
        {
            m_classes[cPlusPlusScope.getName()].addFunction(functionName);
        }
        else if(cPlusPlusScope.isNamespace())
        {
            m_namespaces[cPlusPlusScope.getName()].addFunction(functionName);
        }
        else if(cPlusPlusScope.isTemplateClass())
        {
            m_templateClasses[cPlusPlusScope.getName()].addFunction(functionName);
        }
    }
}

void CPlusPlusDatabase::addNamespaceToScope(string const& namespaceName)
{
    CPlusPlusScope& cPlusPlusScope = getCurrentScope();
    cPlusPlusScope.addNamespace(namespaceName);
    if(getCurrentScope().isSpecializedScope())
    {
        if(cPlusPlusScope.isClass())
        {
            m_classes[cPlusPlusScope.getName()].addNamespace(namespaceName);
        }
        else if(cPlusPlusScope.isNamespace())
        {
            m_namespaces[cPlusPlusScope.getName()].addNamespace(namespaceName);
        }
        else if(cPlusPlusScope.isTemplateClass())
        {
            m_templateClasses[cPlusPlusScope.getName()].addNamespace(namespaceName);
        }
    }
}

void CPlusPlusDatabase::addTypeToScope(string const& namespaceName)
{
    CPlusPlusScope& cPlusPlusScope = getCurrentScope();
    cPlusPlusScope.addType(namespaceName);
}

void CPlusPlusDatabase::addVariableToScope(string const& variableName)
{
    CPlusPlusScope& cPlusPlusScope = getCurrentScope();
    cPlusPlusScope.addVariable(variableName);
    if(getCurrentScope().isSpecializedScope())
    {
        if(cPlusPlusScope.isClass())
        {
            m_classes[cPlusPlusScope.getName()].addVariable(variableName);
        }
        else if(cPlusPlusScope.isNamespace())
        {
            m_namespaces[cPlusPlusScope.getName()].addVariable(variableName);
        }
        else if(cPlusPlusScope.isTemplateClass())
        {
            m_templateClasses[cPlusPlusScope.getName()].addVariable(variableName);
        }
    }
}

string CPlusPlusDatabase::getAliasWithCurrentScope(string const& name)
{
    return getCurrentScope().getAliasForThisScope(name);
}

void CPlusPlusDatabase::enterScope(CPlusPlusScopeType const scopeType, string const& name)
{
    m_scopes.emplace_back(scopeType, name);
}

void CPlusPlusDatabase::exitScope()
{
    if(!m_scopes.empty())
    {
        CPlusPlusScope& cPlusPlusScope = getCurrentScope();
        if(!cPlusPlusScope.isSpecializedScope())
        {
            for(auto const& functionName : cPlusPlusScope.getFunctionNamesReference())
            {
                m_functions.erase(functionName);
            }
            for(auto const& variableName : cPlusPlusScope.getVariableNamesReference())
            {
                m_variables.erase(variableName);
            }
        }
        m_scopes.pop_back();
    }
}

}// namespace codeReview
