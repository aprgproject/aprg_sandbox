#include "EnumHelpers.hpp"

#include <Common/Macros/AlbaMacros.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

int getOperatorTypeInversePriority(OperatorType const operatorType) {
    int result(0);
    switch (operatorType) {
        case OperatorType::Unknown:
            result = 0;
            break;
        case OperatorType::Not:
            result = 1;
            break;
        case OperatorType::And:
            result = 2;
            break;
        case OperatorType::Or:
            result = 3;
            break;
    }
    return result;
}

int getOperatorLevelInversePriority(OperatorLevel const operatorLevel) {
    int result(0);
    switch (operatorLevel) {
        case OperatorLevel::Unknown:
            result = 0;
            break;
        case OperatorLevel::And:
            result = 1;
            break;
        case OperatorLevel::Or:
            result = 2;
            break;
    }
    return result;
}

int getTermTypePriorityValue(TermType const termType) {
    int result(0);
    switch (termType) {
        case TermType::Empty:
            result = 0;
            break;
        case TermType::Operator:
            result = 1;
            break;
        case TermType::Constant:
            result = 2;
            break;
        case TermType::VariableTerm:
            result = 3;
            break;
        case TermType::Expression:
            result = 4;
            break;
    }
    return result;
}

OperatorLevel getDualOperatorLevel(OperatorLevel const operatorLevel) {
    OperatorLevel result(OperatorLevel::Unknown);
    switch (operatorLevel) {
        case OperatorLevel::And:
            result = OperatorLevel::Or;
            break;
        case OperatorLevel::Or:
            result = OperatorLevel::And;
            break;
        default:
            break;
    }
    return result;
}

string getEnumShortString(TermType const termType) {
    switch (termType) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Empty, "Empty")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Constant, "Constant")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::VariableTerm, "VariableTerm")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Operator, "Operator")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Expression, "Expression")
        default:
            return "default";
    }
}

string getEnumShortString(OperatorType const operatorType) {
    switch (operatorType) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorType::Unknown, "{?}")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorType::Not, "{~}")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorType::And, "{&}")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorType::Or, "{|}")
        default:
            return "default";
    }
}

string getEnumShortString(OperatorLevel const operatorLevel) {
    switch (operatorLevel) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::Unknown, "{?}")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::And, "{&}")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::Or, "{|}")
        default:
            return "default";
    }
}

}  // namespace booleanAlgebra

}  // namespace alba
