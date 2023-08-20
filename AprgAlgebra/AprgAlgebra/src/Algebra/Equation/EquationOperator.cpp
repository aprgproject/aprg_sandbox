#include "EquationOperator.hpp"

#include <ostream>

using namespace std;

namespace alba {

namespace algebra {

EquationOperator::EquationOperator(string const& operatingString) : m_operatingString(operatingString) {}

bool EquationOperator::operator==(EquationOperator const& second) const {
    return m_operatingString == second.m_operatingString;
}

bool EquationOperator::operator!=(EquationOperator const& second) const {
    return m_operatingString != second.m_operatingString;
}

bool EquationOperator::operator<(EquationOperator const& second) const {
    return m_operatingString < second.m_operatingString;
}

bool EquationOperator::isEqual() const { return "==" == m_operatingString || "=" == m_operatingString; }

bool EquationOperator::isNotEqual() const { return "!=" == m_operatingString; }

bool EquationOperator::isLessThan() const { return "<" == m_operatingString; }

bool EquationOperator::isGreaterThan() const { return ">" == m_operatingString; }

bool EquationOperator::isLessThanOrEqual() const { return "<=" == m_operatingString; }

bool EquationOperator::isGreaterThanOrEqual() const { return ">=" == m_operatingString; }

bool EquationOperator::isAnEqualityVariant() const { return isEqual() || isNotEqual(); }

bool EquationOperator::isALessThanVariant() const { return isLessThan() || isLessThanOrEqual(); }

bool EquationOperator::isAGreaterThanVariant() const { return isGreaterThan() || isGreaterThanOrEqual(); }

string EquationOperator::getOperatorString() const { return m_operatingString; }

ostream& operator<<(ostream& out, EquationOperator const& equationOperator) {
    out << equationOperator.m_operatingString;
    return out;
}

}  // namespace algebra

}  // namespace alba
