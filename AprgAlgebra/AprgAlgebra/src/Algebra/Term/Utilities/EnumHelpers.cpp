#include "EnumHelpers.hpp"

#include <Common/Macros/AlbaMacros.hpp>

using namespace std;
namespace alba
{
namespace algebra
{

unsigned int getAssociationPriority(TermAssociationType const association)
{
    unsigned int result(0);
    switch(association)
    {
    case TermAssociationType::Positive:
        result=1;
        break;
    case TermAssociationType::Negative:
        result=2;
        break;
    }
    return result;
}

unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel)
{
    unsigned int result(0);
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
        result=0;
        break;
    case OperatorLevel::AdditionAndSubtraction:
        result=3;
        break;
    case OperatorLevel::MultiplicationAndDivision:
        result=2;
        break;
    case OperatorLevel::RaiseToPower:
        result=1;
        break;
    }
    return result;
}

unsigned int getTermTypePriorityValue(TermType const termType)
{
    unsigned int result(0);
    switch(termType)
    {
    case TermType::Empty:
        result=0;
        break;
    case TermType::Operator:
        result=1;
        break;
    case TermType::Constant:
        result=2;
        break;
    case TermType::Variable:
        result=3;
        break;
    case TermType::Monomial:
        result=4;
        break;
    case TermType::Polynomial:
        result=5;
        break;
    case TermType::Expression:
        result=6;
        break;
    case TermType::Function:
        result=7;
        break;
    }
    return result;
}

TermAssociationType getReversedAssociationType(TermAssociationType const associationType)
{
    TermAssociationType reversedAssociationType;
    if(TermAssociationType::Positive == associationType)
    {
        reversedAssociationType = TermAssociationType::Negative;
    }
    else if(TermAssociationType::Negative == associationType)
    {
        reversedAssociationType = TermAssociationType::Positive;
    }
    return reversedAssociationType;
}

string getEnumShortString(TermType const termType)
{
    switch(termType)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Empty, "Empty")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Constant, "Constant")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Variable, "Variable")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Operator, "Operator")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Monomial, "Monomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Polynomial, "Polynomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Expression, "Expression")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Function, "Function")
            default:
        return "default";
    }
}

string getEnumShortString(TermAssociationType const association)
{
    switch(association)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Positive, "{POS}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Negative, "{NEG}")
            default:
        return "default";
    }
}

string getEnumShortString(OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::Unknown, "{?}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::AdditionAndSubtraction, "{+-}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::MultiplicationAndDivision, "{*/}")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::RaiseToPower, "{^}")
            default:
        return "default";
    }
}

}

}
