#include "AlbaGrepStringEvaluatorTerm.hpp"

using namespace std;

namespace alba
{

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm()
    : m_type(AlbaGrepStringEvaluatorTermType::Dummy)
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(
        AlbaGrepStringEvaluatorTermType type)
    : m_type(type)
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(
        AlbaGrepStringEvaluatorTermType type,
        string stringToFind)
    : m_type(type)
    , m_stringToFind(stringToFind)
{}

bool AlbaGrepStringEvaluatorTerm::isToBeIgnored() const
{
    return AlbaGrepStringEvaluatorTermType::Dummy == m_type || AlbaGrepStringEvaluatorTermType::IgnoreOperator == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isOperator() const
{
    return AlbaGrepStringEvaluatorTermType::AndOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::NotOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::OrOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::XnorOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::XorOperator == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isClosingParenthesis() const
{
    return AlbaGrepStringEvaluatorTermType::ClosingParenthesis == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isOpeningParenthesis() const
{
    return AlbaGrepStringEvaluatorTermType::OpeningParenthesis == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isString() const
{
    return AlbaGrepStringEvaluatorTermType::String == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isBiDirectionalOperation() const
{
    return AlbaGrepStringEvaluatorTermType::AndOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::OrOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::XnorOperator == m_type ||
            AlbaGrepStringEvaluatorTermType::XorOperator == m_type;
}

bool AlbaGrepStringEvaluatorTerm::isPrefixOperation() const
{
    return AlbaGrepStringEvaluatorTermType::NotOperator == m_type;
}

AlbaGrepStringEvaluatorTermType AlbaGrepStringEvaluatorTerm::getTermType() const
{
    return m_type;
}

string AlbaGrepStringEvaluatorTerm::getTermTypeString() const
{
#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

    switch(m_type)
    {
    GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::AndOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::ClosingParenthesis)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::Dummy)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::IgnoreOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::NotOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::OpeningParenthesis)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::OrOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::XorOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::XnorOperator)
            GET_ENUM_STRING(AlbaGrepStringEvaluatorTermType::String)
    }
    return string("");
#undef GET_ENUM_STRING
}

string AlbaGrepStringEvaluatorTerm::getString() const
{
    return m_stringToFind;
}

int AlbaGrepStringEvaluatorTerm::getPriorityScore() const
{
    int score(0);
    switch(m_type)
    {
    case AlbaGrepStringEvaluatorTermType::NotOperator:
        score = 3;
        break;
    case AlbaGrepStringEvaluatorTermType::AndOperator:
    case AlbaGrepStringEvaluatorTermType::OrOperator:
    case AlbaGrepStringEvaluatorTermType::XnorOperator:
    case AlbaGrepStringEvaluatorTermType::XorOperator:
        score = 2;
        break;
    case AlbaGrepStringEvaluatorTermType::OpeningParenthesis:
        score = 1;
        break;
    default:
        score = 0;
        break;
    }
    return score;
}

void AlbaGrepStringEvaluatorTerm::appendToString(char const character)
{
    m_stringToFind += character;
}

void AlbaGrepStringEvaluatorTerm::setType(AlbaGrepStringEvaluatorTermType const type)
{
    m_type = type;
}

}



