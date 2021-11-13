#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

class Monomial : public BaseTermData
{
public:
    using VariablesToExponentsMap = std::map<std::string, AlbaNumber>;
    using VariablesToExponentsMapIterator = VariablesToExponentsMap::iterator;
    using VariablesToExponentsMapConstIterator = VariablesToExponentsMap::const_iterator;
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
    bool operator!=(Monomial const& second) const;
    bool operator<(Monomial const& second) const;

    AlbaNumber const& getConstantConstReference() const;
    VariablesToExponentsMap const& getVariablesToExponentsMapConstReference() const;
    AlbaNumber getExponentForVariable(std::string const& variableName) const;
    std::string getDisplayableString() const;

    void clear();
    void simplify();
    void setConstant(AlbaNumber const& constant);
    void multiplyNumber(AlbaNumber const& number);
    void divideNumber(AlbaNumber const& number);
    void raiseToPowerNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void divideMonomial(Monomial const& monomial);
    void putVariablesWithExponents(std::initializer_list<VariableExponentPair> const& variablesWithExponents);
    void putVariablesWithExponents(VariablesToExponentsMap const& variablesWithExponents);
    void putVariableWithExponent(std::string const& variable, AlbaNumber const& exponent);

    void setAsSimplified();
    void clearInternalFlags();

private:
    bool isLessThanByComparingVariableNameMaps(
            Monomial const& monomial1,
            Monomial const& monomial2) const;
    void setNanIfNeeded();
    void removeZeroExponents();
    AlbaNumber m_constant;
    VariablesToExponentsMap m_variablesToExponentsMap;
    bool m_isSimplified;
};

using Monomials=std::vector<Monomial>;

std::ostream & operator<<(std::ostream & out, Monomial const& monomial);

}

}
