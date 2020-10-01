#pragma once

#include <string>
#include "../CPlusPlusType.hpp"

namespace codeReview
{

class CPlusPlusFunctionParameter
{
public:
    explicit CPlusPlusFunctionParameter(CPlusPlusType const& type, string const& name);
    bool operator==(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    bool isEqualBasedFromFunctionCall(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    bool areTheNamesEqual(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    string getName() const;
    CPlusPlusType getType() const;
    void set(CPlusPlusType const& type, string const& name);

private:
    CPlusPlusType m_type;
    string m_name;
};

}
