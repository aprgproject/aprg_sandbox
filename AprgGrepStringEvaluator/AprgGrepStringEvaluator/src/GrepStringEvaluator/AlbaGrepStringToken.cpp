#include "AlbaGrepStringToken.hpp"

using namespace std;

namespace alba {

AlbaGrepStringToken::AlbaGrepStringToken()
    : m_type(TokenType::Dummy), m_operatorType(AlbaGrepStringOperatorType::Unknown), m_string() {}

AlbaGrepStringToken::AlbaGrepStringToken(string const& stringToFind)
    : m_type(TokenType::StringToFind), m_operatorType(AlbaGrepStringOperatorType::Unknown), m_string(stringToFind) {}

AlbaGrepStringToken::AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType)
    : m_type(TokenType::Operator), m_operatorType(operatorType), m_string() {}

AlbaGrepStringToken::AlbaGrepStringToken(
    AlbaGrepStringOperatorType const operatorType, std::string const& operatorString)
    : m_type(TokenType::Operator), m_operatorType(operatorType), m_string(operatorString) {}

bool AlbaGrepStringToken::isToBeIgnored() const {
    return TokenType::Dummy == m_type || AlbaGrepStringOperatorType::IgnoreOperator == m_operatorType;
}

bool AlbaGrepStringToken::isOperator() const { return TokenType::Operator == m_type; }

bool AlbaGrepStringToken::isClosingParenthesis() const {
    return AlbaGrepStringOperatorType::ClosingParenthesis == m_operatorType;
}

bool AlbaGrepStringToken::isOpeningParenthesis() const {
    return AlbaGrepStringOperatorType::OpeningParenthesis == m_operatorType;
}

bool AlbaGrepStringToken::isString() const { return TokenType::StringToFind == m_type; }

bool AlbaGrepStringToken::isBiDirectionalOperation() const {
    return AlbaGrepStringOperatorType::AndOperator == m_operatorType ||
           AlbaGrepStringOperatorType::OrOperator == m_operatorType ||
           AlbaGrepStringOperatorType::XnorOperator == m_operatorType ||
           AlbaGrepStringOperatorType::XorOperator == m_operatorType;
}

bool AlbaGrepStringToken::isPrefixOperation() const {
    return AlbaGrepStringOperatorType::NotOperator == m_operatorType;
}

AlbaGrepStringToken::TokenType AlbaGrepStringToken::getTokenType() const { return m_type; }

AlbaGrepStringOperatorType AlbaGrepStringToken::getOperatorType() const { return m_operatorType; }

string AlbaGrepStringToken::getTokenTypeString() const {
    string result;
#define GET_ENUM_STRING(en)      \
    case en:                     \
        result += "TokenType:["; \
        result += #en;           \
        result += "]";           \
        break;
    switch (m_type) {
        GET_ENUM_STRING(TokenType::Dummy)
        GET_ENUM_STRING(TokenType::Operator)
        GET_ENUM_STRING(TokenType::StringToFind)
        GET_ENUM_STRING(TokenType::Result)
    }
#undef GET_ENUM_STRING
#define GET_ENUM_STRING(en)         \
    case en:                        \
        result += "OperatorType:["; \
        result += #en;              \
        result += "]";              \
        break;
    switch (m_operatorType) {
        GET_ENUM_STRING(AlbaGrepStringOperatorType::Unknown)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::AndOperator)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::ClosingParenthesis)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::NotOperator)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::IgnoreOperator)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::OpeningParenthesis)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::OrOperator)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::XorOperator)
        GET_ENUM_STRING(AlbaGrepStringOperatorType::XnorOperator)
    }
#undef GET_ENUM_STRING
    if (!m_string.empty()) {
        result += m_string;
    }
    return result;
}

string AlbaGrepStringToken::getStringToFind() const {
    string result;
    if (TokenType::StringToFind == m_type) {
        result = m_string;
    }
    return result;
}

int AlbaGrepStringToken::getOperatorPriority() const {
    int score(0);
    switch (m_operatorType) {
        case AlbaGrepStringOperatorType::NotOperator:
            score = 3;
            break;
        case AlbaGrepStringOperatorType::AndOperator:
        case AlbaGrepStringOperatorType::OrOperator:
        case AlbaGrepStringOperatorType::XnorOperator:
        case AlbaGrepStringOperatorType::XorOperator:
            score = 2;
            break;
        case AlbaGrepStringOperatorType::OpeningParenthesis:
            score = 1;
            break;
        default:
            score = 0;
            break;
    }
    return score;
}

void AlbaGrepStringToken::appendToString(char const character) { m_string += character; }

void AlbaGrepStringToken::setOperatorType(AlbaGrepStringOperatorType const operatorType) {
    m_type = TokenType::Operator;
    m_operatorType = operatorType;
}

}  // namespace alba
