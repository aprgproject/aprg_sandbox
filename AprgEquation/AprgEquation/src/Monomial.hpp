#pragma once

#include <BaseTerm.hpp>
#include <Math/AlbaNumber.hpp>

#include <map>
#include <string>
#include <vector>

namespace alba
{

namespace equation
{

class Monomial : public BaseTerm
{
public:
    using VariablesToExponentsMap = std::map<std::string, AlbaNumber>;
    using VariableWithExponents = std::pair<std::string, AlbaNumber>;

    Monomial();
    Monomial(AlbaNumber const& constant, std::initializer_list<VariableWithExponents> const& variablesWithExponents);

    AlbaNumber const& getConstantConstReference() const;
    VariablesToExponentsMap const& getVariablesToExponentsMapConstReference() const;

    void setConstant(AlbaNumber const& constant);
    void setVariableWtihExponent(
            std::string const& variable,
            AlbaNumber const& exponent);
    void setVariablesWithExponents(std::initializer_list<VariableWithExponents> const& variablesWithExponents);

private:
    AlbaNumber m_constant;
    VariablesToExponentsMap m_variablesToExponentsMap;
};

using Monomials=std::vector<Monomial>;

}

}
