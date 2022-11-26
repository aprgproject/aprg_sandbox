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

    static VariableTerm createNegatedVariableTerm(std::string const& variableName);

    bool operator==(VariableTerm const& second) const;
    bool operator!=(VariableTerm const& second) const;
    bool operator<(VariableTerm const& second) const;

    VariableTerm operator~() const;

    bool isNegated() const;

    std::string getVariableTermName() const;

    void setVariableTermName(std::string const& variableName);
    void negate();

private:
    void initialize();

    friend std::ostream & operator<<(std::ostream & out, VariableTerm const& variableTerm);

    std::string m_variableName;
    bool m_isNegated;
};

using VariableTerms = std::vector<VariableTerm>;

}

}
