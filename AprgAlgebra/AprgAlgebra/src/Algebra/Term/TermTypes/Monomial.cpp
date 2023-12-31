#include "Monomial.hpp"

#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <set>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

Monomial::Monomial() : m_constant(), m_variablesToExponentsMap(), m_isSimplified(false) {}

Monomial::Monomial(AlbaNumber const& constant, initializer_list<VariableExponentPair> const& variablesWithExponents)
    : m_constant(constant), m_variablesToExponentsMap(), m_isSimplified(false) {
    putVariablesWithExponents(variablesWithExponents);
}

Monomial::Monomial(AlbaNumber const& constant, VariablesToExponentsMap const& variablesWithExponents)
    : m_constant(constant), m_variablesToExponentsMap(variablesWithExponents), m_isSimplified(false) {}

Monomial::VariablesToExponentsMap Monomial::combineVariableExponentMapByMultiplication(
    VariablesToExponentsMap const& variablesMap1, VariablesToExponentsMap const& variablesMap2) {
    VariablesToExponentsMap newVariableMap;
    for (auto const& [variableName, exponent] : variablesMap1) {
        newVariableMap[variableName] += exponent;
    }
    for (auto const& [variableName, exponent] : variablesMap2) {
        newVariableMap[variableName] += exponent;
    }
    return newVariableMap;
}

Monomial::VariablesToExponentsMap Monomial::combineVariableExponentMapByDivision(
    VariablesToExponentsMap const& variablesMap1, VariablesToExponentsMap const& variablesMap2) {
    VariablesToExponentsMap newVariableMap;
    for (auto const& [variableName, exponent] : variablesMap1) {
        newVariableMap[variableName] += exponent;
    }
    for (auto const& [variableName, exponent] : variablesMap2) {
        newVariableMap[variableName] -= exponent;
    }
    return newVariableMap;
}

bool Monomial::operator==(Monomial const& second) const {
    return m_constant == second.m_constant && m_variablesToExponentsMap == second.m_variablesToExponentsMap;
}

bool Monomial::operator!=(Monomial const& second) const { return !(operator==(second)); }

bool Monomial::operator<(Monomial const& second) const {
    bool result(false);
    if (m_variablesToExponentsMap == second.m_variablesToExponentsMap) {
        result = m_constant < second.m_constant;
    } else {
        // highest degree is the lower priority for sorting
        AlbaNumber degree1(getDegree(*this));
        AlbaNumber degree2(getDegree(second));
        if (degree1 == degree2) {
            result = isLessThanByComparingVariableNameMaps(*this, second);
        } else {
            result = degree1 < degree2;
        }
    }
    return result;
}

bool Monomial::isSimplified() const { return m_isSimplified; }

AlbaNumber const& Monomial::getCoefficient() const { return m_constant; }

Monomial::VariablesToExponentsMap const& Monomial::getVariablesToExponentsMap() const {
    return m_variablesToExponentsMap;
}

AlbaNumber Monomial::getExponentForVariable(string const& variableName) const {
    AlbaNumber exponent(0);
    if (m_variablesToExponentsMap.find(variableName) != m_variablesToExponentsMap.cend()) {
        exponent = m_variablesToExponentsMap.at(variableName);
    }
    return exponent;
}

void Monomial::clear() {
    m_constant = AlbaNumber(0);
    m_variablesToExponentsMap.clear();
    clearSimplifiedFlag();
}

void Monomial::simplify() {
    if (!m_isSimplified) {
        setNanIfNeeded();
        removeZeroExponents();
        setAsSimplified();
    }
}

void Monomial::setConstant(AlbaNumber const& constant) {
    m_constant = constant;
    clearSimplifiedFlag();
}

void Monomial::multiplyNumber(AlbaNumber const& number) {
    m_constant = m_constant * number;
    clearSimplifiedFlag();
}

void Monomial::divideNumber(AlbaNumber const& number) {
    m_constant = m_constant / number;
    clearSimplifiedFlag();
}

void Monomial::raiseToPowerNumber(AlbaNumber const& number) {
    m_constant = m_constant ^ number;
    for (auto& [variableName, exponent] : m_variablesToExponentsMap) {
        exponent = exponent * number;
    }
    clearSimplifiedFlag();
}

void Monomial::multiplyMonomial(Monomial const& monomial) {
    VariablesToExponentsMap newVariablesMap(
        combineVariableExponentMapByMultiplication(m_variablesToExponentsMap, monomial.m_variablesToExponentsMap));
    m_constant = m_constant * monomial.m_constant;
    m_variablesToExponentsMap = newVariablesMap;
    clearSimplifiedFlag();
}

void Monomial::divideMonomial(Monomial const& monomial) {
    VariablesToExponentsMap newVariablesMap(
        combineVariableExponentMapByDivision(m_variablesToExponentsMap, monomial.m_variablesToExponentsMap));
    m_constant = m_constant / monomial.m_constant;
    m_variablesToExponentsMap = newVariablesMap;
    clearSimplifiedFlag();
}

void Monomial::putVariablesWithExponents(initializer_list<VariableExponentPair> const& variablesWithExponents) {
    for (auto const& [variableName, exponent] : variablesWithExponents) {
        putVariableWithExponent(variableName, exponent);
    }
    clearSimplifiedFlag();
}

void Monomial::putVariablesWithExponents(VariablesToExponentsMap const& variablesWithExponents) {
    for (auto const& [variableName, exponent] : variablesWithExponents) {
        putVariableWithExponent(variableName, exponent);
    }
    clearSimplifiedFlag();
}

void Monomial::putVariableWithExponent(string const& variable, AlbaNumber const& exponent) {
    m_variablesToExponentsMap[variable] = exponent;
    clearSimplifiedFlag();
}

void Monomial::setAsSimplified() { m_isSimplified = true; }

void Monomial::clearSimplifiedFlag() { m_isSimplified = false; }

bool Monomial::isLessThanByComparingVariableNameMaps(Monomial const& monomial1, Monomial const& monomial2) const {
    set<string> variableNames;
    for (auto const& [variableName, exponent] : monomial1.getVariablesToExponentsMap()) {
        variableNames.emplace(variableName);
    }
    for (auto const& [variableName, exponent] : monomial2.getVariablesToExponentsMap()) {
        variableNames.emplace(variableName);
    }
    bool result(false);
    for (string const& variableName : variableNames) {
        AlbaNumber exponent1(monomial1.getExponentForVariable(variableName));
        AlbaNumber exponent2(monomial2.getExponentForVariable(variableName));
        if (exponent1 != exponent2) {
            result = exponent1 < exponent2;
            break;
        }
    }
    return result;
}

void Monomial::setNanIfNeeded() {
    if (hasNan(*this)) {
        m_variablesToExponentsMap.clear();
        setConstant(ALBA_NUMBER_NOT_A_NUMBER);
    }
}

void Monomial::removeZeroExponents() {
    VariablesToExponentsMap oldVariableMap(m_variablesToExponentsMap);
    m_variablesToExponentsMap.clear();
    for (auto const& [variableName, exponent] : oldVariableMap) {
        if (exponent != 0) {
            m_variablesToExponentsMap.emplace(variableName, exponent);
        }
    }
}

ostream& operator<<(ostream& out, Monomial const& monomial) {
    out << monomial.m_constant;
    for (auto const& [variableName, exponent] : monomial.m_variablesToExponentsMap) {
        out << "[" << variableName;
        if (!(exponent.isIntegerType() && exponent.getInteger() == 1)) {
            out << "^" << exponent;
        }
        out << "]";
    }
    return out;
}

}  // namespace algebra

}  // namespace alba
