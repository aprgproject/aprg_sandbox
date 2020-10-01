#include "CPlusPlusFunction.hpp"

#include "../CPlusPlusClass/CPlusPlusClass.hpp"
#include <iostream>

using namespace std;

namespace codeReview
{

CPlusPlusFunction::CPlusPlusFunction()
{}

void CPlusPlusFunction::printSignatures() const
{
    for(CPlusPlusFunctionSignature const& signature : m_signatures)
    {
        signature.printSignature();
    }
}

bool CPlusPlusFunction::isFunctionSignatureExist(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    //stl algorithm any_of, find_if
    bool isSignatureFound(false);
    for(CPlusPlusFunctionSignature const& signature : m_signatures)
    {
        if(signature==cPlusPlusFunctionSignature)
        {
            isSignatureFound=true;
            break;
        }
    }
    return isSignatureFound;
}

bool CPlusPlusFunction::isFunctionSignatureExistBasedFromFunctionCall(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    //stl algorithm any_of
    bool isSignatureFound(false);
    for(CPlusPlusFunctionSignature const& signature : m_signatures)
    {
        if(signature.isEqualBasedFromFunctionCall(cPlusPlusFunctionSignature))
        {
            isSignatureFound=true;
            break;
        }
    }
    return isSignatureFound;
}

bool CPlusPlusFunction::isFunctionSignatureExistAndNamesDoesNotMatch(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    //stl algorithm any_of
    for(CPlusPlusFunctionSignature const& signature : m_signatures)
    {
        if(signature==cPlusPlusFunctionSignature && !(signature.areTheNamesEqual(cPlusPlusFunctionSignature)))
        {
            return true;
        }
    }
    return false;
}

void CPlusPlusFunction::addFunctionSignature(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature)
{
    if(!isFunctionSignatureExist(cPlusPlusFunctionSignature))
    {
        m_signatures.emplace_back(cPlusPlusFunctionSignature);
    }
}

void CPlusPlusFunction::replaceTemplateParameters(CPlusPlusClassTemplateSignature& templateSignature, CPlusPlusClassTemplateSignature& templateInstantiation)
{
    for(CPlusPlusFunctionSignature& signature : m_signatures)
    {
        for(CPlusPlusFunctionParameter& parameter : signature.getFunctionParametersReference())
        {
            CPlusPlusClassTemplateParameters instantiationParameters = templateInstantiation.getTemplateParametersReference();
            auto it = instantiationParameters.cbegin();
            for(CPlusPlusClassTemplateParameter const& templateParameter : templateSignature.getTemplateParametersReference())
            {
                if(templateParameter.getType() == parameter.getType() && templateParameter.getName() == parameter.getName())
                {
                    parameter.set(it->getType(), it->getName());
                }
                it++;
            }
        }
        CPlusPlusClassTemplateParameters instantiationParameters = templateInstantiation.getTemplateParametersReference();
        auto it = instantiationParameters.begin();
        for(CPlusPlusClassTemplateParameter const& templateParameter : templateSignature.getTemplateParametersReference())
        {
            if(templateParameter.getType() == signature.getReturnType() && templateParameter.getType().isTemplateType())
            {
                signature.setReturnType(it->getType());
            }
            it++;
        }
    }
}

CPlusPlusFunctionSignatures& CPlusPlusFunction::getFunctionSignaturesReference()
{
    return m_signatures;
}

CPlusPlusType CPlusPlusFunction::getReturnTypeWithSignature(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const
{
    for(CPlusPlusFunctionSignature const& signature : m_signatures)
    {
        if(signature.isEqualBasedFromFunctionCall(cPlusPlusFunctionSignature))
        {
            return signature.getReturnType();
        }
    }
    return CPlusPlusType();
}

}
