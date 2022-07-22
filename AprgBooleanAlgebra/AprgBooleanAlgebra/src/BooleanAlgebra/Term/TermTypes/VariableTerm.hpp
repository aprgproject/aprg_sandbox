#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>

#include <string>
#include <vector>

namespace alba
{
namespace booleanAlgebra
{
class VariableTerm : public BaseTermData
{
public:
    VariableTerm();
    VariableTerm(std::string const& variableName);
    VariableTerm(std::string const& variableName, bool const isNegated);

    bool operator==(VariableTerm const& second) const;
    bool operator!=(VariableTerm const& second) const;
    bool operator<(VariableTerm const& second) const;

    VariableTerm operator~() const;

    bool isNegated() const;

    std::string getVariableTermName() const;    std::string getDisplayableString() const;

    void setVariableTermName(std::string const& variableName);
    void negate();
private:
    std::string m_variableName;
    bool m_isNegated;
};

using VariableTerms = std::vector<VariableTerm>;

std::ostream & operator<<(std::ostream & out, VariableTerm const& variableTerm);

}
}