#include "Operator.hpp"

#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

Operator::Operator(string const& operatingString) : m_operatingString(operatingString) {}

bool Operator::operator==(Operator const& second) const { return m_operatingString == second.m_operatingString; }

bool Operator::operator!=(Operator const& second) const { return m_operatingString != second.m_operatingString; }

bool Operator::operator<(Operator const& second) const {
    return getOperatorPriority(m_operatingString) < getOperatorPriority(second.m_operatingString);
}

bool Operator::isNot() const { return "~" == m_operatingString; }

bool Operator::isAnd() const { return "&" == m_operatingString; }

bool Operator::isOr() const { return "|" == m_operatingString; }

bool Operator::isAnOperatorThatCanPerformed() const { return isNot() || isAnd() || isOr(); }

bool Operator::isOpeningGroupOperator() const { return "(" == m_operatingString; }

bool Operator::isClosingGroupOperator() const { return ")" == m_operatingString; }

bool Operator::isUnaryOperator() const { return isNot(); }

bool Operator::isBinaryOperator() const { return isAnd() || isOr(); }

bool Operator::isSameOperatorInputType(OperatorInputType const operatorInputType) const {
    bool result(false);
    if (OperatorInputType::UnaryOperation == operatorInputType) {
        result = isNot();
    } else if (OperatorInputType::BinaryOperation == operatorInputType) {
        result = isAnd() || isOr();
    }
    return result;
}

OperatorType Operator::getOperatorType() const {
    OperatorType result(OperatorType::Unknown);
    if (isNot()) {
        result = OperatorType::Not;
    } else if (isAnd()) {
        result = OperatorType::And;
    } else if (isOr()) {
        result = OperatorType::Or;
    }
    return result;
}

string Operator::getOperatorString() const { return m_operatingString; }

void Operator::setOperatorString(string const& operatingString) { m_operatingString = operatingString; }

ostream& operator<<(ostream& out, Operator const& operatorObject) {
    out << operatorObject.m_operatingString;
    return out;
}

}  // namespace booleanAlgebra

}  // namespace alba
