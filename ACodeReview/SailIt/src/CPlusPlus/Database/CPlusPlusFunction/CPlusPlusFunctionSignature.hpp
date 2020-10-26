#pragma once

#include "../CPlusPlusType.hpp"
#include "CPlusPlusFunctionParameter.hpp"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace codeReview
{

typedef vector<CPlusPlusFunctionParameter> CPlusPlusFunctionParameters;

class CPlusPlusFunctionSignature
{
public:
    void printSignature() const;
    CPlusPlusType& getReturnTypeReference();
    CPlusPlusType getReturnType() const;
    void setReturnType(CPlusPlusType const& type);
    void addParameter(CPlusPlusType const& type);
    void addParameter(CPlusPlusType const& type, string const& name);
    bool operator==(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    bool isEqualBasedFromFunctionCall(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    bool areTheNamesEqual(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    CPlusPlusFunctionParameters& getFunctionParametersReference();

private:
    CPlusPlusType m_returnType;
    CPlusPlusFunctionParameters m_parameters;
};

}


