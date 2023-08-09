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
    using VariablesToExponentsMapIterator = VariablesToExponentsMap::iterator;
    using VariableExponentPair = std::pair<std::string, AlbaNumber>;
    using VariableExponentReferencePair = std::pair<std::string & , AlbaNumber &>;
    using ChangeExponentsForVariableFunction = std::function<void(std::string const&, AlbaNumber&)>;

    Monomial();
    Monomial(AlbaNumber const& constant, std::initializer_list<VariableExponentPair> const& variablesWithExponents);
    Monomial(AlbaNumber const& constant, VariablesToExponentsMap const& variablesWithExponents);

    static VariablesToExponentsMap combineVariableExponentMapByMultiplication(
            VariablesToExponentsMap const& variablesMap1,
            VariablesToExponentsMap const& variablesMap2);
    static VariablesToExponentsMap combineVariableExponentMapByDivision(
            VariablesToExponentsMap const& variablesMap1,
            VariablesToExponentsMap const& variablesMap2);

    bool operator==(Monomial const& second) const;

    bool isZero() const;
    bool isConstantOnly() const;
    bool isVariableOnly() const;

    std::string getDisplayableString() const;
    std::string getFirstVariableName() const;
    AlbaNumber const& getConstantConstReference() const;
    VariablesToExponentsMap & getVariablesToExponentsMapReference();
    VariablesToExponentsMap const& getVariablesToExponentsMapConstReference() const;

    void simplify();
    void removeZeroExponents();

    void multiplyByNumber(AlbaNumber const& number);
    void raiseToPowerByNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void divideMonomial(Monomial const& monomial);


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
