#include "CPlusPlusClass.hpp"

#include <algorithm>

using namespace std;

namespace codeReview
{

CPlusPlusClassTemplateParameter::CPlusPlusClassTemplateParameter(CPlusPlusType type, string name)
    : m_type(type)
    , m_name(name)
{}

string CPlusPlusClassTemplateParameter::getString() const
{
    return m_type.getString()+" "+m_name;
}

string CPlusPlusClassTemplateParameter::getName() const
{
    return m_name;
}

CPlusPlusType CPlusPlusClassTemplateParameter::getType() const
{
    return m_type;
}

bool CPlusPlusClassTemplateParameter::operator==(CPlusPlusClassTemplateParameter const& cPlusPlusClassTemplateParameter) const
{
    return m_type == cPlusPlusClassTemplateParameter.m_type;
}

void CPlusPlusClassTemplateSignature::addParameter(CPlusPlusType type, string name)
{
    m_templateParameters.emplace_back(type, name);
}

string CPlusPlusClassTemplateSignature::getString() const
{
    string signatureString("<");
    for(auto const& templateParameter : m_templateParameters)
    {
        signatureString += templateParameter.getString();
        signatureString += " ";
    }
    signatureString += ">";
    return signatureString;
}

bool CPlusPlusClassTemplateSignature::operator==(CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature) const
{
    if(m_templateParameters.size() != cPlusPlusClassTemplateSignature.m_templateParameters.size())
    {
        return false;
    }
    auto const& templateParameters = cPlusPlusClassTemplateSignature.m_templateParameters;
    auto mismatchPair = std::mismatch (m_templateParameters.cbegin(), m_templateParameters.cend(), templateParameters.cbegin());
    return mismatchPair.first == m_templateParameters.end();
}

CPlusPlusClassTemplateParameters& CPlusPlusClassTemplateSignature::getTemplateParametersReference()
{
    return m_templateParameters;
}

int CPlusPlusClassTemplateSignature::getNumberOfParameters() const
{
    return m_templateParameters.size();
}

CPlusPlusClass::CPlusPlusClass()
{}

CPlusPlusClass::CPlusPlusClass(string const& className)
    : m_type(CPlusPlusType(className, CPlusPlusTypeType::Class))
{}

bool CPlusPlusClass::isVariable(string const& variableName) const
{
    return find(m_variables.begin(), m_variables.end(), variableName)!=m_variables.end();
}

bool CPlusPlusClass::isFunction(string const& functionName) const
{
    return find(m_functions.begin(), m_functions.end(), functionName)!=m_functions.end();
}

bool CPlusPlusClass::isClass(string const& className) const
{
    return find(m_classes.begin(), m_classes.end(), className)!=m_classes.end();
}

bool CPlusPlusClass::isNamespace(string const& namespaceName) const
{
    return find(m_namespaces.begin(), m_namespaces.end(), namespaceName)!=m_namespaces.end();
}

CPlusPlusType& CPlusPlusClass::getTypeReference()
{
    return m_type;
}

VectorOfStrings& CPlusPlusClass::getClassNamesReference()
{
    return m_classes;
}

VectorOfStrings& CPlusPlusClass::getFunctionNamesReference()
{
    return m_functions;
}

VectorOfStrings& CPlusPlusClass::getNamespaceNamesReference()
{
    return m_namespaces;
}

VectorOfStrings& CPlusPlusClass::getVariableNamesReference()
{
    return m_variables;
}

void CPlusPlusClass::addClass(string const& className)
{
    m_classes.push_back(className);
}

void CPlusPlusClass::addFunction(string const& functionName)
{
    m_functions.push_back(functionName);
}

void CPlusPlusClass::addNamespace(string const& namespaceName)
{
    m_namespaces.push_back(namespaceName);
}

void CPlusPlusClass::addVariable(string const& variableName)
{
    m_variables.push_back(variableName);
}

CPlusPlusTemplateClass::CPlusPlusTemplateClass()
{}

CPlusPlusTemplateClass::CPlusPlusTemplateClass(string const& templateClassName, CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature)
    : CPlusPlusClass(templateClassName)
    , m_templateSignature(cPlusPlusClassTemplateSignature)
    , m_type(CPlusPlusType(templateClassName, CPlusPlusTypeType::TemplateClass))
{}

void CPlusPlusTemplateClass::addTemplateInstantiation(CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature)
{
    //check compare wtih signature

    if(cPlusPlusClassTemplateSignature.getNumberOfParameters() == m_templateSignature.getNumberOfParameters())
    {
        auto iterator = find(m_templateInstantiations.begin(), m_templateInstantiations.end(), cPlusPlusClassTemplateSignature);
        if(iterator == m_templateInstantiations.end())
        {
            m_templateInstantiations.emplace_back(cPlusPlusClassTemplateSignature);
        }
    }
    //how about when number of parameters don't match?
}

CPlusPlusType CPlusPlusTemplateClass::getTemplateClassInstantiationType(CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature)
{
    addTemplateInstantiation(cPlusPlusClassTemplateSignature);
    auto iterator = find(m_templateInstantiations.begin(), m_templateInstantiations.end(), cPlusPlusClassTemplateSignature);
    CPlusPlusType type(m_type.getTypeName(), CPlusPlusTypeType::TemplateClassInstantiation);
    type.setTemplateInstantiationIndex(distance(m_templateInstantiations.begin(), iterator));
    return type;
}

CPlusPlusType& CPlusPlusTemplateClass::getTypeReference()
{
    return m_type;
}

CPlusPlusClassTemplateSignature& CPlusPlusTemplateClass::getTemplateSignatureReference()
{
    return m_templateSignature;
}

CPlusPlusClassTemplateSignature& CPlusPlusTemplateClass::getTemplateSignatureInstantiationReference(int instantiationIndex)
{
    return m_templateInstantiations[instantiationIndex];
}

}
