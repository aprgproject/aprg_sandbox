#pragma once

#include <BaseTermData.hpp>
#include <Math/AlbaNumber.hpp>

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace alba
{

namespace equation
{

class Monomial : public BaseTermData
{
public:
    using VariablesToExponentsMap = std::map<std::string, AlbaNumber>;
    using VariableExponentPair = std::pair<std::string, AlbaNumber>;
    using VariableExponentReferencePair = std::pair<std::string & , AlbaNumber &>;
    using ChangeExponentsForVariableFunction = std::function<void(std::string const&, AlbaNumber&)>;

    Monomial();
    Monomial(AlbaNumber const& constant, std::initializer_list<VariableExponentPair> const& variablesWithExponents);
    Monomial(AlbaNumber const& constant, VariablesToExponentsMap const& variablesWithExponents);

    bool operator==(Monomial const& second) const;

    bool isZero() const;
    bool isConstantOnly() const;
    bool isVariableOnly() const;

    std::string getDisplayableString() const;
    std::string getFirstVariableName() const;
    AlbaNumber const& getConstantConstReference() const;
    VariablesToExponentsMap & getVariablesToExponentsMapReference();
    VariablesToExponentsMap const& getVariablesToExponentsMapConstReference() const;

    void setConstant(AlbaNumber const& constant);
    void setVariableWtihExponent(
            std::string const& variable,
            AlbaNumber const& exponent);
    void setVariablesWithExponents(std::initializer_list<VariableExponentPair> const& variablesWithExponents);

private:
    AlbaNumber m_constant;
    VariablesToExponentsMap m_variablesToExponentsMap;
};

using Monomials=std::vector<Monomial>;

}

}
