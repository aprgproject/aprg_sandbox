#include "TermChecker.hpp"

#include "CheckerHelpers.hpp"
#include "Term.hpp"

#include <string>

using namespace std;

namespace codeReview {

TermChecker::TermChecker(TermCheckerType const termCheckerType)
    : m_termCheckerType(termCheckerType), m_term(TermType::Empty) {}

TermChecker::TermChecker(Term const& term) : m_termCheckerType(TermCheckerType::ConcreteTerm), m_term(term) {}

TermChecker::TermChecker(std::initializer_list<Term> const& initializerList)
    : m_termCheckerType(TermCheckerType::MultipleTerms),
      m_term(TermType::Empty),
      m_multipleTermsOptional(MultipleTerms(initializerList)) {}

TermChecker::operator Term() const { return m_term; }

ostream& operator<<(ostream& out, TermChecker const& termChecker) {
    return (out << termChecker.getTermCheckerTypeString() << " Term:[" << termChecker.getTerm() << "]");
}

bool TermChecker::operator==(Term const& term) const {
    if (TermCheckerType::MultipleTerms == m_termCheckerType) {
        return m_multipleTermsOptional.getReference().isEqualToAnyOfTheTerms(term);
    } else if (TermCheckerType::ConcreteTerm == m_termCheckerType) {
        return m_term == term;
    } else {
        return isCorrect(term);
    }
    return false;
}

bool operator==(Term const& term, TermChecker const& termChecker) { return termChecker.operator==(term); }

bool TermChecker::operator!=(Term const& term) const { return !(*this == term); }

bool operator!=(Term const& term, TermChecker const& termChecker) { return termChecker != term; }

bool TermChecker::isCorrect(Term const& termToCheck) const {
    switch (m_termCheckerType) {
        case TermCheckerType::isAssignmentOperator:
            return CheckerHelpers::isAssignmentOperator(termToCheck);
        case TermCheckerType::isBiDirectionalOperator:
            return CheckerHelpers::isBiDirectionalOperator(termToCheck);
        case TermCheckerType::isConstant:
            return CheckerHelpers::isConstant(termToCheck.getTermType());
        case TermCheckerType::isIncrementDecrementOperator:
            return CheckerHelpers::isIncrementDecrementOperator(termToCheck);
        case TermCheckerType::isLValue:
            return CheckerHelpers::isLValue(termToCheck.getTermType());
        case TermCheckerType::isOtherMacro:
            return CheckerHelpers::isOtherMacro(termToCheck);
        case TermCheckerType::isProcessed:
            return CheckerHelpers::isProcessed(termToCheck.getTermType());
        case TermCheckerType::isPrefixOperator:
            return CheckerHelpers::isPrefixOperator(termToCheck);
        case TermCheckerType::isRelationalBiDirectionalOperator:
            return CheckerHelpers::isRelationalBiDirectionalOperator(termToCheck);
        case TermCheckerType::isRelationalPrefixOperator:
            return CheckerHelpers::isRelationalPrefixOperator(termToCheck);
        case TermCheckerType::isRValue:
            return CheckerHelpers::isRValue(termToCheck.getTermType());
        case TermCheckerType::isStopForTermSimplification:
            return CheckerHelpers::isStopForTermSimplification(termToCheck);
        case TermCheckerType::isCPlusPlusType:
            return CheckerHelpers::isCPlusPlusType(termToCheck.getTermType());
        case TermCheckerType::isValue:
            return CheckerHelpers::isValue(termToCheck);
        default:
            break;
    }
    return false;
}

TermCheckerType TermChecker::getTermCheckerType() const { return m_termCheckerType; }

Term TermChecker::getTerm() const { return m_term; }

string TermChecker::getTermCheckerTypeString() const {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;
    switch (m_termCheckerType) {
        GET_ENUM_STRING(TermCheckerType::ConcreteTerm)
        GET_ENUM_STRING(TermCheckerType::isAssignmentOperator)
        GET_ENUM_STRING(TermCheckerType::isBiDirectionalOperator)
        GET_ENUM_STRING(TermCheckerType::isConstant)
        GET_ENUM_STRING(TermCheckerType::isIncrementDecrementOperator)
        GET_ENUM_STRING(TermCheckerType::isLValue)
        GET_ENUM_STRING(TermCheckerType::isOtherMacro)
        GET_ENUM_STRING(TermCheckerType::isProcessed)
        GET_ENUM_STRING(TermCheckerType::isPrefixOperator)
        GET_ENUM_STRING(TermCheckerType::isRelationalBiDirectionalOperator)
        GET_ENUM_STRING(TermCheckerType::isRelationalPrefixOperator)
        GET_ENUM_STRING(TermCheckerType::isRValue)
        GET_ENUM_STRING(TermCheckerType::isStopForTermSimplification)
        GET_ENUM_STRING(TermCheckerType::isCPlusPlusType)
        GET_ENUM_STRING(TermCheckerType::isValue)
        GET_ENUM_STRING(TermCheckerType::MultipleTerms)
    }
    return string("");
}

}  // namespace codeReview
